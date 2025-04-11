<template>
    <div class="page-container">
      <el-row justify="center">
        <el-col :xs="24" :sm="22" :md="20" :lg="18">
          <el-card class="policy-card">
            <template #header>
              <div class="header">
                <h1>隐私政策</h1>
                <p class="update-time">最后更新日期：2025年4月7日</p>
              </div>
            </template>
  
            <article class="policy-content">
              <section v-for="(section, index) in policySections" :key="index">
                <h2 class="section-title">{{ section.title }}</h2>
                <p class="section-text">{{ section.content }}</p>
              </section>
            </article>
  
            <el-alert
              title="重要提示"
              type="warning"
              description="请仔细阅读本隐私政策，了解我们如何处理您的个人信息"
              show-icon
              class="alert-box"
            />
          </el-card>
        </el-col>
      </el-row>
    </div>
  </template>
  
  <script setup>
  const policySections = [
    {
      title: '信息收集',
      content: '我们会在您注册账户、借阅图书时收集必要信息...'
    },
    {
      title: '信息使用',
      content: '收集的信息将用于图书借阅服务、服务改进...'
    },
    {
      title: '信息安全',
      content: '我们采用SSL加密技术保护您的个人信息...'
    }
  ]
  </script>
  
  <style scoped>
  .policy-card {
    margin: 30px 0;
  }
  
  .header {
    text-align: center;
  }
  
  .update-time {
    color: #95a5a6;
    margin-top: 10px;
  }
  
  .section-title {
    color: #2c3e50;
    margin: 25px 0 15px;
  }
  
  .section-text {
    line-height: 1.8;
    color: #7f8c8d;
  }
  
  .alert-box {
    margin-top: 30px;
  }
  </style>