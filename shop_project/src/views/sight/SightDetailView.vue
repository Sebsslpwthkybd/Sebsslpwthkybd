<template>
  <!-- 景点详情 -->
  <div class="page-sight-detail">
    <!-- 页面头部 -->
    <van-nav-bar
      left-text="返回"
      left-arrow
      @click-left="goBack"
      fixed
      />
    <!-- 景点大图 -->
    <div class="sight-banner">
      <van-image src="/static/home/hot/h1_max.jpg" width="100%" height="100%"/>
      <div class="tips">
        <router-link class="pic-sts" :to="{name: 'SightImage', params: {id: 123}}">
          <van-icon name="photo-o" />
          <span>10 图片</span>
        </router-link>
        <div class="title">景点标题</div>
      </div>
    </div>
    <!-- //景点大图 -->
    <!-- 评分、景点介绍 -->
    <div class="sight-info">
      <div class="left">
        <div class="info-title">
          <strong>5分</strong>
          <small>很棒</small>
        </div>
        <div class="info-tips">50 评论</div>
        <van-icon name="arrow" />
      </div>
      <div class="right">
        <div class="info-title">
          <span>景点介绍</span>
        </div>
        <div class="info-tips">开放时间、贴士</div>
        <van-icon name="arrow" />
      </div>
    </div>
    <!-- //评分、景点介绍 -->
    <!-- 地址信息 -->
    <van-cell title="广东省广州市番禺区番禺大道"
      icon="location-o"
      is-link
      :title-style="{'text-align': 'left'}">
      <!-- 使用 right-icon 插槽来自定义右侧图标 -->
      <template #right-icon>
        <van-icon name="arrow"/>
      </template>
    </van-cell>
    <!-- 门票列表 -->
    <div class="sight-ticket">
      <van-cell title="门票" icon="bookmark-o" title-style="text-align: left"/>
      <div class="ticket-item" v-for="i in 5" :key="i">
        <div class="left">
          <div class="title">成人票</div>
          <div class="tips">
            <van-icon name="clock-o"/>
            <span>7点之前可以预定</span>
          </div>
          <div class="tags">
            <van-tag mark type="primary">标签</van-tag>
          </div>
        </div>
        <div class="right">
          <div class="price">
            <span>￥</span>
            <strong>65</strong>
          </div>
          <router-link to="#">
            <van-button type="warning" size="small">预定</van-button>
          </router-link>
        </div>
      </div>
    </div>
    <!-- // 门票列表 -->
    <!-- 评论列表 -->
    <!-- 用户评价 -->
  </div>
</template>

<script>
export default {
  data () {
    return {
        item: []
    }
  },
  methods: {
    goBack () {
      this.$router.go(-1)
    },
  }
}
</script>

<style lang="less">
.page-sight-detail {
  .van-nav-bar {
    background: transparent;
  }
  // 景点大图
  .sight-banner {
    position: relative;
    .tips {
      position: absolute;
      left: 10px;
      bottom: 10px;
      font-size: 16px;
      color: #fff;
      
      .pic-sts {
        color: #fff;
        border-radius: 30px;
        font-size: 14px;
        background-color: rgba(0, 0, 0, 0.4);
      }
    }
  }
  // 评分、景点介绍
  .sight-info {
    display: flex;
    background-color: #fff;
    border-bottom: 1px solid #f6f6f6;

    & > div {
      flex: 1;
      position: relative;
    }
    .right {
      border-left: 1px solid #f6f6f6;
    }
    .info-title {
      text-align: left;
      padding: 5px 10px;
      strong {
        color: #ff8300;
      }
    }
    .info-tips {
      color: #999;
      font-size: 12px;
      text-align: left;
      padding: 5px 10px;
    }
    .van-icon {
      position: absolute;
      right: 5px;
      top: 5px;
    }
  }
  // 门票列表
  .sight-ticket {
    margin-top: 10px;
    background-color: #fff;

    .ticket-item {
      display: flex;
      border-bottom: 1px solid #f6f6f6;
      padding-bottom: 10px;

      .left{
        flex: 1;
        text-align: left;
        padding: 5px 10px;

        .title {
          padding: 5px 0;
        }
        .tips {
          font-size: 12px;
        }
      }
      .right {
        width: 100px;
        
        .price {
          color: #ff9800;
          strong {
            font-size: 20px;
          }
        }
      }
    }
  }
}
</style>