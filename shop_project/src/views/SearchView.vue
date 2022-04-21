<template>
<!--搜索页面  -->
  <div class="page-search">
    <!-- 标题 -->
    <van-nav-bar title="搜索景点"/>    
    <!-- 搜索框 -->
    <van-search
      v-model="sightName"
      show-action
      label="景点"
      placeholder="请输入搜索关键词"
      @search="onSearch"
    >
      <template #action>
        <div @click="onSearch">搜索</div>
      </template>
    </van-search>
    <!-- 景点列表 -->
    <div class="sight-list">
      <sight-item v-for="item in dataList"
        :key="item.id"
        v-bind:item="item"/>
    </div>
    <!-- 分页 -->
    <van-pagination v-model="currentPage" 
    :total-items="totalItems" 
    :items-per-page="PerPage" />
    <!-- 页脚 -->
    <FooterBar/>
  </div>
</template>

<script>
// 景点列表的每一项
import SightItem from '@/components/common/SightList'
// 页脚
import FooterBar from '@/components/common/FooterBar'

export default {
    data () {
        return {
            // 景点名称
            sightName: '',
            // 景点列表的数据
            dataList: [],
            // 当前页码
            currentPage: 1,
            // 总记录数
            totalItems: 24,
            // 每一页数据的大小
            PerPage: 5
        }
    },
    components: {
        SightItem,
        FooterBar
    },
    methods: {
      onSearch () {
          console.log('onSearch')
      }
    }
}
</script>