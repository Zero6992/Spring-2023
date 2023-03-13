import numpy as np
import pandas as pd

# 讀取數據
data  = pd.read_excel('./Artificial Intelligence/hw01/week01-data.xlsx')
train_data = data.iloc[:10]
test_data = data.iloc[10:]

np.random.seed(10)
w1 = 2 * np.random.random((3,2)) - 1 # 3*2
b1 = 2 * np.random.random((1,2)) - 1 # 1*2

X_train = np.array(train_data[['抽問分數', '作業平均', '測驗平均']]) * 0.008
y_train = (np.array(train_data['總成績']) * 0.008)[np.newaxis]

hidden_layer_input = np.dot(X_train, w1) + b1