import numpy as np
import pandas as pd

data  = pd.read_excel('week01-data.xlsx')
train_data = data.iloc[:10]
test_data = data.iloc[10:]

X_train = np.array(train_data[['抽問分數', '作業平均', '測驗平均']]) * 0.008 # 10*3
y_train = np.array(train_data['總成績']) * 0.008 # 1*10
X_test = np.array(test_data[['抽問分數', '作業平均', '測驗平均']]) * 0.008 # 4*3
y_test = np.array(test_data['總成績']) * 0.008 # 1*4

def sigmoid(x):
    return 1 / (1 + np.exp(-x))

np.random.seed(10)

# 初始化 weight 和 bias
w1 = 2 * np.random.random((3,4)) - 1 # 3*4
b1 = 2 * np.random.random((1,4)) - 1 # 1*4
w2 = 2 * np.random.random((4,2)) - 1 # 4*2
b2 = 2 * np.random.random((1,2)) - 1 # 1*2
w3 = 2 * np.random.random((2,1)) - 1 # 2*1
b3 = 2 * np.random.random((1,1)) - 1 # 1*1

learning_rate = 0.1
num_iterations = 100000

for i in range(num_iterations):
    # 前向傳播
    hidden_layer_input = np.dot(X_train, w1) + b1
    hidden_layer_output = sigmoid(hidden_layer_input)
    second_layer_input = np.dot(hidden_layer_output, w2) + b2
    second_layer_output = sigmoid(second_layer_input)
    output_layer_input = np.dot(second_layer_output, w3) + b3
    output_layer_output = sigmoid(output_layer_input)

    # 計算誤差
    output_error = y_train.reshape((-1,1)) - output_layer_output
    second_error = np.dot(output_error * output_layer_output * (1 - output_layer_output), w3.T)
    hidden_error = np.dot(second_error * second_layer_output * (1 - second_layer_output), w2.T)

    # 反向傳播
    w3 += learning_rate * np.dot(second_layer_output.T, output_error * output_layer_output * (1 - output_layer_output))
    b3 += learning_rate * np.sum(output_error * output_layer_output * (1 - output_layer_output), axis=0, keepdims=True)
    w2 += learning_rate * np.dot(hidden_layer_output.T, second_error * second_layer_output * (1 - second_layer_output))
    b2 += learning_rate * np.sum(second_error * second_layer_output * (1 - second_layer_output), axis=0, keepdims=True)
    w1 += learning_rate * np.dot(X_train.T, hidden_error * hidden_layer_output * (1 - hidden_layer_output))
    b1 += learning_rate * np.sum(hidden_error * hidden_layer_output * (1 - hidden_layer_output), axis=0, keepdims=True)

    # 每迭代1000次輸出訓練成果
    if i%1000 == 0:
        print("\n第"+str(i)+"次訓練資料預測總成績:")
        print(output_layer_output / 0.008)


first_neuron_input = np.dot(X_train, w1) + b1
first_neuron_output = sigmoid(first_neuron_input)
second_neuron_input = np.dot(first_neuron_output, w2) + b2
second_neuron_output = sigmoid(second_neuron_input)
third_neuron_input = np.dot(second_layer_output, w3) + b3
y_train_pred = (sigmoid(third_neuron_input) / 0.008).round()
train_mse = np.mean((y_train_pred.T - y_train.T / 0.008) ** 2)
print('\n\nTrain Mean Square Error:', train_mse)

first_neuron_input = np.dot(X_test, w1) + b1
first_neuron_output = sigmoid(first_neuron_input)
second_neuron_input = np.dot(first_neuron_output, w2) + b2
second_neuron_output = sigmoid(second_neuron_input)
third_neuron_input = np.dot(second_neuron_output, w3) + b3
y_test_pred = (sigmoid(third_neuron_input) / 0.008).round()
test_mse = np.square(np.subtract(y_test_pred.T, y_test.T / 0.008)).mean()
print('Test Mean Square Error:', test_mse)

print("\n測試資料預測總成績:")
print(y_test_pred)
