import numpy as np
import pandas as pd

data  = pd.read_excel('week01-data.xlsx')
train_data = data.iloc[:10]
test_data = data.iloc[10:]

X_train = np.array(train_data[['抽問分數', '作業平均', '測驗平均']] - 60) * 0.008 # 10*3
y_train = np.array(train_data['總成績'] - 60) * 0.008 # 1*10
X_test = np.array(test_data[['抽問分數', '作業平均', '測驗平均']] - 60) * 0.008 # 4*3
y_test = np.array(test_data['總成績'] - 60) * 0.008 # 1*4

def tanh(x):
    return np.tanh(x)

np.random.seed(10)

# 初始化 weight 和 bias
w1 = 2 * np.random.random((3,2)) - 1 # 3*2
b1 = 2 * np.random.random((1,2)) - 1 # 1*2
w2 = 2 * np.random.random((2,1)) - 1 # 2*1
b2 = 2 * np.random.random((1,1)) - 1 # 1*1

learning_rate = 0.1
num_iterations = 100000

for i in range(num_iterations):
    # 前向傳播
    hidden_layer_input = np.dot(X_train, w1) + b1
    hidden_layer_output = tanh(hidden_layer_input)
    output_layer_input = np.dot(hidden_layer_output, w2) + b2
    output_layer_output = tanh(output_layer_input)

    # 計算誤差
    output_error = y_train.reshape((-1,1)) - output_layer_output
    hidden_error = np.dot(output_error * (1 - np.square(output_layer_output)), w2.T)

    # 反向傳播
    # bias在同一個類別中是相同的，對同類別的梯度進行求和
    w2 += learning_rate * np.dot(hidden_layer_output.T, output_error * (1 - np.square(output_layer_output)))
    b2 += learning_rate * np.sum(output_error * (1 - np.square(output_layer_output)), axis=0, keepdims=True)
    w1 += learning_rate * np.dot(X_train.T, hidden_error * (1 - np.square(hidden_layer_output)))
    b1 += learning_rate * np.sum(hidden_error * (1 - np.square(hidden_layer_output)), axis=0, keepdims=True)


    # 每迭代1000次輸出訓練成果
    if i%1000 == 0:
        print("\n第"+str(i)+"次訓練資料預測總成績:")
        print(output_layer_output / 0.008)


first_neuron_input = np.dot(X_train, w1) + b1
first_neuron_output = tanh(first_neuron_input)
second_neuron_input = np.dot(first_neuron_output, w2) + b2
y_train_pred = (tanh(second_neuron_input) / 0.008 + 60).round()
train_mse = np.mean((y_train_pred.T - (y_train.T / 0.008 + 60)) ** 2)
print('\n\nTrain Mean Square Error:', train_mse)

first_neuron_input = np.dot(X_test, w1) + b1
first_neuron_output = tanh(first_neuron_input)
second_neuron_input = np.dot(first_neuron_output, w2) + b2
y_test_pred = (tanh(second_neuron_input) / 0.008 + 60).round()
test_mse = np.square(np.subtract(y_test_pred.T, y_test.T / 0.008 + 60)).mean()
print('Test Mean Square Error:', test_mse)

print("\n測試資料預測總成績:")
print(y_test_pred)
