# coding:utf-8


class Create_table(object):
    sql_statement = []

    def start_transaction(self):
        self.sql_statement.append("set session transaction isolation level "
                                  "read committed;")

    def add_create_sql_statement(self, sql=""):
        self.sql_statement.append("create table branch ("
                                  "branch_name          varchar(50)         not null,"
                                  "branch_city          varchar(50)         null,"
                                  "branch_assets        decimal(18,4)       null,"
                                  "constraint PK_BRANCH primary key nonclustered (branch_name)"
                                  ");")

        self.sql_statement.append("create table staff ("
                                  "staff_id             char(18)            not null,"
                                  "manager_id           char(18)            null,"
                                  "branch_name          varchar(50)         not null,"
                                  "staff_name           varchar(20)         null,"
                                  "staff_tel            varchar(20)         null,"
                                  "staff_addr           varchar(50)         null,"
                                  "start_time           datetime            null,"
                                  "constraint PK_STAFF primary key nonclustered (staff_id)"
                                  ");")

        self.sql_statement.append("create table customer("
                                  "customer_id          char(18)            not null,"
                                  "loan_id              varchar(20)         null,"
                                  "customer_name        varchar(20)         null,"
                                  "customer_tel         varchar(25)         null,"
                                  "customer_address     varchar(50)         null,"
                                  "contact_name         varchar(25)         null,"
                                  "contact_tel          varchar(25)         null,"
                                  "contact_emai         varchar(25)         null,"
                                  "relationship         varchar(25)         null,"
                                  "constraint PK_CUSTOM primary key nonclustered(customer_id)"
                                  ");")

        self.sql_statement.append("create table account ("
                                  "account_id           varchar(20)         not null,"
                                  "branch_name          varchar(50)         not null,"
                                  "account_balance      decimal(18,4)       null,"
                                  "constraint PK_ACCOUNT primary key nonclustered (account_id)"
                                  ");")

        self.sql_statement.append("create table loan ("
                                  "loan_id              varchar(20)         not null,"
                                  "branch_name          varchar(50)         not null,"
                                  "loan_sum             decimal(18,4)       null,"
                                  "constraint PK_LOAN primary key nonclustered (loan_id)"
                                  ");")

        self.sql_statement.append("create table checkAccount ("
                                  "account_id           varchar(20)         not null,"
                                  "branch_name          varchar(50)         null,"
                                  "account_balance      decimal(18,4)       null,"
                                  "overdraft            decimal(18,4)       null,"
                                  "constraint PK_CHECKACCOUNT primary key (account_id)"
                                  ");")

        self.sql_statement.append("create table have ("
                                  "account_id           varchar(20)          not null,"
                                  "customer_id          char(18)             not null,"
                                  "recent_time          datetime             null,"
                                  "constraint PK_HAVE primary key (account_id, customer_id)"
                                  ");")

        self.sql_statement.append("create table payment ("
                                  "loan_id              varchar(20)          not null,"
                                  "pay_time             datetime             not null,"
                                  "pay_sum              decimal(18,4)        null,"
                                  "constraint PK_PAYMENT primary key nonclustered (loan_id, pay_time)"
                                  ");")

        self.sql_statement.append("create table responsible ("
                                  "staff_id             char(18)             not null,"
                                  "customer_id          char(18)             not null,"
                                  "identities           varchar(20)          null,"
                                  "constraint PK_RESPONSIBLE primary key (staff_id, customer_id)"
                                  ");")

        self.sql_statement.append("create table savingAccount ("
                                  "account_id           varchar(20)          not null,"
                                  "branch_name          varchar(50)          null,"
                                  "account_balance      decimal(18,4)        null,"
                                  "rate                 decimal(8,3)         null,"
                                  "constraint PK_SAVINGACCOUNT primary key (account_id)"
                                  ");")

    def add_constraints_sql_statement(self):
        self.sql_statement.append("alter table account "
                                  "add constraint FK_ACCOUNT_OPEN_BRANCH foreign key (branch_name) "
                                  "references branch (branch_name);"
                                  )

        self.sql_statement.append("alter table checkAccount "
                                  "add constraint FK_CHECKACC_CAINHERIT_ACCOUNT foreign key (account_id) "
                                  "references account (account_id) "
                                  "on delete cascade "
                                  "on update no action;"
                                  )

        self.sql_statement.append("alter table customer "
                                  "add constraint FK_CUSTOM_APPLY_LOAN foreign key (loan_id) "
                                  "references loan (loan_id);"
                                  )

        self.sql_statement.append("alter table have "
                                  "add constraint FK_HAVE_HAVE_ACCOUNT foreign key (account_id) "
                                  "references account (account_id);"
                                  )

        self.sql_statement.append("alter table have "
                                  "add constraint FK_HAVE_HAVE2_CUSTOM foreign key (customer_id) "
                                  "references customer (customer_id);"
                                  )

        self.sql_statement.append("alter table loan "
                                  "add constraint FK_LOAN_GRANT_BRANCH foreign key (branch_name) "
                                  "references branch (branch_name);"
                                  )

        self.sql_statement.append("alter table payment "
                                  "add constraint FK_PAYMENT_LOAN_PAY_LOAN foreign key (loan_id) "
                                  "references loan (loan_id) "
                                  "on delete cascade "
                                  "on update no action;"
                                  )

        self.sql_statement.append("alter table responsible "
                                  "add constraint FK_RESPONSI_RESPONSIB_STAFF foreign key (staff_id) "
                                  "references staff (staff_id);"
                                  )

        self.sql_statement.append("alter table responsible "
                                  "add constraint FK_RESPONSI_RESPONSIB_CUSTOM foreign key (customer_id) "
                                  "references customer (customer_id);"
                                  )

        self.sql_statement.append("alter table savingAccount "
                                  "add constraint FK_SAVINGAC_SAINERITA_ACCOUNT foreign key (account_id) "
                                  "references account (account_id) "
                                  "on delete cascade "
                                  "on update no action;"
                                  )

        self.sql_statement.append("alter table staff "
                                  "add constraint FK_STAFF_LEAD_STAFF foreign key (manager_id) "
                                  "references staff (staff_id);"
                                  )

        self.sql_statement.append("alter table staff "
                                  "add constraint FK_STAFF_WORK_BRANCH foreign key (branch_name) "
                                  "references branch (branch_name);"
                                  )

    def end_transaction(self):
        self.sql_statement.append("commit;")

    def rollback(self):
        self.sql_statement.append("rollback;")

    def create_table(self):
        cmd = self.con.cursor()
        self.add_create_sql_statement()
        self.add_constraints_sql_statement()

        # 建表
        try:
            for i in range(0, len(self.sql_statement) - 1):
                cmd.execute(self.sql_statement[i])
        except Exception as e:
            print('执行创建不成功，错误信息：%s' % e)
            self.rollback()
        else:
            self.end_transaction()
        finally:
            cmd.execute(self.sql_statement[-1])

    def __init__(self, con):
        self.con = con
        self.create_table()
