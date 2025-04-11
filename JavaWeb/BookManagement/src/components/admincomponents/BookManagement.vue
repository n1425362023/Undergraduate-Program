<template>
  <div class="book-management">
   
    <div class="search-box">
      <el-input v-model="searchParams.bookId" placeholder="图书编号" style="width: 200px" />
      <el-input v-model="searchParams.title" placeholder="图书名称" style="width: 200px; margin-left: 10px" />
      <el-input v-model="searchParams.author" placeholder="作者姓名" style="width: 200px; margin-left: 10px" />
      <el-button type="primary" @click="handleSearch" style="margin-left: 10px">搜索</el-button>
    </div>


    <div class="action-buttons" style="display: flex; justify-content: space-between; margin: 20px 0">
      <div>
        <el-button type="danger" @click="handleBatchDelete">批量删除</el-button>
        <el-button @click="handleCancelSelect">取消选择</el-button>
      </div>
      <el-button type="primary" @click="handleAddBook">新增图书</el-button>
    </div>

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
      <el-table-column prop="author" label="作者" width="200" />
      <el-table-column prop="publisher" label="出版社" width="200" />
      <el-table-column prop="publishDate" label="出版时间" width="180">
        <template #default="{ row }">
          <el-date-picker
            v-model="row.publishDate"
            type="date"
            value-format="YYYY-MM-DDTHH:mm:ss.000Z"
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
      <el-table-column label="操作" width="120">
        <template #default="{ row }">
          <el-button type="primary" size="small" @click="handleViewDetail(row)">详情</el-button>
        </template>
      </el-table-column>
    </el-table>


    <el-pagination
      v-model:current-page="currentPage"
      v-model:page-size="pageSize"
      :total="filteredData.length"
      :page-sizes="[5, 10, 20]"
      layout="total, sizes, prev, pager, next, jumper"
      style="margin-top: 20px"
      @current-change="handlePageChange"
    />


    <el-dialog
      v-model="dialogVisible"
      :title="`图书详情 - ${formData.title}`"
      width="30%"
      :before-close="handleBeforeClose"
    >
      <el-form :model="formData" label-width="80px">
        <el-form-item label="图书编号">
          <el-input v-model="formData.bookId" disabled />
        </el-form-item>
        <el-form-item label="图书名称">
          <el-input v-model="formData.title" :disabled="!isEditing" />
        </el-form-item>
        <el-form-item label="作者">
          <el-input v-model="formData.author" :disabled="!isEditing" />
        </el-form-item>
        <el-form-item label="出版社">
          <el-input v-model="formData.publisher" :disabled="!isEditing" />
        </el-form-item>
        <el-form-item label="出版时间">
          <el-date-picker
            v-model="formData.publishDate"
            type="date"
            value-format="YYYY-MM-DD"
            placeholder="选择日期"
            style="width: 100%"
            :disabled="!isEditing"
            :disabled-date="disabledDate"
          />
        </el-form-item>
      </el-form>
      <template #footer>
        <span class="dialog-footer">
          <template v-if="!isEditing">
            <el-button type="primary" @click="enterEditMode">编辑</el-button>
          </template>
          <template v-else>
            <el-button @click="handleCancelEdit">取消</el-button>
            <el-button type="primary" @click="handleConfirmSave">保存</el-button>
          </template>
        </span>
      </template>
    </el-dialog>


    <el-dialog
      v-model="addDialogVisible"
      title="新增图书"
      width="30%"
    >
      <el-form :model="newBookForm" label-width="80px" :rules="formRules" ref="newBookFormRef">
        <el-form-item label="图书编号" prop="bookId">
          <el-input v-model="newBookForm.bookId" />
        </el-form-item>
        <el-form-item label="图书名称" prop="title">
          <el-input v-model="newBookForm.title" />
        </el-form-item>
        <el-form-item label="作者" prop="author">
          <el-input v-model="newBookForm.author" />
        </el-form-item>
        <el-form-item label="出版社" prop="publisher">
          <el-input v-model="newBookForm.publisher" />
        </el-form-item>
        <el-form-item label="出版时间" prop="publishDate">
          <el-date-picker
            v-model="newBookForm.publishDate"
            type="date"
            value-format="YYYY-MM-DD"
            placeholder="选择日期"
            style="width: 100%"
            :disabled-date="disabledDate"
          />
        </el-form-item>
      </el-form>
      <template #footer>
        <span class="dialog-footer">
          <el-button @click="addDialogVisible = false">取消</el-button>
          <el-button type="primary" @click="submitNewBook">保存</el-button>
        </span>
      </template>
    </el-dialog>
  </div>
</template>

<script setup>
import { ref, reactive, computed, nextTick, onMounted } from 'vue'
import { ElMessage, ElMessageBox } from 'element-plus'
import { getBookList, addBook, deleteBooks, updateBook } from '../../api/book'

const bookTableRef = ref()
const selectedIds = ref(new Set())
const newBookFormRef = ref()
const mockData = ref([])


const searchParams = reactive({
  bookId: '',
  title: '',
  author: ''
})

const currentPage = ref(1)
const pageSize = ref(10)
const dialogVisible = ref(false)
const isEditing = ref(false)
const tempFormData = ref(null)
const formData = reactive({
  bookId: '',
  title: '',
  author: '',
  publisher: '',
  publishDate: ''
})

const addDialogVisible = ref(false)
const newBookForm = reactive({
  bookId: '',
  title: '',
  author: '',
  publisher: '',
  publishDate: ''
})

