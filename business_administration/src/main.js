import Vue from 'vue'
// import vueConfig from 'vue.config'
import App from './App.vue'
import router from './router'
import store from './store'
// import * as filters from './utils/filters'

Vue.config.productionTip = false

// 注册过滤器
// Object.keys(filters).forEach(k => Vue.filter(k, filters[k]))

Vue.filter('priceToDollar', function(price){
  if(price === undefined || price === null || isNaN(price)){
    return null
  }
  price = price * 0.1472
  return '$' + price.toFixed(2)
})

new Vue({
  router,
  store,
  render: h => h(App)
}).$mount('#app')
