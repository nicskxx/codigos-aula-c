/**
 * Gerenciador de Tarefas para Windows
 * 
 * Compilação: gcc teste8.c -o Gerenciador.exe -mwindows -lpsapi -lcomctl32
 */

#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <commctrl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma comment(lib, "comctl32.lib")

// Constantes de identificação de controles
#define ID_LISTVIEW       1001
#define ID_BUTTON_KILL    1002
#define ID_BUTTON_REFRESH 1003
#define ID_TIMER_REFRESH  1
#define IDC_STATIC_STATS  1004

// Definições de colunas
#define COL_NAME    0
#define COL_PID     1
#define COL_MEMORY  2
#define COL_STATUS  3
#define COL_TYPE    4
#define COL_COUNT   5

// Estrutura para armazenar informações de um processo
typedef struct {
    DWORD pid;
    char name[MAX_PATH];
    SIZE_T memoryMB;
    BOOL isForeground;
    BOOL isSystemCritical;
    BOOL safeToKill;
} ProcessInfo;

// Estrutura auxiliar para enumeração de janelas (usada no callback)
typedef struct {
    DWORD* pids;
    int* count;
    int maxCount;
} EnumWindowsData;

// Variáveis globais
HWND g_hListView = NULL;
HWND g_hStatusLabel = NULL;
ProcessInfo* g_processes = NULL;
int g_processCount = 0;
DWORD g_top5PIDs[5] = {0};
int g_sortDescending = 1;    // 1 = decrescente (maior memória primeiro), 0 = crescente
BOOL g_autoRefresh = TRUE;

// Protótipos das funções
BOOL GetProcessMemoryMB(DWORD pid, SIZE_T* memoryMB);
BOOL IsSystemCritical(DWORD pid, const char* processName);
BOOL IsInWhitelist(const char* processName);
BOOL ProcessHasWindow(DWORD pid);
void CollectWindowsPIDs(DWORD* pids, int* count);
ProcessInfo* GetProcessList(int* count);
void UpdateStatistics();
void PopulateListView(ProcessInfo* processes, int count);
int CompareProcessMemory(const void* a, const void* b);
void RefreshProcessList();
void KillSelectedProcess();
void EnableDisableKillButton();
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam);

// Listas de segurança
const char* systemCriticalList[] = {
    "System", "System Idle Process", "Registry", "smss.exe", "csrss.exe",
    "wininit.exe", "services.exe", "lsass.exe", "winlogon.exe", "svchost.exe",
    "dwm.exe", "explorer.exe", "taskhost.exe", "spoolsv.exe", "WUDFHost.exe",
    "SearchIndexer.exe", "MsMpEng.exe", "audiodg.exe", "fontdrvhost.exe",
    "Memory Compression", "Secure System"
};
#define CRITICAL_COUNT (sizeof(systemCriticalList) / sizeof(systemCriticalList[0]))

const char* whitelist[] = {
    "chrome.exe", "firefox.exe", "msedge.exe", "notepad.exe", "code.exe",
    "discord.exe", "spotify.exe", "devenv.exe", "idea64.exe", "python.exe",
    "winrar.exe", "calc.exe", "mspaint.exe", "putty.exe", "git-bash.exe",
    "cmd.exe", "powershell.exe"
};
#define WHITELIST_COUNT (sizeof(whitelist) / sizeof(whitelist[0]))

// ----------------------------------------------------------------------
// Obtém a memória utilizada por um processo (Working Set) em MB
BOOL GetProcessMemoryMB(DWORD pid, SIZE_T* memoryMB) {
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
    if (hProcess == NULL) {
        *memoryMB = 0;
        return FALSE;
    }
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
        *memoryMB = pmc.WorkingSetSize / (1024 * 1024);
    } else {
        *memoryMB = 0;
    }
    CloseHandle(hProcess);
    return TRUE;
}

// ----------------------------------------------------------------------
// Verifica se o processo é crítico para o sistema (PROTEGIDO)
BOOL IsSystemCritical(DWORD pid, const char* processName) {
    if (pid == 0 || pid == 4) return TRUE;
    for (int i = 0; i < CRITICAL_COUNT; i++) {
        if (_stricmp(processName, systemCriticalList[i]) == 0)
            return TRUE;
    }
    return FALSE;
}

