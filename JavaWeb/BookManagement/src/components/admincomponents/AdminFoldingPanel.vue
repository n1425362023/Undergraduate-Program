<template>
    <el-menu
      default-active="2"
      class="el-menu-vertical-demo"
      :collapse="isCollapse"
      @select="handleMenuSelect"
      @mouseover="handleMouseOver"
      @mouseleave="handleMouseLeave"
    >
  
      <el-sub-menu index="1">
        <template #title>
          <el-icon><IconMenu /></el-icon>
          <span>个人信息</span>
        </template>
        <el-menu-item-group>
          <el-menu-item index="1-1">
            <el-icon><Edit /></el-icon>
            <span>修改信息</span>
          </el-menu-item>
          <el-menu-item index="1-2">
            <el-icon><Lock /></el-icon>
            <span>修改密码</span>
          </el-menu-item>
        </el-menu-item-group>
      </el-sub-menu>
  
    
      <el-menu-item index="2">
        <el-icon><Memo /></el-icon>
        <template #title>图书管理</template>
      </el-menu-item>
      <el-menu-item index="3">
        <el-icon><Reading /></el-icon>
        <template #title>借阅管理</template>
      </el-menu-item>
      <el-menu-item index="4">
        <el-icon><Management /></el-icon>
        <template #title>借阅历史</template>
      </el-menu-item>
      <el-menu-item index="5">
        <el-icon><User /></el-icon>
        <template #title>用户管理</template>
      </el-menu-item>
    <el-menu-item index="6">
        <el-icon><Orange /></el-icon>
        <template #title>数据统计</template>
      </el-menu-item>
    </el-menu>
  </template>
  
  <script setup lang="ts">
  import { ref } from 'vue'
  import { useRouter } from 'vue-router'
  
  import {
    Memo,
    Lock,
    Edit,
    Menu as IconMenu,
    Management,
    User,
    Orange,
    Reading
  } from '@element-plus/icons-vue'
  
  const isCollapse = ref(true)
  let hoverTimeout: number | null = null
  
  const handleMouseOver = () => {
    if (isCollapse.value) {
      hoverTimeout = window.setTimeout(() => {
        isCollapse.value = false
      }, 1000)
    }
  }
  
  const handleMouseLeave = () => {
    if (hoverTimeout) {
      clearTimeout(hoverTimeout)
      hoverTimeout = null
    }
    isCollapse.value = true
  }
  
  const handleOpen = (key: string, keyPath: string[]) => {
    console.log(key, keyPath)
  }
  const handleClose = (key: string, keyPath: string[]) => {
    console.log(key, keyPath)
  }
  const emit = defineEmits(['menu-change'])
  

  const handleMenuSelect = (index: string) => {
    emit('menu-change', index) 
  }
  
  </script>
  
  <style scoped>
  

  .el-main {
    padding: 20px;
    height: calc(100vh - 60px);
    overflow-y: auto;
  }
  

  .el-menu-item:hover {
    background-color: #ecf5ff !important;
  }
  
  .el-menu--collapse .el-menu-item span,
  .el-menu--collapse .el-sub-menu__title span {
    height: 0;
    width: 0;
    overflow: hidden;
    visibility: hidden;
    display: inline-block;
  }
  
  .el-menu--collapse .el-menu-item .el-icon,
  .el-menu--collapse .el-sub-menu__title .el-icon {
    margin-right: 0;
  }
  </style>