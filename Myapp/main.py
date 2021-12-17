# coding:utf-8

# class and global variables
import copy
import gui
import random_formula

global formulas


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
    return int(numerator), int(denominator)


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


# 计算一个算式的值
def calculating(formula):
    new_formula = copy.deepcopy(formula)  # 保护原有式子不损坏

    i = 2  # 从第二个数字开始
    while len(new_formula) != 1 and len(new_formula) - 1 >= i:  # 检测是否为乘号或除号
        if new_formula[i - 1] == '*':
            result = multiply_proper_fraction(new_formula[i - 2], new_formula[i])  # 进行一次乘法运算
            del new_formula[i - 2:i + 1]
            new_formula.insert(i - 2, result)
            i = 2  # 重新开始遍历
            continue
        elif new_formula[i - 1] == '/':
            result = divide_proper_fraction(new_formula[i - 2], new_formula[i])
            del new_formula[i - 2:i + 1]
            new_formula.insert(i - 2, result)
            i = 2  # 重新开始遍历
            continue
        i += 2  # 让index（i）指向下一个数字的位置

    i = 2  # 从第一个运算符开始
    while len(new_formula) != 1 and len(new_formula) - 1 >= i:  # 检测加号和减号
        if new_formula[i - 1] == '+':
            result = add_proper_fraction(new_formula[i - 2], new_formula[i])
            del new_formula[i - 2:i + 1]
            new_formula.insert(i - 2, result)
            i = 2  # 重新开始遍历
            continue
        elif new_formula[i - 1] == '-':
            result = subtract_proper_fraction(new_formula[i - 2], new_formula[i])
            del new_formula[i - 2:i + 1]
            new_formula.insert(i - 2, result)
            i = 2  # 重新开始遍历
            continue
        i += 2  # 让index（i）指向下一个数字的位置

    return new_formula[0]


# 计算数字的大小
def calculating_number(number):
    if number.denominator == 0:
        return number.numerator
    else:
        return int(number.numerator / number.denominator) + number.integer


# 把数字变成可以直观看见的字符串
def print_number(number):
    if number.numerator != 0:  # 分数部分不为零
        if number.numerator != number.denominator:  # 分数部分不为1/1
            number.numerator, number.denominator = reduce_fraction(number.numerator, number.denominator)  # 将分数部分约分至最简
            return str(number.integer) + "'" + str(number.numerator) + '/' + str(number.denominator)
        else:
            return str(number.integer + 1)  # 分数部分为1/1，直接返回整数部分+1结果
    else:
        return str(number.integer)  # 分数部分分子为零，直接返回整数部分


# 把公式中的数字都变为可以直观看见的字符串
def print_formula(formula):
    str_formula = []
    for i in range(0, len(formula)):
        if isinstance(formula[i], str):
            str_formula.append(formula[i])
        else:
            str_formula.append(print_number(formula[i]))
    return str_formula


# 比对输入的答案和正确答案并返回正确和错误的题号
def correct(correct_answer):
    correct_number = []
    error = []

    for i in range(0, int(gui.exercise_quantity)):
        if gui.answer[i] == correct_answer[i]:
            correct_number.append(i)
        else:
            error.append(i)
    student_mark = {'correct_order': correct_number, 'error_order': error}

    return student_mark


if __name__ == '__main__':
    formula_dict = []
    formula_answer = []

    # 载入用户界面
    gui.Entrance()

    # 用户选择了自动生成公式
    if gui.create_formula:
        maximum = int(gui.maximum)
        minimum = int(gui.minimum)
        exercise_quantity = gui.exercise_quantity

        # 随机生成四则运算
        formula_dict, formula_answer = random_formula.random_formula_list(exercise_quantity, minimum, maximum)
        global formulas
        formulas = copy.deepcopy(formula_dict)
        gui.Create_Formula()

        # 批改
        mark = correct(formula_answer)
        gui.Choose_save_path(mark)

        gui.Result_print(formula_dict)