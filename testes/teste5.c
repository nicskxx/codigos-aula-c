#include <windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <stdio.h>
#include <string.h>

#define MAX_PROCESSOS 1024

typedef struct {
    char nome[MAX_PATH];
    DWORD pid;
    SIZE_T memoriaMB;
} Processo;

Processo processos[MAX_PROCESSOS];
int totalProcessos = 0;

int comparar(const void *a, const void *b)
{
    Processo *p1 = (Processo *)a;
    Processo *p2 = (Processo *)b;

    if (p2->memoriaMB > p1->memoriaMB) return 1;
    if (p2->memoriaMB < p1->memoriaMB) return -1;
    return 0;
}

void coletarProcessos()
{
    HANDLE snapshot;
    PROCESSENTRY32 pe32;

    snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if(snapshot == INVALID_HANDLE_VALUE)
        return;

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if(Process32First(snapshot, &pe32))
    {
        do
        {
            HANDLE hProcess = OpenProcess(
                PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
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
                    strcpy(processos[totalProcessos].nome,
                           pe32.szExeFile);

                    processos[totalProcessos].pid =
                        pe32.th32ProcessID;

                    processos[totalProcessos].memoriaMB =
                        pmc.WorkingSetSize / (1024 * 1024);

                    totalProcessos++;
                }

                CloseHandle(hProcess);
            }

        } while(Process32Next(snapshot, &pe32));
    }

    CloseHandle(snapshot);
}

int WINAPI WinMain(HINSTANCE hInst,
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

    char resultado[12000] = "";
    char linha[300];

    strcat(resultado,
           "TOP 10 PROCESSOS QUE MAIS CONSOMEM RAM\n\n");

    for(int i = 0;
        i < 10 && i < totalProcessos;
        i++)
    {
        sprintf(
            linha,
            "%2d. %-25s %4llu MB\n",
            i + 1,
            processos[i].nome,
            (unsigned long long)
            processos[i].memoriaMB
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