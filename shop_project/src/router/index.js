import Vue from 'vue'
import VueRouter from 'vue-router'
import HomeView from '../views/HomeView.vue'
import SearchView from '../views/SearchView.vue'
import SightDetailView from '../views/sight/SightDetailView.vue'
import SightListView from '../views/sight/SightListView.vue'
import SightInfoView from '../views/sight/SightInfoView.vue'
import SightCommentView from '../views/sight/SightCommentView.vue'
import SightImageView from '../views/sight/SightImageView.vue'


Vue.use(VueRouter)

const routes = [
  {
    path: '/',
    name: 'Home',
    component: HomeView
  },
  {
    path: '/search',
    name: 'Search',
    component: SearchView
  },
  // 景点列表
  {
    path: '/sight/list',
    name: 'SightList',
    component: SightListView
  },
  // 景点详情
  {
    path: '/sigt/detail/:id',
    name: 'SightDetail',
    component: SightDetailView
  },
  // 景点介绍
  {
    path: '/sight/info/:id',
    name: 'SightInfo',
    component: SightInfoView
  },
  // 评论列表
  {
    path: '/sight/comment/:id',
    name: 'SightComment',
    component: SightCommentView
  },
  // 景点下的图片
  {
    path: '/sight/img/:id',
    name: 'SightImage',
    component: SightImageView
  }
]

const router = new VueRouter({
  routes
})

export default router
