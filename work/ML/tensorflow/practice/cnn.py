#!/usr/bin/env python
# coding=utf-8
import tensorflow as tf

def foo():
    print ("Function for foo")


if __name__ == "__main__":
    weight = tf.Variable(tf.random_normal([0,1] , stddev=0.1) , name="weight")
    biases = tf.Variable(tf.random_normal([0,2] , stddev=0.5) , name="biases")
    tf.initialize_all_tables()

    print weight
