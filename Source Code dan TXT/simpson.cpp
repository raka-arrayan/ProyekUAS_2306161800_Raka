#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <fstream>
#include <chrono>

using namespace std;
/**
 * SimpsonsRuleIntegrator
 * Digunakan untuk melakukan integrasi numerik menggunakan metode Simpson's Rule
 * Mendukung Simpson's 1/3 Rule, 3/8 Rule, dan kombinasi keduanya.
 */
class SimpsonsRuleIntegrator
{
private:
    vector<double> x_values; // Menyimpan nilai x (titik-titik data)
    vector<double> y_values; // Menyimpan nilai f(x) yang bersesuaian
    int n;                   // Jumlah interval (bukan jumlah titik)
    double h;                // Step size (jarak antar x)

public:
    /**
     * Constructor
     * Inisialisasi objek dengan data diskrit (x dan y)
     * Menghitung jumlah interval (n) dan step size (h)
     */
    SimpsonsRuleIntegrator(const vector<double> &x, const vector<double> &y)
    {
        x_values = x;
        y_values = y;
        n = x.size() - 1;
        h = (x_values[n] - x_values[0]) / n;
    }

    /**
     * Simpson's 1/3 Rule
     * Melakukan integrasi numerik untuk jumlah interval genap
     * Proses:
     * 1. Tambahkan nilai y pada ujung (x0 dan xn)
     * 2. Kalikan 4 pada nilai y pada indeks ganjil
     * 3. Kalikan 2 pada nilai y pada indeks genap (kecuali ujung)
     * 4. Kalikan total dengan h/3
     */
    double simpsons13Rule()
    {
        if (n % 2 != 0)
        {
            cout << "Error: Jumlah interval harus genap untuk Simpson's 1/3 Rule!" << endl;
            return 0;
        }

        double sum = y_values[0] + y_values[n]; // f(x0) + f(xn)

        // Koefisien 4 untuk indeks ganjil
        for (int i = 1; i < n; i += 2)
        {
            sum += 4 * y_values[i];
        }

        // Koefisien 2 untuk indeks genap (kecuali ujung)
        for (int i = 2; i < n; i += 2)
        {
            sum += 2 * y_values[i];
        }

        return (h / 3.0) * sum;
    }

    /**
     * Simpson's 3/8 Rule
     * Digunakan hanya jika terdapat 3 interval (4 titik data)
     * Proses:
     * 1. Gunakan rumus khusus: (3h/8)*(y0 + 3y1 + 3y2 + y3)
     */
    double simpsons38Rule()
    {
        if (n != 3)
        {
            cout << "Error: Simpson's 3/8 Rule memerlukan tepat 3 interval!" << endl;
            return 0;
        }

        return (3 * h / 8.0) * (y_values[0] + 3 * y_values[1] + 3 * y_values[2] + y_values[3]);
    }

    /**
     * Combined Simpson's Rule
     * Menangani kasus jumlah interval ganjil atau tidak bisa dibagi rata
     * Proses:
     * 1. Gunakan Simpson's 1/3 untuk bagian awal (jika genap)
     * 2. Gunakan Simpson's 3/8 untuk bagian akhir (jika 3 titik tersisa)
     * 3. Koreksi dengan mengurangi trapezoidal pada overlap jika perlu
     */
    double combinedSimpsonsRule()
    {
        if (n < 2)
        {
            cout << "Error: Minimal 2 interval diperlukan!" << endl;
            return 0;
        }

        double result = 0;
        int remaining = n;
        int start_idx = 0;

        // Gunakan Simpson's 1/3 untuk interval genap
        while (remaining >= 2 && remaining % 2 == 0)
        {
            vector<double> sub_x(x_values.begin() + start_idx, x_values.begin() + start_idx + remaining + 1);
            vector<double> sub_y(y_values.begin() + start_idx, y_values.begin() + start_idx + remaining + 1);

            SimpsonsRuleIntegrator sub_integrator(sub_x, sub_y);
            result += sub_integrator.simpsons13Rule();
            break;
        }

        // Jika masih ada sisa interval ganjil, gunakan Simpson's 3/8 atau Trapezoidal
        if (remaining % 2 != 0 && remaining >= 3)
        {
            vector<double> sub_x(x_values.end() - 4, x_values.end());
            vector<double> sub_y(y_values.end() - 4, y_values.end());

            SimpsonsRuleIntegrator sub_integrator(sub_x, sub_y);

            // Kurangi hasil sebelumnya untuk 1 interval terakhir
            vector<double> overlap_x(x_values.end() - 2, x_values.end());
            vector<double> overlap_y(y_values.end() - 2, y_values.end());
            result -= (overlap_x[1] - overlap_x[0]) * (overlap_y[0] + overlap_y[1]) / 2.0; // Trapezoidal

            result += sub_integrator.simpsons38Rule();
        }

        return result;
    }

