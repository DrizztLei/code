# -*- coding: utf-8 -*-

import numpy as np


'''读取训练数据[N*K,D]'''
'''读取训练数据[N*K,D]'''
# 每个类中的样本数
N = 10

# 维度1*201
D = 201

# 类别个数0-9
K = 5

# 样本input
X = np.zeros((N*K,D)) 

# 类别标签
y = np.zeros(N*K, dtype='uint8') 

file = open('./Data/a.txt')

lines = file.readlines()

strdata = []

for line in lines:

    strdata.append(line.split(' '))

data = np.array(strdata).flatten()

data[data == ''] = 0.0

data = data.astype(np.float)

j = 0

for i in range(data.shape[0] - 1):

  if(i%202 == 0 and i !=0):

    print data[i - 1] , data[i - 2]
    




