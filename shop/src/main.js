import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'
// VantUI组件库
import Vant from 'vant'
import 'vant/lib/index.css'

Vue.use(Vant)

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
// createApp(App).use(store).use(router).mount('#app')
