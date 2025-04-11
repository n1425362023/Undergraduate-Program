<template>
  <div class="borrow-management">
    <!-- 搜索区域 -->
    <div class="search-box">
      <el-input
        v-model="searchParams.bookLoanId"
        placeholder="图书借阅ID"
        style="width: 200px"
        clearable
      />
      <el-input
        v-model="searchParams.bookId"
        placeholder="图书ID"
        style="width: 200px;margin-left: 10px"
        clearable
      />
      <el-input
        v-model="searchParams.userId"
        placeholder="读者ID"
        style="width: 200px; margin-left: 10px"
        clearable
      />
      <el-button type="primary" @click="handleSearch" style="margin-left: 10px">
        搜索
      </el-button>
    </div>

    <!-- 操作按钮 -->
    <div v-if="isSearched" class="action-buttons" style="margin: 20px 0">
      <el-button type="danger" @click="handleBatchReturn">批量归还</el-button>
      <el-button @click="handleCancelSelect">取消选择</el-button>
    </div>

    <!-- 数据表格 -->
    <el-table
      v-if="isSearched"
      ref="borrowTableRef"
      :data="pagedData"
      style="width: 100%"
      @selection-change="handleSelectionChange"
      row-key="bookId"
      border
    >
      <el-table-column type="selection" width="55" :reserve-selection="true" />
      <el-table-column prop="bookLoanId" label="借阅编号" width="180" sortable />>
      <el-table-column prop="bookId" label="图书ID" width="120" sortable />
      <el-table-column prop="title" label="书名" width="140" />
      <el-table-column prop="userId" label="读者ID" width="150" sortable/>
      <el-table-column prop="name" label="读者姓名" width="120" />
      <el-table-column prop="loanDate" label="借阅时间" width="180"sortable>
        <template #default="{ row }">
          <el-date-picker
            v-model="row.loanDate"
            type="date"
            value-format="YYYY-MM-DDTHH:mm:ss.000Z"
            placeholder="借阅日期"
            style="width: 100%"
            readonly
            :disabled="true"
          />
        </template>
      </el-table-column>

      <el-table-column prop="dueDate" label="预期归还时间" width="180"sortable>
        <template #default="{ row }">
          <el-date-picker
            v-model="row.dueDate"
            type="date"
            value-format="YYYY-MM-DDTHH:mm:ss.000Z"
            placeholder="归还日期"
            style="width: 100%"
            readonly
            :disabled="true"
          />
        </template>
      </el-table-column>

      <el-table-column label="操作" width="120" fixed="right">
        <template #default="{ row }">
          <el-button type="primary" size="small" @click="handleReturn(row)">
            归还
          </el-button>
        </template>
      </el-table-column>
    </el-table>

    <!-- 分页组件 -->
    <el-pagination
      v-if="isSearched"
      v-model:current-page="currentPage"
      v-model:page-size="pageSize"
      :total="filteredData.length"
      :page-sizes="[5, 10, 20]"
      layout="total, sizes, prev, pager, next, jumper"
      style="margin-top: 20px; justify-content: flex-end"
      background
      @current-change="handlePageChange"
      @size-change="handlePageChange"
    />

    <!-- 空状态提示 -->
    <el-empty
      v-if="isSearched && filteredData.length === 0"
      description="未找到相关借阅记录"
      style="margin-top: 40px"
    />
  </div>
</template>

<script setup>
import { ref, reactive, computed, nextTick, onMounted } from 'vue'
import { ElMessage, ElMessageBox } from 'element-plus'
import { getBookLoanList, deleteBookLoan } from '@/api/bookLoan'
import { getBook, returnBooks } from '@/api/book'
import { getPeople } from '@/api/authentication'
import { createBookLoanRecord } from '@/api/bookLoanRecord'

const borrowTableRef = ref()
const selectedRows = ref([])
const isSearched = ref(false)
const isLoading = ref(false)

// 搜索参数
const searchParams = reactive({
  bookLoanId: '',
  bookId: '',
  userId: ''
})

// 分页参数
const currentPage = ref(1)
const pageSize = ref(10)

// 计算属性
const filteredData = computed(() => {
  if (!isSearched.value) return []
  
  return mockData.value.filter(record => {
    const bookLoanMatch = searchParams.bookLoanId === '' ||
                      String(record.bookLoanId).includes(searchParams.bookLoanId)
    const bookMatch = searchParams.bookId === '' || 
                     String(record.bookId).includes(searchParams.bookId)
    const userMatch = searchParams.userId === '' || 
                     String(record.userId).includes(searchParams.userId)
    return bookLoanMatch && bookMatch && userMatch
  })
})

const pagedData = computed(() => {
  const start = (currentPage.value - 1) * pageSize.value
  return filteredData.value.slice(start, start + pageSize.value)
})


// 搜索处理
const handleSearch = () => {
  isSearched.value = true
  currentPage.value = 1
  selectedRows.value = []
}

// 选择处理
const handleSelectionChange = (selection) => {
  selectedRows.value = selection
}

