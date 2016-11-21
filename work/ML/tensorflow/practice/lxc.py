#!/usr/bin/env python
# coding=utf-8

import tensorflow as tf

matrix1 = tf.constant([[3.,3.]])
matrix2 = tf.constant([[2.],[3,]])

product = tf.matmul(matrix1 , matrix2)

sess = tf.Session()

result = sess.run(product)

print result

sess.close()