const formRules = reactive({
  bookId: [
    { required: true, message: '请输入图书编号', trigger: 'blur' },
    { pattern: /^[A-Z]\d{4}$/, message: '编号格式示例A+4位数字', trigger: 'blur' }
  ],
  title: [
    { required: true, message: '请输入图书名称', trigger: 'blur' },
    { min: 2, max: 50, message: '长度在2到50个字符', trigger: 'blur' }
  ],
  author: [
    { required: true, message: '请输入作者姓名', trigger: 'blur' }
  ],
  publisher: [
    { required: true, message: '请输入出版社', trigger: 'blur' }
  ],
  publishDate: [
    { required: true, message: '请选择出版日期', trigger: 'change' }
  ]
})


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


const disabledDate = (time) => {
  const today = new Date()
  today.setHours(0, 0, 0, 0)
  return time.getTime() > today.getTime()
}


const handleSearch = () => {
  currentPage.value = 1
  selectedIds.value.clear()
}

const handleSelectionChange = (selection) => {
  const currentPageIds = new Set(pagedData.value.map(item => item.bookId))
  const newSelected = new Set(selection.map(item => item.bookId))
  
  currentPageIds.forEach(bookId => {
    if (newSelected.has(bookId)) {
      selectedIds.value.add(bookId)
    } else {
      selectedIds.value.delete(bookId)
    }
  })
}

const handleBatchDelete = () => {
  if (selectedIds.value.size === 0) {
    ElMessage.warning('请选择要删除的图书')
    return
  }

  ElMessageBox.confirm(`确定要删除选中的${selectedIds.value.size}本图书吗？`, '警告', {
    confirmButtonText: '确定',
    cancelButtonText: '取消',
    type: 'warning'
  }).then(async() => {
    const response = await deleteBooks(Array.from(selectedIds.value))
    if(response.code === 200){
      mockData.value = mockData.value.filter(book => !selectedIds.value.has(book.bookId))
      ElMessage.success('删除成功')
      handleCancelSelect()
    }else{
      ElMessage.error(response.message)
    }
  }).catch((error) => {
    console.error('删除失败:', error)
  })
}

const handleCancelSelect = () => {
  selectedIds.value.clear()
  bookTableRef.value?.clearSelection()
}

const handlePageChange = () => {
  nextTick(() => {
    if (!bookTableRef.value) return
    
    pagedData.value.forEach(row => {
      if (selectedIds.value.has(row.bookId)) {
        bookTableRef.value.toggleRowSelection(row, true)
      }
    })
  })
}

const handleViewDetail = (row) => {
  Object.assign(formData, row)
  tempFormData.value = { ...row }
  dialogVisible.value = true
  isEditing.value = false
}

const enterEditMode = () => {
  isEditing.value = true
}

const handleCancelEdit = () => {
  if (hasFormChanged()) {
    ElMessageBox.confirm('当前修改未保存，确定要放弃吗？', '提示', {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'warning'
    }).then(() => {
      resetFormData()
      isEditing.value = false
    }).catch(() => {})
  } else {
    isEditing.value = false
  }
}

const handleConfirmSave = () => {
  ElMessageBox.confirm('确定要保存修改吗？', '提示', {
    confirmButtonText: '确定',
    cancelButtonText: '取消',
    type: 'warning'
  }).then(async () => {
    const index = mockData.value.findIndex(book => book.bookId === formData.bookId)
    if (index !== -1) {
      const response = await updateBook(formData)
      if(response.code === 200){
        mockData.value[index] = { ...formData }
        tempFormData.value = { ...formData }
        isEditing.value = false
        ElMessage.success('修改成功')
      }else{
        ElMessage.error(response.message)
      }
    }
  }).catch((error) => {
    console.error('保存失败:', error)
  })
}

const handleBeforeClose = (done) => {
  if (isEditing.value && hasFormChanged()) {
    ElMessageBox.confirm('当前修改未保存，确定要关闭吗？', '提示', {
      confirmButtonText: '确定',
      cancelButtonText: '取消',
      type: 'warning'
    }).then(() => {
      resetFormData()
      done()
    }).catch(() => {})
  } else {
    done()
  }
}

const handleAddBook = () => {
  Object.assign(newBookForm, {
    bookId: '',
    title: '',
    author: '',
    publisher: '',
    publishDate: ''
  })
  addDialogVisible.value = true
  nextTick(() => {
    if (newBookFormRef.value) {
      newBookFormRef.value.clearValidate()
    }
  })
}

const submitNewBook = () => {
  newBookFormRef.value.validate(async(valid) => {
    if (valid) {
      const response = await addBook(newBookForm);
      if(response.code === 200){
       mockData.value.unshift(response.data)
        ElMessage.success('新增图书成功')
        addDialogVisible.value = false
      }else{
        ElMessage.error(response.message)
      }
    }
  })
}


const hasFormChanged = () => {
  return JSON.stringify(formData) !== JSON.stringify(tempFormData.value)
}

const resetFormData = () => {
  Object.assign(formData, tempFormData.value)
}


onMounted(async () => {
  try {
    const response = await getBookList();
    if (response.code === 200) {
      mockData.value = response.data;
    } else {
      ElMessage.error(response.message);
    }
  } catch (error) {
    ElMessage.error(error);
  }
});
</script>

<style scoped>
.book-management {
  padding: 20px;
}
.search-box {
  margin-bottom: 20px;
}
</style>