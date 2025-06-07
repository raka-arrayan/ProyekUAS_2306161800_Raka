import matplotlib.pyplot as plt

# Data dari tabel
intervals = [4, 8, 16, 32]
simpson_results = [101.146996, 101.045646, 101.039898, 101.039547]
error_abs = [0.107472, 0.006122, 0.000374, 0.000023]
error_rel = [0.106366, 0.006059, 0.000370, 0.000023]

# Membuat figure dan axis
fig, ax1 = plt.subplots(figsize=(8, 5))

# Plot Simpson's Result
ax1.plot(intervals, simpson_results, 'bo-', label="Simpson's Result")
ax1.set_xlabel('Interval (n)')
ax1.set_ylabel("Simpson's Result", color='blue')
ax1.tick_params(axis='y', labelcolor='blue')
ax1.set_xticks(intervals)
ax1.set_title('Visualisasi Hasil Simpson dan Error')

# Membuat axis kedua untuk error
ax2 = ax1.twinx()
ax2.plot(intervals, error_abs, 'ro--', label='Error Absolut')
ax2.plot(intervals, error_rel, 'go--', label='Error Relatif (%)')
ax2.set_ylabel('Error', color='red')
ax2.tick_params(axis='y', labelcolor='red')
ax2.set_yscale('log')  # Skala log untuk error agar perbedaan jelas

# Gabungkan legend
lines_1, labels_1 = ax1.get_legend_handles_labels()
lines_2, labels_2 = ax2.get_legend_handles_labels()
ax1.legend(lines_1 + lines_2, labels_1 + labels_2, loc='upper right')

plt.show()
