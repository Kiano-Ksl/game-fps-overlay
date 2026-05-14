# 🎯 FPS Counter Overlay (DirectX 11 Hooking)

![Version](https://img.shields.io/badge/Version-1.0.0-brightgreen)
![Platform](https://img.shields.io/badge/Platform-Windows-blue)
![Language](https://img.shields.io/badge/Language-C++-orange)

Sebuah program pemantau FPS (*Frames Per Second*) yang sangat ringan dan elegan. Program ini dirancang dengan bahasa C++ murni untuk berjalan di latar belakang (siluman) dan menyuntikkan *overlay* angka FPS langsung ke dalam game yang menggunakan mesin DirectX 11. 

Berbeda dengan aplikasi *monitoring* berat lainnya, program ini menggunakan jendela transparan (*click-through*) yang bersih, ringkas, dan memakan **0% CPU Usage** saat *idle*.

---

## ✨ Fitur Utama
*   **🪟 Layar Kaca Transparan:** Angka FPS melayang di pojok layar tanpa mengganggu klik mouse kamu saat bermain game.
*   **🎯 Target Spesifik:** Program hanya akan menyuntikkan agen ke game yang sudah kamu daftarkan (Aman dan terstruktur).
*   **🪶 Sangat Ringan:** Kode sumber telah dibersihkan dan dioptimalkan agar berjalan cepat tanpa beban sistem tambahan.
*   **🎨 Warna Kustom:** Teks FPS dapat disesuaikan warnanya sesuai selera langsung dari *source code*.

---

## 📂 Struktur Proyek
Pastikan susunan folder kamu terlihat seperti ini sebelum memulai kompilasi:

```text
📦 FPS_Counter
 ┣ 📂 include          # File header MinHook
 ┣ 📂 src              # File source MinHook
 ┣ 📜 data_fps.txt     # File dinamis penyimpan angka FPS
 ┣ 📜 layar_fps.cpp    # Source code: Jendela Overlay Kaca
 ┣ 📜 mesin_fps.cpp    # Source code: Agen DLL pembaca DirectX 11
 ┗ 📜 peluncur.cpp     # Source code: Penyuntik otomatis ke dalam game
```

---

## ⚙️ Persyaratan Sistem (Prerequisites)
Sebelum mengunduh dan menggunakan program ini, pastikan komputermu sudah memiliki:
1. OS Windows (10 atau 11).
2. **MinGW (g++)** compiler terinstal dan terdaftar di *Environment Variables*.
3. Visual Studio Code (Atau *code editor* pilihanmu).

---

## 🚀 Panduan Instalasi & Kompilasi (Step-by-Step)

### 1. Download Repository
Kamu bisa mengunduh proyek ini dengan perintah Git berikut:
```bash
git clone [https://github.com/USERNAME_GITHUB_KAMU/FPS-Counter-Overlay.git](https://github.com/USERNAME_GITHUB_KAMU/FPS-Counter-Overlay.git)
```

### 2. Konfigurasi Game Kamu
Secara *default*, program ini menargetkan game *Spider-Man*. Jika kamu ingin menambahkan game lain, buka file `peluncur.cpp`, cari bagian ini, dan masukkan nama `.exe` game kamu:

```cpp
std::vector<const char*> daftarGame = {
    // MASUKIN NAMA GAME KAMU DI SINI "NAMA GAME.exe"
    "Spider-Man2.exe", 
    "MilesMorales.exe", 
    "Spider-Man.exe",
    "ForzaHorizon4.exe"
};
```

### 3. Proses Kompilasi (Build)
Buka terminal (CMD/PowerShell) tepat di dalam folder `FPS_Counter`, lalu jalankan ketiga perintah sakti ini secara berurutan:

**A. Membuat Agen DLL (Mesin FPS)**
```bash
g++ mesin_fps.cpp src/buffer.c src/hook.c src/trampoline.c src/hde/hde32.c src/hde/hde64.c -shared -o mesin_fps.dll -ld3d11 -lgdi32 -I./include
```

**B. Membuat Jendela Overlay (Layar FPS)**
```bash
g++ layar_fps.cpp -o layar_fps.exe -lgdi32
```

**C. Membuat Program Penyuntik (Peluncur)**
```bash
g++ peluncur.cpp -o peluncur.exe
```

---

## 🎮 Cara Penggunaan
Jika ketiga file `.exe` dan `.dll` sudah berhasil dibuat, ikuti langkah ini setiap kali kamu ingin bermain game:

1. Buka/Jalankan file **`layar_fps.exe`** (Akan muncul teks `FPS: --` di pojok kiri atas monitormu).
2. **Sangat Penting:** Klik kanan pada **`peluncur.exe`** lalu pilih **Run as Administrator**. (Terminal hitam akan muncul menunggu game dibuka).
3. Buka game yang sudah kamu daftarkan tadi. 
4. Pantau terminal, jika tertulis `[SUKSES] Agen berhasil ditanam!`, maka FPS-mu akan langsung muncul di layar!

---
*Developed for educational purposes regarding Windows API & DirectX 11 Hooking.*
