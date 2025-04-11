<template>
  <div class="borrow-management">
    <!-- 借阅记录列表 -->
    <div v-if="borrowList.length > 0" class="borrow-list">
      <el-card
        v-for="item in borrowList"
        :key="item.bookLoanId"
        class="borrow-item"
        shadow="hover"
        
      >
        <el-descriptions :column="2" :size='large' border>
          <el-descriptions-item label="借阅编号" >
            <el-tag type="primary">{{ item.bookLoanId }}</el-tag>
          </el-descriptions-item>
          <el-descriptions-item label="图书ID" >
            <el-tag type="warning">{{ item.bookId }}</el-tag>
          </el-descriptions-item>
          
          <el-descriptions-item label="书名">{{ item.title }}</el-descriptions-item>
          <el-descriptions-item label="作者">{{ item.author }}</el-descriptions-item>
          
          <el-descriptions-item label="出版社">{{ item.publisher }}</el-descriptions-item>
          <el-descriptions-item label="出版时间">
            <el-tag type="info">
              {{ formatDate(item.publishDate) }}
            </el-tag>
          </el-descriptions-item>
          
          <el-descriptions-item label="借阅时间">
            <el-tag type="success">
              {{ formatDate(item.loanDate) }}
            </el-tag>
          </el-descriptions-item>
          <el-descriptions-item label="预计归还">
            <el-tag :type="isOverdue(item.dueDate) ? 'danger' : 'warning'">
              {{ formatDate(item.dueDate) }}
              <span v-if="isOverdue(item.dueDate)" class="overdue-badge">（已逾期）</span>
            </el-tag>
          </el-descriptions-item>
        </el-descriptions>

        <div class="renew-action">
          <el-button
            type="primary"
            @click="handleRenew(item)"
            :disabled="isOverdue(item.dueDate)"
            plain
          >
            {{ isOverdue(item.dueDate) ? '已逾期' : '续借' }}
          </el-button>
        </div>
      </el-card>
    </div>

    <!-- 无借阅记录提示 -->
    <el-empty
      v-else
      description="暂无借阅记录"
      :image-size="200"
    />

    <!-- 续借对话框 -->
    <el-dialog
      v-model="renewDialogVisible"
      title="图书续借"
      width="500px"
    >
      <div class="renew-content">
        <el-form label-width="120px">
          <el-form-item label="借阅编号:">
            <span class="dialog-value">{{ currentBook?.bookLoanId }}</span>
          </el-form-item>
          <el-form-item label="图书ID:">
            <span class="dialog-value">{{ currentBook?.bookId }}</span>
          </el-form-item>
          <el-form-item label="书名：">
            <span class="dialog-value">{{ currentBook?.title }}</span>
          </el-form-item>
          <el-form-item label="原应归还：">
            <el-tag type="warning">
              {{ formatDate(currentBook?.dueDate) }}
            </el-tag>
          </el-form-item>
          <el-form-item label="新归还时间：" required>
            <el-date-picker
              v-model="newDueDate"
              type="date"
              placeholder="选择新归还日期"
              :disabled-date="disabledDate"
              value-format="YYYY-MM-DDTHH:mm:ss.000Z"
              class="full-width-datepicker"
              :shortcuts="dateShortcuts"
            />
          </el-form-item>
        </el-form>
      </div>
      
      <template #footer>
        <el-button @click="renewDialogVisible = false">取消</el-button>
        <el-button type="primary" @click="confirmRenew">确认续借</el-button>
      </template>
    </el-dialog>
  </div>
</template>

<script setup>
import { onMounted, ref } from 'vue'
import { ElMessage } from 'element-plus'
import { useRouter } from 'vue-router'
import { getBookLoanById, getBookLoanList, updateBookLoan } from '@/api/bookLoan'
import { getBook } from '@/api/book'
import dayjs from 'dayjs'


const router = useRouter()
const borrowList = ref([])
const renewDialogVisible = ref(false)
const currentBook = ref(null)
const newDueDate = ref('')



