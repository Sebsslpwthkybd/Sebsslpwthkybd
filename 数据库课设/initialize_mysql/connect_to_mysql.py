# coding:utf-8
import mysql.connector
from .import create_table


class Connecting(object):
    def connecting(self):  # 连接至数据库
        self.con = mysql.connector.connect(**self.config)

    def do(self):  # 要对数据库执行的操作
        create_table.Create_table(self.con)

    def disconnecting(self):  # 断开与数据库的连接
        self.con.close()

    def __init__(self, config):
        self.config = config
        self.connecting()
        self.do()
        self.disconnecting()