// ----------------------------------------------------------------------
// Verifica se o processo está na whitelist de encerramento seguro
BOOL IsInWhitelist(const char* processName) {
    for (int i = 0; i < WHITELIST_COUNT; i++) {
        if (_stricmp(processName, whitelist[i]) == 0)
            return TRUE;
    }
    return FALSE;
}

// ----------------------------------------------------------------------
// Callback para EnumWindows - coleta PIDs de janelas visíveis
BOOL CALLBACK EnumWindowsProc(HWND hWnd, LPARAM lParam) {
    EnumWindowsData* data = (EnumWindowsData*)lParam;
    if (*data->count >= data->maxCount) return FALSE;
    DWORD pid;
    GetWindowThreadProcessId(hWnd, &pid);
    if (IsWindowVisible(hWnd)) {
        data->pids[(*data->count)++] = pid;
    }
    return TRUE;
}

// ----------------------------------------------------------------------
// Coleta os PIDs de todas as janelas visíveis (para determinar programas abertos)
void CollectWindowsPIDs(DWORD* pids, int* count) {
    EnumWindowsData data;
    data.pids = pids;
    data.count = count;
    data.maxCount = 1024; // tamanho máximo do array (suficiente)
    *count = 0;
    EnumWindows(EnumWindowsProc, (LPARAM)&data);
}

// ----------------------------------------------------------------------
// Coleta todos os processos do sistema e preenche um array ProcessInfo
ProcessInfo* GetProcessList(int* count) {
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        *count = 0;
        return NULL;
    }
    
    PROCESSENTRY32 pe;
    pe.dwSize = sizeof(PROCESSENTRY32);
    
    int totalProcesses = 0;
    if (Process32First(hSnapshot, &pe)) {
        do {
            totalProcesses++;
        } while (Process32Next(hSnapshot, &pe));
    }
    
    ProcessInfo* processes = (ProcessInfo*)malloc(sizeof(ProcessInfo) * totalProcesses);
    if (!processes) {
        CloseHandle(hSnapshot);
        *count = 0;
        return NULL;
    }
    
    // Coleta PIDs das janelas visíveis
    DWORD windowPIDs[1024];
    int windowPIDsCount = 0;
    CollectWindowsPIDs(windowPIDs, &windowPIDsCount);
    
    int idx = 0;
    Process32First(hSnapshot, &pe);
    do {
        DWORD pid = pe.th32ProcessID;
        char* name = pe.szExeFile;
        if (name[0] == '\0') name = "<unknown>";
        
        SIZE_T memoryMB = 0;
        GetProcessMemoryMB(pid, &memoryMB);
        
        BOOL hasWindow = FALSE;
        for (int i = 0; i < windowPIDsCount; i++) {
            if (windowPIDs[i] == pid) {
                hasWindow = TRUE;
                break;
            }
        }
        
        BOOL isCritical = IsSystemCritical(pid, name);
        BOOL inWhitelist = IsInWhitelist(name);
        BOOL safe = (!isCritical && inWhitelist);
        
        processes[idx].pid = pid;
        strcpy(processes[idx].name, name);
        processes[idx].memoryMB = memoryMB;
        processes[idx].isForeground = hasWindow;
        processes[idx].isSystemCritical = isCritical;
        processes[idx].safeToKill = safe;
        idx++;
    } while (Process32Next(hSnapshot, &pe));
    
    CloseHandle(hSnapshot);
    *count = idx;
    return processes;
}

// ----------------------------------------------------------------------
// Comparação para ordenar processos por memória
int CompareProcessMemory(const void* a, const void* b) {
    ProcessInfo* pa = (ProcessInfo*)a;
    ProcessInfo* pb = (ProcessInfo*)b;
    if (g_sortDescending)
        return (pb->memoryMB - pa->memoryMB);
    else
        return (pa->memoryMB - pb->memoryMB);
}

