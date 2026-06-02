#include <stdio.h>

void calcularHorasCurso(int semestres, int horasPorSemana) {
    int mesesPorSemestre = 5;
    int semanasPorMes = 4;

    int totalHoras = semestres * mesesPorSemestre * semanasPorMes * horasPorSemana;

    printf("Carga horaria total do curso: %d horas\n", totalHoras);
}

int main() {
    int semestres = 8;
    int horasPorSemana = 20;

    calcularHorasCurso(semestres, horasPorSemana);

    return 0;
}