#!/usr/bin/env python
# coding=utf-8
import numpy as np

num = 1000
set = []
for i in xrange(num):
    x1 = np.random.normal(0.0 , 0.55)
    y1 = x1 * 0.1 + 0.3 + np.random.normal(0.0 , 0.03)
    set.append([x1 , y1])

x_data = [v[0] for v in set]
y_data = [v[1] for v in set]

import matplotlib.pyplot as plt

plt.plot(x_data , y_data , 'ro' , label='Original')
plt.legend()
plt.show()

import tensorflow as tf

W = tf.Variable(tf.random_uniform([1] , -1.0 , 1.0))
b = tf.Variable(tf.zeros([1]))
y = W * x_data + b

loss = tf.reduce_sum(tf.square(y - y_data))
optimizer = tf.train.GradientDescentOptimizer(0.5)
train = optimizer.minimize(loss)

init = tf.initialize_all_variables()

sess = tf.Session()
sess.run(init)

for step in xrange(8):
    
    sess.run(train)

    print (step , sess.run(W) , sess.run(b))
    print (step , sess.run(loss))

    plt.plot(x_data , y_data , 'ro')
    plt.plot(x_data , sess.run(W) * x_data + sess.run(b))
    plt.xlabel('x')
    plt.xlim(-2,2)
    plt.ylim(0.1,0.6)
    plt.ylabel('y')
    plt.legend()
    plt.show()

sess.close()
