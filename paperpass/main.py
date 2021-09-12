# coding:utf-8
import math
"""
这个程序用于完成简易的论文查重功能
使用的计算论文相似度的方法是：余弦相似度文本比较法
使用的词语权重计算方法是：term frequency_inverse document frequency（TF-IDF）
"""
# Class and Global Variable
#class Word:


# Function

def weight_calculation(word, files_quantity, paper1, paper2):
    # variable definition
    word_list = set(word)  # 创建一个不可重复的词集合
    times_per_word = {}  # 用于存放词频
    files_include_words = {}  # 用于存放包含该词的文件数
    times_each_word = len(word)  # 记录所有词的数目
    tf = {}
    idf = {}  # tf、idf列表用于记录词频与逆向文件频率
    weight = {}  # 用于保存TF-IDF值

    # 计算每个词出现的次数
    for i in word_list:
        for j in word:
            if i == j:
                times_per_word[i] += 1

    # 计算包含词语的文件数
    for i in word_list:
        for j in range(0, len(word_list) - 1):
            if i in paper1[j]:
                files_include_words[i] += 1
                break
        for j in range(0, len(word_list) - 1):
            if i in paper2[j]:
                files_include_words[i] += 1
                break

    # 计算词频TF
    for i in word_list:
        tf[i] = times_per_word[i] / times_each_word

    # 计算逆向文本频率IDF
    for i in word_list:
        idf[i] = math.log(files_quantity /files_include_words[i])

    # 计算权重
    for i in word_list:
       weight[i] = tf[i] * idf[i]

    return weight
# 词频统计

#def compare(weight):
# 余弦相似度比较


# Entrance
if __name__ == '__main__':

