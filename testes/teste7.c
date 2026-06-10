#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

// Definições manuais das mensagens e macros do ListView (para não depender do commctrl.h)
#ifndef LVM_FIRST 
    #define LVM_FIRST 0x1000
#endif
#define LVM_INSERTCOLUMN   (LVM_FIRST + 97)
#define LVM_SETITEMTEXT    (LVM_FIRST + 116)
#define LVM_INSERTITEM     (LVM_FIRST + 77)
#define LVM_DELETEALLITEMS (LVM_FIRST + 9)
#define LVM_GETNEXTITEM    (LVM_FIRST + 12)
#define LVM_GETITEMTEXT    (LVM_FIRST + 115)

#define LVIF_TEXT 0x0001
#define LVCF_TEXT 0x0001
#define LVCF_WIDTH 0x0002
#define LVCF_SUBITEM 0x0008

#define LVS_REPORT 0x0001
#define LVS_SINGLESEL 0x0004

#define LVNI_SELECTED 0x0002

#define WC_LISTVIEW "SysListView32"

#define MAKELPARAM(low, high) ((LPARAM)(DWORD)MAKELONG(low, high))

// Estruturas necessárias
typedef struct _LVCOLUMN {
    UINT mask;
    int fmt;
    int cx;
    LPTSTR pszText;
    int cchTextMax;
    int iSubItem;
    int iImage;
    int iOrder;
} LVCOLUMN, *LPLVCOLUMN;

typedef struct _LVITEM {
    UINT mask;
    int iItem;
    int iSubItem;
    UINT state;
    UINT stateMask;
    LPTSTR pszText;
    int cchTextMax;
    int iImage;
    LPARAM lParam;
    int iIndent;
    int iGroupId;
    UINT cColumns;
    UINT puColumns;
} LVITEM, *LPLVITEM;

// --- Seu código original continua aqui ---
#define MAX_PROCESSOS 2048
#define ID_LISTVIEW 1001
#define ID_TERMINATE_BTN 1002
#define REFRESH_TIMER 1003
#define REFRESH_INTERVAL_MS 2000

typedef struct
{
    char nome[MAX_PATH];
    DWORD pid;
    SIZE_T memoriaMB;
    int aberto;
    int protegido;
    int permitido;
} Processo;

Processo processos[MAX_PROCESSOS];
int totalProcessos = 0;
HWND hListView;
HWND hMainWindow;

char* whitelist[] = {
    "chrome.exe", "msedge.exe", "firefox.exe",
    "discord.exe", "spotify.exe", "code.exe",
    "notepad.exe", "explorer.exe", "cmd.exe",
    "powershell.exe", "winword.exe", "excel.exe"
};
int whitelistCount = sizeof(whitelist) / sizeof(whitelist[0]);

int isProcessWhitelisted(const char* nome)
{
    char nomeLower[MAX_PATH];
    strcpy(nomeLower, nome);
    for(int i = 0; nomeLower[i]; i++) nomeLower[i] = tolower(nomeLower[i]);
    for(int i = 0; i < whitelistCount; i++)
        if(strcmp(nomeLower, whitelist[i]) == 0) return 1;
    return 0;
}

int isProcessProtected(const char* nome)
{
    const char* protegidos[] = {
        "System","System Idle Process","svchost.exe","winlogon.exe",
        "csrss.exe","smss.exe","services.exe","lsass.exe","wininit.exe"
    };
    int protegidosCount = sizeof(protegidos)/sizeof(protegidos[0]);
    char nomeLower[MAX_PATH];
    strcpy(nomeLower, nome);
    for(int i=0; nomeLower[i]; i++) nomeLower[i] = tolower(nomeLower[i]);
    for(int i=0; i<protegidosCount; i++) {
        char protLower[MAX_PATH];
        strcpy(protLower, protegidos[i]);
        for(int j=0; protLower[j]; j++) protLower[j] = tolower(protLower[j]);
        if(strcmp(nomeLower, protLower)==0) return 1;
    }
    return 0;
}

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);
    if(pid == (DWORD)lParam && IsWindowVisible(hwnd) && GetWindow(hwnd, GW_OWNER)==NULL)
        return FALSE;
    return TRUE;
}

int ProcessoEstaAberto(DWORD pid)
{
    return !EnumWindows(EnumWindowsProc, (LPARAM)pid);
}

