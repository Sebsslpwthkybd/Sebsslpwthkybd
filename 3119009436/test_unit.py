# coding:utf-8
import unittest
import main
import coverage

# Test case
class Test_case(unittest.TestCase):
    # 等待接收测试用例
    paper1_path = r'D:\code\Sebsslpwthkybd\3119009436\test_paper\orig.txt'
    paper2_path = r'D:\code\Sebsslpwthkybd\3119009436\test_paper\orig_0.8_add.txt'

    # 错误的路径
    error_path = 'C:/1.txt'

    # 文件后缀错误的文件路径
    error_file_type1 = r'D:\code\Sebsslpwthkybd\3119009436\test_paper\1.pptx'

    # 用于测试weight_calculation函数
    __test_paper1 = ['我', '是', '我', '是', '我', '塞巴斯', '\n', '。', '，']
    __test_paper2 = ['我', '是', '是', '塞巴斯', '塞巴斯', '塞巴斯', '\n', '。', '，']

    # 用于测试vector_calculation函数
    __test_weight1 = [('我', '1'), ('是', '2'), ('计科国际班', '3'), ('抱着键盘睡觉的sebs', '4')]
    __test_weight2 = {'我': '7', '是': '8', '抱着键盘睡觉的sebs': '6', '计科国际班': '5'}

    # 用于测试余弦相似度的运算
    __test_vector1 = [6, 8, 10]
    __test_vector2 = [6, 8, 10]

    '''def __init__(self, paper1, paper2, ans_paper, error_file):
        self.paper1_path = paper1
        self.paper2_path = paper2
        self.answer_path = ans_paper
        self.errorFileType = error_file'''

    def test_get_encoding(self):
        with self.assertRaises(UnicodeDecodeError):
            main.read_papers(self.error_file_type1, self.paper2_path)

    def test_read(self):  # 测试读取文本和分词是否成功
        with self.assertRaises(FileNotFoundError):
            main.read_papers(self.error_path, self.paper2_path)
        paper1, paper2 = main.read_papers(self.paper1_path, self.paper2_path)
        self.assertNotEqual(paper1, [])
        self.assertNotEqual(paper2, [])

    def test_weight(self):  # 测试sorted函数是否正常运转
        test_result1, test_result2 = main.weight_calculation(self.__test_paper1, self.__test_paper2)
        for i in test_result1:
            self.assertEqual(str(type(i)), "<class 'tuple'>")

    def test_vector(self):  # 测试向量的运算
        vector1, vector2 = main.vector_calculation(self.__test_weight1, self.__test_weight2, len(self.__test_weight1))
        self.assertEqual(vector1, [1, 2, 3, 4])
        self.assertEqual(vector2, [7, 8, 5, 6])

    def test_cos(self):  # 测试余弦相似度的计算
        self.assertEqual(main.cosine_calculation(self.__test_vector1, self.__test_vector1), '1.000')


if __name__ == '__main__':
    unittest.main()
