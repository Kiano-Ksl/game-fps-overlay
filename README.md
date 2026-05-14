# 🎯 FPS Counter Overlay (DirectX 11 Hooking)

![Platform](https://img.shields.io/badge/Platform-Windows-blue)
![Language](https://img.shields.io/badge/Language-C++-orange)

Sebuah program pemantau FPS (*Frames Per Second*) yang sangat ringan. Program ini dirancang dengan bahasa C++ murni untuk berjalan di latar belakang (siluman) dan menyuntikkan *overlay* angka FPS langsung ke dalam game yang menggunakan mesin DirectX 11. 

Berbeda dengan aplikasi *monitoring* berat lainnya, program ini menggunakan jendela transparan (*click-through*) yang bersih, ringkas, dan memakan **0% CPU Usage** saat *idle*.

## ✨ Fitur Utama
*   **🪟 Layar Kaca Transparan:** Angka FPS melayang di pojok layar tanpa mengganggu klik mouse kamu saat bermain game.
*   **🎯 Target Spesifik:** Program hanya akan menyuntikkan agen ke game yang sudah kamu daftarkan secara spesifik.
*   **🪶 Sangat Ringan:** Kode sumber telah dibersihkan dan dioptimalkan agar berjalan cepat tanpa beban sistem tambahan.

## 🛠️ Teknologi yang Dipakai
*   **C++** (Core Programming Language)
*   **Windows API** (Pembuatan jendela transparan & Process Management)
*   **MinHook** (Library untuk API Hooking)
*   **DirectX 11** (Target render engine untuk perhitungan *frame*)

## 📂 Struktur Project
```text
📦 FPS_Counter
 ┣ 📂 include          # File header MinHook
 ┣ 📂 src              # File source MinHook
 ┣ 📜 data_fps.txt     # File dinamis penyimpan angka FPS
 ┣ 📜 layar_fps.cpp    # Source code: Jendela Overlay Kaca
 ┣ 📜 mesin_fps.cpp    # Source code: Agen DLL pembaca DirectX 11
 ┗ 📜 peluncur.cpp     # Source code: Penyuntik otomatis ke dalam game
```

## ⚙️ Persyaratan Sistem
1. OS Windows (10 atau 11).
2. **MinGW (g++)** compiler terinstal dan terdaftar di *Environment Variables*.

## 🚀 Panduan Instalasi & Kompilasi

### 1. Download & Konfigurasi
Clone repository ini, lalu buka file `peluncur.cpp`. Masukkan nama file `.exe` game yang ingin kamu pantau ke dalam daftar berikut:
```cpp
std::vector<const char*> daftarGame = {
    // Masukkan nama executable game kamu di sini
    "Spider-Man2.exe", 
    "MilesMorales.exe"
};
```

### 2. Proses Kompilasi (Build)
Buka terminal di dalam folder project, lalu jalankan ketiga perintah ini secara berurutan:
```bash
# A. Membuat Agen DLL
g++ mesin_fps.cpp src/buffer.c src/hook.c src/trampoline.c src/hde/hde32.c src/hde/hde64.c -shared -o mesin_fps.dll -ld3d11 -lgdi32 -I./include

# B. Membuat Jendela Overlay
g++ layar_fps.cpp -o layar_fps.exe -lgdi32

# C. Membuat Program Penyuntik
g++ peluncur.cpp -o peluncur.exe
```

## 🎮 Cara Penggunaan
1. Buka file **`layar_fps.exe`** (Akan muncul teks FPS di pojok layar).
2. Klik kanan pada **`peluncur.exe`** lalu pilih **Run as Administrator**.
3. Buka game yang sudah kamu daftarkan tadi. Angka FPS akan otomatis muncul dan ter-*update*!
