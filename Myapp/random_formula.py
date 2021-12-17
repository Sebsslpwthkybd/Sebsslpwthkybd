# coding:utf-8
import random
import main
from main import *


# function
# 随机一个数字
def random_number(minimum, maximum, number):
    """
    随机一个分数
    """
    gui.minimum = 0
    gui.maximum = 1
    if maximum <= 1:
        number.integer = 0
        number.numerator = random.randint(gui.minimum, gui.maximum)
        number.denominator = random.randint(number.numerator, gui.maximum)
    else:
        maximum_integer = maximum - 1
        number.integer = random.randint(minimum, maximum_integer)
        number.denominator = random.randint(minimum, maximum)
        number.numerator = random.randint(minimum, number.denominator)


# 随机生成一个运算符
def random_operator():
    operator_list = ['+', '-', '*', '/']
    return random.choice(operator_list)


# 随机两个数和一个运算符
def random_block(minimum, maximum, form=None):
    op = random_operator()
    first_number = main.proper_fraction(0, 1, 1)
    second_number = main.proper_fraction(0, 1, 1)
    if form is None:  # 如果式子并未传入，则直接生成完整的子式
        random_number(minimum, maximum, first_number)
        form = [first_number, op]
        if op == '-':  # 如果是减号，则被减数的上限应小于等于减数
            maximum = main.calculating_number(main.calculating([first_number]))
            random_number(minimum, maximum, second_number)
        else:
            random_number(minimum, maximum, second_number)
        form.append(second_number)
        return form
    else:  # 运算符右边已有元素，直接生成左边元素和运算符即可
        if op == '-':  # 如果是减号，则减数的下限应大于等于被减数
            minimum = main.calculating_number(main.calculating(form))
            maximum += minimum
        random_number(minimum, maximum, first_number)
        new_form = [first_number, op]
        if isinstance(form, list):
            new_form.extend(form)
        else:
            new_form.append(form)
        return new_form


# 返回运算符的数量
def random_operator_quantity():
    return random.randint(1, 3)


"""def random_brackets(brackets_quantity):
    if brackets_quantity == 0:
        return None
    elif brackets_quantity == 1:
        starting_position = random.randrange(0, 4, 2)
        ending_position = random.randrange(starting_position + 4, 8, 2)
        return [starting_position, ending_position]
    else:
        if random.randint(0, 1) == 0:  # 0代表两个括号不存在包含与被包含关系
            starting_position1 = 0
            ending_position1 = 4
            starting_position2 = 6
            ending_position2 = 10
        else:
            starting_position1 = random.choice([0, 2])
            ending_position1 = random.choice([starting_position1 + 7, 12])
            starting_position2 = random.choice([starting_position1 + 1, starting_position1 + 3, ending_position1 - 4])
            ending_position2 = starting_position2 + 4
        return [starting_position1, ending_position1, starting_position2, ending_position2]"""


# 随机一条算式
def random_formula(minimum, maximum):
    form = main.formula
    op = random_operator_quantity()

    if op == 1:  # 只有一个运算符，意味着没有括号，直接生成
        form.equation = random_block(minimum, maximum)
    elif op == 2:  # 有两个运算符
        """brackets_quantity = random.choice([0, 1])
        if brackets_quantity == 0:"""
        form.equation = (random_block(minimum, maximum))
        form.equation = (random_block(minimum, maximum, form.equation))
        """
        else:
            starting_position = random.choice([0, 2])
        form.equation = (random_block(minimum, maximum))
        form.equation = (random_block(minimum, maximum, form.equation))
        """
    else:
        form.equation = (random_block(minimum, maximum))
        form.equation = (random_block(minimum, maximum, form.equation))
        form.equation = (random_block(minimum, maximum, form.equation))
        """brackets_quantity = random.randint(0, 2)
        if brackets_quantity == 1:
            starting_position = random.choice([0, 2])
            brackets_position = [starting_position, starting_position + 4]
        else:
            brackets_position = random_brackets(brackets_quantity)"""
    form.result = main.calculating(form.equation)
    return form


# 随机指定数量的算式
def random_formula_list(quantity, minimum, maximum):
    formula_dict = []
    formula_answer = []

    for i in range(0, int(quantity)):
        formula_dict.append(random_formula(minimum, maximum))
        print(main.print_formula(formula_dict[i].equation))
        formula_answer.append(formula_dict[i].result)
    return formula_dict, formula_answer
