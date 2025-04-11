
import { createRouter, createWebHistory, type RouteMeta } from 'vue-router'
import LoginView from '@/views/LoginView.vue'
import About from '@/views/About.vue'
import Privacy from '@/views/Privacy.vue'
import Contact from '@/views/Contact.vue'


// 扩展 RouteMeta 接口
declare module 'vue-router' {
  interface RouteMeta {
    requiresAuth?: boolean
    roles?: string[]
  }
}

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      component: LoginView ,
    },
    {
      path: '/passwordforget',
      name: 'passwordforget',
      component: () => import('../views/Passwordforget.vue'),
    },
    {
      path:'/user',
      name: 'user',
      meta: { requiresAuth: true ,roles: ['USER']},
      component: () => import('../views/UserHomeView.vue'),
      children: [
        {
          path:'/userinfo',
          name: 'userinfo',
          component: () => import('../components/usercomponents/UserInfo.vue'),
          meta: { requiresAuth: true ,roles: ['USER']},
        },
        {
          path:'/passwordupdate',
          name: 'passwordupdate',
          component: () => import('../components/usercomponents/PasswordUpdate.vue'),
          meta: { requiresAuth: true ,roles: ['USER']},
        },
        {
          path:'/borrowhistory',
          name: 'borrowhistory',
          component: () => import('../components/usercomponents/BorrowHistory.vue'),
          meta: { requiresAuth: true ,roles: ['USER']},
        },{
          path:'/booksearch',
          name: 'booksearch',
          component: () => import('../components/usercomponents/BookSearch.vue'),
          meta: { requiresAuth: true ,roles: ['USER']},
        },{
          path:'/information',
          name: 'information',
          component: () => import('../components/usercomponents/UserInfo.vue'),
          meta: { requiresAuth: true ,roles: ['USER']},
        }
      ]
    },
    {
      path:'/admin',
      name: 'admin',
      meta: { requiresAuth: true ,roles: ['ADMIN']},
      component: () => import('../views/AdminHomeView.vue'),
      children: [
        {
          path:'/admininfo',
          name: 'admininfo',
          component: () => import('../components/admincomponents/AdminInfo.vue'),
          meta: { requiresAuth: true ,roles: ['ADMIN']},
        },
        {
          path:'/passwordupdate',
          name: 'passwordupdate',
          component: () => import('../components/admincomponents/PasswordUpdate.vue'),
          meta: { requiresAuth: true ,roles: ['ADMIN']},
        },
        {
          path:'/borrowhistory',
          name: 'borrowhistory',
          component: () => import('../components/admincomponents/BorrowHistory.vue'),
          meta: { requiresAuth: true ,roles: ['ADMIN']},
        },{
          path:'/bookmanagement',
          name: 'bookmanagement',
          component: () => import('../components/admincomponents/BookManagement.vue'),
          meta: { requiresAuth: true ,roles: ['ADMIN']},
        },{
          path:'/borrowmanagement',
          name: 'borrowmanagement',
          component: () => import('../components/admincomponents/BorrowManagement.vue'),
          meta: { requiresAuth: true ,roles: ['ADMIN']},
        },{
          path:'/usermanagement',
          name: 'usermanagement',
          component: () => import('../components/admincomponents/UserManagement.vue'),
          meta: { requiresAuth: true ,roles: ['ADMIN']},
        },{
          path:'/datastatistics',
          name: 'datastatistics',
          component: () => import('../components/admincomponents/DataStatistics.vue'),
          meta: { requiresAuth: true ,roles: ['ADMIN']},
        }
      ]
    },
    {
      path: '/forbidden',
      component: () => import('@/views/ForbiddenView.vue')
    },
    { path: '/about', component: About },
    { path: '/privacy', component: Privacy },
    { path: '/contact', component: Contact },
  ]
})

router.beforeEach((to, from, next) => {
  const isLoggedIn = localStorage.getItem('token')
  const userRole = localStorage.getItem('role')

  if (to.meta.requiresAuth && !isLoggedIn) {
    next('/') 
    return
  }

  // 添加类型守卫检查
  if (to.meta.roles && userRole) {
    if (!to.meta.roles.includes(userRole)) {
      console.log("当前权限"+userRole)
      next('/forbidden') // 需要创建对应的 403 页面或调整跳转逻辑
      return
    }
  }

  next()
})

export default router