from fractions import Fraction


const_frac = Fraction(0, 1)

# 检查题目是否重复
def check_rep(rep, table):
    if str(rep) in table: return False          #若有重复的式子，返回False
    const_op = ("+", "-", "×", "÷")           #固定的算术符号

    op = []
    cnt_op = 0
    for i in rep:
        if i in const_op:
            cnt_op += 1
            op.append(i)

    #运算式只有1个运算符

    if cnt_op == 1:
        if op[0] == "-" or op[0] == "÷":
            table[str(rep)] = True
            return True
        tmp = rep                                       #将该式子交换，若交换后结果相同，返回False
        tmp[0], tmp[2] = tmp[2], tmp[0]

        if str(tmp) in table:
            return False
        else:                                          #否则，说明两式子不同，返回True
            table[str(tmp)] = True
            table[str(rep)] = True
            return True
    #2个运算符
    elif cnt_op == 2:
        if op[0] == "-" or op[0] == "÷":
            if op[1] == "-" or op[1] == "÷":
                table[str(rep)] = True
                return True

        pos = -1
        for i in range(len(rep)):
            if rep[i] == "(": pos = i                   #若式子的第i个位置出现左括号

        #交换
        if rep[pos + 2] == "+" or rep[pos + 2] == "×":  #左括号右边出现“+”或“*”
            if rep[pos + 1] > rep[pos + 3]:
              rep[pos + 1], rep[pos + 3] = rep[pos + 3], rep[pos + 1]
                                                        #让检测位继续往后
              tmp = ["("] +\
              [rep[pos + 1]] +\
              [rep[pos + 2]] +\
              [rep[pos + 3]] + [")"]

        #另一个运算符和运算数，首先将运算符置为空，运算数置为0
        anot_op = ""
        anot_num = 0

        for i in range(0, max(0, pos)):
            if anot_op != "" and anot_num != 0:
                break
            if rep[i] in const_op:
                anot_op = rep[i]
            else:
                anot_num = rep[i]

        for i in range(len(rep)):
            if rep[i] == ")":
                pos = i

        if pos == -1:                           #若检测到在最后一位，将检测位拨回到开始
            pos = 2

        for i in range(pos + 1, len(rep)):
            if anot_op != "" and anot_num != 0:
                break
            if rep[i] in const_op:
                anot_op = rep[i]
            else:
                anot_num = rep[i]

        #合并到tmp
        tmp = tmp + [anot_op] + [anot_num]

        if str(tmp) in table:
            return False
        else:
            table[str(tmp)] = True
            table[str(rep)] = True
            return True
    #3个运算符
    else:
        table[str(rep)] = True
        return True
