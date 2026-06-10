#include "raylib.h"
#include <stdio.h>

#define MAX_TAREFAS 10

typedef struct {
    char texto[50];
    bool concluida;
} Tarefa;

int main() {
    InitWindow(800, 600, "Gerenciador de Tarefas");

    Tarefa tarefas[MAX_TAREFAS] = {
        {"Estudar C", false},
        {"Fazer atividade", false},
        {"Entregar projeto", false}
    };

    int total = 3;

    while (!WindowShouldClose()) {

        if (IsKeyPressed(KEY_ONE))
            tarefas[0].concluida = !tarefas[0].concluida;

        if (IsKeyPressed(KEY_TWO))
            tarefas[1].concluida = !tarefas[1].concluida;

        if (IsKeyPressed(KEY_THREE))
            tarefas[2].concluida = !tarefas[2].concluida;

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("GERENCIADOR DE TAREFAS", 220, 30, 30, BLACK);
        DrawText("Pressione 1, 2 ou 3 para concluir tarefas", 150, 80, 20, DARKGRAY);

        for (int i = 0; i < total; i++) {
            Color cor = tarefas[i].concluida ? GREEN : RED;

            DrawRectangle(50, 150 + i * 70, 30, 30, cor);
            DrawText(tarefas[i].texto, 100, 155 + i * 70, 25, BLACK);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}