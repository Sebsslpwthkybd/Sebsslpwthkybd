# coding:utf-8
import math
import jieba

"""
这个程序用于完成简易的论文查重功能
使用的计算论文相似度的方法是：Cosine Similarity（余弦相似度文本比较法）
使用的词语权重计算方法是：Term frequency-Inverse document frequency（TF-IDF）
"""


# Class and Global Variable
# class Word:


# Function
def read_papers(paper1, paper2):
    with open(paper1, "r", encoding='UTF-8') as paper1:  # 打开文件
        origin_paper_string = jieba.lcut(paper1.read(), use_paddle=False, cut_all=False)  # 读取文件

    with open(paper2, "r", encoding='UTF-8') as paper2:  # 打开文件
        exam_paper_string = jieba.lcut(paper2.read(), use_paddle=False, cut_all=False)  # 读取文件

    return origin_paper_string, exam_paper_string

# 读取需要对比的论文文档


def weight_calculation(word, paper, files_quantity=2):
    # variable definition
    word_list = set(word)  # 创建一个不可重复的词集合
    times_per_word1 = {}  # 用于存放第一篇文章的词频
    times_per_word2 = {}  # 用于存放第二篇文章的词频
    files_include_words = {}  # 用于存放包含该词的文件数
    times_each_word = len(word)  # 记录所有词的数目
    tf1 = {}
    tf2 = {}
    idf = {}  # tf、idf列表用于记录词频与逆向文件频率
    weight1 = {}  # 用于保存第一篇文章的TF-IDF值
    weight2 = {}  # 用于保存第二篇文章的TF-IDF值

    # 初始化字典
    for i in word_list:
        times_per_word1[i] = 0
        times_per_word2[i] = 0
        files_include_words[i] = 0

    # 计算每个词出现的次数
    for i in word_list:
        for j in word:
            if i == j:
                times_per_word1[i] += 1
        for j in paper:
            if i == j:
                times_per_word2[i] += 1

    # 计算包含词语的文件数
    for i in word_list:
        for j in range(0, len(word_list) - 1):
            if i in word[j]:
                files_include_words[i] += 1
                break
        for j in range(0, len(word_list) - 1):
            if i in paper[j]:
                files_include_words[i] += 1
                break

    # 计算词频TF
    for i in word_list:
        tf1[i] = times_per_word1[i] / times_each_word
        tf2[i] = times_per_word2[i] / times_each_word

    # 计算逆向文本频率IDF
    for i in word_list:
        idf[i] = math.log(files_quantity / (files_include_words[i] + 1))

    # 计算权重
    for i in word_list:
        weight1[i] = '%.8f' % (tf1[i] * idf[i])
        weight2[i] = '%.8f' % (tf2[i] * idf[i])

    # 将词语以权重降序形式排列
    w1 = sorted(weight1.items(), key=lambda x: x[1], reverse=True)

    return w1, weight2

# 词频统计


def vector_calculation(weight1, weight2):
    # variable definition
    vector1 = []
    vector2 = []  # 用于存放文章的向量
    word_list = []

    # 由于使用sorted函数会将字典变为包含元组的列表，此循环可以将元组里的词和其权重拆分
    for i in range(0, 40):
        """请注意，此处range参数决定了查重精度，务必选择在安全的范围内（内存不溢出且精度不要过小），
        此处不选择让用户定义主要是因为参数错误可能会导致发生重大错误！！！
        """
        n_str1 = []

        str1 = str(weight1[i]).split(',')
        n_str1.append(str1[0].lstrip('(').strip("'"))
        n_str1.append(str1[1].rstrip(')').lstrip(' ').strip("'"))
        word_list.append(n_str1[0])
        vector1.append(float(n_str1[1]))

    for i in word_list:
        v = float(weight2[i].strip("'"))
        vector2.append(v)

    return vector1, vector2

# 向量计算


def cosine_calculation(v1, v2):
    numerator = 0  # 用于存放分子的运算结果
    denominator1 = 0  # 用于存放向量1的模的平方
    denominator2 = 0  # 用于存放向量2的模的平方

    # 计算分子的值
    for i in range(0, len(v1)-1):
        numerator += (v1[i] * v2[i])

    # 计算两个向量的模的平方
    for i in range(0, len(v1)-1):
        denominator1 += v1[i] * v1[i]
        denominator2 += v2[i] * v2[i]

    # 计算余弦值
    cos = '%.3f' % (numerator / (math.sqrt(denominator1) * math.sqrt(denominator2)))

    return cos

# 余弦相似度计算


# Entrance
if __name__ == '__main__':
    weight0 = {}
    weight1 = {}
    v1 = []
    v2 = []

    # 导入文章
    paper1_path = input('请输入第一篇文章的完整路径：')
    paper2_path = input('请输入第二篇文章的完整路径：')

    case_paper, test_paper = read_papers(paper1_path, paper2_path)

    weight0, weight1 = weight_calculation(case_paper, test_paper)

    v1, v2 = vector_calculation(weight0, weight1)

    similarity = float(cosine_calculation(v1, v2))
    similarity *= 100

    print('两篇文章的相似度为:' + str(similarity) + '%')
