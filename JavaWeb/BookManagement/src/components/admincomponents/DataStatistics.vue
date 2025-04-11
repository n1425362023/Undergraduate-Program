<template>
  <div class="dashboard-container">
    <div class="main-charts">
      <div class="chart-row">
        <div class="chart-container">
          <h3>图书借阅状态</h3>
          <div ref="pieChart" class="chart"></div>
        </div>
        <div class="chart-container">
          <h3>用户状态分布</h3>
          <div ref="frozenChart" class="chart"></div>
        </div>
        <div class="chart-container">
          <h3>资源统计概览</h3>
          <div ref="barChart" class="chart"></div>
        </div>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import * as echarts from 'echarts'
import { User, Notebook } from '@element-plus/icons-vue'
import { getPeopleList } from '@/api/authentication'
import { getBookList } from '@/api/book'



// 图表引用
const pieChart = ref(null)
const barChart = ref(null)
const frozenChart = ref(null)

// 数据响应
const userCount = ref([])
const totalBooks = ref([])
const bookStatus = ref([])
const userStatus = ref([])

// 图表初始化
const initCharts = () => {
  // 图书借阅状态饼图
  const pieOption = {
    tooltip: { trigger: 'item', formatter: '{b}: {c} ({d}%)' },
    series: [{
      name: '借阅状态',
      type: 'pie',
      radius: ['50%', '70%'],
      itemStyle: {
        borderRadius: 10,
        borderColor: '#fff',
        borderWidth: 2
      },
      data: bookStatus.value.map(item => ({
        ...item,
        itemStyle: { 
          color: item.name === '已借阅' ? '#409EFF' : '#67C23A' 
        }
      }))
    }]
  }

  // 用户状态饼图
  const frozenOption = {
    tooltip: { trigger: 'item', formatter: '{b}: {c} ({d}%)' },
    series: [{
      name: '用户状态',
      type: 'pie',
      radius: '55%',
      itemStyle: {
        borderRadius: 5,
        borderColor: '#fff',
        borderWidth: 2
      },
      data: userStatus.value.map(item => ({
        ...item,
        itemStyle: { 
          color: item.name === '正常用户' ? '#53a8ff' : '#909399' 
        }
      }))
    }]
  }

  // 资源统计柱状图
  const barOption = {
    tooltip: { trigger: 'axis' },
    xAxis: {
      type: 'category',
      data: ['用户数', '图书数'],
      axisLabel: { color: '#606266' }
    },
    yAxis: { type: 'value' },
    series: [{
      data: [userCount.value.length, totalBooks.value.length],
      type: 'bar',
      itemStyle: {
        color: '#409EFF',
        borderRadius: [4, 4, 0, 0]
      },
      barWidth: '40%'
    }]
  }

  // 初始化图表
  const initChart = (ref, option) => {
    const chart = echarts.init(ref.value)
    chart.setOption(option)
    return chart
  }

  const charts = [
    initChart(pieChart, pieOption),
    initChart(frozenChart, frozenOption),
    initChart(barChart, barOption)
  ]

  // 响应式调整
  const handleResize = () => charts.forEach(chart => chart.resize())
  window.addEventListener('resize', handleResize)
}

// 数据加载
onMounted(async () => {
  try {
    const [peopleRes, bookRes] = await Promise.all([
      getPeopleList(),
      getBookList()
    ])
    
    userCount.value = peopleRes.data
    totalBooks.value = bookRes.data

    bookStatus.value = [
      { value: totalBooks.value.filter(b => b.isBorrowed).length, name: '已借阅' },
      { value: totalBooks.value.filter(b => !b.isBorrowed).length, name: '未借阅' }
    ]

    userStatus.value = [
      { value: userCount.value.filter(u => !u.isFrozen).length, name: '正常用户' },
      { value: userCount.value.filter(u => u.isFrozen).length, name: '冻结用户' }
    ]

    initCharts()
  } catch (error) {
    console.error('数据加载失败:', error)
  }
})
</script>

<style scoped>
.dashboard-container {
  padding: 20px;
  background-color: #f5f7fa;
  min-height: 100vh;
}



.main-charts {
  display: flex;
  flex-direction: column;
  gap: 20px;
}

.chart-row {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(380px, 1fr));
  gap: 20px;
}

.chart-container {
  background: #fff;
  border-radius: 8px;
  padding: 20px;
  box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
}

.chart-container h3 {
  margin: 0 0 15px 0;
  font-size: 16px;
  color: #303133;
  text-align: center;
}

.chart {
  width: 100%;
  height: 350px;
}

@media (max-width: 1200px) {
  .chart-row {
    grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
  }
}

@media (max-width: 768px) {
  .chart-row {
    grid-template-columns: 1fr;
  }
}

/* 统计卡片样式 */
.stat-card {
  display: flex;
  background: #fff;
  border-radius: 8px;
  padding: 20px;
  box-shadow: 0 2px 12px 0 rgba(0, 0, 0, 0.1);
  border-left: 4px solid;
}

.stat-card .icon-container {
  width: 50px;
  height: 50px;
  border-radius: 8px;
  display: flex;
  align-items: center;
  justify-content: center;
  margin-right: 15px;
}

.stat-card .icon {
  width: 24px;
  height: 24px;
}

.stat-card .content {
  flex: 1;
}

.stat-card h3 {
  margin: 0 0 5px 0;
  font-size: 14px;
  color: #909399;
  font-weight: normal;
}

.stat-card p {
  margin: 0 0 5px 0;
  font-size: 24px;
  font-weight: bold;
}

.trend-indicator {
  font-size: 12px;
  color: #909399;
}

.trend-indicator .up {
  color: #67c23a;
  margin-right: 5px;
}

.trend-indicator .down {
  color: #f56c6c;
  margin-right: 5px;
}
</style>