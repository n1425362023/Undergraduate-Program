<template>
  <div class="reader-management">
   
    <div class="search-box">
      <el-input
        v-model="searchParams.userId"
        placeholder="用户ID"
        style="width: 200px"
        clearable
      />
      <el-input
        v-model="searchParams.name"
        placeholder="姓名"
        style="width: 200px; margin-left: 10px"
        clearable
      />
      <el-button
        type="primary"
        style="margin-left: 10px"
        @click="handleSearch"
      >
        搜索
      </el-button>
    </div>

    <div v-if="searchResults.length > 0" class="results-container">
      <div v-for="user in searchResults" :key="user.userId" class="user-card">
        <el-descriptions title="读者信息" :column="2" border>
          <el-descriptions-item :span="2" label="头像" align="center">
            <el-avatar :size="100" :src="'https://cube.elemecdn.com/0/88/03b0d39583f48206768a7534e55bcpng.png'" />
          </el-descriptions-item>
          
          <el-descriptions-item label="姓名">{{ user.name }}</el-descriptions-item>
          <el-descriptions-item label="用户ID">
            <el-tag>{{ user.userId }}</el-tag>
          </el-descriptions-item>
          
          <el-descriptions-item label="性别">
            {{ user.gender === 'MALE' ? '男' : '女' }}
          </el-descriptions-item>
          <el-descriptions-item label="电话">{{ user.phoneNumber }}</el-descriptions-item>
          
          <el-descriptions-item label="状态">
            <el-tag :type="user.isFrozen ? 'danger' : 'success'">
              {{ user.isFrozen ? '已冻结' : '正常' }}
            </el-tag>
          </el-descriptions-item>
          <el-descriptions-item label="身份">
            <el-tag>{{ user.role }}</el-tag>
          </el-descriptions-item>
        </el-descriptions>

        <div class="action-buttons">
          <el-button
            v-if="!user.isFrozen"
            type="warning"
            @click="handleFreeze(user.userId)"
          >
            冻结账户
          </el-button>
          <el-button
            v-else
            type="success"
            @click="handleUnfreeze(user.userId)"
          >
            解冻账户
          </el-button>
          <el-button
            type="danger"
            @click="handleDelete(user.userId)"
          >
            注销账户
          </el-button>
        </div>
      </div>
    </div>

   
    <el-empty
      v-else-if="hasSearched"
      description="未找到匹配的读者"
      style="margin-top: 50px"
    />

  
    <div v-else class="empty-tip">
      <el-icon :size="50" color="#909399"><InfoFilled /></el-icon>
      <p>请输入搜索条件查询读者信息</p>
    </div>
  </div>
</template>

<script setup>
import { ref, reactive, onMounted } from 'vue'
import { ElMessage, ElMessageBox } from 'element-plus'
import { InfoFilled } from '@element-plus/icons-vue'
import { freezePeople, unfreezePeople,getPeopleList ,deletePeople} from '@/api/authentication'


const searchParams = reactive({
  userId: '',
  name: ''
})


const searchResults = ref([])
const hasSearched = ref(false)


const mockUsers = ref([])

onMounted(async () => {
  try {
    const response = await getPeopleList();
    if (response.code === 200) {
      mockUsers.value = response.data;
    } else {
      ElMessage.error(response.message);
    }
  } catch (error) {
    ElMessage.error('获取用户信息失败，请稍后再试。');
    console.error('获取用户信息失败：', error);
  }
});


const handleSearch = () => {
  if (!searchParams.userId && !searchParams.name) {
    ElMessage.warning('请输入用户ID或姓名进行搜索')
    return
  }


  setTimeout(() => {
    searchResults.value = mockUsers.value.filter(user => {
      const idMatch = searchParams.userId 
        ? user.userId.includes(searchParams.userId)
        : true
      const nameMatch = searchParams.name
        ? user.name.includes(searchParams.name)
        : true
      return idMatch && nameMatch
    })
    
    hasSearched.value = true
  }, 500)
}


const handleFreeze = (userId) => {
  ElMessageBox.confirm('确定要冻结该用户账户吗？', '警告', {
    confirmButtonText: '确认',
    cancelButtonText: '取消',
    type: 'warning'
  }).then(() => {
    setTimeout(async() => {

      const user = searchResults.value.find(u => u.userId === userId);
      if (user) {
        const response = await freezePeople(user.userId);
        if (response.code === 200) { 
           user.isFrozen = true
          ElMessage.success('账户已冻结')

        } else {
          ElMessage.error(response.message)
        }
      }
    }, 500)
  }).catch(() => {
    ElMessage.info('已取消操作')
  })
}


const handleUnfreeze = (userId) => {
  ElMessageBox.confirm('确定要解冻该用户账户吗？', '提示', {
    confirmButtonText: '确认',
    cancelButtonText: '取消',
    type: 'info'
  }).then(() => {
    
    setTimeout(async() => {
      const user = searchResults.value.find(u => u.userId === userId)
      if (user) {
        const response = await unfreezePeople(user.userId);
        if (response.code === 200) { 
           user.isFrozen = false
          ElMessage.success('账户已冻结')

        } else {
          ElMessage.error(response.message)
        }
      }
    }, 500)
  }).catch(() => {
    ElMessage.info('已取消操作')
  })
}


const handleDelete = (userId) => {
  ElMessageBox.confirm('确定要永久注销该用户账户吗？此操作不可撤销！', '危险操作', {
    confirmButtonText: '确认注销',
    cancelButtonText: '取消',
    type: 'error',
    confirmButtonClass: 'el-button--danger'
  }).then(() => {
    
    setTimeout(async() => {
      const response = await deletePeople(userId);
      if (response.code === 200) {
        searchResults.value = searchResults.value.filter(u => u.userId !== userId)
        ElMessage.success('账户已注销')
      } else {
        ElMessage.error(response.message)
      }
    }, 500)
  }).catch(() => {
    ElMessage.info('已取消操作')
  })
}
</script>

<style scoped>

.reader-management {
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

.results-container {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(500px, 1fr));
  gap: 20px;
  margin-top: 20px;
}

.user-card {
  background: white;
  padding: 20px;
  border-radius: 4px;
  box-shadow: 0 2px 8px rgba(0,0,0,0.1);
}

.action-buttons {
  display: flex;
  justify-content: flex-end;
  margin-top: 20px;
  gap: 10px;
}

.empty-tip {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: 300px;
  color: #909399;
  font-size: 16px;
}

.empty-tip p {
  margin-top: 20px;
}

:deep(.el-descriptions__title) {
  font-size: 18px;
  font-weight: bold;
}

:deep(.el-descriptions__label) {
  width: 100px;
  font-weight: bold;
}
</style>