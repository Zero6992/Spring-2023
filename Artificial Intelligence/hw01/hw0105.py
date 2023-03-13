import numpy as np
import pandas as pd

# 讀取數據
data  = pd.read_excel('week01-data.xlsx')
train_data = data.iloc[:10]
test_data = data.iloc[10:]

# 轉換為 NumPy 陣列
X_train = np.array(train_data[['抽問分數', '作業平均', '測驗平均']]) * 0.008
y_train = np.array(train_data['總成績']) * 0.008
X_test = np.array(test_data[['抽問分數', '作業平均', '測驗平均']]) * 0.008
y_test = np.array(test_data['總成績']) * 0.008

# 定義 sigmoid 函數
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

# 設定隨機種子，使每次運行結果一致
np.random.seed(10)

# 初始化權重和偏差
w1 = 2 * np.random.random((3,2)) - 1
b1 = 2 * np.random.random((1,2)) - 1
w2 = 2 * np.random.random((2,1)) - 1
b2 = 2 * np.random.random((1,1)) - 1

# 設定學習率和訓練次數
learning_rate = 0.1
num_iterations = 10000

# 訓練神經網路
for i in range(num_iterations):
    # 前向傳播
    hidden_layer_input = np.dot(X_train, w1) + b1
    hidden_layer_output = sigmoid(hidden_layer_input)
    output_layer_input = np.dot(hidden_layer_output, w2) + b2
    output_layer_output = sigmoid(output_layer_input)

    # 計算誤差
    output_error = y_train.reshape((-1,1)) - output_layer_output
    hidden_error = np.dot(output_error * output_layer_output * (1 - output_layer_output), w2.T)

    # 反向傳播
    w2 += learning_rate * np.dot(hidden_layer_output.T, output_error * output_layer_output * (1 - output_layer_output))
    b2 += learning_rate * np.sum(output_error * output_layer_output * (1 - output_layer_output), axis=0, keepdims=True)
    w1 += learning_rate * np.dot(X_train.T, hidden_error * hidden_layer_output * (1 - hidden_layer_output))
    b1 += learning_rate * np.sum(hidden_error * hidden_layer_output * (1 - hidden_layer_output), axis=0, keepdims=True)

    # 計算訓練誤差
    train_mse = np.mean((output_layer_output - y_train.reshape((-1,1))) ** 2)

    # 輸出訓練進度
    print("\n第"+str(i)+"次訓練資料預測總成績:")
    print(output_layer_output / 0.008)


z1 = np.dot(X_train, w1) + b1
a1 = sigmoid(z1)
z2 = np.dot(a1, w2) + b2
y_train_pred = sigmoid(z2)
train_mse = np.mean((y_train_pred - y_train.reshape((-1, 1))) ** 2)
print('\n\nTrain Mean Square Error:', train_mse)

z1 = np.dot(X_test, w1) + b1
a1 = sigmoid(z1)
z2 = np.dot(a1, w2) + b2
y_test_pred = sigmoid(z2)
test_mse = np.mean((y_test_pred - y_test.T) ** 2)
print('Test Mean Square Error:', test_mse)

print("\n測試資料預測總成績:")
print((y_test_pred / 0.008).round())
