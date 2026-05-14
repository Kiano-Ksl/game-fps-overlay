#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>
#include <fstream>

DWORD CariIDProses(const char* namaExe) {
    DWORD idProses = 0;
    HANDLE alatCari = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    
    if (alatCari != INVALID_HANDLE_VALUE) {
        PROCESSENTRY32 infoProgram;
        infoProgram.dwSize = sizeof(infoProgram);
        
        if (Process32First(alatCari, &infoProgram)) {
            do {
                if (_stricmp(infoProgram.szExeFile, namaExe) == 0) {
                    idProses = infoProgram.th32ProcessID;
                    break;
                }
            } while (Process32Next(alatCari, &infoProgram));
        }
    }
    CloseHandle(alatCari);
    return idProses;
}

int main() {
    const char* jalurFileDLL = "C:\\FPS_Counter\\mesin_fps.dll"; 
    const char* jalurFileData = "C:\\FPS_Counter\\data_fps.txt"; 
    
    std::vector<const char*> daftarGame = {
        // MASUKIN NAMA GAME KAMU DI SINI "NAMA GAME.exe"
        "Spider-Man2.exe", 
        "MilesMorales.exe", 
        "Spider-Man.exe",
        "ForzaHorizon4.exe"
    };

    std::cout << "[INFO] Peluncur Aktif! Terminal ini menunggu game..." << std::endl;
    DWORD idGameTerakhir = 0; 

    while (true) {
        bool adaGameNyala = false; 

        for (const char* namaExe : daftarGame) {
            DWORD idProses = CariIDProses(namaExe);
            
            if (idProses != 0) {
                adaGameNyala = true; 
                
                if (idProses != idGameTerakhir) {
                    std::cout << "\n[+] Game Ditemukan: " << namaExe << std::endl;
                    HANDLE aksesGame = OpenProcess(PROCESS_ALL_ACCESS, FALSE, idProses);
                    if (aksesGame != NULL) {
                        LPVOID lokasiMemori = VirtualAllocEx(aksesGame, NULL, strlen(jalurFileDLL) + 1, MEM_COMMIT, PAGE_READWRITE);
                        WriteProcessMemory(aksesGame, lokasiMemori, (LPVOID)jalurFileDLL, strlen(jalurFileDLL) + 1, NULL);
                        
                        LPVOID fungsiLoadLibrary = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");
                        HANDLE eksekusi = CreateRemoteThread(aksesGame, NULL, 0, (LPTHREAD_START_ROUTINE)fungsiLoadLibrary, lokasiMemori, 0, NULL);
                        
                        if (eksekusi != NULL) {
                            std::cout << "[SUKSES] Agen berhasil ditanam!" << std::endl;
                            idGameTerakhir = idProses; 
                            CloseHandle(eksekusi);
                        }
                        CloseHandle(aksesGame);
                    }
                }
            }
        }

        if (!adaGameNyala && idGameTerakhir != 0) {
            std::cout << "[-] Game ditutup. Mereset angka FPS ke '--'..." << std::endl;
            idGameTerakhir = 0; 

            std::ofstream fileData(jalurFileData);
            if (fileData.is_open()) {
                fileData << "--";
                fileData.close();
            }
        }

        Sleep(2000); 
    }
    return 0;
}