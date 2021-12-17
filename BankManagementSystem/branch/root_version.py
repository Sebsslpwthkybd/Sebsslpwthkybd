# coding:utf-8
import connect_to_mysql


class branch(object):
    branch_name = None
    branch_city = None
    branch_assets = None

    def __init__(self, branch_name, branch_city, branch_assets):
        self.branch_name = branch_name
        self.branch_city = branch_city
        self.branch_assets = branch_assets


class Branch_operating(object):
    def __execute_sql(self, sql):
        try:
            cursor = self.con.cursor()
            cursor.execute(sql)
            return cursor
        except Exception as e:
            return -1, e

    # 添加一个新的支行
    def add_branch(self, branch_name, branch_city, branch_assets):
        sql = "INSERT INTO branch(branch_name, branch_city, branch_assets) VALUES({}, {}, {});"\
            .format(branch_name, branch_city, branch_assets)
        self.__execute_sql(sql)

    # 删除一个支行的所有信息
    def delete_branch(self, branch_name):
        sql = "DELETE FROM branch WHERE branch_name={};"\
            .format(branch_name)
        self.__execute_sql(sql)

    # 更改一个支行的信息
    def update_branch(self, branch_name, branch_city, branch_assets):
        sql = "SET branch_city={},branch_assets={} WHERE branch_name={};"\
            .format(branch_city, branch_assets, branch_name)
        self.__execute_sql(sql)

    # 查找支行的信息
    def seek_branch(self, branch_field, op):

        if op == 0:  # 查询指定名称的支行
            sql = "SELECT * FROM branch WHERE branch_name = {};" \
                .format(branch_field)
        elif op == 1:  # 查询资产条件符合的支行
            sql = "SELECT * FROM branch WHERE branch_assets {};"\
                .format(branch_field)
        else:  # 查询一个城市所有的支行
            sql = "SELECT * FROM branch WHERE branch_city = {};" \
                .format(branch_field)

        self.__execute_sql(sql)

        # 接收查询结果并返回

    def finish_operating(self):
        self.con.close()

    def __init__(self):
        # 连接数据库
        self.con = connect_to_mysql.connect_to_root.connecting()
