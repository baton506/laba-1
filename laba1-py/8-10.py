import matplotlib.pyplot as plt

N = [100, 1000, 10000, 100000, 1000000]

A_smooth = [0.1141, 0.9716, 8.6014, 75.1948, 792.313]
A_not_smooth = [0.106, 0.5828, 7.9122, 99.7479, 1138.92]

B_smooth = [0.0863, 0.8289, 9.6076, 88.9821, 700.525]
B_not_smooth = [0.176, 0.6406, 7.4579, 106.983, 620.885]

C_smooth = [0.202, 0.7918, 10.1375, 76.6659, 719.715]
C_not_smooth = [0.1256, 0.6793, 6.6357, 90.949, 621.893]

plt.figure(figsize=(14, 6))

plt.subplot(1, 2, 1)
plt.plot(N, A_smooth, 'o-', label='A')
plt.plot(N, B_smooth, 's-', label='B')
plt.plot(N, C_smooth, '^-', label='C')
plt.xscale('log')
plt.yscale('log')
plt.title('Равномерное')
plt.xlabel('N')
plt.ylabel('Время (мкс)')
plt.grid(True, which="both", ls="-", alpha=0.3)
plt.legend()

plt.subplot(1, 2, 2)
plt.plot(N, A_not_smooth, 'o-', label='A')
plt.plot(N, B_not_smooth, 's-', label='B')
plt.plot(N, C_not_smooth, '^-', label='C')
plt.xscale('log')
plt.yscale('log')
plt.title('Неравномерное')
plt.xlabel('N')
plt.ylabel('Время (мкс)')
plt.grid(True, which="both", ls="-", alpha=0.3)
plt.legend()

plt.tight_layout()
plt.show()