// ----------------------------------------------------------------------
// Atualiza os labels de estatísticas
void UpdateStatistics() {
    MEMORYSTATUSEX memStatus;
    memStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memStatus);
    DWORDLONG totalRAMMB = memStatus.ullTotalPhys / (1024 * 1024);
    
    int totalProcs = g_processCount;
    int openProgs = 0;
    int background = 0;
    for (int i = 0; i < g_processCount; i++) {
        if (g_processes[i].isForeground) openProgs++;
        else background++;
    }
    
    char stats[512];
    snprintf(stats, sizeof(stats),
             "Total de RAM: %llu MB   |   Processos ativos: %d   |   Programas abertos: %d   |   Segundo plano: %d",
             totalRAMMB, totalProcs, openProgs, background);
    SetWindowText(g_hStatusLabel, stats);
}

// ----------------------------------------------------------------------
// Preenche a ListView com os dados atuais (ordenados)
void PopulateListView(ProcessInfo* processes, int count) {
    qsort(processes, count, sizeof(ProcessInfo), CompareProcessMemory);
    
    // Identifica os 5 maiores consumidores
    memset(g_top5PIDs, 0, sizeof(g_top5PIDs));
    int topCount = (count < 5) ? count : 5;
    for (int i = 0; i < topCount; i++) {
        g_top5PIDs[i] = processes[i].pid;
    }
    
    ListView_DeleteAllItems(g_hListView);
    
    LVITEM lvItem;
    for (int i = 0; i < count; i++) {
        ProcessInfo* p = &processes[i];
        
        lvItem.mask = LVIF_TEXT | LVIF_PARAM;
        lvItem.iItem = i;
        lvItem.iSubItem = 0;
        lvItem.pszText = p->name;
        lvItem.lParam = (LPARAM)p->pid;
        ListView_InsertItem(g_hListView, &lvItem);
        
        char pidStr[16];
        snprintf(pidStr, sizeof(pidStr), "%lu", p->pid);
        ListView_SetItemText(g_hListView, i, COL_PID, pidStr);
        
        char memStr[32];
        snprintf(memStr, sizeof(memStr), "%llu MB", (unsigned long long)p->memoryMB);
        ListView_SetItemText(g_hListView, i, COL_MEMORY, memStr);
        
        char* status = p->isForeground ? "ABERTO" : "SEGUNDO PLANO";
        ListView_SetItemText(g_hListView, i, COL_STATUS, status);
        
        char* tipo = p->isSystemCritical ? "PROTEGIDO" : "SEGURO";
        ListView_SetItemText(g_hListView, i, COL_TYPE, tipo);
    }
    
    UpdateStatistics();
}

// ----------------------------------------------------------------------
// Atualiza completamente a lista de processos e a interface
void RefreshProcessList() {
    if (g_processes) {
        free(g_processes);
        g_processes = NULL;
    }
    
    g_processes = GetProcessList(&g_processCount);
    if (g_processes) {
        PopulateListView(g_processes, g_processCount);
    } else {
        ListView_DeleteAllItems(g_hListView);
        SetWindowText(g_hStatusLabel, "Erro ao obter lista de processos.");
    }
}

