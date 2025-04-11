<template>
    <div class="login-view">
      <el-container>
        <el-header class="header">
          <WebHeader />
        </el-header>
  
        <el-main class="main">
            <div class="password-reset-container">
                <div class="password-reset-form">
                <h2 class="form-title">密码重置</h2>
                <el-form 
                :model="form" 
                :rules="rules" 
                ref="resetForm"
                label-width="100px"
                @keyup.enter="handleSubmit"
                >
                <!-- 学工号输入 -->
                <el-form-item label="学工号" prop="userId">
                    <el-input 
                    v-model="form.userId" 
                    placeholder="请输入您的学工号"
                    clearable
                    prefix-icon="User"
                    />
                </el-form-item>
        
                <!-- 图形验证码 -->
                <el-form-item label="验证码" prop="captcha">
                    <div class="captcha-container">
                    <el-input
                        v-model="form.captcha"
                        placeholder="请输入验证码"
                        prefix-icon="Key"
                        style="width: 60%"
                    />
                <div class="captcha-code" @click="refreshCaptcha">
                    {{ captchaCode }}
                </div>
            </div>
          </el-form-item>
  
          <!-- 新密码 -->
          <el-form-item label="新密码" prop="newPassword">
            <el-input
              v-model="form.newPassword"
              type="password"
              placeholder="请输入6-20位密码"
              show-password
              prefix-icon="Lock"
            />
          </el-form-item>
  
          <!-- 确认密码 -->
          <el-form-item label="确认密码" prop="confirmPassword">
            <el-input
              v-model="form.confirmPassword"
              type="password"
              placeholder="请再次输入密码"
              show-password
              prefix-icon="Lock"
            />
          </el-form-item>
  
          <!-- 按钮组 -->
          <el-form-item class="form-buttons">
            <div class="button-group">
              <el-button 
                plain
                @click="handleReturn"
                class="full-width-button"
              >
                <el-icon><ArrowLeft /></el-icon>
                返回登录
              </el-button>
              <el-button 
                type="primary" 
                :loading="submitting"
                @click="handleSubmit"
                class="full-width-button"
              >
                确认重置
              </el-button>
            </div>
          </el-form-item>
        </el-form>
      </div>
    </div>
        </el-main>
        
        <el-footer class="footer">
          <WebFooter />
        </el-footer>
      </el-container>
    </div>
  </template>



