<template>
  <router-link class="sight-item" 
  :to="{name: 'SightDetail', params: {id: LocalItem.id}}">
    <img src="static/home/hot/h1.jpg" alt="">
    <div class="right">
      <h5>{{ LocalItem.name }}</h5>
      <van-rate v-model="LocalItem.score" readonly/>
      <div class="tips">4人点评 | 100%满意</div>
      <div class="tips light">{{ LocalItem.location }}</div>
      <div class="line-price">￥ {{ LocalItem.price }} 起</div>
    </div>
  </router-link>
</template>

<script>
export default {
  props: ['item'],
  data: function () {
    return {
      LocalItem: this.item
    }
  }
}
</script>

<style lang="less">
    .sight-item{
      display: flex;
      margin-top: 10px;
      border-bottom: 1px solid #f6f6f6;
      img {
        width: 100px;
        height: 100px;
      }
      h5 {
        color: #212121;
        font-size: 14px;
        padding: 5px 0;
        margin: 0;
      }
      .right {
        text-align: left;
        flex-grow: 1;
        justify-content: left;
        padding-left: 5px;
        position: relative;
      }
      .line-price {
        position: absolute;
        right: 10px;
        top: 20px;
        display: inline-block;
        color: #f50;
        font-size: 16px;
        font-weight: bold;
      }
      .tips {
        font-size: 12px;
        color: #666;
        &.light {
          color: #999;
        }
      }
    }
</style>