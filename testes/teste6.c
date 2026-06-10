#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PROCESSOS 2048

typedef struct
{
    char nome[MAX_PATH];
    DWORD pid;
    SIZE_T memoriaMB;
    int aberto;
} Processo;

Processo processos[MAX_PROCESSOS];
int totalProcessos = 0;

/* Verifica se existe uma janela visível associada ao PID */
BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
    DWORD pid;
    GetWindowThreadProcessId(hwnd, &pid);

    if(pid == (DWORD)lParam &&
       IsWindowVisible(hwnd) &&
       GetWindow(hwnd, GW_OWNER) == NULL)
    {
        return FALSE; // encontrou janela visível
    }

    return TRUE;
}

int ProcessoEstaAberto(DWORD pid)
{
    if(EnumWindows(EnumWindowsProc, (LPARAM)pid))
        return 0;

    return 1;
}

int comparar(const void *a, const void *b)
{
    Processo *p1 = (Processo *)a;
    Processo *p2 = (Processo *)b;

    if(p2->memoriaMB > p1->memoriaMB)
        return 1;

    if(p2->memoriaMB < p1->memoriaMB)
        return -1;

    return 0;
}

void coletarProcessos()
{
    HANDLE snapshot;
    PROCESSENTRY32 pe32;

    snapshot = CreateToolhelp32Snapshot(
        TH32CS_SNAPPROCESS,
        0
    );

    if(snapshot == INVALID_HANDLE_VALUE)
        return;

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if(Process32First(snapshot, &pe32))
    {
        do
        {
            HANDLE hProcess = OpenProcess(
                PROCESS_QUERY_INFORMATION |
                PROCESS_VM_READ,
                FALSE,
                pe32.th32ProcessID
            );

            if(hProcess)
            {
                PROCESS_MEMORY_COUNTERS pmc;

                if(GetProcessMemoryInfo(
                    hProcess,
                    &pmc,
                    sizeof(pmc)))
                {
                    strcpy(
                        processos[totalProcessos].nome,
                        pe32.szExeFile
                    );

                    processos[totalProcessos].pid =
                        pe32.th32ProcessID;

                    processos[totalProcessos].memoriaMB =
                        pmc.WorkingSetSize /
                        (1024 * 1024);

                    processos[totalProcessos].aberto =
                        ProcessoEstaAberto(
                            pe32.th32ProcessID
                        );

                    totalProcessos++;
                }

                CloseHandle(hProcess);
            }

        } while(Process32Next(snapshot, &pe32));
    }

    CloseHandle(snapshot);
}

int WINAPI WinMain(
    HINSTANCE hInst,
    HINSTANCE hPrev,
    LPSTR lpCmdLine,
    int nCmdShow)
{
    coletarProcessos();

    qsort(
        processos,
        totalProcessos,
        sizeof(Processo),
        comparar
    );

    char resultado[15000] = "";
    char linha[300];

    strcat(
        resultado,
        "TOP PROCESSOS POR USO DE MEMORIA\n\n"
    );

    for(int i = 0;
        i < 15 && i < totalProcessos;
        i++)
    {
        sprintf(
            linha,
            "%2d. %-25s %5llu MB [%s]\n",
            i + 1,
            processos[i].nome,
            (unsigned long long)
            processos[i].memoriaMB,
            processos[i].aberto ?
            "ABERTO" :
            "SEGUNDO PLANO"
        );

        strcat(resultado, linha);
    }

    MessageBox(
        NULL,
        resultado,
        "Gerenciador de Tarefas",
        MB_OK
    );

    return 0;
}