<script setup lang="ts">
import { ref, reactive } from 'vue'
import { useRouter } from 'vue-router'
import WebHeader from '@/components/WebHeader.vue'
import WebFooter from '@/components/WebFooter.vue'
import { ElMessage, type FormInstance, type FormRules } from 'element-plus'
import { ArrowLeft } from '@element-plus/icons-vue'
import { resetPassword } from '../api/authentication'
import { encrypt } from '../utils/crypto'
  
  const router = useRouter()
  const resetForm = ref<FormInstance>()
  const submitting = ref(false)
  
  // 图形验证码
  const captchaCode = ref('')
  const generateCaptcha = () => {
    // 生成4位随机数字验证码
    captchaCode.value = Math.floor(1000 + Math.random() * 9000).toString()
  }
  
  // 刷新验证码
  const refreshCaptcha = () => {
    generateCaptcha()
    ElMessage.info('验证码已刷新')
  }
  
  // 表单数据
  const form = reactive({
    userId: '',
    captcha: '',
    newPassword: '',
    confirmPassword: ''
  })
  
  // 表单验证规则
  const validatePassword = (rule: any, value: string, callback: any) => {
    if (!value) {
      callback(new Error('请输入密码'))
    } else if (value.length < 6) {
      callback(new Error('密码长度不能少于6位'))
    } else if (value.length > 20) {
      callback(new Error('密码长度不能超过20位'))
    } else {
      callback()
    }
  }
  
  const validateConfirmPassword = (rule: any, value: string, callback: any) => {
    if (!value) {
      callback(new Error('请再次输入密码'))
    } else if (value !== form.newPassword) {
      callback(new Error('两次输入的密码不一致'))
    } else {
      callback()
    }
  }
  
  const rules = reactive<FormRules>({
    userId: [
      { required: true, message: '请输入学工号', trigger: 'blur' },
      { min: 3, max: 15, message: '学工号长度在 3 到 15 个字符', trigger: 'blur' },
    ],
    captcha: [
      { required: true, message: '请输入验证码', trigger: 'blur' },
      { pattern: /^\d{4}$/, message: '验证码应为4位数字', trigger: 'blur' }
    ],
    newPassword: [
      { validator: validatePassword, trigger: 'blur' }
    ],
    confirmPassword: [
      { validator: validateConfirmPassword, trigger: 'blur' }
    ]
  })
  
  // 初始化验证码
  generateCaptcha()
  
  // 返回登录
  const handleReturn = () => {
    router.push('/')
  }
  
  // 提交处理
  const handleSubmit = async () => {
    try {
      await resetForm.value?.validate()
      submitting.value = true
  
      // 验证码校验
      if (form.captcha !== captchaCode.value) {
        ElMessage.warning('验证码不正确')
        refreshCaptcha()
        return
      }
  
      // 调用API
      const response = await resetPassword({
        userId: form.userId,
        passwordHash: encrypt(form.newPassword)
      })
  
      if (response.code === 200) {
        ElMessage.success('密码重置成功！')
        resetForm.value?.resetFields()
        refreshCaptcha()
        setTimeout(() => router.push('/'), 1500)
      } else {
        ElMessage.error(response.message)
        refreshCaptcha()
      }
    } catch (error) {
      console.error('表单验证失败:', error)
    } finally {
      submitting.value = false
    }
  }
  </script>
  
<style scoped>


.header {
  height: 60px;
  background-color: rgb(125, 161, 205);
  padding: 0;
}

.main {
  background-image: url('https://cdn.jsdelivr.net/gh/n1425362023/Picture@main/img/640.jpg');
  background-size: cover;
  background-position: center;
  min-height: 60vh;
  padding: 20px;
  flex: 1;
}



.button-group {
  display: flex;
  gap: 12px;
  margin-bottom: 24px;
}

.footer {
  background-color: #333;
  color: white;
  padding: 0;
  margin-top: auto;
}
.password-reset-container {
    display: flex;
    justify-content: center;
    align-items: center;
    min-height: 80vh;
    /*background-color: rgba(254, 246, 246, 0.068);*/
}
  
.password-reset-form {
    width: 100%;
    max-width: 500px;
    padding: 40px;
    background: #ffffff;
    border-radius: 8px;
    box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
}
  
.form-title {
    margin-bottom: 30px;
    text-align: center;
    color: #303133;
}
  
.captcha-container {
    display: flex;
    gap: 10px;
    width: 100%;
}
  
.captcha-code {
    width: 40%;
    height: 40px;
    line-height: 40px;
    text-align: center;
    background: linear-gradient(145deg, #f0f2f5, #e4e7ed);
    border-radius: 4px;
    cursor: pointer;
    user-select: none;
    font-family: 'Courier New', monospace;
    font-size: 20px;
    letter-spacing: 5px;
    color: #409eff;
    border: 1px solid #dcdfe6;
    transition: all 0.3s;
}
  
.captcha-code:hover {
    background: linear-gradient(145deg, #e4e7ed, #d3d9e6);
}

.form-buttons {
    margin-top: 30px;
}
  
.button-group {
    display: flex;
    gap: 15px;
    width: 100%;
}
  
  
@media (max-width: 768px) {
    .password-reset-form {
      padding: 20px;
      margin: 20px;
    }
    
    .button-group {
      flex-direction: column;
    }
    
    .captcha-container {
      flex-direction: column;
    }
    
    .captcha-code {
      width: 100%;
      margin-top: 10px;
    }
}
</style>