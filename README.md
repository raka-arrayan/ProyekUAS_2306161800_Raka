# IMPLEMENTASI SIMPSON'S RULE UNTUK PERHITUNGAN TOTAL HEAT TRANSFER

## Nama dan NPM

| Nama                       | NPM         |
|----------------------------|-------------|
| Raka Arrayan Muttaqien     | 2306161800  |
---

## Deskripsi Proyek

### Metode Simpson’s Rule

Simpson’s Rule adalah salah satu metode numerik untuk menghitung integral tentu, terutama ketika data tersedia dalam bentuk diskrit. Dalam proyek ini, metode ini digunakan untuk menghitung **total perpindahan panas (heat transfer)** berdasarkan distribusi temperatur terhadap waktu dalam sistem termal.

#### Rumus Simpson’s 1/3 Rule

Untuk jumlah interval genap (n), dengan step size `h = (b-a)/n`:

```
∫[a,b] f(x) dx ≈ (h / 3) × [f(x₀) + 4f(x₁) + 2f(x₂) + 4f(x₃) + ... + f(xₙ)]
```

Metode ini memberikan estimasi numerik terhadap integral dari fungsi temperatur terhadap waktu.

#### Rumus Simpson’s 3/8 Rule

```
∫[a,b] f(x) dx ≈ (3h / 8) × [f(x₀) + 3f(x₁) + 3f(x₂) + f(x₃)]
```

Metode ini cocok digunakan saat metode Simpson 1/3 tidak bisa digunakan sepenuhnya.

---

## Tujuan Proyek

- Mengimplementasikan metode Simpson’s Rule untuk menghitung integral numerik.
- Mengestimasi total heat transfer berdasarkan data temperatur.
- Menganalisis pengaruh jumlah titik data terhadap akurasi hasil integral.
- Memberikan solusi perhitungan numerik pada data eksperimental.

---

## Studi Kasus

### Perpindahan Panas

Sistem mengumpulkan data temperatur (°C) pada interval waktu tertentu (jam). Tujuannya adalah menghitung total panas yang ditransfer ke atau dari sistem dengan mengintegralkan fungsi temperatur terhadap waktu.

---

## Opsi Input Program

### Pilihan 1: Berdasarkan Interval

Pengguna memasukkan waktu awal, waktu akhir, dan jumlah interval (harus genap).

**Contoh:**

```
Pilihan Anda: 1
Masukkan waktu awal (jam): 0
Masukkan waktu akhir (jam): 8
Masukkan jumlah interval: 4
```

Program akan menghasilkan nilai x dan menghitung y = f(x), lalu menggunakan Simpson’s Rule untuk menghitung integral.

---

### Pilihan 2: Input Manual Titik Data

Pengguna memasukkan pasangan (x, y) secara manual.

**Contoh:**

```
Pilihan Anda: 2
Masukkan jumlah titik data: 5
Masukkan data (x, y):
Titik 1 - x: 0     y: 12.0
Titik 2 - x: 2     y: 13.5
Titik 3 - x: 4     y: 15.2
Titik 4 - x: 6     y: 14.0
Titik 5 - x: 8     y: 12.5
```

---

### Pilihan 3: Input dari File

File `heat_data.txt` berisi data seperti:

```
0  12.0
2  13.5
4  15.2
6  14.0
8  12.5
```

Program akan membaca data tersebut dan menghitung total heat transfer.

---

## Langkah Perhitungan

1. **Validasi jumlah titik**: Harus ganjil (interval genap).
2. **Baca data (x, y)**: Dari input manual atau file.
3. **Hitung h**: Selisih antar x.
4. **Terapkan Simpson’s Rule**:
   - Koefisien 1 di awal dan akhir
   - Koefisien 4 untuk indeks ganjil
   - Koefisien 2 untuk indeks genap (selain akhir)
5. **Hitung nilai total heat transfer** dengan rumus `Q'(t) = 10 + 5sin(0.5t) + 2cos(0.3t)`

---

## Contoh Output

```
| Interval (n) | Simpson's Result | Error Absolut | Error Relatif (%) |
|--------------|------------------|---------------|-------------------|
| 4            | 101.146996       | 0.107472      | 0.106366          |
| 8            | 101.045646       | 0.006122      | 0.006059          |
| 16           | 101.039898       | 0.000374      | 0.000370          |
| 32           | 101.039547       | 0.000023      | 0.000023          |
```

Simpson's Rule memberikan hasil yang semakin akurat saat jumlah interval (n) bertambah dan Error absolut dan error relatif menurun drastis seiring peningkatan jumlah interval

---

## Kesimpulan

- Metode Simpson's Rule terbukti efektif dalam menghitung total heat transfer dari data diskrit dengan akurasi yang tinggi.
- Ketelitian hasil perhitungan meningkat secara signifikan dengan bertambahnya jumlah interval (n), di mana error absolut dan error relatif semakin kecil.
- Penggunaan jumlah interval genap sangat penting untuk penerapan Simpson's Rule agar menghasilkan estimasi yang valid.
- Hasil perhitungan total heat transfer dengan metode ini dapat digunakan sebagai dasar analisis efisiensi dan performa sistem termal dalam berbagai aplikasi teknik.
- Peningkatan jumlah interval harus diimbangi dengan pertimbangan kebutuhan komputasi agar efisiensi tetap optimal.

---


<div align="center">
  <strong>© 2025 Proyek UAS - Komputasi Numerik</strong>
</div>
