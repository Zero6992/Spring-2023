# -*- coding: utf-8 -*-
import numpy as np
import pandas as pd

data  = pd.read_excel('week01-data.xlsx')

train_data = data.iloc[:10]
test_data = data.iloc[10:]

X_train = np.array(train_data[['抽問分數', '作業平均', '測驗平均']])  * 0.008
y_train = np.array(train_data['總成績'])  * 0.008
X_test = np.array(test_data[['抽問分數', '作業平均', '測驗平均']]) * 0.008
y_test = np.array(test_data['總成績']) * 0.008


def sigmoid(x):
    return 1 / (1 + np.exp(-x))

np.random.seed(10)
w = 2 * np.random.random((3,1)) - 1

learning_rate = 0.1
num_iterations = 100000

for i in range(num_iterations):
    y_train_pred  = sigmoid(np.dot(X_train, w))
    print("\n第"+str(i)+"次訓練資料預測總成績:")
    print(y_train_pred / 0.008)
    error = y_train.reshape((-1, 1)) - y_train_pred
    w += learning_rate * np.dot(X_train.T, error * y_train_pred  * (1 - y_train_pred))


y_train_pred = (sigmoid(np.dot(X_train, w))/ 0.008).round()
train_mse = np.mean((y_train_pred.T - y_train.T / 0.008) ** 2)
print('\n\nTrain Mean Square Error:', train_mse)

y_test_pred = (sigmoid(np.dot(X_test, w)) / 0.008).round()
test_mse = np.mean((y_test_pred.T - y_test.T / 0.008) ** 2)
print('Test Mean Square Error:', test_mse)

print("\n測試資料預測總成績:")
print(y_test_pred)
