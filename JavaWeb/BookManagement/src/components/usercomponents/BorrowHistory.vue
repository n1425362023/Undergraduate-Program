<template>
    <div class="borrow-history">
      <!-- 用户信息展示 -->
      <div class="user-info">
        <span style="margin-left: 20px; color: #409EFF">
          当前用户：{{ currentUserName }}
        </span>
        
        <span style="margin-left: 20px; color: #409EFF">
        学号:   {{ currentUserId }}
        </span>
      </div>
  
      <!-- 搜索和过滤区域 -->
      <div class="search-box">
        <el-input
          v-model="searchParams.bookLoanRecordId"
          placeholder="输入借阅编号搜索"
          style="width: 300px"
          clearable
          @clear="handleSearch"
        />
        <el-input
          v-model="searchParams.title"
          placeholder="输入书名搜索"
          style="width: 300px"
          clearable
          @clear="handleSearch"
        />
        <el-input
          v-model="searchParams.bookId"
          placeholder="输入图书ID搜索"
          style="width: 300px"
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
        <el-button
          type="danger"
          style="margin-left: 10px"
          @click="handleDeleteSelected"
          :disabled="selectedBookLoanRecordId.size === 0"
        >
          删除选中记录 ({{ selectedBookLoanRecordId.size }})
        </el-button>
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
          border
          @selection-change="handleSelectionChange"
          v-loading="initialLoading"
        >
          <el-table-column type="selection" width="55" />
          <el-table-column prop="bookLoanRecordId" label="借阅编号" width="180" sortable />
          <el-table-column prop="bookId" label="图书ID" width="160" sortable />
          <el-table-column prop="title" label="书名" width="200" />
          <el-table-column label="借阅时间" width="130" sortable>
            <template #default="{ row }">
              <el-tag type="success">
                {{ formatDate(row.loanDate) }}
              </el-tag>
            </template>
          </el-table-column>
          <el-table-column label="预定归还时间" width="130" sortable>
            <template #default="{ row }">
              <el-tag type="primary">
                {{ formatDate(row.dueDate) }}
              </el-tag>
            </template>
          </el-table-column>
      
          <el-table-column label="实际归还时间" width="130">
            <template #default="{ row }">
              <el-tag type = warning>
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
          <el-empty v-if="!initialLoading && displayData.length === 0" description="暂无借阅记录" />
        </div>
      </div>
    </div>
  </template>
  
<script setup>
  import { ref, reactive, computed, onMounted } from 'vue'
  import { ElMessage, ElMessageBox } from 'element-plus'
  import { Loading } from '@element-plus/icons-vue'
  import { useRouter } from 'vue-router';
  import { getBook, } from '@/api/book'
  import { getPeopleInfo ,getPeople} from '@/api/authentication'
  import {getBookLoanRecord ,deleteBookLoanRecordList} from '@/api/bookLoanRecord'
  import dayjs from 'dayjs'


  const router = useRouter()
  // 当前用户信息（模拟数据）
  const currentUserId = ref()
  const currentUserName = ref()


  
  // 数据状态
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
    title: '',
    bookId: '',
    showOverdueOnly: false
  })
  
  // 分页相关
  const pageSize = 20
  const currentPage = ref(1)
  const loading = ref(false)
  const noMoreData = ref(false)
  
  // 计算属性（增加当前用户过滤）
  const filteredData = computed(() => {
    return allData.value.filter(item => {
      const isCurrentUser = item.userId === currentUserId.value
      const bookLoanRecordIdMatch = searchParams.bookLoanRecordId 
        ? item.bookLoanRecordId.includes(searchParams.bookLoanRecordId)
        : true
      const titleMatch = searchParams.title 
        ? item.title.includes(searchParams.title)
        : true
      const bookIdMatch = searchParams.bookId
        ? item.bookId.includes(searchParams.bookId)
        : true
      const overdueMatch = searchParams.showOverdueOnly 
        ? item.isOverdue 
        : true
      return isCurrentUser && bookLoanRecordIdMatch && titleMatch && bookIdMatch && overdueMatch
    })
  })
  
  // 显示数据
  const displayData = ref([])
  

  
  // 搜索处理（保持不变）
  const handleSearch = () => {
    currentPage.value = 1
    displayData.value = []
    noMoreData.value = false
    selectedBookLoanRecordId.value.clear()
    loadMore()
  }
  
  // 加载更多数据（保持不变）
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
        
        noMoreData.value = end >= filteredData.value.length
        loading.value = false
        resolve()
      }, 500)
    })
  }
  
  // 选择处理（保持不变）
  const handleSelectionChange = (selection) => {
    selectedBookLoanRecordId.value = new Set(selection.map(item => item.bookLoanRecordId))
  }
  
  // 删除选中记录（保持不变）
  const handleDeleteSelected = async () => {
    try {
      await ElMessageBox.confirm(
        `确定要删除选中的 ${selectedBookLoanRecordId.value.size} 条借阅记录吗？`,
        '删除确认',
        {
          confirmButtonText: '确认删除',
          cancelButtonText: '取消',
          type: 'warning'
        }
      )
      const BookLoanRecordListResponse = await deleteBookLoanRecordList(Array.from(selectedBookLoanRecordId.value))
      if (BookLoanRecordListResponse.code === 200) {
        // 执行删除（确保只删除当前用户的数据）
        allData.value = allData.value.filter(
        item => !selectedBookLoanRecordId.value.has(item.bookLoanRecordId)
        
        )
        selectedBookLoanRecordId.value.clear()
        handleSearch()
        
        ElMessage.success({
          message: '删除成功',
          duration: 2000
        })
      }else{
        ElMessage.error(Response.message)
      }
      
    } catch (error) {
      ElMessage.info('已取消删除操作')
    }
  }
  // 初始化加载数据
onMounted(async () => {
  initialLoading.value = true
  try {
    // 模拟API请求延迟
    if(!localStorage.getItem('token')) {
        ElMessage.error('请先登录！');
        router.push('/');
        return;
      }
    const PeopleResponse = await getPeopleInfo(localStorage.getItem('token'));
    if (PeopleResponse.code === 200) {
      currentUserId.value = PeopleResponse.data.userId
      currentUserName.value = PeopleResponse.data.name
    } else {
      ElMessage.error('获取用户信息失败，请重新登录。');
      router.push('/');
      return;
    }
    const BookLoanRecordResponse = await getBookLoanRecord(PeopleResponse.data.userId)
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
  // 初始化加载数据（修改部分）
  /*onMounted(async () => {
    initialLoading.value = true
    try {
      await new Promise(resolve => setTimeout(resolve, 800))
      // 生成当前用户的借阅数据
      allData.value = generateHistoryData(50)
      // 初始化后直接执行搜索加载数据
      handleSearch()
    } finally {
      initialLoading.value = false
    }
  })*/
</script>
  
  <style scoped>
  .borrow-history {
    padding: 20px;
    background: #f5f7fa;
    min-height: calc(100vh - 40px);
  }
  
  .user-info {
    padding: 16px;
    margin-bottom: 20px;
    background: white;
    border-radius: 4px;
    box-shadow: 0 2px 8px rgba(0,0,0,0.1);
    font-weight: 500;
    color: #606266;
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
    height: calc(100vh - 220px);
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
  </style>