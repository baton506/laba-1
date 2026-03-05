import matplotlib.pyplot as plt

N = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]

real_quad_worst = [0.001, 0.003, 0.006, 0.011, 0.017, 0.024, 0.033, 0.042, 0.053, 0.065, 0.079, 0.094, 0.11, 0.128, 0.147, 0.167, 0.188, 0.211, 0.236, 0.261]
real_quad_avg = [0.0006, 0.0015, 0.0031, 0.0055, 0.0086, 0.0121, 0.0165, 0.0213, 0.0265, 0.0326, 0.0392, 0.0468, 0.055, 0.064, 0.073, 0.083, 0.094, 0.106, 0.119, 0.133]
real_lin_worst = [0.0002, 0.0003, 0.0004, 0.0005, 0.0005, 0.0006, 0.0006, 0.0007, 0.0007, 0.0008, 0.0008, 0.0009, 0.0009, 0.001, 0.001, 0.0011, 0.0011, 0.0012, 0.0012, 0.0013]
real_lin_avg = [0.0001, 0.00015, 0.0002, 0.00025, 0.00025, 0.0003, 0.0003, 0.00035, 0.00035, 0.0004, 0.0004, 0.00045, 0.00045, 0.0005, 0.0005, 0.00055, 0.00055, 0.0006, 0.0006, 0.00065]

plt.figure(figsize=(10, 8))
plt.loglog(N, real_quad_worst, 'ro-', linewidth=2, markersize=6, label='Квадратичный (wcs)')
plt.loglog(N, real_quad_avg, 'go-', linewidth=2, markersize=6, label='Квадратичный (acs)')
plt.loglog(N, real_lin_worst, 'mo-', linewidth=2, markersize=6, label='Линейный (wcs)')
plt.loglog(N, real_lin_avg, 'co-', linewidth=2, markersize=6, label='Линейный (acs)')
plt.xlabel('Размер массива (N)')
plt.ylabel('Время выполнения (мкс)')
plt.title('Сравнение алгоритмов поиска суммы двух элементов')
plt.grid(True, which='both', linestyle='--', alpha=0.7)
plt.legend(fontsize=10)
plt.xlim(4, 110)
plt.tight_layout()
plt.show()