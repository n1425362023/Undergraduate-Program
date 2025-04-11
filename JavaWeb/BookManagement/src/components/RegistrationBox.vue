<template>
  <div class="signup-form">
    <el-form :model="form" label-width="70px" :rules = "rules"> 
     
      <el-form-item label="学工号" prop="userId"> 
        <el-input v-model="form.userId" placeholder="请输入学工号"  class="full-width-input" />
      </el-form-item>

      <el-form-item label="密码" >
        <el-input v-model="form.password1" type="password" placeholder="请输入密码" prop="password1" show-password class="full-width-input" />
        <el-input v-model="form.password2" type="password" placeholder="重新输入密码" prop="password2" show-password class="full-width-input input-gap" />
      </el-form-item>

     
      <el-form-item label="姓名" prop="name"> 
        <el-input v-model="form.name" placeholder="请输入姓名" class="full-width-input" />
      </el-form-item>

   
      <el-form-item label="性别" prop="gender"> 
        <el-radio-group v-model="form.gender">
          <el-radio label="MALE">男</el-radio>
          <el-radio label="FEMALE">女</el-radio>
        </el-radio-group>
      </el-form-item>

     
      <el-form-item label="角色" prop="role"> 
        <el-radio-group v-model="form.role">
          <el-radio label="USER">普通用户</el-radio>
          <el-radio label="ADMIN">管理员</el-radio>
        </el-radio-group>
      </el-form-item>

     
      <el-form-item label="电话" prop="phone_number"> 
        <el-input v-model="form.phone_number" placeholder="请输入电话号码" class="full-width-input" />
      </el-form-item>

      
      <el-form-item>
        <el-button type="primary" class="full-width-button" @click="onSubmit">注册</el-button>
      </el-form-item>
    </el-form>
  </div>
</template>

<script setup lang="ts">
import { reactive } from 'vue';
import { useRouter } from 'vue-router';
import { ElMessage } from 'element-plus';
import { signup } from '@/api/authentication';
import { encrypt } from '@/utils/crypto';
import axios from 'axios';
import { defineEmits } from 'vue'; 

const emit = defineEmits<{
  (e: 'registration-success'): void
}>()

const router = useRouter();
const form = reactive({
  userId: '',
  password1: '',
  password2: '',
  name: '',
  gender: '',
  role: '',
  phone_number: ''
});
const rules = {
  userId: [
    { required: true, message: '请输入学工号', trigger: 'blur' },
    { min: 3, max: 15, message: '学工号长度在 3 到 15 个字符', trigger: 'blur' },
  ],
  password1: [
    { required: true, message: '请输入密码', trigger: 'blur' },
    //{ min: 6, max: 15, message: '密码长度在 6 到 15 个字符', trigger: 'blur' },
  ],
  password2: [
    { required: true, message: '请输入密码', trigger: 'blur' },
    //{ min: 6, max: 15, message: '密码长度在 6 到 15 个字符', trigger: 'blur' },
  ],
  name: [
    { required: true, message: '请输入姓名', trigger: 'blur' },
  ],
  gender: [
    { required: true, message: '请选择性别', trigger: 'change' },
  ],
  role: [
    { required: true, message: '请选择角色', trigger: 'change' },
  ],
  phone_number: [
    { required: true, message: '请输入电话号码', trigger: 'blur' },
    { pattern: /^1[3456789]\d{9}$/, message: '请输入正确的电话号码', trigger: 'blur' },
  ],
}
const onSubmit = async () => {
  if (form.password1 !== form.password2) {
    console.error('两次输入的密码不一致');
    ElMessage.warning('两次输入的密码不一致');
    return;
  }
  try {
    const hashedPassword = encrypt(form.password1);
    
    const response = await signup({
      userId: form.userId,
      passwordHash: hashedPassword,
      name: form.name,
      gender: form.gender,
      role: form.role,
      phoneNumber: form.phone_number,
    });
    if(response.code === 200){
      console.log('注册成功:', response.data);
      
      ElMessage.success('注册成功');
      emit('registration-success'); 
    }else{
      console.error('注册失败:', response.message);
    
      ElMessage.error(response.message);
    }
  } catch (error : any) {
    console.error('注册失败:', error);

    if (error instanceof axios.AxiosError) {
    
      if (!error.response) {
        ElMessage.error('网络错误，请检查您的连接');
      } else if (error.response.status >= 500) {
      
        ElMessage.error('服务器错误，请稍后再试');
      } else {
       
        ElMessage.error(error.response.data.message || '注册失败，请稍后再试');
      }
    } else {
      
      ElMessage.error(error.message || '注册失败，请稍后再试');
    }
  }
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


.el-form-item {
  width: 100%;
}


.full-width-input,
.full-width-button {
  width: 100%;
  box-sizing: border-box; 
}


.input-gap {
  margin-top: 10px;
}


.el-radio-group {
  display: flex;
  gap: 10px; 
}
</style>