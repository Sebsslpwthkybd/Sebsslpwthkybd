# coding:utf-8

import gui
import main


def correct():
    correct = []
    error = []

    for i in range(0, int(gui.exercise_quantity)):
        if gui.answer[i] == correct_answer[i]:
            correct.append(i)
        else:
            error.append(i)
    mark = {'correct_order':correct, 'error_order':error}

    return mark
