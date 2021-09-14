# coding:utf-8
import math
import jieba
"""
这个程序用于完成简易的论文查重功能
使用的计算论文相似度的方法是：Cosine Similarity（余弦相似度文本比较法）
使用的词语权重计算方法是：Term frequency-Inverse document frequency（TF-IDF）
"""
# Class and Global Variable
#class Word:


# Function
def read_papers():
    with open("orig.txt", "r", encoding='UTF-8') as paper1:  # 打开文件
        origin_paper_string = jieba.lcut(paper1.read(), use_paddle = False, cut_all = False)  # 读取文件
        print(origin_paper_string)
    with open("orig_0.8_add.txt", "r", encoding='UTF-8') as paper2:  # 打开文件
        exam_paper_string1 = jieba.lcut(paper2.read(), use_paddle = False, cut_all = False)  # 读取文件

    with open("orig_0.8_del.txt", "r", encoding='UTF-8') as paper3:  # 打开文件
        exam_paper_string2 = jieba.lcut(paper3.read(), use_paddle = False, cut_all = False)  # 读取文件

    with open("orig_0.8_dis_1.txt", "r", encoding='UTF-8') as paper4:  # 打开文件
        exam_paper_string3 = jieba.lcut(paper4.read(), use_paddle = False, cut_all = False)  # 读取文件

    with open("orig_0.8_dis_10.txt", "r", encoding='UTF-8') as paper5:  # 打开文件
        exam_paper_string4 = jieba.lcut(paper5.read(), use_paddle = False, cut_all = False)  # 读取文件

    with open("orig_0.8_dis_15.txt", "r", encoding='UTF-8') as paper6:  # 打开文件
        exam_paper_string5 = jieba.lcut(paper6.read(), use_paddle = False, cut_all = False)  # 读取文件

    return origin_paper_string, exam_paper_string1, exam_paper_string2, exam_paper_string3, exam_paper_string4, exam_paper_string5
# 读取需要对比的论文文档

def weight_calculation(word, paper1, paper2, files_quantity = 2):
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
        idf[i] = math.log(files_quantity /(files_include_words[i] + 1))

    # 计算权重
    for i in word_list:
       weight[i] = tf[i] * idf[i]

    weight_after_sorting = sorted(weight.items(), key = lambda x:x[1], reverse = True)
    return weight_after_sorting
# 词频统计

def vector_calculation(weight1, weight2):
    # variable definition
    vector2 = []  # 用于存放第二篇文章的向量

    word_list = weight1.keys()  # 创建一个以第一篇文章的高频词为模板的词组列表
    vector1 = list(weight1.values())  # 直接导出第一篇文章的向量

    # 计算第二篇文章的向量
    j = 0
    for i in word_list:
        vector2[j] = weight2[i]
        j += 1

    return vector1, vector2
# 向量计算

def cosine_calculation(v1, v2):
    # variable definition
    vector1 = v1[0: 19]
    vector2 = v2[0: 19]
    numerator = None  # 用于存放分子的运算结果
    denominator1 = None  # 用于存放向量1的模的平方
    denominator2 = None  # 用于存放向量2的模的平方

    # 计算分子的值
    for i in range(0, 19):
        numerator += vector1[i] * vector2[i]

    # 计算两个向量的模的平方
    for i in range(0, 19):
        denominator1 += vector1[i] * vector1[i]
        denominator2 += vector2[i] * vector2[i]

    # 计算余弦值
    cos = numerator / (math.sqrt(denominator1) * math.sqrt(denominator2))

    return cos
# 余弦相似度计算

# Entrance
if __name__ == '__main__':
    read_papers()

