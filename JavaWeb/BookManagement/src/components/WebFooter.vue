<!-- WebFooter.vue -->
<template>
  <footer class="footer">
    <div class="footer-content">
      <p>&copy; 2025 My Awesome App. All rights reserved.</p>
      <nav class="footer-links">
        <router-link to="/about">关于我们</router-link>
        <router-link to="/privacy">隐私政策</router-link>
        <router-link to="/contact">联系我们</router-link>
      </nav>
      <div class="social-media">
        <a href="https://facebook.com" target="_blank">Facebook</a>
        <a href="https://twitter.com" target="_blank">Twitter</a>
        <a href="https://instagram.com" target="_blank">Instagram</a>
      </div>
    </div>
  </footer>
</template>

<style scoped>
.footer {
  width: 100%;
  padding: 20px 0;
  background-color: #333;
}

.footer-content {
  max-width: 1200px;
  margin: 0 auto;
  text-align: center;
}

.footer-links a,
.social-media a {
  color: #fff;
  margin: 0 12px;
  text-decoration: none;
  transition: opacity 0.3s;
}

.footer-links a:hover,
.social-media a:hover {
  opacity: 0.8;
}

.social-media {
  margin-top: 12px;
}
</style>