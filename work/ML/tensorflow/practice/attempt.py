#!/usr/bin/python
# coding=utf-8

import tensorflow as tf
import os as linux
import numpy as np


x = tf.constant(2)

y = tf.constant(2)

sess = tf.Session()

result = sess.run(x*y)

print result

sess.close()
