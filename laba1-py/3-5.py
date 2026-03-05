import matplotlib.pyplot as plt

data = {
    'N': [100, 1000, 10000, 100000, 1000000],
    'lin_worst': [0.17, 1.69, 15.31, 119.81, 1221.57],
    'lin_avg': [0.098, 0.8218, 8.7131, 77.2108, 778.538],
    'bin_worst': [0.04, 0.05, 0.09, 0.10, 0.11],
    'bin_avg': [0.0244, 0.0425, 0.0669, 0.0704, 0.0984]
}

plt.figure(figsize=(10, 8))
plt.loglog(data['N'], data['lin_worst'], 'ro-', linewidth=2, markersize=8, label='Линейный поиск (wcs)')
plt.loglog(data['N'], data['lin_avg'], 'go-', linewidth=2, markersize=8, label='Линейный поиск (acs)')
plt.loglog(data['N'], data['bin_worst'], 'mo-', linewidth=2, markersize=8, label='Бинарный поиск (wcs)')
plt.loglog(data['N'], data['bin_avg'], 'co-', linewidth=2, markersize=8, label='Бинарный поиск (acs)')
plt.xlabel('Размер массива (N) - логарифмическая шкала', fontsize=12)
plt.ylabel('Время выполнения (мкс)', fontsize=12)
plt.title('Сравнение времени выполнения алгоритмов поиска (лог. шкала по N)', fontsize=14)
plt.grid(True, which='both', linestyle='--', alpha=0.7)
plt.legend(fontsize=10)
plt.xlim(50, 2000000)
plt.tight_layout()
plt.show()