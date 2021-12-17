# coding:utf-8
import mysql.connector


class connect_to_root(object):
    config = {
        "host" : "", "port" : "",
        "user" : "root", "password" : "",
        "database" : ""
    }

    def connecting(self):
        self.con = mysql.connector.connect(**self.config)
        return self.con

    def disconnecting(self):
        self.con.close()
