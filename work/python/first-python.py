import tensorflow as tf

hello = tf.constant('Hello,Tensorflow!')
sess = tf.Session()
print sess.run(hello)

a = tf.constant(10)

b = tf.constant(10)

print sess.run(a+b)
