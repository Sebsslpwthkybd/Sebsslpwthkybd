# coding:utf-8
import unittest
from random_formula import *
import main


class Test_random_formula(unittest.TestCase):
    def test_random_number(self):
        number = main.proper_fraction
        random_number(0, 10, number)
        print('随机出来的带分数：' + str(number.integer) + "'" + str(number.numerator) + '/' + str(number.denominator))

    def test_random_operator(self):
        print('随机出来的运算符：' + random_operator())

    """def test_random_brackets(self):
        print('random_brackets(1):' + str(random_brackets(1)))
        print('random_brackets(2):' + str(random_brackets(2)))
        print('random_brackets(3):' + str(random_brackets(3)))"""

    def test_random_block(self):
        test1 = [proper_fraction(1, 5, 6), '+', proper_fraction(2, 7, 8), '+', proper_fraction(8, 1, 6)]
        result1 = random_block(1, 10)
        result2 = random_block(1, 10, form=test1)
        print('生成新算式：' + print_number(result1[0]) + ' ' + result1[1] + ' ' + print_number(result1[2]))
        print('继续补充已有的算式：' + print_number(result2[0]) + ' ' + result2[1] + ' ' + print_number(result2[2])
              + ' ' + result2[3] + ' ' + print_number(result2[4]) + ' ' + result2[5] + ' ' + print_number(result2[6]))
        print('三个运算符的结果：' + str(calculating_number(calculating(result2))))


if __name__ == '__main__':
    unittest.main()
