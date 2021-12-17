# coding:utf-8
import datetime


# class and global variable

class account:
    operator = []
    opera_data = []
    opera_type = []
    opera_value = []
    opera_currency = None
    total_value = 0.00
    opera_times = 0
    opera_total_value = []

    def __init__(self):
        self.opera_currency = input('请输入要创建帐户的币种：')

    def operating(self, op):
        if op == '0':
            self.__withdraw()
        elif op == '1':
            self.__deposit()
            self.operator.append(op)
        elif op == '3':
            self.print()
        else:
            print('输入的操作码有误，请重新输入！')
            return -1  # -1码提醒程序需要重新获取用户输入

    def __deposit(self):
        value = float(input('请输入要存入的金额：'))
        if value <= 0:
            print('输入了错误的金额！')
            self.__deposit()
        self.opera_times += 1
        self.opera_data.append(datetime.date.today())
        self.opera_value.append(value)
        self.total_value += value
        self.opera_total_value.append(self.total_value)
        return 0

    def __withdraw(self):
        op = input('0：转出' + '\n' + '2：网转' + '\n' + '请选择取款方式：')
        if op != '0' and op != '2':
            print('输入了错误的操作码!')
            return -1
        print('目前余额为：{}'.format(self.total_value))
        value = float(input('请输入要取出的金额：'))
        if value <= 0 or value > self.total_value:
            print('输入了错误的金额！')
            return -1
        self.opera_times += 1
        self.opera_data.append(datetime.date.today())
        self.operator.append(op)
        self.opera_type.append(0)
        self.opera_value.append(value)
        self.total_value -= value
        self.opera_total_value.append(self.total_value)
        return 0

    def print(self):
        import prettytable as pt
        op = None
        tb = pt.PrettyTable()
        tb.field_names = ['交易日期', '摘要', '金额', '币种', '余额']
        for i in range(self.opera_times - 1, 0, -1):
            self.opera_value[i] = '%.2f' % self.opera_value[i]
            self.opera_total_value[i] = '%.2f' % self.opera_total_value[i]
            if self.operator[i] == '0':
                op = '消费'
                value = '-' + self.opera_value[i]
            elif self.operator[i] == '1':
                op = '转入'
                value = '+' + self.opera_value[i]
            elif self.operator[i] == '2':
                op = '网转'
                value = '-' + self.opera_value[i]
            tb.add_row([self.opera_data[i], op, value, self.opera_currency, self.opera_total_value[i]])
        print(tb)


if __name__ == '__main__':
    bank_account = account()
    operator = None
    while operator != '-1':
        operator = input('0：取款' + '\n' + '1：存款' + '\n' + '3：打印流水' + '\n' + '-1：退出' + '\n'
                         + '请选择要办理的业务：')
        if operator == '-1':
            break
        elif bank_account.operating(operator) == -1:
            continue
