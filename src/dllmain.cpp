#include <windows.h>

static HMODULE g_module = nullptr;

static bool IsEnabled() {
    wchar_t path[MAX_PATH];
    DWORD len = GetModuleFileNameW(g_module, path, MAX_PATH);
    if (len == 0 || len >= MAX_PATH) return true;

    wchar_t* dot = nullptr;
    for (wchar_t* p = path; *p; ++p) {
        if (*p == L'.') dot = p;
        else if (*p == L'\\' || *p == L'/') dot = nullptr;
    }
    if (!dot || (dot - path) + 5 > MAX_PATH) return true;
    lstrcpyW(dot, L".ini");

    wchar_t value[16];
    GetPrivateProfileStringW(L"General", L"Enabled", L"true", value, 16, path);
    return lstrcmpiW(value, L"false") != 0 && lstrcmpiW(value, L"0") != 0;
}

// Screen rectangle of the client area of the foreground window, if that window
// belongs to the game process and is not minimized.
static bool GetGameClientRect(RECT* out) {
    HWND fg = GetForegroundWindow();
    if (!fg || IsIconic(fg)) return false;

    DWORD pid = 0;
    GetWindowThreadProcessId(fg, &pid);
    if (pid != GetCurrentProcessId()) return false;

    RECT rc;
    if (!GetClientRect(fg, &rc)) return false;

    POINT topLeft = { rc.left, rc.top };
    POINT bottomRight = { rc.right, rc.bottom };
    if (!ClientToScreen(fg, &topLeft) || !ClientToScreen(fg, &bottomRight)) return false;
    if (bottomRight.x <= topLeft.x || bottomRight.y <= topLeft.y) return false;

    *out = { topLeft.x, topLeft.y, bottomRight.x, bottomRight.y };
    return true;
}

static DWORD WINAPI ClipThread(LPVOID) {
    if (!IsEnabled()) return 0;

    bool clipped = false;
    for (;;) {
        RECT target;
        if (GetGameClientRect(&target)) {
            RECT current;
            if (!GetClipCursor(&current) || !EqualRect(&current, &target)) {
                ClipCursor(&target);
            }
            clipped = true;
        } else if (clipped) {
            ClipCursor(nullptr);
            clipped = false;
        }
        Sleep(100);
    }
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID) {
    if (reason == DLL_PROCESS_ATTACH) {
        g_module = hModule;
        DisableThreadLibraryCalls(hModule);
        HANDLE thread = CreateThread(nullptr, 0, ClipThread, nullptr, 0, nullptr);
        if (thread) CloseHandle(thread);
    }
    return TRUE;
}