// 日期快捷选项
const dateShortcuts = [
  {
    text: '延长一周',
    value: () => {
      const date = new Date(newDueDate.value || currentBook.value?.dueDate)
      date.setDate(date.getDate() + 7)
      return date
    },
  },
  {
    text: '延长两周',
    value: () => {
      const date = new Date(newDueDate.value || currentBook.value?.dueDate)
      date.setDate(date.getDate() + 14)
      return date
    },
  },
  {
    text: '延长一个月',
    value: () => {
      const date = new Date(newDueDate.value || currentBook.value?.dueDate)
      date.setMonth(date.getMonth() + 1)
      return date
    },
  },
]

// 日期格式化
const formatDate = (dateStr) => {
  return dayjs(dateStr).format('YYYY-MM-DD')
}

// 判断是否逾期
const isOverdue = (dueDate) => {
  return dayjs(dueDate).isBefore(dayjs(), 'day')
}

// 处理续借操作
const handleRenew = (book) => {
  currentBook.value = book
  newDueDate.value = book.dueDate
  renewDialogVisible.value = true
}

// 禁用今天之前的日期
const disabledDate = (date) => {
  return date < new Date(new Date().setHours(0, 0, 0, 0))
}

// 确认续借
const confirmRenew = async () => {
  if (!newDueDate.value) {
    ElMessage.warning('请选择新的归还日期')
    return
  }

  try {
    const response = await updateBookLoan(currentBook.value.bookLoanId, newDueDate.value)
    if (response.code !== 200) {
      ElMessage.error(response.message || '续借失败，请稍后重试')
      return
    }
    
    const index = borrowList.value.findIndex(b => b.bookId === currentBook.value.bookId)
    if (index > -1) {
      borrowList.value[index].dueDate = newDueDate.value
      ElMessage.success('续借成功')
      renewDialogVisible.value = false
    }
  } catch (error) {
    ElMessage.error('续借失败，请稍后重试')
  }
}

// 初始化加载数据
onMounted(async () => {
  try {
    if(!localStorage.getItem('userId')) {
      ElMessage.error('请登录用户账号查看借阅记录')
      router.push('/')
      return
    }
    const response = await getBookLoanById(localStorage.getItem('userId'))
    if (response.code !== 200) {
      ElMessage.error(response.message || '获取借阅记录失败')
      return
    }

    const loansWithDetails = await Promise.all(
      response.data.map(async loan => {
        try {
          const bookResponse = await getBook(loan.bookId)
          return {
            ...loan,
            ...(bookResponse.code === 200 ? bookResponse.data : {}),
          }
        } catch (error) {
          console.error('获取书籍详情失败:', error)
          return loan
        }
      })
    )

    borrowList.value = loansWithDetails.filter(item => 
      item.bookId && !isOverdue(item.dueDate)
    )
  } catch (error) {
    ElMessage.error('数据加载失败，请稍后重试')
  }
})
</script>

<style scoped>
.borrow-management {
  padding: 20px;
  background: #f5f7fa;
  min-height: calc(100vh - 40px);
}

.borrow-list {
  display: grid;
  gap: 20px;
  grid-template-columns: repeat(auto-fill, minmax(500px, 1fr));
}

.borrow-item {
  margin-bottom: 15px;
  background: white;
  transition: transform 0.2s;
}

.borrow-item:hover {
  transform: translateY(-3px);
}

.renew-action {
  margin-top: 15px;
  display: flex;
  justify-content: flex-end;
}

.overdue-badge {
  color: #fff;
  margin-left: 8px;
  font-size: 0.9em;
}

.dialog-value {
  font-weight: 500;
  color: #606266;
}

.full-width-datepicker {
  width: 100%;
}

:deep(.el-descriptions__body) {
  background-color: #fff;
}

:deep(.el-descriptions__label) {
  font-weight: 500;
  color: #909399;
}

:deep(.el-descriptions__content) {
  color: #606266;
}
</style>