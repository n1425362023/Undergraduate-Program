<template>
  <div class="signin-form">
    <el-form :model="form" label-width="60px">
      <el-form-item label="学工号">
        <el-input v-model="form.userId" placeholder="请输入学工号" clearable class="full-width-input" />
      </el-form-item>
      <el-form-item label="密码">
        <el-input v-model="form.password" type="password" placeholder="请输入密码" clearable show-password class="full-width-input" />
      </el-form-item>
      <el-form-item>
        <div class="password-options">
          <el-checkbox v-model="form.rememberPassword">保存密码</el-checkbox>
          <el-link type="primary" @click="handleForgotPassword">忘记密码</el-link>
        </div>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="onSubmit" class="full-width-button">登录</el-button>
      </el-form-item>
    </el-form>
  </div>
</template>

<script setup lang="ts">
import { reactive, onMounted } from 'vue';
import { ElMessage } from 'element-plus';
import { signin } from '../api/authentication';
import { encrypt } from '../utils/crypto';
import { useRouter } from 'vue-router';

const router = useRouter();

const form = reactive({
  userId: '',
  password: '',
  rememberPassword: false,
});

onMounted(() => {
  const savedUserId = localStorage.getItem('userId');
  const savedPassword = localStorage.getItem('password');
  const rememberPassword = localStorage.getItem('rememberPassword') === 'true';

  if (savedUserId && savedPassword && rememberPassword) {
    form.userId = savedUserId;
    form.password = savedPassword;
    form.rememberPassword = true;
  }
});

const onSubmit = async () => {
  if (!form.userId || !form.password) {
    ElMessage.warning('请输入学工号和密码');
    return;
  }

  try {
    const hashedPassword = encrypt(form.password);
    const response = await signin({
      userId: form.userId,
      passwordHash: hashedPassword,
    });
    
    if (response.code === 200) {
      localStorage.setItem('token', response.data.token);
      localStorage.setItem('role', response.data.role);
      localStorage.setItem('userId', response.data.userId);
      ElMessage.success('登录成功！');
      
      if (form.rememberPassword) {
        localStorage.setItem('userId', form.userId);
        localStorage.setItem('password', form.password);
        localStorage.setItem('rememberPassword', 'true');
      } else {
        
        localStorage.removeItem('rememberPassword');
      }
      
      if (response.data.role === 'ADMIN') {
        router.push('/admin');
      } else if (response.data.role === 'USER') {
        router.push('/user');
      }
      console.log('登录响应:', response);
    } else {
      ElMessage.error(response.message);
    }
  } catch (error) {
    ElMessage.error('登录失败，请检查学工号和密码');
    console.error('登录失败:', error);
  }
};

const handleForgotPassword = () => {
  router.push('/passwordforget');
};
</script>

<style scoped>
.signup-form {
  max-width: 300px; 
  margin: 20px auto; 
  padding: 20px;
  border: 1px solid #ddd;
  border-radius: 8px;
}

.password-options {
  display: flex; 
  justify-content: space-between;
  align-items: center; 
  width: 100%; 
}

.full-width-input,
.full-width-button {
  width: 100%;
  box-sizing: border-box; 
}
</style>
