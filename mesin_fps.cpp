#include <windows.h>
#include <d3d11.h>
#include <fstream>
#include <string>

#include "include/MinHook.h" 

typedef HRESULT(__stdcall* TipePresent)(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags);
TipePresent FungsiPresentAsli = nullptr;

HRESULT __stdcall FungsiPresentPalsu(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
    static int jumlahFrame = 0;
    static DWORD waktuTerakhir = GetTickCount();
    DWORD waktuSekarang = GetTickCount();

    jumlahFrame++;

    if (waktuSekarang - waktuTerakhir >= 1000) {
        
        std::ofstream fileCatatan("C:\\FPS_Counter\\data_fps.txt");
        if (fileCatatan.is_open()) {
            fileCatatan << jumlahFrame;
            fileCatatan.close();
        }
        
        jumlahFrame = 0;
        waktuTerakhir = waktuSekarang;
    }

    return FungsiPresentAsli(pSwapChain, SyncInterval, Flags);
}

DWORD WINAPI UtasUtama(HMODULE modulDLL) {
    WNDCLASSEXA kelasUmpan = { sizeof(WNDCLASSEX), CS_CLASSDC, DefWindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "JendelaUmpan", NULL };
    RegisterClassExA(&kelasUmpan);
    HWND jendelaPalsu = CreateWindowA("JendelaUmpan", NULL, WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, kelasUmpan.hInstance, NULL);

    DXGI_SWAP_CHAIN_DESC deskripsiUmpan;
    ZeroMemory(&deskripsiUmpan, sizeof(deskripsiUmpan));
    deskripsiUmpan.BufferCount = 1;
    deskripsiUmpan.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    deskripsiUmpan.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    deskripsiUmpan.OutputWindow = jendelaPalsu;
    deskripsiUmpan.SampleDesc.Count = 1;
    deskripsiUmpan.Windowed = TRUE;

    IDXGISwapChain* rantaiGambar;
    ID3D11Device* mesinDirectX;
    D3D_FEATURE_LEVEL levelFitur;
    ID3D11DeviceContext* konteks;

    HRESULT hasilPancingan = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &deskripsiUmpan, &rantaiGambar, &mesinDirectX, &levelFitur, &konteks);

    if (SUCCEEDED(hasilPancingan)) {
        void** tabelMemori = *reinterpret_cast<void***>(rantaiGambar);
        void* alamatFungsiAsli = tabelMemori[8]; 

        MH_Initialize();
        MH_CreateHook(alamatFungsiAsli, reinterpret_cast<LPVOID>(&FungsiPresentPalsu), reinterpret_cast<void**>(&FungsiPresentAsli));
        MH_EnableHook(alamatFungsiAsli);

        rantaiGambar->Release();
        mesinDirectX->Release();
        konteks->Release();
    }

    DestroyWindow(jendelaPalsu);
    UnregisterClassA("JendelaUmpan", kelasUmpan.hInstance);

    return 0; 
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD alasanDipanggil, LPVOID lpReserved) {
    if (alasanDipanggil == DLL_PROCESS_ATTACH) {
        DisableThreadLibraryCalls(hModule);
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)UtasUtama, hModule, 0, nullptr);
    }
    return TRUE;
}