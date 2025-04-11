<template>
  <div class="book-management">
    <!-- 搜索区域 -->
    <div class="search-box">
      <el-input v-model="searchParams.bookId" placeholder="图书编号" style="width: 200px" />
      <el-input v-model="searchParams.title" placeholder="图书名称" style="width: 200px; margin-left: 10px" />
      <el-input v-model="searchParams.author" placeholder="作者姓名" style="width: 200px; margin-left: 10px" />
      <el-button type="primary" @click="handleSearch" style="margin-left: 10px">搜索</el-button>
    </div>

    <!-- 操作按钮 -->
    <div class="action-buttons" style="margin: 20px 0">
      <el-button type="primary" @click="handleBatchBorrow">批量借阅</el-button>
      <el-button @click="handleCancelSelect">取消选择</el-button>
    </div>

    <!-- 表格 -->
    <el-table
      ref="bookTableRef"
      :data="pagedData"
      style="width: 100%"
      @selection-change="handleSelectionChange"
      row-key="bookId"
    >
      <el-table-column type="selection" width="55" :reserve-selection="true" />
      <el-table-column prop="bookId" label="图书编号" width="120" />
      <el-table-column prop="title" label="书名" width="180" />
      <el-table-column prop="author" label="作者" width="120" />
      <el-table-column prop="publisher" label="出版社" width="180" />
      <el-table-column prop="publishDate" label="出版时间" width="180">
        <template #default="{ row }">
          <el-date-picker
            v-model="row.publishDate"
            type="date"
            value-format="YYYY-MM-DD"
            placeholder="选择日期"
            style="width: 100%"
            readonly
            :disabled="true"
          />
        </template>
      </el-table-column>
      <el-table-column prop="isBorrowed" label="借阅状态" width="100">
        <template #default="{ row }">
          <el-tag :type="row.isBorrowed ? 'danger' : 'success'">
            {{ row.isBorrowed ? '已借出' : '可借阅' }}
          </el-tag>
        </template>
      </el-table-column>
    </el-table>

    <!-- 分页 -->
    <el-pagination
      v-model:current-page="currentPage"
      v-model:page-size="pageSize"
      :total="filteredData.length"
      :page-sizes="[5, 10, 20]"
      layout="total, sizes, prev, pager, next, jumper"
      style="margin-top: 20px"
      @current-change="handlePageChange"
    />

    <!-- 借阅对话框 -->
    <el-dialog
      v-model="dialogVisible"
      title="借阅信息"
      width="500px"
      @closed="handleDialogClose"
    >
      <el-form
        ref="formRef"
        :model="formData"
        :rules="formRules"
        label-width="100px"
      >
        <el-form-item label="用户ID" prop="userId">
          <el-input v-model="formData.userId" disabled />
        </el-form-item>
        <el-form-item label="借阅时间" prop="loanDate">
          <el-input :value="formData.loanDate" disabled />
        </el-form-item>
        <el-form-item label="归还时间" prop="dueDate">
          <el-date-picker
            v-model="formData.dueDate"
            type="date"
            placeholder="选择归还日期"
            :disabled-date="disabledDueDate"
            value-format="YYYY-MM-DD"
            style="width: 100%"
          />
        </el-form-item>
      </el-form>
      <template #footer>
        <el-button @click="dialogVisible = false">取消</el-button>
        <el-button type="primary" @click="handleConfirmBorrow">确定</el-button>
      </template>
    </el-dialog>
  </div>
</template>

<script setup>
import { ref, reactive, computed, nextTick } from 'vue'
import { ElMessage, ElMessageBox } from 'element-plus'
import dayjs from 'dayjs'
import { borrowBooks, getBookList } from '@/api/book'
import { createBookLoan } from '@/api/bookLoan'
import { onMounted } from 'vue'
import { useRouter } from 'vue-router'

const router = useRouter()
const bookTableRef = ref()
const formRef = ref()
const selectedIds = ref(new Set())
const mockData = ref([])
const dialogVisible = ref(false)

