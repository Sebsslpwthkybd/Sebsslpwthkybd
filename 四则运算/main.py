# coding:utf-8

# class and global variables
class formula:
    equation = []
    result = None

    def __init__(self, equation, result):
        self.equation = equation
        self.result = result


class proper_fraction:
    integer = 0
    numerator = None
    denominator = None

    def __init__(self, integer, numerator, denominator):
        self.integer = integer
        self.numerator = numerator
        self.denominator = denominator


# function
# 真分数加法
def add_proper_fraction(num1, num2):
    result = proper_fraction
    result.denominator = num1.denominator * num2.denominator
    numerator = num1.numerator * num2.denominator + num2.numerator * num1.denominator
    if numerator < 1:
        result.integer = num1.integer + num2.integer
        result.numerator = numerator
    else:
        result.integer = num1.integer + num2.integer + 1
        result.numerator = numerator - result.denominator
    result.numerator, result.denominator = reduce_fraction(result.numerator, result.denominator)
    return result


# 真分数减法
def subtract_proper_fraction(num1, num2):
    result = proper_fraction
    result.denominator = num1.denominator * num2.denominator
    numerator = num1.numerator * num2.denominator - num2.numerator * num1.denominator
    if numerator < 1:
        result.integer = num1.integer - num2.integer - 1
        result.numerator = numerator + result.denominator
    else:
        result.integer = num1.integer - num2.integer
        result.numerator = numerator
    result.numerator, result.denominator = reduce_fraction(result.numerator, result.denominator)
    return result


# 约分(默认传入为真分数)
def reduce_fraction(numerator, denominator):
    for i in range(numerator, 1, -1):
        if numerator % i == 0 and denominator % i == 0:
            numerator /= i
            denominator /= i
    return numerator, denominator


# 真分数乘法
def multiply_proper_fraction(num1, num2):
    result = proper_fraction
    result.numerator = (num1.numerator + (num1.integer * num1.denominator)) * \
                       (num2.numerator + (num2.integer * num2.denominator))
    result.denominator = num1.denominator * num2.denominator
    if result.numerator > result.denominator:
        result.integer = result.numerator // result.denominator
        result.numerator -= result.denominator * result.integer
    else:
        result.integer = 0
    result.numerator, result.denominator = reduce_fraction(result.numerator, result.denominator)
    return result


# 真分数除法
def divide_proper_fraction(num1, num2):
    result = proper_fraction
    numerator_num1 = num1.numerator + num1.integer * num1.denominator
    numerator_num2 = num2.numerator + num2.integer * num2.denominator
    result.numerator = numerator_num1 * num2.denominator
    result.denominator = numerator_num2 * num1.denominator
    if result.numerator > result.denominator:
        result.integer = result.numerator // result.denominator
        result.numerator -= result.denominator * result.integer
    else:
        result.integer = 0
    result.numerator, result.denominator = reduce_fraction(result.numerator, result.denominator)
    return result
