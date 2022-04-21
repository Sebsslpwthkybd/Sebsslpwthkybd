<template>
  <!-- 景点评论 -->
  <div class="page-sight-comment">
    <!-- 页面头部 -->
    <van-nav-bar
      left-text="返回"
      title="景点评论"
      left-arrow
      @click-left="goBack"
    />
    <van-pull-refresh v-model="refreshing" @refresh="onRefresh">
      <van-list
        class="sight-comment"
        v-model="loading"
        :finished="finished"
        finished-text="没有更多了"
        :error.sync="error"
        error-text="请求失败，点击重新加载"
        @load="getCommentList"
      >
        <comment-item v-for="item in commentList" :key="item.pk" :item="item" />
      </van-list>
    </van-pull-refresh>
  </div>
</template>
<script>
import { ajax } from '@/utils/ajax'
import { SightApis } from '@/utils/apis'
// 评论项组件
import CommentItem from '@/components/sight/CommentItem'
export default {
  components: {
    CommentItem
  },
  data () {
    return {
      // 评论列表
      commentList: [],
      // 当前的页码
      currentPage: 1,
      // 正在加载中
      loading: false,
      // 所有的内容加载完
      finished: false,
      // 请求失败
      error: false,
      // 是否正在下拉刷新中
      refreshing: false
    }
  },
  methods: {
    goBack () {
      this.$router.go(-1)
    },
    /**
     * 下拉刷新执行
     */
    onRefresh () {
      // 清空数据
      this.commentList = []
      this.currentPage = 1

      this.finished = false
      this.error = false

      // 重新加载数据
      this.getCommentList()
    },
    /**
     * 评论列表
     */
    getCommentList () {
      const url = SightApis.sightCommentUrl.replace('#{id}', this.id)
      ajax.get(url, {
        params: {
          page: this.currentPage
        }
      }).then(({ data: { meta, objects } }) => {
        this.commentList = this.commentList.concat(objects)
        // 加载状态结束
        this.loading = false
        // 设置下一页的页码
        this.currentPage = meta.current_page + 1
        // 数据全部加载完成： 当前页面 == 总页数
        if (meta.current_page === meta.page_count) {
          this.finished = true
        }
        this.refreshing = false
      }).catch(() => {
        this.loading = false
        this.error = true
        this.refreshing = false
      })
    }
  },
  mounted () {
    this.id = this.$route.params.id
    // this.getCommentList()
  }
}
</script>
<style lang="less">
.page-sight-comment {
  background-color: #fff;
}
</style>
