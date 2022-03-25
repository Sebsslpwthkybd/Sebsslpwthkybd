# coding:utf-8

import sys
import random
import datetime


class RangeError(Exception):
    def __init__(self, message):
        self.message = message


class GuessError(Exception):
    def __init__(self, message):
        self.message = message


class Guess(object):
    real_range = []
    times = 0

    def __check_range(self):
        if self.real_range[0] == self.real_range[1]:
            raise RangeError('您输入的区间数字相同！！请重新启动程序。')
        elif self.real_range[0] > self.real_range[1]:
            raise RangeError('您输入的数字区间大小有误！！请重新启动程序。')
        else:
            print('所产生的随机数字区间为: {}'.format(self.str_range))

    def __str_to_int(self):
        try:
            for i in self.str_range:
                self.real_range.append(int(i))
        except ValueError:
            raise RangeError('您输入的为非数字字符，请重新启动！')

    def __get_number(self):
        self.number = random.randint(self.real_range[0], self.real_range[1])

    def __write_log(self, guess_number):
        with open('record.txt', 'a+', encoding='gbk') as f:
            current_time = datetime.datetime.now()
            current_time_str = current_time.strftime('%H:%M:%S')
            f.write('{} 玩家猜测次数：{} 本次猜测的具体数字：{}\n'.format(current_time_str, self.times, guess_number))

    def compete(self, guess_number):
        if self.real_range[0] > guess_number or self.real_range[1] < guess_number:
            raise RangeError('对不起您输入的数字未在指定区间！！！')
        elif guess_number == self.number:
            self.times += 1
            print('*' * 10)
            print('恭喜您！只用了{}次就赢得了游戏'.format(self.times))
            return 1  # correct
        elif guess_number > self.number:
            self.times += 1
            self.__write_log(guess_number)
            raise GuessError('Lower than the answer')
        elif guess_number < self.number:
            self.times += 1
            self.__write_log(guess_number)
            raise GuessError('Higher than the answer')

    def __init__(self, min, max):
        self.str_range = list(filter(lambda x: x.isdigit(), [min, max]))

        self.__str_to_int()

        self.__check_range()

        self.__get_number()


if __name__ == '__main__':
    print('*' * 34 + '欢迎进入数字猜猜猜小游戏' + '*' * 34)

    minimum = input('数字区间起始值:')
    maximum = input('数字区间终止值:')
    op = None

    try:
        game = Guess(minimum, maximum)
    except RangeError as e:
        print(e)
        sys.exit()

    while 1:
        try:
            op = game.compete(int(input('请继续输入您猜测的数字:')))
        except GuessError as e:
            print('*' * 10)
            print(e)
        except RangeError as e:
            print(e)
        except ValueError:
            print('您输入的并非数字，请重新输入！')

        if op: quit()
