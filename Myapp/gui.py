# coding:utf-8
import copy
import tkinter as tk
from tkinter.filedialog import *
from tkinter import scrolledtext
import chardet
import correct

import main

global exercise_quantity
global maximum
global minimum
global create_formula
global answer


class Entrance(object):
    """
    窗口的入口
    在此窗口选择一个模式（上传题目和答案进行评改或由系统自动生成题目）
    """
    def go_load_formula(self):
        self.root.destroy()
        Load_formula()

    def go_set_range(self):
        self.root.destroy()
        Set_range()

    def __init__(self):
        self.root = tk.Tk()
        self.root.title('Myapp')

        # 选择提交给定的题目
        self.button1 = tk.Button(self.root, text='上传题目并批改', command=self.go_load_formula)

        # 选择由系统生成题目
        self.button2 = tk.Button(self.root, text='自动生成小学四则运算题目', command=self.go_set_range)

        # 设定大小和位置
        self.button1.grid(row=1, column=0, padx=5, pady=3)
        self.button2.grid(row=2, column=0, padx=5, pady=3)

        self.root.mainloop()


class Load_formula(object):
    """
    读取上传的题目
    """
    formula_paper = None

    def search_file(self):
        file_path = askopenfilename()
        self.read_file_path.set(file_path)
        self.read_file()

    def read_file(self):
        full_path = self.read_file_path.get()
        with open(full_path, 'rb') as data:
            code_format = chardet.detect(data.read())['encoding']
        with open(full_path, 'r', encoding=code_format) as txt1:  # 打开文件
            self.formula_paper = txt1.read()  # 读取文件

    def go_load_answer(self):
        self.root.destroy()
        Load_answer()

    def __init__(self):
        self.root = tk.Tk()
        self.root.title('Myapp')
        self.read_file_path = tk.StringVar()
        self.read_file_name = tk.StringVar()

        # 选择要读取的题目目录
        self.tip1 = tk.Label(self.root, text='选择要读取的题目的路径')
        self.txt1 = tk.Entry(self.root, textvariable=self.read_file_name)
        self.button1 = tk.Button(self.root, text='点击选择', command=self.search_file)

        # 接收答案
        self.button2 = tk.Button(self.root, text='选择提交答案的路径', command=self.go_load_answer)

        # 设定大小和位置
        self.tip1.grid(row=1, column=0, padx=5, pady=3)
        self.txt1.grid(row=1, column=1, padx=5, pady=3)
        self.button1.grid(row=1, column=2, padx=5, pady=3)
        self.button2.grid(row=2, column=1, padx=5, pady=3)

        self.root.mainloop()


class Set_range(object):
    """
    设定生成题目范围的数据
    """
    exercise_quantity = 0  # 生成题目的个数
    exercise_range = []  # 题目中数值的范围

    def go_produce(self):
        global exercise_quantity
        exercise_quantity = self.txt1.get()

        global minimum
        minimum = self.txt2.get()

        global maximum
        maximum = self.txt3.get()

        self.root.destroy()
        global create_formula
        create_formula = True

    def __init__(self):
        self.root = tk.Tk()
        self.root.title('Myapp')

        # 设定题目数量
        self.tip1 = tk.Label(self.root, text='输入需要生成的题目数量：')
        self.txt1 = tk.Entry(self.root)

        # 设定数值范围
        self.tip2 = tk.Label(self.root, text='题目中数值（自然数、真分数和真分数分母）的下限为：')
        self.txt2 = tk.Entry(self.root)

        self.tip3 = tk.Label(self.root, text='题目中数值（自然数、真分数和真分数分母）的上限为：')
        self.txt3 = tk.Entry(self.root)

        self.button1 = tk.Button(self.root, text='开始生成题目', command=self.go_produce)

        # 设定大小和位置
        self.tip1.grid(row=1, column=0, padx=5, pady=3)
        self.txt1.grid(row=1, column=1, padx=5, pady=3)
        self.tip2.grid(row=2, column=0, padx=5, pady=3)
        self.txt2.grid(row=2, column=1, padx=5, pady=3)
        self.tip3.grid(row=3, column=0, padx=5, pady=3)
        self.txt3.grid(row=3, column=1, padx=5, pady=3)
        self.button1.grid(row=4, column=1, padx=5, pady=3)

        self.root.mainloop()


class Create_Formula(object):
    """
    生成题目
    """

    def go_save(self):
        self.root.destroy()
        Load_answer()

    def output_file(self):
        file_path = askdirectory()
        self.output_file_path.set(file_path)
        self.file_save()

    def file_save(self):
        full_path = self.output_file_path.get() + '/Problems.txt'
        with open(full_path, 'w') as file:
            for i in range(0, int(exercise_quantity)):
                formula = main.print_formula(main.formulas[i].equation)
                print(str(i) + str(formula))
                str_formula = formula[0] + ' '
                for j in range(1, len(formula)):
                    str_formula = str_formula + formula[j] + ' '
                file.writelines(str(i) + '、' + str_formula + '=' + ' ' + '\n')

    def __init__(self):
        self.root = tk.Tk()
        self.root.title('Myapp')
        self.output_file_path = tk.StringVar()

        # 生成题目
        self.tip1 = tk.Label(self.root, text='生成成功！')

        # 保存题目
        self.tip2 = tk.Label(self.root, text='选择保存题目文件的路径')
        self.txt2 = tk.Entry(self.root, textvariable=self.output_file_path)
        self.button2 = tk.Button(self.root, text='点击选择', command=self.output_file)

        # 收集答案
        self.button1 = tk.Button(self.root, text='提交答案', command=self.go_save)

        # 设定大小和位置
        self.tip1.grid(row=1, column=1, padx=5, pady=3)
        self.button1.grid(row=3, column=1, padx=5, pady=3)
        self.tip2.grid(row=2, column=0, padx=5, pady=3)
        self.txt2.grid(row=2, column=1, padx=5, pady=3)
        self.button2.grid(row=2, column=2, padx=5, pady=3)

        self.root.mainloop()


