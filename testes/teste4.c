#include <windows.h>
#include <tlhelp32.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
                   LPSTR lpCmdLine, int nCmdShow)
{
    HANDLE hProcessSnap;
    PROCESSENTRY32 pe32;

    char buffer[10000] = "";
    char linha[300];

    hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (hProcessSnap == INVALID_HANDLE_VALUE)
        return 1;

    pe32.dwSize = sizeof(PROCESSENTRY32);

    if (Process32First(hProcessSnap, &pe32))
    {
        do
        {
            sprintf(linha, "%s\n", pe32.szExeFile);
            strcat(buffer, linha);

        } while (Process32Next(hProcessSnap, &pe32));
    }

    CloseHandle(hProcessSnap);

    MessageBox(NULL, buffer, "Processos em Execucao", MB_OK);

    return 0;
}