int comparar(const void *a, const void *b)
{
    Processo *p1 = (Processo*)a, *p2 = (Processo*)b;
    if(p2->memoriaMB > p1->memoriaMB) return 1;
    if(p2->memoriaMB < p1->memoriaMB) return -1;
    return 0;
}

void coletarProcessos()
{
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
    if(snapshot == INVALID_HANDLE_VALUE) return;
    PROCESSENTRY32 pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32);
    totalProcessos = 0;
    if(Process32First(snapshot, &pe32)) {
        do {
            HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION|PROCESS_VM_READ,FALSE,pe32.th32ProcessID);
            if(hProcess && totalProcessos<MAX_PROCESSOS) {
                PROCESS_MEMORY_COUNTERS pmc;
                if(GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                    strcpy(processos[totalProcessos].nome, pe32.szExeFile);
                    processos[totalProcessos].pid = pe32.th32ProcessID;
                    processos[totalProcessos].memoriaMB = pmc.WorkingSetSize/(1024*1024);
                    processos[totalProcessos].aberto = ProcessoEstaAberto(pe32.th32ProcessID);
                    processos[totalProcessos].protegido = isProcessProtected(pe32.szExeFile);
                    processos[totalProcessos].permitido = isProcessWhitelisted(pe32.szExeFile);
                    totalProcessos++;
                }
                CloseHandle(hProcess);
            }
        } while(Process32Next(snapshot, &pe32));
    }
    CloseHandle(snapshot);
}

void popularListView()
{
    Processo temp[MAX_PROCESSOS];
    memcpy(temp, processos, sizeof(Processo)*totalProcessos);
    qsort(temp, totalProcessos, sizeof(Processo), comparar);
    
    SendMessage(hListView, LVM_DELETEALLITEMS, 0, 0);
    char buffer[100];
    LVITEM lvItem = {0};
    lvItem.mask = LVIF_TEXT;
    for(int i=0; i<totalProcessos; i++) {
        lvItem.iItem = i;
        lvItem.iSubItem = 0;
        lvItem.pszText = temp[i].nome;
        SendMessage(hListView, LVM_INSERTITEM, 0, (LPARAM)&lvItem);
        
        sprintf(buffer, "%d", temp[i].pid);
        SendMessage(hListView, LVM_SETITEMTEXT, i, MAKELPARAM(1, (LPARAM)buffer));
        sprintf(buffer, "%.2f MB", (double)temp[i].memoriaMB);
        SendMessage(hListView, LVM_SETITEMTEXT, i, MAKELPARAM(2, (LPARAM)buffer));
        sprintf(buffer, "%s", temp[i].aberto ? "ABERTO" : "SEGUNDO PLANO");
        SendMessage(hListView, LVM_SETITEMTEXT, i, MAKELPARAM(3, (LPARAM)buffer));
        if(temp[i].protegido) sprintf(buffer, "PROTEGIDO");
        else if(temp[i].permitido) sprintf(buffer, "ENCERRAR");
        else sprintf(buffer, "BLOQUEADO");
        SendMessage(hListView, LVM_SETITEMTEXT, i, MAKELPARAM(4, (LPARAM)buffer));
    }
}

