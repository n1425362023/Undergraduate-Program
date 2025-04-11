<template>
    <el-container>
      <el-header>
        <h1>联系我们</h1>
      </el-header>
      <el-main>
        <div class="contact-info">
          <h2>燕山大学图书馆</h2>
          <p><strong>地址：</strong>河北省秦皇岛市燕山大学校区</p>
          <p><strong>电话：</strong>(0335) 1234-5678</p>
          <p><strong>邮箱：</strong>library@ysu.edu.cn</p>
          <p><strong>工作时间：</strong>周一至周五 8:00 AM - 5:00 PM</p>
        </div>
  
        <div class="message">
          <p>如果您有任何问题，欢迎通过电话或电子邮件与我们联系！</p>
        </div>
      </el-main>
    </el-container>
  </template>
  
  <script setup>
  import { ElContainer, ElHeader, ElMain } from 'element-plus'
  </script>
  
  <style scoped>
  .el-header {
    background-color: #f4f4f4;
    text-align: center;
    padding: 20px 0;
  }
  
  h1 {
    margin: 0;
    font-size: 24px;
  }
  
  .contact-info {
    max-width: 600px;
    margin: 20px auto;
    font-size: 16px;
  }
  
  .contact-info p {
    margin: 10px 0;
  }
  
  .message {
    text-align: center;
    font-size: 18px;
    margin-top: 20px;
  }
  </style>
  