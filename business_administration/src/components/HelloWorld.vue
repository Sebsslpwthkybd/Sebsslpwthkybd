<template>
  <div class="hello">
    <h1>{{ msg }}</h1>
    <input type="text" name=ori_data v-model.number="ori_data"><br/>
    <input type="button" value="反转" @click="reverse">
    <h3>数据：{{ rev_data }}</h3><br/>

    <label>货币转换</label>
    <input type="text" name=price v-model.number="price">
    <input type="radio" id="美元" value=0 v-model.number="target">美元
    <input type="radio" id="人民币" value=1 v-model.number="target">人民币
    <br/>
    <h3 v-show="target === 1">人民币：{{ price | priceToRMB }}</h3>
    <h3 v-show="target === 0" v-bind:data-id="price | priceToDollar">美元：{{ price | priceToDollar }}</h3>
  </div>
</template>

<script>
// import { filter } from 'vue/types/umd'
export default {
  name: 'HelloWorld',
  props: {
    msg: String
  },
  data(){
    return{
      "ori_data" :0,
      "rev_data" :0,
      price :0.00,
      target :0
    }
  },
  methods:{
    reverse(){
        if(this.ori_data < 0){
          this.rev_data = (-1 * this.ori_data).toString().split('').reverse()
          this.rev_data.unshift('-')
          this.rev_data = this.rev_data.join('')
        }
        else
          this.rev_data = this.ori_data.toString().split('').reverse().join('')
    }
  },
  filters:{
    priceToRMB: function(price) {
      if(price === undefined || price === null || isNaN(price)){
        return null
      }
      price = price * 6.7951
      return '￥' + price.toFixed(2)
    }
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
h3 {
  margin: 40px 0 0;
}
/* ul {
  list-style-type: none;
  padding: 0;
}
li {
  display: inline-block;
  margin: 0 10px;
}
a {
  color: #42b983;
} */
</style>
