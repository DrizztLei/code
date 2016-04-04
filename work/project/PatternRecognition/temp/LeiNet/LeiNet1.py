# -*- coding: utf-8 -*-

import numpy as np


import matplotlib.pyplot as plt

'''读取训练数据[N*K,D]'''
# 每个类中的样本数
N = 10

# 维度1*201
D = 201

# 类别个数0-9
K = 6

# 样本input
X = np.zeros((N*K,D)) 

# 类别标签
y = np.zeros(N*K, dtype='uint8') 

file = open('./Data/train.txt')

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

    y[j] = data[i - 1]

    j += 1
  
  
  elif(j < N*K):
    
    X[j][i%202 - 1] = data[i]

    
'''读取测试数据[NC*K,D]'''

# 总样本数
NC = 28

# 测试样本input
XC = np.zeros((NC,D)) 

# 测试样本类别标签
yC = np.zeros(NC, dtype='uint8') 

file = open('./Data/test.txt')

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

    yC[j] = data[i - 1]

    j += 1
  
  
  elif(j < NC):
    
    XC[j][i%202 - 1] = data[i]

 
'''双隐层神经网络 '''
# 随机初始化参数

#迭代次数
rangeN = 12000

#可视化相关变量
#损失
losspoint = np.zeros((rangeN))

#准确度
accuracy_t = np.zeros((rangeN))
accuracy_v = np.zeros((rangeN))

# 隐层大小
h1 = 30

h2 = 30

# 第一层：W1权重（D*h） b1偏移（h个）
W1 = 0.01 * np.random.randn(D,h1)
b1 = np.zeros((1,h1))

# 第二层：W2权重（h*K） b2偏移（K个）
W2 = 0.01 * np.random.randn(h1,h2)
b2 = np.zeros((1,h2))

# 第三层：W3权重（h*K） b3偏移（K个）
W3 = 0.01 * np.random.randn(h2,K)
b3 = np.zeros((1,K))

#步长
step_size = 1e-2

#正则化系数
reg = 1e-2

model = {}

#点的个数(300)
num_examples = X.shape[0]

# 梯度迭代与循环
for i in xrange(rangeN):

  '''计算类别得分'''
  #2层神经网络的前向计算
  hidden_layer1 = np.maximum(0, np.dot(X, W1) + b1) #使用的ReLU神经元
  hidden_layer2 = np.maximum(0, np.dot(hidden_layer1, W2) + b2)
  scores = np.dot(hidden_layer2, W3) + b3

  '''计算类别概率（Softmax函数）'''
  # 用指数函数还原
  exp_scores = np.exp(scores) 
  # 归一化
  probs = exp_scores / np.sum(exp_scores, axis=1, keepdims=True) # [N x K]

  '''计算损失loss(包括互熵损失和正则化部分)'''
  #互熵损失
  corect_logprobs = -np.log(probs[range(num_examples),y])
  data_loss = np.sum(corect_logprobs)/num_examples

  #正则化部分
  reg_loss = 0.5*reg*np.sum(W1*W1) + 0.5*reg*np.sum(W2*W2) + 0.5*reg*np.sum(W3*W3)

  #损失
  loss = data_loss + reg_loss

  if i % 1 == 0:
    print "iteration %d: loss %f" % (i, loss)

  # 计算得分上的梯度
  dscores = probs
  dscores[range(num_examples),y] -= 1
  dscores /= num_examples

  # 梯度回传
  dW3 = np.dot(hidden_layer2.T, dscores)
  db3 = np.sum(dscores, axis=0, keepdims=True)

  dhidden2 = np.dot(dscores, W3.T)

  dhidden2[hidden_layer2 <= 0] = 0

  dW2 = np.dot(hidden_layer1.T, dhidden2)
  db2 = np.sum(dhidden2, axis=0, keepdims=True)

  dhidden = np.dot(dhidden2, W2.T)

  dhidden[hidden_layer1 <= 0] = 0

  # 拿到最后W,b上的梯度
  dW1 = np.dot(X.T, dhidden)
  db1 = np.sum(dhidden, axis=0, keepdims=True)

  # 加上正则化梯度部分
  dW3 += reg * W3
  dW2 += reg * W2
  dW1 += reg * W1

  # 参数迭代与更新
  W1 += -step_size * dW1
  b1 += -step_size * db1
  W2 += -step_size * dW2
  b2 += -step_size * db2
  W3 += -step_size * dW3
  b3 += -step_size * db3

  model = { 'W1': W1, 'b1': b1, 'W2': W2, 'b2': b2, 'W3': W3, 'b3': b3}
  
  #计算分类准确度
  hidden_layer1 = np.maximum(0, np.dot(X, W1) + b1) #使用的ReLU神经元
  hidden_layer2 = np.maximum(0, np.dot(hidden_layer1, W2) + b2)
  scores = np.dot(hidden_layer2, W3) + b3
  predicted_class = np.argmax(scores, axis=1)
  ta = np.mean(predicted_class == y)
  print 'training accuracy:   %.4f' % (ta)

  #计算测试准确度
  hidden_layer1 = np.maximum(0, np.dot(XC, W1) + b1) #使用的ReLU神经元
  hidden_layer2 = np.maximum(0, np.dot(hidden_layer1, W2) + b2)
  scores = np.dot(hidden_layer2, W3) + b3
  predicted_class = np.argmax(scores, axis=1)
  va = np.mean(predicted_class == yC)
  print 'validation accuracy: %.4f' % (va)

  #记录损失
  losspoint[i] = loss

  #记录准确率
  accuracy_t[i] = ta
  accuracy_v[i] = va


#绘制
plt.subplot(1, 2, 1)

plt.plot(losspoint)

plt.xlabel('epoch')
plt.ylabel('loss')

plt.title('loss Test')

plt.subplot(1, 2, 2)

plt.plot(accuracy_t)
plt.plot(accuracy_v)

plt.xlabel('epoch')
plt.ylabel('accuracy')

plt.title('accuracy Test')

plt.legend(['training accuracy:', 'validation accuracy:'])

plt.show()
  




