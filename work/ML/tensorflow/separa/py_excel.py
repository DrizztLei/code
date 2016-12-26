# -*- coding: utf-8 -*-

import xlrd

FILE = '/home/elvis/DATASET/SCORE/bc/lda.xlsx'


def open_excel(file):
    try:
        data = xlrd.open_workbook(file)
        return data
    except Exception, e:
        print str(e)


def excel_table_byindex(file, colnameindex=0, by_index=0):
    data = open_excel(file)
    table = data.sheets()[by_index]
    nrows = table.nrows
    ncols = table.ncols
    colnames = table.row_values(colnameindex)
    list = []
    for rownum in range(1, nrows):

        row = table.row_values(rownum)
        if row:
            app = {}
            for i in range(len(colnames)):
                app[colnames[i]] = row[i]
            list.append(app)
    return list


def excel_table_byname(file, colnameindex=0, by_name=u'Sheet1'):
    data = open_excel(file)
    table = data.sheet_by_name(by_name)
    nrows = table.nrows  # 行数
    colnames = table.row_values(colnameindex)  # 某一行数据
    list = []
    for rownum in range(1, nrows):
        row = table.row_values(rownum)
        if row:
            app = {}
            for i in range(len(colnames)):
                app[colnames[i]] = row[i]
            list.append(app)
    return list


def main():
    tables = excel_table_byindex(FILE)

    for row in tables:
        print row
        directory = row[u'balance-scale']
        print (directory)
        score_a = row[5.0]
        score_b = row[1.0]
        print (score_a)
        print (score_b)

    """
    tables = excel_table_byname(FILE)
    for row in tables:
        print row
    """

if __name__ == "__main__":
    main()
