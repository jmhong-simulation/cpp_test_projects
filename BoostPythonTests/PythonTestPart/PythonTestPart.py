import tensorflow as tf
import numpy as np

sess = tf.InteractiveSession()

input = tf.placeholder(tf.float32, [None, 1])
target = tf.placeholder(tf.float32, [None, 1])


pp = (input, 1)
print(type(pp))

ka = {'inputs' : input, 'units' : 1, 'activation' : tf.nn.tanh, 'name' : 'temp_dense'}
print(type(ka))

def run_with_pos_key(positional, keywords, function):
    return function(*positional, **keywords)

#temp = run_with_pos_key(pp, ka, tf.layers.dense) 
temp = tf.layers.dense(**ka)
print(temp)

# 1. default way
# temp = tf.layers.dense(inputs = input, units = 1, activation = tf.nn.tanh)

# 2. using positional/keyword argumetns
# pp = (input, 1)
# print(type(pp))
# ka = {'activation' : tf.nn.tanh}
# print(type(ka))
# temp = tf.layers.dense(*pp, **ka)

# 3. using executer function
# def run_with_pos_key(positional, keywords, function):
#    return function(*positional, **keywords)
# temp = run_with_pos_key(pp, ka, tf.layers.dense) 

loss = tf.losses.mean_squared_error(*(target, temp))
train = tf.train.AdamOptimizer(1e-1).minimize(loss)

x_input = np.ones((1, 1), 'f')
y_target = np.ones((1, 1), 'f')

#print([tensor.name for tensor in tf.get_default_graph().as_graph_def().node])

init_op = tf.global_variables_initializer()
sess.run(init_op)

for i in range(0, 20):
    # temp = tf.get_default_graph().get_tensor_by_name('temp_dense/Tanh:0') # find by node name
    y_out, lo, _ = sess.run([tf.get_default_graph().get_tensor_by_name('temp_dense/Tanh:0'), loss, train], {input: x_input, target : y_target})
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