class Load_answer(object):
    """
    读取答案
    """
    answer = []

    def search_file(self):
        file_path = askopenfilename()
        self.read_file_path.set(file_path)
        self.read_file()

    def read_file(self):
        txt1_data = []
        full_path = self.read_file_path.get()
        with open(full_path, 'rb') as data:
            code_format = chardet.detect(data.read())['encoding']
        with open(full_path, 'r', encoding=code_format) as txt1:  # 打开文件
            for i in range(0, int(exercise_quantity)):
                txt1_data.append(txt1.readline())  # 读取文件
                if txt1_data[i].endswith('\n'):
                    new_answer_i = txt1_data[i].rstrip('\n').split('、')
                else:
                    new_answer_i = txt1_data[i].split('、')
                self.answer.append(new_answer_i[1])
        global answer
        answer = self.answer

    def go_choose_save_path(self):
        self.root.destroy()

    def __init__(self):
        self.root = tk.Tk()
        self.root.title('Myapp')
        self.read_file_path = tk.StringVar()
        self.read_file_name = tk.StringVar()

        # 选择要读取的目录
        self.tip1 = tk.Label(self.root, text='选择要提交的答案的路径')
        self.txt1 = tk.Entry(self.root, textvariable=self.read_file_name)
        self.button1 = tk.Button(self.root, text='点击选择', command=self.search_file)

        # 保存文件
        self.button2 = tk.Button(self.root, text='选择保存结果的路径', command=self.go_choose_save_path)

        # 设定大小和位置
        self.tip1.grid(row=1, column=0, padx=5, pady=3)
        self.txt1.grid(row=1, column=1, padx=5, pady=3)
        self.button1.grid(row=1, column=2, padx=5, pady=3)
        self.button2.grid(row=2, column=1, padx=5, pady=3)

        self.root.mainloop()


class Choose_save_path(object):
    """
    让用户选择保存答案的路径
    并输出成绩及对错题的统计结果到指定路径下的Grade.txt文件中
    """
    correct_number = None
    incorrect_number = None

    def output_file(self):
        file_path = askdirectory()
        self.output_file_path.set(file_path)
        self.file_save()

    def file_save(self):
        full_path = self.output_file_path.get() + '/Grade.txt'
        self.correct_number = self.mark['correct_order']
        self.incorrect_number = self.mark['error_order']
        with open(full_path, 'w') as file:
            file.write('Correct: ' + str(len(self.correct_number)) + ' ' + str(tuple(self.correct_number)) + '\n')
            file.write('Wrong: ' + str(len(self.incorrect_number)) + ' ' + str(tuple(self.incorrect_number)))

    def go_print(self):
        self.root.destroy()

    def __init__(self, mark):
        self.mark = mark
        self.root = tk.Tk()
        self.root.title('Myapp')
        self.output_file_path = tk.StringVar()

        # 选择要保存的目录
        self.tip1 = tk.Label(self.root, text='选择保存成绩文件的路径')
        self.txt1 = tk.Entry(self.root, textvariable=self.output_file_path)
        self.button1 = tk.Button(self.root, text='点击选择', command=self.output_file)

        # 保存文件
        self.button2 = tk.Button(self.root, text='打印正确答案', command=self.go_print)

        # 设定大小和位置
        self.tip1.grid(row=1, column=0, padx=5, pady=3)
        self.txt1.grid(row=1, column=1, padx=5, pady=3)
        self.button1.grid(row=1, column=2, padx=5, pady=3)
        self.button2.grid(row=3, column=1, padx=5, pady=3)

        self.root.mainloop()


class Result_print(object):
    """
    打印正确答案
    """
    def outro(self):
        self.root.destroy()

    def output_file(self):
        file_path = askdirectory()
        self.output_file_path.set(file_path)
        self.file_save()

    def file_save(self):
        full_path = self.output_file_path.get() + '/Correct answer.txt'
        with open(full_path, 'w') as file:
            for i in range(0, int(exercise_quantity)):
                result = self.formula_dict[i].result
                file.write(str(i + 1) + '、' + str(result) + '\n')

    def __init__(self, formula_dict):
        self.root = tk.Tk()
        self.root.title('Myapp')
        self.output_file_path = tk.StringVar()
        self.formula_dict = copy.deepcopy(formula_dict)

        # 保存答案
        self.tip2 = tk.Label(self.root, text='选择保存答案文件的路径')
        self.txt2 = tk.Entry(self.root, textvariable=self.output_file_path)
        self.button2 = tk.Button(self.root, text='点击选择', command=self.output_file)

        # 退出
        self.button1 = tk.Button(self.root, text='退出', command=self.outro)

        # 设定大小和位置
        self.button1.grid(row=2, column=1, padx=5, pady=3)
        self.tip2.grid(row=1, column=0, padx=5, pady=3)
        self.txt2.grid(row=1, column=1, padx=5, pady=3)
        self.button2.grid(row=1, column=2, padx=5, pady=3)

        self.root.mainloop()


if __name__ == '__main__':
    Entrance()




