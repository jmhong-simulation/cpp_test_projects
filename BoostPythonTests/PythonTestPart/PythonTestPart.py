import tensorflow as tf
import numpy as np

sess = tf.InteractiveSession()

input = tf.placeholder(tf.float32, [None, 1, 1])
target = tf.placeholder(tf.float32, [None, 1, 1])

pp = (input, 1)
print(type(pp))

ka = {'activation' : tf.nn.tanh}
print(type(ka))

def run_with_pos_key(positional, keywords, function):
    return function(*positional, **keywords)

temp = run_with_pos_key(pp, ka, tf.layers.dense) # equavalent to temp = tf.layers.dense(*pp, **ka)
#temp = tf.layers.dense(inputs = input, units = 1, activation = tf.nn.tanh)
loss = tf.losses.mean_squared_error(target, temp)
train = tf.train.AdamOptimizer(1e-1).minimize(loss)

x_input = np.ones((1, 1, 1), 'f')
y_target = np.ones((1, 1, 1), 'f')

init_op = tf.global_variables_initializer()
sess.run(init_op)

for i in range(0, 20):
    y_out, lo, _ = sess.run([temp, loss, train], {input: x_input, target : y_target})
    print(y_out, " ", lo)

# data type check version
#import tensorflow as tf
#import numpy as np

#sess = tf.InteractiveSession()

#data_type = tf.float32
#dense_shape_size = [1, 1]

#none_type_object = None
#dense_shape = [none_type_object]
#dense_shape.extend(dense_shape_size)
#print(dense_shape)

#input = tf.placeholder(data_type, dense_shape, "input")
#temp = tf.layers.dense(input, 1)

#print(type(data_type))
#print(type(None))
#print(type(dense_shape))

#x_input = np.ones((1, 1, 1), 'f')

#init_op = tf.global_variables_initializer()
#sess.run(init_op)

#feed_dict = {input: x_input}
#print(type(feed_dict))
#y_out = sess.run([temp], feed_dict)

#print(y_out)