<template>
  <div class="page-home">
    <!-- 导航栏 -->
    <van-nav-bar title="旅游网">
    </van-nav-bar>
    <!-- 轮播图 -->
    <Banner/>
    <!-- 景点列表 -->
    <Fine/>
    <footer-bar/>
  </div>
</template>

<script>
// @ is an alias to /src
import Banner from '@/components/home/BannerBox'
import Fine from '@/components/home/FineBox'
import FooterBar from '@/components/common/FooterBar'

export default {
  name: 'HomeView',
  components: {
    // banner图
    Banner,
    // 精选景点
    Fine,
    // 底部导航
    FooterBar
  }
}
</script>
