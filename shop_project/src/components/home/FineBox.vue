<template>
  <div class="home-fine-box">
    <!-- 顶上导航 -->
    <van-cell 
      title="精选景点"
      icon="location-o"
      is-link
      title-style="text-align:left"
      value="更多"
      :to="{name: 'SightList', query: {name: '精选景点'}}"/>
    <!-- //顶上导航 -->
    <!-- 景点列表 -->
    <div class="box-main">
      <sight-item v-for="item in dataList"
        :key="item.id"
        v-bind:item="item"/>
    </div>
    <!-- //景点列表 -->
  </div>
</template>

<script>
// @ is an alias to /src
import SightItem from '@/components/common/SightList'
export default {
  components: {
    SightItem
  },
  data() {
    return {
      dataList: []
    }
  },
  created () {
    this.dataList = [
      {id: 1, name: '景点名称', score: 5, price: 98, location: '广东-广州'},
      {id: 2, name: '景点名称', score: 4.5, price: 98, location: '广东-广州'},
      {id: 3, name: '景点名称', score: 4, price: 98, location: '广东-广州'},
      {id: 4, name: '景点名称', score: 4.5, price: 98, location: '广东-广州'},
      {id: 5, name: '景点名称', score: 4.5, price: 98, location: '广东-广州'},
      {id: 6, name: '景点名称', score: 4.5, price: 98, location: '广东-广州'}
    ]
  }
}
</script>

<style lang="less">
.home-fine-box {
  padding: 0 10px;
  .van-cell{
    padding: 10px 0;
  }
  .box-main{
    color: #f6f6f6;
    // 景点列表
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
  }
}
</style>