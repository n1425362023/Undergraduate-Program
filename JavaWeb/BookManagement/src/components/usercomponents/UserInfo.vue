<template>
    <div class="user-info-container">
      <el-descriptions title="个人信息" :column="3" border>
        <el-descriptions-item
          :rowspan="3"
          :width="140"
          direction="vertical"
          label="Photo"
          label-class-name="user-label"
          class-name="user-content"
          align="center"
        >
          <el-image
            style="width: 100px; height: 100px; border-radius: 50%;"
            src="https://cube.elemecdn.com/0/88/03b0d39583f48206768a7534e55bcpng.png"
          />
        </el-descriptions-item>
  
        <el-descriptions-item label="姓名：">
          <template v-if="editing">
            <el-input v-model="userInfo.name" size="large" />
          </template>
          <template v-else>
            {{ userInfo.name }}
          </template>
        </el-descriptions-item>
  
        <el-descriptions-item label="学工号：">
          <el-tag type = 'info' size="large">{{ userInfo.userId }}</el-tag>
            
          
        </el-descriptions-item>
  
        <el-descriptions-item label="性别：">
      <template v-if="editing">
        <el-radio-group v-model="userInfo.gender" size="large" required>
          <el-radio label="MALE">男</el-radio>
          <el-radio label="FEMALE">女</el-radio>
        </el-radio-group>
      </template>
      <template v-else>
        {{ displayGender }}
      </template>
    </el-descriptions-item>
  
    <el-descriptions-item label="电话：">
          <template v-if="editing">
            <el-form-item prop="telephone">
              <el-input 
                v-model="userInfo.phoneNumber" 
                size="large" 
                :class="{ 'is-error': telephoneError }"
              />
              <div v-if="telephoneError" class="error-message">{{ telephoneError }}</div>
            </el-form-item>
          </template>
          <template v-else>
            {{ userInfo.phoneNumber }}
          </template>
        </el-descriptions-item>
  
        <el-descriptions-item label="身份：">
          <el-tag size="large">{{ userInfo.role }}</el-tag>
        </el-descriptions-item>
        <el-descriptions-item label="状态">
          <el-tag :type="userInfo.isFrozen ? 'danger' : 'success'">
            {{ userInfo.isFrozen ?  "冻结" : "正常"}}
          </el-tag>
        </el-descriptions-item>
      </el-descriptions>
  
      <div class="button-container">
        <el-button v-if="editing" @click="cancelEdit" size="large" class="cancel-button">
          取消
        </el-button>
        <el-button @click="toggleEdit" size="large" class="edit-button">
          {{ editing ? '保存' : '编辑' }}
        </el-button>
      </div>
    </div>
  </template>
  
  <script setup>
  import { ref ,computed, reactive} from 'vue';
  import { ElMessageBox ,ElMessage,ElLoading} from 'element-plus';
  import { getPeopleInfo, updatePeopleInfo} from '@/api/authentication';
  import { onMounted } from 'vue';
  
  const userInfo = ref({});
  const originalUserInfo = reactive({});
  
  onMounted(async () => {
    try {
      if(!localStorage.getItem('token')) {
        ElMessage.error('请先登录！');
        router.push('/');
        return;
      }
      const response = await getPeopleInfo(localStorage.getItem('token'));
      localStorage.setItem('userId', response.data.userId);
      if (response.code === 200) {
        userInfo.value = reactive(response.data);
        // 复制数据到 originalUserInfo
        Object.assign(originalUserInfo, userInfo.value);
         // Copy data to originalUserInfo
      } else {
        ElMessage.error('获取用户信息失败，请稍后再试。');
      }
    } catch (error) {
      ElMessage.error('获取用户信息失败，请稍后再试。');
    }
  });
  
  
  
  const editing = ref(false);
  const displayGender = computed(() => {
    switch (userInfo.value.gender) {
      case 'MALE':
        return '男';
      case 'FEMALE':
        return '女';
    }
  });
  const telephoneError = ref('');
  
  // 电话号码验证函数
  const validateTelephone = () => {
    const phonePattern = /^1[3-9]\d{9}$/;
    if (!phonePattern.test(userInfo.value.phoneNumber)) {
      telephoneError.value = '请输入有效的11位手机号码';
      return false;
    }
    telephoneError.value = '';
    return true;
  };
  
  
  const toggleEdit = () => {
    if (editing.value) {
      ElMessageBox.confirm('您确定要保存更改吗?', 'Confirm', {
        confirmButtonText: '确认',
        cancelButtonText: '取消',
        type: 'warning'
      }).then(() => {
        // 先验证电话号码
        if (!validateTelephone()) {
          ElMessage.error('请修正电话号码格式后再保存！');
          return;
        }
        saveChanges();
        editing.value = false;
      }).catch(() => {
        // User canceled the action
      });
    } else {
      editing.value = true;
    }
  };
  const saveChanges = async () => {
    try {
      // 显示加载状态
      const loadingInstance = ElLoading.service({
        lock: true,
        text: '正在保存...',
        background: 'rgba(0, 0, 0, 0.7)'
      });
  
      // 调用更新接口
      const response = await updatePeopleInfo({
        userId: userInfo.value.userId,
        name: userInfo.value.name,
        gender: userInfo.value.gender,
        phoneNumber: userInfo.value.phoneNumber
  
      });
  
      // 关闭加载状态
      loadingInstance.close();
  
      if (response.code === 200) {
        // 更新本地数据（保持响应性）
        Object.assign(userInfo.value, response.data);
        Object.assign(originalUserInfo, response.data);
        
        ElMessage.success('信息更新成功');
        editing.value = false; // 关闭编辑模式
      } else {
        ElMessage.error(`保存失败：${response.message || '未知错误'}`);
      }
    } catch (error) {
      // 异常处理
      ElMessage.error({
        message: `网络错误：${error.message}`,
        duration: 3000
      });
      console.error('保存请求失败:', error);
    } finally {
      // 确保始终关闭加载状态
      loadingInstance?.close();
    }
  };
  
  const cancelEdit = () => {
    ElMessageBox.confirm('您确定要取消更改吗?', 'Confirm', {
      confirmButtonText: '确认',
      cancelButtonText: '取消',
      type: 'warning'
    }).then(() => {
      // Reset userInfo to original state
      userInfo.value = { ...originalUserInfo };
      editing.value = false; // Cancel editing
    }).catch(() => {
      // User canceled the action
    });
  };
  
  
  
  </script>
  
  <style scoped>
  .user-info-container {
    width: 100%;
    margin: auto;
    padding: 20px;
    border-radius: 8px;
    box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1);
    background-color: #ffffff;
  }
  
  :deep(.user-label) {
    background: var(--el-color-success-light-9) !important;
    font-weight: bold;
    font-size: 18px;
    white-space: nowrap;
    overflow: hidden;
    text-overflow: ellipsis;
    padding: 10px;
  }
  
  :deep(.user-content) {
    background: var(--el-color-danger-light-9);
  }
  
  .el-descriptions-item {
    min-width: 180px;
  }
  
  .button-container {
    display: flex;
    justify-content: flex-end; /* Align buttons to the right */
    margin-top: 20px;
  }
  
  .el-button.edit-button {
    background-color: #409eff;
    border-color: #409eff;
    color: #ffffff;
  }
  
  .el-button.edit-button:hover {
    background-color: #66b1ff;
    border-color: #66b1ff;
  }
  
  .cancel-button {
    margin-right: 10px; /* Space between buttons */
  }
  </style>
  
  