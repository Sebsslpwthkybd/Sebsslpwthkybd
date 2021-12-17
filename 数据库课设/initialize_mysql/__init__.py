# coding:utf-8
import mysql.connector
from . import connect_to_mysql


class Database_connection_failed(Exception):
    def __init__(self, message):
        self.message = message


def connect():
    config = {
        'host': 'localhost', 'user': 'root',
        'password': 'Paul34252780*', 'port': 3306,
        'database': 'demo'
    }
    try:
        connect_to_mysql.Connecting(config)
    except mysql.connector.errors.ProgrammingError:
        raise Database_connection_failed('警告：连接数据库失败！请检查连接信息')