// 批量归还
const handleBatchReturn = async () => {
  if (selectedRows.value.length === 0) {
    ElMessage.warning('请选择要归还的图书')
    return
  }

  try {
    await ElMessageBox.confirm(
      `确定要归还选中的${selectedRows.value.length}本图书吗？`,
      '操作确认',
      { confirmButtonText: '确认归还', cancelButtonText: '取消', type: 'warning' }
    )
    
    // 准备参数
    const bookIds = selectedRows.value.map(row => row.bookId)
    const userIds = [...new Set(selectedRows.value.map(row => row.userId))] // 去重的用户ID
    
    // 创建借阅记录
    const records = selectedRows.value.map(row => {
      const returnDate = new Date()
      const dueDate = new Date(row.dueDate)
      return {
        bookLoanRecordId: row.bookLoanId,
        userId: row.userId,
        bookId: row.bookId,
        loanDate: row.loanDate,
        dueDate: row.dueDate,
        returnDate: returnDate,
        isOverdue: returnDate >= dueDate
      }
    })

    // 1. 创建借阅历史记录
    const recordResponse = await createBookLoanRecord(records)
    if (recordResponse.code !== 200) {
      throw new Error(recordResponse.message || '创建借阅记录失败')
    }

    // 2. 删除借阅记录
    const loanResponse = await deleteBookLoan(bookIds)
    if (loanResponse.code !== 200) {
      throw new Error(loanResponse.message || '删除借阅记录失败')
    }

    // 3. 更新图书状态
    const bookResponse = await returnBooks(bookIds)
    if (bookResponse.code !== 200) {
      throw new Error(bookResponse.message || '更新图书状态失败')
    }

    // 更新本地数据
    mockData.value = mockData.value.filter(
      record => !bookIds.includes(record.bookId)
    )
    
    ElMessage.success('批量归还成功')
    handleCancelSelect()
  } catch (error) {
    console.error('归还操作失败:', error)
    ElMessage.error(error.message || '归还操作失败')
  }
}

// 单个归还
const handleReturn = async (row) => {
  try {
    await ElMessageBox.confirm(
      `确定要归还图书《${row.title}》吗？`,
      '操作确认',
      { confirmButtonText: '确认归还', cancelButtonText: '取消', type: 'warning' }
    )

    const returnDate = new Date()
    const dueDate = new Date(row.dueDate)
    
    // 1. 创建借阅历史记录
    const recordResponse = await createBookLoanRecord([{
      bookLoanRecordId: row.bookLoanId,
      userId: row.userId,
      bookId: row.bookId,
      loanDate: row.loanDate,
      dueDate: dueDate,
      returnDate: returnDate,
      isOverdue: returnDate >= dueDate
    }])
    
    if (recordResponse.code !== 200) {
      throw new Error(recordResponse.message || '创建借阅记录失败')
    }

    // 2. 删除借阅记录
    const loanResponse = await deleteBookLoan([row.bookId])
    if (loanResponse.code !== 200) {
      throw new Error(loanResponse.message || '删除借阅记录失败')
    }

    // 3. 更新图书状态
    const bookResponse = await returnBooks([row.bookId])
    if (bookResponse.code !== 200) {
      throw new Error(bookResponse.message || '更新图书状态失败')
    }

    // 更新本地数据
    mockData.value = mockData.value.filter(
      record => record.bookId !== row.bookId
    )
    
    ElMessage.success('归还成功')
    handleCancelSelect()
  } catch (error) {
    console.error('归还操作失败:', error)
    if (error !== 'cancel') {
      ElMessage.error(error.message || '归还操作失败')
    }
  }
}

// 取消选择
const handleCancelSelect = () => {
  selectedRows.value = []
  borrowTableRef.value?.clearSelection()
}

// 分页变化处理
const handlePageChange = () => {
  nextTick(() => {
    if (!borrowTableRef.value) return
    borrowTableRef.value.clearSelection()
  })
}

// 初始化数据
const mockData = ref([])
onMounted(async () => {
  try {
    isLoading.value = true
    const loanResponse = await getBookLoanList()
    
    if (loanResponse.code !== 200) {
      throw new Error(loanResponse.message || '获取借阅记录失败')
    }

    const dataWithDetails = await Promise.all(
      loanResponse.data.map(async loan => {
        try {
          const [bookRes, userRes] = await Promise.all([
            getBook(loan.bookId),
            getPeople(loan.userId)
          ])

          return {
            ...loan,
            title: bookRes.code === 200 ? bookRes.data.title : '[书籍信息缺失]',
            name: userRes.code === 200 ? userRes.data.name : '[用户信息缺失]'
          }
        } catch (error) {
          console.error('获取详情失败:', error)
          return {
            ...loan,
            title: '[数据加载失败]',
            name: '[数据加载失败]'
          }
        }
      })
    )

    mockData.value = dataWithDetails.filter(Boolean)
  } catch (error) {
    ElMessage.error(error.message || '初始化数据失败')
  } finally {
    isLoading.value = false
  }
})
</script>

<style scoped>
.borrow-management {
  padding: 20px;
  background-color: #f5f7fa;
  min-height: calc(100vh - 40px);
}

.search-box {
  margin-bottom: 20px;
  display: flex;
  align-items: center;
  background: #ffffff;
  padding: 20px;
  border-radius: 4px;
  box-shadow: 0 2px 12px 0 rgba(0,0,0,.1);
}

.action-buttons {
  background: #ffffff;
  padding: 10px 20px;
  border-radius: 4px;
}

.el-table {
  box-shadow: 0 2px 12px 0 rgba(0,0,0,.1);
  border-radius: 4px;
  overflow: hidden;
}

.el-pagination {
  padding: 16px;
  background: #ffffff;
  border-radius: 4px;
  margin-top: 20px;
}
</style>