    /**
     * Menampilkan data input yang diberikan (x dan y)
     */
    void displayData()
    {
        cout << "\nData Input:" << endl;
        cout << "x\t\tf(x)" << endl;
        cout << "------------------------" << endl;
        for (int i = 0; i <= n; i++)
        {
            cout << fixed << setprecision(2) << x_values[i] << "\t\t" << y_values[i] << endl;
        }
        cout << "\nJumlah interval (n) = " << n << endl;
        cout << "Step size (h) = " << h << endl;
    }
};

/**
 * Fungsi heatTransferRate
 * Contoh fungsi laju transfer panas Q'(t) dalam kW sebagai fungsi waktu
 * Digunakan untuk simulasi kasus teknik
 */
double heatTransferRate(double time)
{
    // Contoh: Q'(t) = 10 + 5*sin(0.5*t) + 2*cos(0.3*t)
    // Dimana Q'(t) adalah laju transfer panas dalam kW pada waktu t (jam)
    return 10 + 5 * sin(0.5 * time) + 2 * cos(0.3 * time);
}

int main()
{
    cout << "==========================================" << endl;
    cout << "  APLIKASI SIMPSON'S RULE" << endl;
    cout << "  Untuk Perhitungan Total Heat Transfer" << endl;
    cout << "==========================================" << endl;

    int choice;
    cout << "\nPilih sumber data:" << endl;
    cout << "1. Data dari fungsi (Heat Transfer Rate)" << endl;
    cout << "2. Input data manual" << endl;
    cout << "3. Load data dari file" << endl;
    cout << "Pilihan Anda: ";
    cin >> choice;

    vector<double> x_data, y_data;

    switch (choice)
    {
    case 1:
    {
        /**
         * Kasus Heat Transfer
         * Menghitung total panas yang ditransfer selama periode waktu tertentu menggunakan integrasi numerik.
         *
         * - Fungsi laju transfer panas yang digunakan:
         *   Q'(t) = 10 + 5*sin(0.5*t) + 2*cos(0.3*t) [dalam kW]
         * - Pengguna diminta memasukkan waktu awal dan akhir (dalam jam), serta jumlah interval untuk integrasi.
         * - Data titik waktu (x_data) dan laju panas (y_data) dikumpulkan untuk digunakan dalam integrasi.
         * - Nilai x_data berisi waktu, dan y_data berisi nilai fungsi Q'(t) pada waktu tersebut.
         */
        double t_start, t_end;
        int intervals;

        cout << "\n=== KASUS HEAT TRANSFER ===" << endl;
        cout << "Fungsi laju transfer panas: Q'(t) = 10 + 5*sin(0.5*t) + 2*cos(0.3*t) kW" << endl;
        cout << "Masukkan waktu awal (jam): ";
        cin >> t_start;
        cout << "Masukkan waktu akhir (jam): ";
        cin >> t_end;
        cout << "Masukkan jumlah interval: ";
        cin >> intervals;

        double step = (t_end - t_start) / intervals;

        for (int i = 0; i <= intervals; i++)
        {
            double t = t_start + i * step;
            x_data.push_back(t);
            y_data.push_back(heatTransferRate(t));
        }
        break;
    }

    case 2:
    {
        /**
         * Kasus Input Manual Data Titik
         * Pengguna memasukkan sejumlah titik data secara manual untuk dilakukan integrasi numerik.
         *
         * - Pengguna diminta memasukkan jumlah titik data (n).
         * - Untuk setiap titik, pengguna menginput pasangan nilai x dan y.
         * - Nilai x dimasukkan ke dalam vektor x_data.
         * - Nilai y (hasil dari f(x)) dimasukkan ke dalam vektor y_data.
         * - Data ini kemudian dapat digunakan dalam metode integrasi Simpson.
         */
        int n;
        cout << "Masukkan jumlah titik data: ";
        cin >> n;

        cout << "Masukkan data (x, y):" << endl;
        for (int i = 0; i < n; i++)
        {
            double x, y;
            cout << "Titik " << i + 1 << " - x: ";
            cin >> x;
            cout << "Titik " << i + 1 << " - y: ";
            cin >> y;
            x_data.push_back(x);
            y_data.push_back(y);
        }
        break;
    }

    case 3:
    {
        /**
         * Kasus Input dari File
         * Program akan membaca data titik (x, y) dari sebuah file teks eksternal.
         *
         * - Pengguna diminta memasukkan nama file.
         * - File dibuka menggunakan ifstream.
         * - Jika file tidak dapat dibuka, akan ditampilkan pesan error dan program dihentikan.
         * - Data dibaca per baris dalam format: <x> <y>
         * - Setiap nilai x dan y ditambahkan ke dalam vektor x_data dan y_data.
         */
        string filename;
        cout << "Masukkan nama file: ";
        cin >> filename;

        ifstream file(filename);
        if (!file.is_open())
        {
            cout << "Error: Tidak dapat membuka file!" << endl;
            return 1;
        }

        double x, y;
        while (file >> x >> y)
        {
            x_data.push_back(x);
            y_data.push_back(y);
        }
        file.close();
        break;
    }

    default:
        cout << "Pilihan tidak valid!" << endl;
        return 1;
    }

    if (x_data.size() < 2)
    {
        cout << "Error: Minimal 2 titik data diperlukan!" << endl;
        return 1;
    }

    // Membuat objek integrator
    SimpsonsRuleIntegrator integrator(x_data, y_data);

    // Menampilkan data
    integrator.displayData();

    // Melakukan integrasi dengan pengukuran waktu
    auto start = chrono::high_resolution_clock::now();

    cout << "\n=== HASIL INTEGRASI ===" << endl;

    int n = x_data.size() - 1;
    double result;

    if (n % 2 == 0)
    {
        cout << "Menggunakan Simpson's 1/3 Rule:" << endl;
        result = integrator.simpsons13Rule();
    }
    else if (n == 3)
    {
        cout << "Menggunakan Simpson's 3/8 Rule:" << endl;
        result = integrator.simpsons38Rule();
    }
    else
    {
        cout << "Menggunakan Combined Simpson's Rule:" << endl;
        result = integrator.combinedSimpsonsRule();
    }

    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    cout << fixed << setprecision(6);
    cout << "Hasil integrasi = " << result << endl;
    cout << "Waktu komputasi = " << duration.count() << " mikrosekond" << endl;

    if (choice == 1)
    {
        cout << "\nInterpretasi:" << endl;
        cout << "Total panas yang ditransfer = " << result << " kWh" << endl;
        cout << "Selama periode " << x_data[0] << " hingga " << x_data.back() << " jam" << endl;
    }

    // Error analysis (jika menggunakan fungsi yang diketahui)
    if (choice == 1)
    {
        cout << "\n=== ANALISIS ERROR ===" << endl;

        // Untuk fungsi Q'(t) = 10 + 5*sin(0.5*t) + 2*cos(0.3*t)
        // Integral analitik: Q(t) = 10*t - 10*cos(0.5*t) + (20/3)*sin(0.3*t) + C
        double t1 = x_data[0];
        double t2 = x_data.back();

        double exact = 10 * (t2 - t1) - 10 * (cos(0.5 * t2) - cos(0.5 * t1)) +
                       (20.0 / 3.0) * (sin(0.3 * t2) - sin(0.3 * t1));

        double error = abs(exact - result);
        double relative_error = (error / abs(exact)) * 100;

        cout << "Solusi eksak = " << exact << endl;
        cout << "Error absolut = " << error << endl;
        cout << "Error relatif = " << relative_error << "%" << endl;

        /**
         * Menggunakan Richardson extrapolation untuk mengestimasi error dari hasil integrasi.
         * Richardson extrapolation memberikan pendekatan estimasi error dengan:
         * - Menggunakan data dengan jumlah interval setengah dari aslinya (mengambil titik genap saja)
         * - Menghitung ulang hasil integrasi dengan Simpson’s 1/3 Rule pada subset data
         * - Menghitung error estimasi dengan rumus |result_half - result| / 15
         *
         * Hasil estimasi error akan dibandingkan dengan error aktual (jika diketahui),
         * dan akurasi estimasi juga ditampilkan dalam bentuk persentase.
         * Estimasi ini hanya dilakukan jika jumlah interval `n` ≥ 4.
         */
        if (n >= 4)
        {
            cout << "\n=== ESTIMASI ERROR (Richardson Extrapolation) ===" << endl;
            // Hitung dengan setengah interval untuk estimasi
            vector<double> x_half, y_half;
            for (int i = 0; i <= n; i += 2)
            {
                x_half.push_back(x_data[i]);
                y_half.push_back(y_data[i]);
            }

            SimpsonsRuleIntegrator half_integrator(x_half, y_half);
            double result_half = half_integrator.simpsons13Rule();
            double estimated_error = abs(result_half - result) / 15.0;

            cout << "Estimated error ≈ " << estimated_error << endl;
            cout << "Actual error = " << error << endl;
            cout << "Estimation accuracy = " << (1 - abs(estimated_error - error) / error) * 100 << "%" << endl;
        }
    }

    // Menyimpan hasil ke file
    cout << "\nSimpan hasil ke file? (y/n): ";
    char save;
    cin >> save;
    /**
     * Menyimpan hasil integrasi ke dalam file jika pengguna memilih untuk menyimpannya.
     * File yang disimpan bernama "simpson_result.txt" dan berisi:
     * - Jumlah interval yang digunakan
     * - Hasil integrasi numerik
     * - Tabel data titik x dan nilai f(x)
     *
     * Program akan membuat file output, menuliskan hasil dan data, lalu menutup file.
     * Jika berhasil, pesan konfirmasi akan ditampilkan ke pengguna.
     */
    if (save == 'y' || save == 'Y')
    {
        ofstream output("simpson_result.txt");
        output << "Simpson's Rule Integration Results\n";
        output << "==================================\n";
        output << "Number of intervals: " << n << "\n";
        output << "Integration result: " << fixed << setprecision(6) << result << "\n";

        output << "\nData points:\n";
        output << "x\t\tf(x)\n";
        for (size_t i = 0; i < x_data.size(); i++)
        {
            output << x_data[i] << "\t\t" << y_data[i] << "\n";
        }

        output.close();
        cout << "Hasil disimpan dalam file 'simpson_result.txt'" << endl;
    }

    return 0;
}