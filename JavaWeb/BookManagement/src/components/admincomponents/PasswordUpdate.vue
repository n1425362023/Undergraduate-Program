<template>
    <div class="password-update-container">
      <h2>修改密码</h2>
      <el-form :model="form" label-width="100px" style="max-width: 500px">
        <el-form-item label="学工号">
          <el-input v-model="form.userId" disabled />
        </el-form-item>
        <el-form-item label="新密码">
          <el-input v-model="form.newPassword" type="password" show-password />
        </el-form-item>
        <el-form-item label="确认密码">
          <el-input v-model="form.confirmPassword" type="password" show-password />
        </el-form-item>
        <el-form-item>
          <el-button type="primary" @click="submitForm">提交修改</el-button>
        </el-form-item>
      </el-form>
    </div>
</template>
  
<script setup lang="ts">
  import { onMounted, ref } from 'vue'
  import { ElMessage } from 'element-plus'
  import { useRouter } from 'vue-router'
  import { encrypt } from '@/utils/crypto'
  import { resetPassword } from '@/api/authentication'
  const form = ref({
    userId: localStorage.getItem('userId') || '', 
    newPassword: '',
    confirmPassword: ''
  })
  const router = useRouter();
  const submitForm = async() => {
    if (form.value.newPassword !== form.value.confirmPassword) {
      ElMessage.error('两次输入的密码不一致')
      return
    }
    // 这里添加实际提交逻辑
    try {
      const user = localStorage.getItem('userId');
        if (!user) {
          ElMessage.error('无法获取用户信息，请重新登录。');
          router.push('/');
          return;
      }
      const response = await resetPassword({
        userId: form.value.userId,
        passwordHash: encrypt(form.value.confirmPassword)
      });
    if (response.code === 200) {
      ElMessage.success('更改用户密码成功。');
    } else {
      ElMessage.error('更改用户密码失败，请稍后再试。');
    }
  } catch (error) {
    ElMessage.error('更改用户密码失败，请稍后再试。');
  }
}
</script>
  