// 表单数据
const formData = reactive({
  userId: localStorage.getItem('userId') || '',
  loanDate: dayjs().format('YYYY-MM-DD'),
  dueDate: ''
})

// 表单验证规则
const formRules = reactive({
  userId: [{ required: true, message: '获取用户ID失败', trigger: 'blur' }],
  dueDate: [{ required: true, message: '请选择归还日期', trigger: 'change' }]
})

// 搜索参数
const searchParams = reactive({
  bookId: '',
  title: '',
  author: ''
})

// 分页参数
const currentPage = ref(1)
const pageSize = ref(10)

// 计算属性
const filteredData = computed(() => {
  return mockData.value.filter(book => {
    return (
      book.bookId.includes(searchParams.bookId) &&
      book.title.toLowerCase().includes(searchParams.title.toLowerCase()) &&
      book.author.toLowerCase().includes(searchParams.author.toLowerCase())
    )
  })
})

const pagedData = computed(() => {
  const start = (currentPage.value - 1) * pageSize.value
  return filteredData.value.slice(start, start + pageSize.value)
})

// 方法
const handleSearch = () => {
  currentPage.value = 1
  selectedIds.value.clear()
}

const handleSelectionChange = (selection) => {
  const currentPageIds = new Set(pagedData.value.map(item => item.bookId))
  const newSelected = new Set(selection.map(item => item.bookId))
  
  currentPageIds.forEach(bookId => {
    newSelected.has(bookId) ? selectedIds.value.add(bookId) : selectedIds.value.delete(bookId)
  })
}

const handleBatchBorrow = () => {
  if (selectedIds.value.size === 0) {
    ElMessage.warning('请选择要借阅的图书')
    return
  }
  dialogVisible.value = true
}

const handleConfirmBorrow = async () => {
  try {
    // 验证表单
    await formRef.value.validate()
    
    // 构造请求参数
    const loans = Array.from(selectedIds.value).map(bookId => ({
      userId: formData.userId,
      bookId: bookId,
      loanDate: formData.loanDate,
      dueDate: formData.dueDate
    }))

    // 调用API
    const bookIds = Array.from(selectedIds.value)
    
    const response = await createBookLoan(loans)
    if(response.code === 200) {
      
      try{
        const response1 = await borrowBooks(bookIds)
      
        if (response1.code === 200) {
          // 更新本地状态
          mockData.value = mockData.value.map(book => {
            if (selectedIds.value.has(book.bookId)) {
              return { ...book, isBorrowed: true }
            }
            return book
          }) 
          ElMessage.success('借阅成功')
          dialogVisible.value = false
          handleCancelSelect()
        } else {
          ElMessage.error(response1.message)
        }
      }catch (error) {
        console.error('借阅失败:', error)
      
      }} else {
        ElMessage.error(response.message)
      }
    } catch (error) {
    console.error('借阅失败:', error)
  }
}

const disabledDueDate = (date) => {
  return dayjs(date).isBefore(dayjs(), 'day')
}

const handleDialogClose = () => {
  formRef.value.resetFields()
  formData.loanDate = dayjs().format('YYYY-MM-DD')
}

const handleCancelSelect = () => {
  selectedIds.value.clear()
  bookTableRef.value?.clearSelection()
}

const handlePageChange = () => {
  nextTick(() => {
    if (!bookTableRef.value) return
      pagedData.value.forEach(row => {
      bookTableRef.value.toggleRowSelection(row, selectedIds.value.has(row.bookId))
    })
  })
}

// 初始化数据
onMounted(async () => {
  try {
    if (!localStorage.getItem('userId')) {
        ElMessage.error('用户ID未找到,请重新登录')
        router.push('/')
        return
      }
    const response = await getBookList()
    if (response.code === 200) {
      mockData.value = response.data
    } else {
      ElMessage.error(response.message)
    }
  } catch (error) {
    ElMessage.error('获取图书列表失败')
  }
})
</script>

<style scoped>
.book-management {
  padding: 20px;
}
.search-box {
  margin-bottom: 20px;
}
</style>