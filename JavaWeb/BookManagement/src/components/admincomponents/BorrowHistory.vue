<template>
  <div class="borrow-history">
    <!-- 搜索和过滤区域 -->
    <div class="search-box">
      <el-input
        v-model="searchParams.bookLoanRecordId"
        placeholder="借阅编号"
        style="width: 200px"
        clearable
        @clear="handleSearch"
      />
      <el-input
        v-model="searchParams.userId"
        placeholder="用户ID"
        style="width: 200px; margin-left: 10px"
        clearable
        @clear="handleSearch"
      />
      <el-input
        v-model="searchParams.bookId"
        placeholder="图书ID"
        style="width: 200px; margin-left: 10px"
        clearable
        @clear="handleSearch"
      />
      <el-checkbox
        v-model="searchParams.showOverdueOnly"
        style="margin-left: 20px"
        @change="handleSearch"
      >
        仅显示逾期记录
      </el-checkbox>
      
      <div style="flex-grow: 1"></div>
      
      <el-button
        type="primary"
        style="margin-left: 10px"
        @click="handleSearch"
      >
        搜索
      </el-button>
      <!--
      <el-button
        type="danger"
        style="margin-left: 10px"
        @click="handleDeleteSelected"
        :disabled="selectedBookLoanRecordId.size === 0"
      >
        删除选中记录 ({{ selectedBookLoanRecordId.size }})
      </el-button>
      -->
    </div>

    <!-- 数据表格 -->
    <div
      class="scroll-container"
      v-infinite-scroll="loadMore"
      :infinite-scroll-disabled="loading || noMoreData"
      :infinite-scroll-distance="100"
    >
    <el-table
      :data="displayData"
      style="width: 100%"
      row-key="bookLoanRecordId"
      v-loading="initialLoading"
      border
    >
    
      <el-table-column prop="bookLoanRecordId" label="借阅编号" width="200" sortable />
      <el-table-column prop="bookId" label="图书ID" width="100" sortable />
      <el-table-column prop="title" label="书名" width="160" />
      <el-table-column prop="userId" label="用户ID" width="140" sortable />
      <el-table-column prop="name" label="用户名" width="120" />
      
      <el-table-column label="借阅时间" width="130" sortable>
        <template #default="{ row }">
          <el-tag type="success">
            {{ formatDate(row.loanDate) }}
          </el-tag>
        </template>
      </el-table-column>
      <el-table-column label="预定归还时间" width="130" sortable>
        <template #default="{ row }">
          <el-tag type = "primary">
            {{ formatDate(row.dueDate) }}
          </el-tag>
        </template>
      </el-table-column>
      
      <el-table-column label="实际归还时间" width="130">
        <template #default="{ row }">
          <el-tag type = "warning">
            {{ formatDate(row.returnDate) }}
          </el-tag>
      </template>
    </el-table-column>
      
      <el-table-column label="是否逾期" width="100" sortable :sort-by="row => row.isOverdue ? 1 : 0">
        <template #default="{ row }">
          <el-tag 
            :type="row.isOverdue ? 'danger' : 'success'" 
            size="small"
            effect="dark"
          >
            {{ row.isOverdue ? '已逾期' : '正常' }}
          </el-tag>
        </template>
      </el-table-column>
    </el-table>

      <!-- 加载状态 -->
      <div class="loading-wrapper">
        <el-icon v-if="loading" class="is-loading">
          <Loading />
        </el-icon>
        <span v-if="noMoreData && displayData.length > 0" class="no-more">
          已加载全部数据（共 {{ filteredData.length }} 条）
        </span>
        <el-empty v-if="!initialLoading && displayData.length === 0" description="未找到匹配的记录" />
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, reactive, computed, onMounted } from 'vue'
import { ElMessage, ElMessageBox } from 'element-plus'
import { Loading } from '@element-plus/icons-vue'
import { getBookLoanRecordList ,deleteBookLoanRecordList} from '@/api/bookLoanRecord'
import { getBook } from '@/api/book'
import { getPeople } from '@/api/authentication'
import dayjs from 'dayjs'


const allData = ref([])
const selectedBookLoanRecordId = ref(new Set())
const initialLoading = ref(true)


// 日期格式化
const formatDate = (dateStr) => {
  return dayjs(dateStr).format('YYYY-MM-DD')
}
// 搜索参数
const searchParams = reactive({
  bookLoanRecordId: '',
  userId: '',
  bookId: '',
  showOverdueOnly: false
})

// 分页相关
const pageSize = 20
const currentPage = ref(1)
const loading = ref(false)
const noMoreData = ref(false)