// ----------------------------------------------------------------------
// Encerra o processo selecionado (corrigido)
void KillSelectedProcess() {
    int selIndex = ListView_GetNextItem(g_hListView, -1, LVNI_SELECTED);
    if (selIndex == -1) {
        MessageBox(GetParent(g_hListView), "Nenhum processo selecionado.", "Aviso", MB_OK | MB_ICONWARNING);
        return;
    }
    
    // Obtém o PID corretamente
    LVITEM lvi;
    lvi.mask = LVIF_PARAM;
    lvi.iItem = selIndex;
    lvi.iSubItem = 0;
    SendMessage(g_hListView, LVM_GETITEM, 0, (LPARAM)&lvi);
    DWORD pid = (DWORD)lvi.lParam;
    
    ProcessInfo* target = NULL;
    for (int i = 0; i < g_processCount; i++) {
        if (g_processes[i].pid == pid) {
            target = &g_processes[i];
            break;
        }
    }
    if (!target) {
        MessageBox(GetParent(g_hListView), "Processo não encontrado.", "Erro", MB_OK | MB_ICONERROR);
        return;
    }
    
    if (!target->safeToKill) {
        MessageBox(GetParent(g_hListView), "Este processo é protegido ou não está na lista de permissões.\nNão é possível encerrá-lo.", "Acesso negado", MB_OK | MB_ICONERROR);
        return;
    }
    
    char msg[256];
    snprintf(msg, sizeof(msg), "Deseja realmente encerrar o processo:\n%s (PID: %lu) ?", target->name, pid);
    int resposta = MessageBox(GetParent(g_hListView), msg, "Confirmar encerramento", MB_YESNO | MB_ICONQUESTION);
    if (resposta != IDYES) return;
    
    HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
    if (hProcess == NULL) {
        MessageBox(GetParent(g_hListView), "Não foi possível abrir o processo para encerramento.\nVerifique as permissões.", "Erro", MB_OK | MB_ICONERROR);
        return;
    }
    
    if (TerminateProcess(hProcess, 0)) {
        MessageBox(GetParent(g_hListView), "Processo encerrado com sucesso.", "Sucesso", MB_OK | MB_ICONINFORMATION);
        RefreshProcessList();
    } else {
        MessageBox(GetParent(g_hListView), "Falha ao encerrar o processo.", "Erro", MB_OK | MB_ICONERROR);
    }
    CloseHandle(hProcess);
}

// ----------------------------------------------------------------------
// Habilita/desabilita o botão "Encerrar" (corrigido)
void EnableDisableKillButton() {
    HWND hBtn = GetDlgItem(GetParent(g_hListView), ID_BUTTON_KILL);
    int selIndex = ListView_GetNextItem(g_hListView, -1, LVNI_SELECTED);
    BOOL enable = FALSE;
    if (selIndex != -1) {
        LVITEM lvi;
        lvi.mask = LVIF_PARAM;
        lvi.iItem = selIndex;
        lvi.iSubItem = 0;
        SendMessage(g_hListView, LVM_GETITEM, 0, (LPARAM)&lvi);
        DWORD pid = (DWORD)lvi.lParam;
        
        for (int i = 0; i < g_processCount; i++) {
            if (g_processes[i].pid == pid && g_processes[i].safeToKill) {
                enable = TRUE;
                break;
            }
        }
    }
    EnableWindow(hBtn, enable);
}

