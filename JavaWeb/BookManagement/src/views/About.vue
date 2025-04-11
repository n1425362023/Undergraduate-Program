<template>
    <div class="page-container">
      <el-row justify="center">
        <el-col :xs="24" :sm="22" :md="20" :lg="18">
          <el-card class="box-card">
            <template #header>
              <div class="card-header">
                <h1 class="title">关于燕山大学图书馆</h1>
              </div>
            </template>
  
            <el-space direction="vertical" size="large">
              <el-image 
                src="https://imgs.knowsafe.com:8087/img/chayuqing/2021/11/10/b1ab90522875e2e3b84c44bb778f0bb7.jpg"
                fit="cover"
                class="banner-image"
              />
              
              <section>
                <h2 class="section-title">图书馆概况</h2>
                <p class="section-content">
                  燕山大学图书馆成立于1985年，是一座致力于为师生提供全面学术支持的现代化图书馆。馆内收藏丰富，涵盖了各类学术、科技、文化资源。
                </p>
              </section>
  
              <el-divider />
  
              <section>
                <h2 class="section-title">我们的使命与愿景</h2>
                <p class="section-content">
                  燕山大学图书馆秉承“服务科研，服务教学，服务学生”的宗旨，致力于成为一流的学术资源中心，推动知识共享与创新。
                </p>
              </section>
  
              <el-timeline>
                <el-timeline-item
                  v-for="(event, index) in historyEvents"
                  :key="index"
                  :timestamp="event.date"
                >
                  {{ event.content }}
                </el-timeline-item>
              </el-timeline>
            </el-space>
          </el-card>
        </el-col>
      </el-row>
    </div>
  </template>
  
  <script setup>
  const historyEvents = [
    { date: '1985年', content: '燕山大学图书馆成立' },
    { date: '1995年', content: '图书馆扩建，增加多功能阅览区' },
    { date: '2005年', content: '数字化资源全面升级' },
    { date: '2022年', content: '引入智能化自助借还系统' },
  ]
  </script>
  
  <style scoped>
  .page-container {
    padding: 40px 20px;
  }
  
  .box-card {
    margin: 20px 0;
  }
  
  .title {
    text-align: center;
    color: #2c3e50;
  }
  
  .banner-image {
    width: 100%;
    border-radius: 8px;
  }
  
  .section-title {
    color: #34495e;
    margin-bottom: 15px;
  }
  
  .section-content {
    line-height: 1.8;
    color: #7f8c8d;
  }
  </style>
  