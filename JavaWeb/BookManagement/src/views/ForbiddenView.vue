<template>
    <div class="forbidden-container">
      <el-container>
        <el-header height="60px"></el-header>
        
        <el-main>
          <div class="content-wrapper">
            <div class="error-content">
              
              <el-icon class="error-icon" :size="100" color="#F56C6C">
                <CircleClose />
              </el-icon>
  
              
              <h1 class="error-title">403 Forbidden</h1>
              <p class="error-description">抱歉，您没有权限访问该页面</p>
  
              
              <el-button 
                type="primary" 
                @click="goHome"
                class="back-button"
              >
                <el-icon><HomeFilled /></el-icon>
                <span>返回首页</span>
              </el-button>
            </div>
          </div>
        </el-main>
  
        <el-footer></el-footer>
      </el-container>
    </div>
  </template>
  
  <script setup>
  import { useRouter } from 'vue-router'
  import { CircleClose, HomeFilled } from '@element-plus/icons-vue'
  
  const router = useRouter()
  
  const goHome = () => {
    router.push('/')
  }
  </script>
  
  <style scoped>
  .forbidden-container {
    height: 100vh;
  }
  
  .content-wrapper {
    display: flex;
    justify-content: center;
    align-items: center;
    height: calc(100vh - 120px); /* 减去 header 和 footer 的高度 */
  }
  
  .error-content {
    text-align: center;
    padding: 40px;
    background: #fff;
    border-radius: 8px;
    box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
  }
  
  .error-icon {
    margin-bottom: 24px;
  }
  
  .error-title {
    font-size: 32px;
    color: #303133;
    margin-bottom: 16px;
  }
  
  .error-description {
    font-size: 16px;
    color: #606266;
    margin-bottom: 32px;
  }
  
  .back-button {
    padding: 12px 24px;
    font-size: 16px;
  }
  
  .back-button span {
    margin-left: 8px;
  }
  </style>