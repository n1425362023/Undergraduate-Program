<template>
  <div class="login-view">
    <el-container>
      <el-header class="header">
        <WebHeader />
      </el-header>

      <el-main class="main">
        <div class="log-wrapper">
          <div class="log-container">
            <div class="button-group">
              <el-button 
                type="primary" 
                size="large" 
                @click="showLoginBox"
                style="flex: 1">
                登录
              </el-button>
              <el-button 
                type="success" 
                size="large" 
                @click="showRegistrationBox"
                style="flex: 1">
                注册
              </el-button>
            </div>
            <component 
              :is="currentComponent as ComponentType"
              @registration-success="showLoginBox"
            />
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
import { ref } from 'vue'
import LoginBox from '../components/LoginBox.vue'
import RegistrationBox from '../components/RegistrationBox.vue'
import WebHeader from '../components/WebHeader.vue'
import WebFooter from '../components/WebFooter.vue'

type ComponentType = typeof LoginBox | typeof RegistrationBox
const currentComponent = ref<ComponentType>(LoginBox)

const showLoginBox = () => {
  currentComponent.value = LoginBox
}

const showRegistrationBox = () => {
  currentComponent.value = RegistrationBox
}
</script>


<style scoped>
.login-view {
  min-height: 100vh;
  display: flex;
  flex-direction: column;
}

.header {
  height: 60px;
  background-color: rgb(125, 161, 205);
  padding: 0;
}

.main {
  background-image: url('../assets/login-background.png');
  background-size: cover;
  background-position: center;
  min-height: 60vh;
  padding: 20px;
  flex: 1;
}

.log-wrapper {
  display: flex;
  justify-content: flex-end;
  height: 100%;
}

.log-container {
  background-color: rgba(255, 255, 255, 0.65);
  padding: 24px;
  border-radius: 8px;
  box-shadow: 0 4px 16px rgba(0,0,0,0.1);
  width: 350px;
  margin-right: 5%;
  margin-top: 5%;
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
</style>