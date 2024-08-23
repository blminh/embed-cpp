import { createRouter, createWebHistory } from 'vue-router'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      name: 'led',
      component: () => import('@/views/LedView.vue')
    },
    {
      path: '/lcd16',
      name: 'lcd16',
      component: () => import('@/views/Lcd16View.vue')
    }
  ]
})

export default router
