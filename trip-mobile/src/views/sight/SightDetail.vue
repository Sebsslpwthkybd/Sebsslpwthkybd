<template>
  <!-- 景点详情 -->
  <div class="page-sight-detail">
    <!-- 页面头部 -->
    <van-nav-bar
    left-text="返回"
    left-arrow
    fixed
    @click-left="goBack"
  />
    <!-- 大图 -->
    <div class="sight-banner">
      <van-image :src="sightDetail.img" width="100%" height="100%"/>
      <div class="tips">
        <router-link class="pic-sts" :to="{name: 'SightImage', params: {id}}">
          <van-icon name="video-o" />
          <span>{{ sightDetail.image_count }} 图片</span>
        </router-link>
        <div class="title">{{ sightDetail.name }}</div>
      </div>
    </div>
    <!-- //大图 -->
    <!-- 评分、景点介绍 -->
    <div class="sight-info">
      <div class="left" @click="goPage()">
        <div class="info-title">
          <strong>{{ sightDetail.score }}分</strong>
          <small>很棒</small>
        </div>
        <div class="info-tips">{{ sightDetail.comment_count }} 评论</div>
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
    <van-cell :title="fullArea" icon="location-o"
      is-link
      :title-style="{'text-align': 'left'}">
      <template #right-icon>
        <van-icon name="arrow" />
      </template>
    </van-cell>
    <!-- 门票列表 -->
    <div class="sight-ticket">
      <van-cell title="门票" icon="bookmark-o" title-style="text-align:left"/>
      <div class="ticket-item" v-for="item in ticketList" :key="item.pk">
        <div class="left">
          <div class="title">{{ item.name }}</div>
          <div class="tips">
            <van-icon name="clock-o" />
            <span>{{ item.desc }}</span>
          </div>
          <div class="tags">
            <van-tag mark type="primary">标签1</van-tag>
          </div>
        </div>
        <div class="right">
          <div class="price">
            <span>￥</span>
            <strong>{{ item.sell_price }}</strong>
          </div>
          <router-link to="#">
            <van-button type="warning" size="small">预定</van-button>
          </router-link>
        </div>
      </div>
    </div>
    <!-- //门票列表 -->
    <!-- 用户评价 -->
    <div class="sight-comment">
      <van-cell title="热门评论" icon="comment-o" title-style="text-align:left"/>
      <comment-item v-for="item in commentList" :key="item.pk" :item="item" />
      <router-link class="link-more" :to="{name: 'SightComment', params: {id}}">查看更多</router-link>
    </div>
    <!-- //用户评价 -->
  </div>
</template>
<script>
import { ajax } from '@/utils/ajax'
import { SightApis } from '@/utils/apis'
// 评论项组件
import CommentItem from '@/components/sight/CommentItem'
export default {
  data () {
    return {
      id: '',
      // 景点详细信息
      sightDetail: {},
      // 门票列表
      ticketList: [],
      // 评论列表
      commentList: []
    }
  },
  components: {
    CommentItem
  },
  computed: {
    /**
     * 地址的全部信息
     */
    fullArea () {
      let area = this.sightDetail.province + this.sightDetail.city
      if (this.sightDetail.area) {
        area += this.sightDetail.area
      }
      if (this.sightDetail.town) {
        area += this.sightDetail.town
      }
      return area
    }
  },
  watch: {
    $route () {
      this.loadData()
    }
  },
  methods: {
    /**
     * 跳转到评论列表
     */
    goPage () {
      this.$router.push({name: 'SightComment', params: {id: this.id}})
    },
    loadData () {
      this.id = this.$route.params.id
      // 获取景点详细信息
      this.getSightDetail()
      // 门票列表
      this.getTicketList()
      // 评论列表
      this.getCommentList()
    },
    goBack () {
      this.$router.go(-1)
    },
    /**
     * 获取景点详细信息
     */
    getSightDetail () {
      const url = SightApis.sightDetailUrl.replace('#{id}', this.id)
      ajax.get(url).then(({ data }) => {
        this.sightDetail = data
      })
    },
    /**
     * 门票列表
     */
    getTicketList () {
      const url = SightApis.sightTicketUrl.replace('#{id}', this.id)
      ajax.get(url).then(({ data: { objects } }) => {
        this.ticketList = objects
      })
    },
    /**
     * 评论列表
     */
    getCommentList () {
      const url = SightApis.sightCommentUrl.replace('#{id}', this.id)
      ajax.get(url).then(({ data: { objects } }) => {
        this.commentList = objects
      })
    }
  },
  created () {
    this.loadData()
  }
}
</script>
<style lang="less">
.page-sight-detail {
  .van-nav-bar {
    background-color: transparent;
  }
  // 景点大图
  .sight-banner{
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
        background-color: rgba(0,0,0,0.4);
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
      top: 5px
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

      .left {
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
  // 评论列表
  .sight-comment {
    margin-top: 10px;
    background-color: #fff;
  }
  // 查看更多
  .link-more {
    display: block;
    color: #666;
    padding: 10px;
  }
}
</style>
