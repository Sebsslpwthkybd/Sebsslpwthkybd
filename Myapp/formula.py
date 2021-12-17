# coding:utf-8
import random
from main import *
import datetime


# function
# 随机一个数字
class formula:
    equation = []  # 用于存放对应运算符的数字
    operator = []  # 用于存放运算符
    result = None

    def __init__(self, equation, operator, result):
        self.equation = equation
        self.operator = operator
        self.result = result


class Random_formula(object):
    form = formula

    def __random_number(self, minimum, maximum, number):
        """
        随机一个分数
        """
        if maximum == 1:
            number.integer = 0
        else:
            number.integer = random.randint(minimum, maximum - 1)
        number.denominator = random.randint(minimum, maximum)
        number.numerator = random.randint(minimum, number.denominator)

    # 随机生成一个运算符
    def __random_operator(self):
        operator_list = ['+', '-', '*', '/']
        return random.choice(operator_list)

    # 随机生成一个运算符的四则运算
    def random_formula(self, minimum, maximum):
        op = self.__random_operator()
        self.form.operator.append(op)
        random.seed(2)
        first_number = proper_fraction(0, 1, 1)
        second_number = proper_fraction(0, 1, 1)
        random.seed(datetime.datetime.microsecond)
        if self.form.equation is None:  # 如果式子并未传入，则直接生成完整的子式
            self.__random_number(minimum, maximum, first_number)
            self.form.equation.append(first_number)
            if op == '-':  # 如果是减号，则被减数的上限应小于等于减数
                maximum = int(calculating(self.form.equation[0]))
                self.__random_number(minimum, maximum, second_number)
            else:
                self.__random_number(minimum, maximum, second_number)
            form.append(second_number)
        else:  # 运算符右边已有元素，直接生成左边元素和运算符即可
            if op == '-':  # 如果是减号，则减数的下限应大于等于被减数
                minimum = int(calculating(self.form.equation))
            self.__random_number(minimum, maximum, first_number)
            self.form.equation.append(first_number)

    def __init__(self, minimum, maximum):
        for i in range(0, random.randint(2, 4)):
            self.random_formula(minimum, maximum)
