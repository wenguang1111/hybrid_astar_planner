import pandas as pd
import matplotlib.pyplot as plt

file_path = 'variable_double.csv'
data = pd.read_csv(file_path)

column_stats = {}

for column in data.columns:
    max_value = data[column].max()
    min_value = data[column].min()
    std_dev = data[column].std()
    
    column_stats[column] = {'max_value': max_value, 'min_value': min_value, 'std_dev': std_dev}


for column, stats in column_stats.items():
    print(f"variable： {column}:")
    print("max_value:", stats['max_value'])
    print("min_value:", stats['min_value'])
    print("std_dev:", stats['std_dev'])
    print("\n")

values = data['Car::getOutline()::head_l[i]']  # 获取列的数值
plt.hist(values, bins=100, edgecolor='black')  # 绘制直方图，可以根据需要调整 bins 的数量
plt.title(f"Histogram for {column}")
plt.xlabel(column)
plt.ylabel("Frequency")
plt.show()