void encerrarProcesso()
{
    int selectedIndex = (int)SendMessage(hListView, LVM_GETNEXTITEM, -1, LVNI_SELECTED);
    if(selectedIndex == -1) {
        MessageBox(hMainWindow, "Selecione um processo!", "Aviso", MB_OK|MB_ICONWARNING);
        return;
    }
    char pidStr[20], acaoStr[20], nomeProcesso[MAX_PATH];
    SendMessage(hListView, LVM_GETITEMTEXT, selectedIndex, MAKELPARAM(0, (LPARAM)nomeProcesso));
    SendMessage(hListView, LVM_GETITEMTEXT, selectedIndex, MAKELPARAM(1, (LPARAM)pidStr));
    SendMessage(hListView, LVM_GETITEMTEXT, selectedIndex, MAKELPARAM(4, (LPARAM)acaoStr));
    DWORD pid = atoi(pidStr);
    if(strcmp(acaoStr, "ENCERRAR") != 0) {
        MessageBox(hMainWindow, "Processo protegido ou bloqueado!", "Ação negada", MB_OK|MB_ICONERROR);
        return;
    }
    char msg[256];
    sprintf(msg, "Encerrar '%s' (PID %d)?", nomeProcesso, pid);
    if(MessageBox(hMainWindow, msg, "Confirmar", MB_YESNO|MB_ICONQUESTION)==IDYES) {
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
        if(hProcess) {
            if(TerminateProcess(hProcess,0)) {
                MessageBox(hMainWindow, "Processo encerrado!", "Sucesso", MB_OK);
                coletarProcessos();
                popularListView();
            } else MessageBox(hMainWindow, "Falha ao encerrar!", "Erro", MB_OK);
            CloseHandle(hProcess);
        } else MessageBox(hMainWindow, "Não foi possível abrir o processo!", "Erro", MB_OK);
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg) {
        case WM_CREATE: {
            hListView = CreateWindowEx(0, WC_LISTVIEW, "", WS_CHILD|WS_VISIBLE|LVS_REPORT|LVS_SINGLESEL,
                                       10,10,580,400, hwnd, (HMENU)ID_LISTVIEW, GetModuleHandle(NULL), NULL);
            LVCOLUMN col = {0};
            col.mask = LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM;
            col.pszText = "Nome do Processo"; col.cx = 200;
            SendMessage(hListView, LVM_INSERTCOLUMN, 0, (LPARAM)&col);
            col.pszText = "PID"; col.cx = 80;
            SendMessage(hListView, LVM_INSERTCOLUMN, 1, (LPARAM)&col);
            col.pszText = "Memória (MB)"; col.cx = 100;
            SendMessage(hListView, LVM_INSERTCOLUMN, 2, (LPARAM)&col);
            col.pszText = "Status"; col.cx = 100;
            SendMessage(hListView, LVM_INSERTCOLUMN, 3, (LPARAM)&col);
            col.pszText = "Ação"; col.cx = 80;
            SendMessage(hListView, LVM_INSERTCOLUMN, 4, (LPARAM)&col);
            
            CreateWindow("BUTTON", "Encerrar Processo Selecionado", WS_CHILD|WS_VISIBLE|BS_PUSHBUTTON,
                         10,420,200,30, hwnd, (HMENU)ID_TERMINATE_BTN, GetModuleHandle(NULL), NULL);
            coletarProcessos();
            popularListView();
            SetTimer(hwnd, REFRESH_TIMER, REFRESH_INTERVAL_MS, NULL);
            break;
        }
        case WM_TIMER:
            if(wParam == REFRESH_TIMER) { coletarProcessos(); popularListView(); }
            break;
        case WM_COMMAND:
            if(LOWORD(wParam)==ID_TERMINATE_BTN) encerrarProcesso();
            break;
        case WM_SIZE: {
            int w = LOWORD(lParam), h = HIWORD(lParam);
            SetWindowPos(hListView, NULL, 10, 10, w-20, h-80, SWP_NOZORDER);
            SetWindowPos(GetDlgItem(hwnd, ID_TERMINATE_BTN), NULL, 10, h-60, 200, 30, SWP_NOZORDER);
            break;
        }
        case WM_DESTROY:
            KillTimer(hwnd, REFRESH_TIMER);
            PostQuitMessage(0);
            break;
        default: return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR cmd, int show)
{
    // Inicializar controles comuns (obrigatório para ListView)
    INITCOMMONCONTROLSEX icex = {sizeof(INITCOMMONCONTROLSEX), ICC_LISTVIEW_CLASSES};
    InitCommonControlsEx(&icex);
    
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.lpszClassName = "TaskManagerClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    if(!RegisterClass(&wc)) { MessageBox(NULL,"Erro ao registrar classe","Erro",MB_OK); return 1; }
    hMainWindow = CreateWindowEx(0, "TaskManagerClass", "Gerenciador de Tarefas",
                                 WS_OVERLAPPEDWINDOW|WS_VISIBLE,
                                 CW_USEDEFAULT, CW_USEDEFAULT, 600, 500,
                                 NULL, NULL, hInst, NULL);
    if(!hMainWindow) { MessageBox(NULL,"Erro ao criar janela","Erro",MB_OK); return 1; }
    ShowWindow(hMainWindow, show);
    UpdateWindow(hMainWindow);
    MSG msg;
    while(GetMessage(&msg, NULL, 0,0)) { TranslateMessage(&msg); DispatchMessage(&msg); }
    return msg.wParam;
}