// 计算属性
const filteredData = computed(() => {
  return allData.value.filter(item => {
    const bookLoanRecordIdMatch = searchParams.bookLoanRecordId 
      ? item.bookLoanRecordId.includes(searchParams.bookLoanRecordId)
      : true
    const userIdMatch = searchParams.userId 
      ? item.userId.includes(searchParams.userId)
      : true
    const bookIdMatch = searchParams.bookId
      ? item.bookId.includes(searchParams.bookId)
      : true
    const overdueMatch = searchParams.showOverdueOnly 
      ? item.isOverdue 
      : true
    return bookLoanRecordIdMatch && userIdMatch && bookIdMatch && overdueMatch
  })
})

// 显示数据
const displayData = ref([])


// 搜索处理
const handleSearch = () => {
  currentPage.value = 1
  displayData.value = []
  noMoreData.value = false
  selectedBookLoanRecordId.value.clear()
  loadMore()
}

// 加载更多数据
const loadMore = () => {
  return new Promise((resolve) => {
    if (loading.value || noMoreData.value) {
      resolve()
      return
    }
    
    loading.value = true
    
    setTimeout(() => {
      const start = (currentPage.value - 1) * pageSize
      const end = start + pageSize
      const newData = filteredData.value.slice(start, end)
      
      displayData.value.push(...newData)
      currentPage.value++
      
      // 检查是否还有数据
      noMoreData.value = end >= filteredData.value.length
      loading.value = false
      resolve()
    }, 500)
  })
}
/*c
// 选择处理
const handleSelectionChange = (selection) => {
  selectedBookLoanRecordId.value = new Set(selection.map(item => item.bookLoanRecordId))
}

// 删除选中记录
onst handleDeleteSelected = async () => {
  try {
    await ElMessageBox.confirm(
      `确定要永久删除选中的 ${selectedBookLoanRecordId.value.size} 条记录吗？此操作不可撤销！`,
      '危险操作',
      {
        confirmButtonText: '确认删除',
        cancelButtonText: '取消',
        type: 'error',
        confirmButtonClass: 'el-button--danger',
        distinguishCancelAndClose: true,
        beforeClose: async (action, instance, done) => {
          if (action === 'confirm') {
            instance.confirmButtonLoading = true
            // 模拟删除操作延迟
            const BookLoanRecordListResponse = await deleteBookLoanRecordList(Array.from(selectedBookLoanRecordId.value))
            if( BookLoanRecordListResponse.code === 200) {
              // 更新本地数据
              allData.value = allData.value.filter(
                item => !selectedBookLoanRecordId.value.has(item.bookLoanRecordId)
              )
              selectedBookLoanRecordId.value.clear()
              handleSearch() // 刷新显示
              ElMessage.success('删除成功')
              done()
            }
          } else {
            ElMessage.error('删除失败，请稍后重试')
            done()
          }
        }
      }
    )
    // 执行删除
    allData.value = allData.value.filter(
      item => !selectedBookLoanRecordId.value.has(item.bookLoanRecordId)
    )
    selectedBookLoanRecordId.value.clear()
    handleSearch() // 刷新显示
    
    ElMessage.success({
      message: '删除成功',
      duration: 2000
    })
  } catch (error) {
    ElMessage.info('已取消删除操作')
  }
}*/

// 初始化加载数据
onMounted(async () => {
  initialLoading.value = true
  try {
    // 模拟API请求延迟
    const BookLoanRecordResponse = await getBookLoanRecordList()
    if (BookLoanRecordResponse.code === 200) {
      const dataWithDetails = await Promise.all(
        BookLoanRecordResponse.data.map(async loan => {
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
      allData.value = dataWithDetails.filter(Boolean)
      await loadMore()
    } else {
      ElMessage.error('获取历史信息失败，请稍后再试。');
    }
  } finally {
    initialLoading.value = false
  }
})
</script>

<style scoped>
.borrow-history {
  padding: 20px;
  background: #f5f7fa;
  min-height: calc(100vh - 40px);
}

.search-box {
  display: flex;
  align-items: center;
  padding: 16px;
  background: white;
  border-radius: 4px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.1);
  margin-bottom: 20px;
}

.scroll-container {
  height: calc(100vh - 180px);
  overflow-y: auto;
  background: white;
  padding: 16px;
  border-radius: 4px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.1);
}

.loading-wrapper {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  padding: 20px;
  color: #909399;
}

.el-icon.is-loading {
  font-size: 24px;
  margin-bottom: 8px;
  animation: rotating 2s linear infinite;
}

.no-more {
  font-size: 14px;
  color: #909399;
}

@keyframes rotating {
  from { transform: rotate(0deg); }
  to { transform: rotate(360deg); }
}

.el-table {
  margin-top: 0;
}

.el-table :deep(.el-table__cell) {
  padding: 8px 0;
}

.el-tag {
  font-weight: 500;
}
</style>