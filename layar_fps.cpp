#include <windows.h>
#include <string>
#include <fstream>

std::string angkaFPS = "--";

LRESULT CALLBACK ProsedurJendela(HWND jendela, UINT pesan, WPARAM wParam, LPARAM lParam) {
    
    if (pesan == WM_PAINT) {
        PAINTSTRUCT ps;
        HDC alatGambar = BeginPaint(jendela, &ps);

        RECT area;
        GetClientRect(jendela, &area);
        HBRUSH kuasHitam = CreateSolidBrush(RGB(0, 0, 0));
        FillRect(alatGambar, &area, kuasHitam);
        DeleteObject(kuasHitam); 
                                // BUAT UBAH WARNA TEKS "FPS" 
        SetTextColor(alatGambar, RGB(255, 255, 255));
        SetBkMode(alatGambar, TRANSPARENT);
        std::string teks = "FPS: " + angkaFPS;
        TextOutA(alatGambar, 0, 0, teks.c_str(), teks.length());

        EndPaint(jendela, &ps);
        return 0;
    }
    
    else if (pesan == WM_TIMER) {
        std::ifstream file("data_fps.txt");
        if (file.is_open()) {
            std::getline(file, angkaFPS);
            file.close();
        } else {
            angkaFPS = "--";
        }
        
        InvalidateRect(jendela, NULL, TRUE);
        return 0;
    }
    
    else if (pesan == WM_DESTROY) {
        PostQuitMessage(0);
        return 0;
    }
    
    return DefWindowProcA(jendela, pesan, wParam, lParam);
}


int main() {
    HWND terminal = GetConsoleWindow();
    ShowWindow(terminal, SW_HIDE);

    WNDCLASSEXA kelas = { sizeof(WNDCLASSEXA), CS_HREDRAW | CS_VREDRAW, ProsedurJendela, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "OverlayFPS", NULL };
    RegisterClassExA(&kelas);

    HWND jendelaOverlay = CreateWindowExA(
        WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOOLWINDOW,
        "OverlayFPS", "FPS Melayang",
        WS_POPUP | WS_VISIBLE,
        10, 10, 200, 50, // Posisi X:10, Y:10
        NULL, NULL, kelas.hInstance, NULL
    );

    SetLayeredWindowAttributes(jendelaOverlay, RGB(0, 0, 0), 0, LWA_COLORKEY);

    SetTimer(jendelaOverlay, 1, 100, NULL);

    MSG pesanSistem;
    while (GetMessage(&pesanSistem, NULL, 0, 0)) {
        TranslateMessage(&pesanSistem);
        DispatchMessage(&pesanSistem);
    }

    return 0;
}