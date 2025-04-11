<template>
  <div id="app">   
    <router-view />
  </div>
</template>

<script setup lang="ts">
import { ref, watch } from 'vue'
import { useRoute } from 'vue-router'
import WebFooter from './components/WebFooter.vue'

const route = useRoute()
/*
const showFooter = ref(false)
// 监听路由变化
watch(route, (newRoute) => {
  showFooter.value = newRoute.path === '/'
})

// 初始判断
showFooter.value = route.path === '/'
*/
</script>

<style>
/* 全局样式 */
html, body {
  height: 100%;
  width: 100%;
  margin: 0;
  padding: 0;
}

#app {
  display: flex;
  flex-direction: column;
  min-height: 100vh; /* 占满整个视口高度 */
  width: 100%;
}

/* 确保 router-view 占满剩余空间 */
#app > router-view {
  flex: 1;
}
</style>