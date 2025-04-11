<template>
    <div class="common-layout">
      <el-container direction="vertical">
        <el-header class="header">
          <div class="header-title">
            <img src="../assets/header.png" alt="logo" />
            <el-text class="header-text">欢迎使用图书管理系统</el-text>
            <el-space class="header-text">
              <el-icon :size = 20><SwitchButton /></el-icon>
              <el-text class="header-text"  @click = quit() style="font-size: 16px;">登出</el-text>
            </el-space>
            
          </div>
        </el-header>
        
        <el-container class="main-container">
          <el-aside width="160px" class="aside">
            <AdminFoldingPanel @menu-change="handleMenuChange" />
          </el-aside>
          
          <el-main>
            <component :is="currentComponent" />
          </el-main>
        </el-container>
      </el-container>
    </div>
  </template>
  
  <script setup lang="ts">
  import { ref, shallowRef, defineAsyncComponent } from 'vue'
  import AdminFoldingPanel from '../components/admincomponents/AdminFoldingPanel.vue'
  import { useRouter } from 'vue-router'
  import {
  SwitchButton
} from '@element-plus/icons-vue'
  // 异步加载组件
  const router = useRouter()
  const AdminInfo = defineAsyncComponent(() => import('@/components/admincomponents/AdminInfo.vue'))
  const PasswordUpdate= defineAsyncComponent(() => import('@/components/admincomponents/PasswordUpdate.vue'))
  const BookManagement = defineAsyncComponent(() => import('@/components/admincomponents/BookManagement.vue'))
  const BorrowManagement = defineAsyncComponent(() => import('@/components/admincomponents/BorrowManagement.vue'))
  const BorrowHistory = defineAsyncComponent(() => import('@/components/admincomponents/BorrowHistory.vue'))
  const UserManagement = defineAsyncComponent(() => import('@/components/admincomponents/UserManagement.vue'))
  const DataStatistics = defineAsyncComponent(() => import('@/components/admincomponents/DataStatistics.vue'))
  // 组件映射表
  const componentMap: Record<string, any> = {
    '1-1': AdminInfo,       // 个人信息
    '1-2': PasswordUpdate,  // 修改密码
    '2': BookManagement,    // 图书管理
    '3': BorrowManagement,  // 借阅管理
    '4': BorrowHistory,      // 借阅历史
    '5': UserManagement,   // 用户管理
    '6': DataStatistics   // 数据统计
  }
  
  // 当前显示的组件（默认显示图书查询）
  const currentComponent = shallowRef(BookManagement)
  
  const handleMenuChange = (menuKey: string) => {
    const component = componentMap[menuKey]
    if (component) {
      currentComponent.value = component
    }
  }
  const quit = () => {
    router.push('/')
  }
  </script>
  
  <style scoped>
  .header {
    height: 60px;
    background-color: rgb(125, 161, 205);
    padding: 0;
  }
  
  .header-title {
    display: flex;
    align-items: center;
    height: 100%;
    padding: 0 100px;
    justify-content: space-between;
  }
  
  .header-text {
    font-family: "Microsoft Yahei", sans-serif;
    font-weight: 500;
    font-size: 2em;
    text-shadow: 0 0 25px #a2e2ef;
    color: #f3f3f3;
    text-align: center;
  }
  
  .aside {
    height: calc(100vh - 60px);
  }
  
  .main-container {
    flex: 1;
    overflow: hidden;
  }
  
  .common-layout,
  .el-container {
    height: 100vh;
  }
  
  /* 主内容区域样式优化 */
  .el-main {
    padding: 20px;
    height: calc(100vh - 60px);
    overflow-y: auto;
    background-color: #f5f7fa;
  }
  .fade-enter-active,
  .fade-leave-active {
    transition: opacity 0.3s ease;
  }
  
  .fade-enter-from,
  .fade-leave-to {
    opacity: 0;
  }
  </style>