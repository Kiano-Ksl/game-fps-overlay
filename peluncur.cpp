#include <windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <vector>

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
    const char* jalurFileDLL = "C:\\FPS_Paten\\mesin_fps.dll"; 
    
    // MASUKIN NAMA GAME KAMU "nama game.exe"
    std::vector<const char*> daftarGame = {
        "Spider-Man2.exe", 
        "MilesMorales.exe", 
        "Spider-Man.exe",
        "ForzaHorizon4.exe"
    };

    std::cout << "[INFO] Peluncur Aktif! Terminal ini menunggu game..." << std::endl;
    DWORD idGameTerakhir = 0; 

    while (true) {
        for (const char* namaExe : daftarGame) {
            DWORD idProses = CariIDProses(namaExe);
            
            if (idProses != 0 && idProses != idGameTerakhir) {
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
        Sleep(2000); 
    }
    return 0;
}