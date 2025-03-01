# 导入相关库
import numpy as np
from scipy import signal

# 定义一个3×3的卷积核
kernel = np.array([[1, 0, -1],
                   [1, 0, -1],
                   [1, 0, -1]])

# 定义一个待处理的二维数据
data = np.array([[0, 0, 0, 0, 0, 0, 0, 0],
                 [1, 1, 1, 1, 1, 1, 1, 1],
                 [2, 2, 2, 2, 2, 2, 2, 2],                        
                 [3, 3, 3, 3, 3, 3, 3, 3],
                 [4, 4, 4, 4, 4, 4, 4, 4],
                 [5, 5, 5, 5, 5, 5, 5, 5],
                 [6, 6, 6, 6, 6, 6, 6, 6],
                 [7, 7, 7, 7, 7, 7, 7, 7]])

# 使用signal.convolve2d进行卷积
result = signal.convolve2d(data, kernel, mode='same')

#输出卷积结果
print("result：\n", result)

# 定义了一个名为max_pooling的最大池化函数
def max_pooling(input_matrix, kernel_size=2, stride=2):
    output_rows = (input_matrix.shape[0] - kernel_size) // stride + 1
    output_cols = (input_matrix.shape[1] - kernel_size) // stride + 1
    output_matrix = np.zeros((output_rows, output_cols))

    for i in range(output_rows):
        for j in range(output_cols):
            output_matrix[i, j] = np.max(input_matrix[i*stride:i*stride+kernel_size, j*stride:j*stride+kernel_size])

    return output_matrix

# 使用max_pooling函数对卷积结果进行池化
output_matrix = max_pooling(result)

#输出池化结果
print("output_matrix：\n", output_matrix)