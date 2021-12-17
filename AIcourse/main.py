# coding:utf-8
import copy
import operator

import numpy as np
import matplotlib.pyplot as plt

"""
此脚本用于实现K-means聚类算法
使用的距离计算方法为：欧式距离
使用的性能度量指标为：DBI指数
使用的降维算法是：PCA
"""


class Data(object):
    file_path = None  # 数据路径
    data_range = []  # 数据所在的区域

    D = []  # 样本集
    k = None  # 聚类簇数

    # 读取数据
    def __load_data(self):
        col_range = np.arange(self.data_range[0], self.data_range[1])
        self.D = np.loadtxt(self.file_path, delimiter=',', usecols=col_range)

    def __init__(self, file_path, data_range, k):
        # 读取数据
        self.file_path = file_path
        self.data_range = data_range
        self.k = k
        self.__load_data()


class K_means(Data):
    C = []  # 簇集
    distance = []  # 样本与均值向量的距离
    tag = []  # 簇标记
    C_tag = {}  # 划分后的样本

    # 计算欧式距离
    def __distance(self, d1, d2):
        distance_square = 0.0

        for i in range(0, len(d1) - 1):
            distance_square += (d1[i] - d2[i]) ** 2
        return np.sqrt(distance_square)

    # 计算向量的模
    def __module(self, d):
        distance_square = 0.0

        for i in range(0, len(d) - 1):
            distance_square += d[i] ** 2
        return np.sqrt(distance_square)

    def __divide(self):
        # 计算样本xj与各均值向量的距离
        for j in range(0, len(self.D) - 1):
            self.distance[j] = []
            for i in range(0, len(self.C)):
                self.distance[j].append(self.__distance(self.D[j], self.C[i]))

        # 根据距离最近的均值向量确定簇标记
        for i in range(0, len(self.D) - 1):
            self.tag.append(self.distance[i].index(min(self.distance[i])))

        # 将样本划入相应的簇
        for j in range(0, len(self.C) - 1):
            self.C_tag[self.C[j]] = []  # 初始化划分后的样本（定义key为簇）
        for i in range(0, len(self.D) - 1):
            self.C_tag[self.C[self.tag[i]]].append(self.D[i])

    def __calculating(self):
        op = 0
        C_origin = copy.deepcopy(self.C)  # 用于暂存原始的簇集
        average = 0.0

        for i in range(0, len(self.C) - 1):
            # 计算新均值向量：
            for j in range(0, self.data_range[1] - self.data_range[0] - 1):
                for k in range(0, len(self.C[i] - 1)):
                    average += self.C[i][k]
            self.C[i] = average /
            if not (operator.eq(C_origin[i], self.C[i])):
                op += 1  # 当前均值向量改变了
        return op

    def __init__(self, file_path, data_range, k):
        # 初始化数据
        super(Data, self).__init__(file_path, data_range, k)
        op = 1
        while op != 0:
            self.__divide()  # 划分簇
            op = self.__calculating()  # 计算新的均值向量


class DBI(object):


"""（用两个颜色（或者图形）表示标签和聚类结果）
class PCA(object):
    # 降维

    # 可视化展示
    def data_visualization(self):
        col = ['HotPink', 'Aqua', 'Chartreuse', 'yellow', 'LightSalmon']
        for i in range(self.k):
            plt.scatter(self.D[i][0], self.D[i][1], linewidth=10, color=col[i])
            plt.scatter([e[0] for e in self.C[i]], [e[1] for e in self.C[i]], color=col[i])
        plt.show()

    def __init__(self):
        pass
"""

if __name__ == '__main__':
    d1 = Data(file_path='zoo.data', data_range=[1, 17], k=3)
