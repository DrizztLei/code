#!/usr/bin/env python
# coding=utf-8

import input_data
import tensorflow as tf

mnist = input_data.read_data_sets("/tmp/mnist" , one_hot=True)

x = tf.placeholder("float" , [None , 784] )
W = tf.Variable(tf.zeros([784 , 10]))
b = tf.Variable(tf.zeros([10]))
y = tf.nn.softmax(tf.matmul(x,W) + b)

y_ = tf.placeholder("float" , [None , 10])
cross_entropy = -tf.reduce_sum(y_*tf.log(y))

train_setp = tf.train.GradientDescentOptimizer(0.01).minimize(cross_entropy)
init = tf.initialize_all_variables()
sess = tf.Session()

sess.run(init)

for i in range(1001) :

    batch_xs,batch_ys = mnist.train.next_batch(100)
    sess.run(train_setp , feed_dict={x:batch_xs , y:batch_ys})

correct_prediction = tf.equal(tf.argmax(y,1) , tf.argmax(y_ , 1))

accuracy = tf.reduce_mean(tf.cast(correct_prediction , "float"))

print sess.run(accuracy , feed_dict = {x:mnist.test.images,y_:mnist.test.labels})

sess.close()