// ----------------------------------------------------------------------
// Tratamento de mensagens da janela principal
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_CREATE: {
            g_hListView = CreateWindow(WC_LISTVIEW, "",
                WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SINGLESEL | LVS_SHOWSELALWAYS,
                10, 10, 600, 400, hWnd, (HMENU)ID_LISTVIEW, GetModuleHandle(NULL), NULL);
            
            LVCOLUMN lvc;
            lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;
            lvc.cx = 180;  lvc.pszText = "Processo";   lvc.iSubItem = COL_NAME;   ListView_InsertColumn(g_hListView, COL_NAME, &lvc);
            lvc.cx = 80;   lvc.pszText = "PID";        lvc.iSubItem = COL_PID;    ListView_InsertColumn(g_hListView, COL_PID, &lvc);
            lvc.cx = 100;  lvc.pszText = "Memória (MB)";lvc.iSubItem = COL_MEMORY; ListView_InsertColumn(g_hListView, COL_MEMORY, &lvc);
            lvc.cx = 110;  lvc.pszText = "Status";     lvc.iSubItem = COL_STATUS;  ListView_InsertColumn(g_hListView, COL_STATUS, &lvc);
            lvc.cx = 100;  lvc.pszText = "Tipo";       lvc.iSubItem = COL_TYPE;    ListView_InsertColumn(g_hListView, COL_TYPE, &lvc);
            
            CreateWindow("BUTTON", "Encerrar Processo", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         10, 420, 150, 30, hWnd, (HMENU)ID_BUTTON_KILL, GetModuleHandle(NULL), NULL);
            CreateWindow("BUTTON", "Atualizar", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                         170, 420, 100, 30, hWnd, (HMENU)ID_BUTTON_REFRESH, GetModuleHandle(NULL), NULL);
            g_hStatusLabel = CreateWindow("STATIC", "", WS_CHILD | WS_VISIBLE | SS_SUNKEN,
                                          10, 460, 680, 25, hWnd, (HMENU)IDC_STATIC_STATS, GetModuleHandle(NULL), NULL);
            
            ListView_SetExtendedListViewStyle(g_hListView, LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
            RefreshProcessList();
            SetTimer(hWnd, ID_TIMER_REFRESH, 3000, NULL);
            break;
        }
        
        case WM_SIZE: {
            int width = LOWORD(lParam);
            int height = HIWORD(lParam);
            SetWindowPos(g_hListView, NULL, 10, 10, width - 20, height - 110, SWP_NOZORDER);
            SetWindowPos(GetDlgItem(hWnd, ID_BUTTON_KILL), NULL, 10, height - 90, 150, 30, SWP_NOZORDER);
            SetWindowPos(GetDlgItem(hWnd, ID_BUTTON_REFRESH), NULL, 170, height - 90, 100, 30, SWP_NOZORDER);
            SetWindowPos(g_hStatusLabel, NULL, 10, height - 50, width - 20, 25, SWP_NOZORDER);
            break;
        }
        
        case WM_TIMER:
            if (wParam == ID_TIMER_REFRESH && g_autoRefresh)
                RefreshProcessList();
            break;
        
        case WM_COMMAND:
            if (LOWORD(wParam) == ID_BUTTON_KILL)
                KillSelectedProcess();
            else if (LOWORD(wParam) == ID_BUTTON_REFRESH)
                RefreshProcessList();
            break;
        
        case WM_NOTIFY: {
            NMHDR* nmhdr = (NMHDR*)lParam;
            if (nmhdr->hwndFrom == g_hListView) {
                switch (nmhdr->code) {
                    case LVN_ITEMCHANGED:
                        EnableDisableKillButton();
                        break;
                    case NM_CUSTOMDRAW: {
                        NMLVCUSTOMDRAW* lvcd = (NMLVCUSTOMDRAW*)lParam;
                        if (lvcd->nmcd.dwDrawStage == CDDS_PREPAINT)
                            return CDRF_NOTIFYITEMDRAW;
                        else if (lvcd->nmcd.dwDrawStage == CDDS_ITEMPREPAINT) {
                            DWORD pid = (DWORD)lvcd->nmcd.lItemlParam;
                            for (int i = 0; i < 5; i++) {
                                if (g_top5PIDs[i] == pid) {
                                    lvcd->clrText = RGB(255, 0, 0);
                                    break;
                                }
                            }
                            return CDRF_DODEFAULT;
                        }
                        break;
                    }
                    case LVN_COLUMNCLICK: {
                        NMLISTVIEW* nmlv = (NMLISTVIEW*)lParam;
                        if (nmlv->iSubItem == COL_MEMORY) {
                            g_sortDescending = !g_sortDescending;
                            RefreshProcessList();
                        }
                        break;
                    }
                }
            }
            break;
        }
        
        case WM_DESTROY:
            KillTimer(hWnd, ID_TIMER_REFRESH);
            if (g_processes) free(g_processes);
            PostQuitMessage(0);
            break;
        
        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }
    return 0;
}

// ----------------------------------------------------------------------
// Ponto de entrada
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC = ICC_LISTVIEW_CLASSES;
    InitCommonControlsEx(&icex);
    
    WNDCLASSEX wc = {0};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "TaskManagerClass";
    if (!RegisterClassEx(&wc)) return 1;
    
    HWND hWnd = CreateWindowEx(0, "TaskManagerClass", "Gerenciador de Tarefas",
                               WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                               CW_USEDEFAULT, CW_USEDEFAULT, 800, 550,
                               NULL, NULL, hInstance, NULL);
    if (!hWnd) return 1;
    
    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);
    
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return (int)msg.wParam;
}