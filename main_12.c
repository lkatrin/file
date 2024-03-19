/*Задание №12. Выполнила Лесникова Екатерина 31ИС-21
Структура входного файла in.txt (Время Зал Фильм Продано)
12-00		Малый	Чапаев	20
13-00		Большой	Захват	50
14-00		Малый	Любовь и голуби	10
...
Определить количество проданных билетов по каждому залу, упорядочив по названию зала.
Структура выходного файла out.txt
Зал	Продано
Большой	50
Малый	30*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для хранения информации о сеансе
struct Session {
    char time[6];
    char hall[50];
    char film[50];
    int soldTickets;
};

// Функция для сравнения залов (используется для qsort)
int compareHalls(const void *a, const void *b) {
    return strcmp(((struct Session *)a)->hall, ((struct Session *)b)->hall);  // Используем функцию strcmp, чтобы сравнить названия залов
}

int main(void) {
    // Имя входного файла
    char *inputFileName = "in.txt";
    // Имя выходного файла
    char *outputFileName = "out.txt";

    // Открываем входной файл для чтения
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        // Вывод сообщения об ошибке при открытии файла
        printf("Ошибка при открытии входного файла\n");
        return 1;
    }

    // Открываем выходной файл для записи
    FILE *outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        // Вывод сообщения об ошибке при открытии файла
        printf("Ошибка при открытии выходного файла\n");
        fclose(inputFile);
        return 1;
    }

    // Массив для хранения сеансов
    struct Session sessions[100];
    int sessionCount = 0;

    // Считываем данные из файла
    while (fscanf(inputFile, "%s %s %s %d", sessions[sessionCount].time, sessions[sessionCount].hall,
                  sessions[sessionCount].film, &sessions[sessionCount].soldTickets) == 4) {
        sessionCount++;
    }

    // Закрываем входной файл
    fclose(inputFile);

    // Сортируем массив сеансов по названию зала
    qsort(sessions, sessionCount, sizeof(struct Session), compareHalls);

    // Выводим результат в выходной файл
    fprintf(outputFile, "Зал\tПродано\n");
    char currentHall[50];
    int currentHallSold = 0;

    for (int i = 0; i < sessionCount; i++) {
        if (strcmp(sessions[i].hall, currentHall) == 0) {
            currentHallSold += sessions[i].soldTickets;
        } else {
            if (i != 0) {
                fprintf(outputFile, "%s\t%d\n", currentHall, currentHallSold);
            }
            strcpy(currentHall, sessions[i].hall);
            currentHallSold = sessions[i].soldTickets;
        }
    }

    // Выводим последний зал и количество проданных билетов
    fprintf(outputFile, "%s\t%d\n", currentHall, currentHallSold);

    // Закрываем выходной файл
    fclose(outputFile);

    return 0;
}
