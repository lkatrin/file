/*
schedule.txt
12-00	Малый	Чапаев
13-00	Большой	Захват
14-00	Малый	Любовь_и_голуби
15-00   Средний Три_богатыря

sales.txt
12-00	Чапаев	20
13-00	Захват	50
14-00	Любовь_и_голуби	10
15-00   Три_богатыря    35

out.txt
Зал	Продано
Большой	50
Малый	30
Средний	35
*/

#include <stdio.h>
#include <locale.h>
#include <string.h>

#define SCHEDULE_SIZE 1000
#define SALES_SIZE 1000

// Структура для хранения данных о расписании киносеансов
typedef struct {
    char time[6]; // Время начала сеанса
    char hall[20]; // Название зала
    char film[50]; // Название фильма
} Schedule;

// Структура для хранения данных о проданных билетах
typedef struct {
    char time[6]; // Время начала сеанса
    char film[50]; // Название фильма
    int sold_tickets; // Количество проданных билетов
} Sales;

int main(void) {
    char *locale = setlocale(LC_ALL, "");

    // Массивы структур для хранения данных о расписании и продажах
    Schedule schedule[SCHEDULE_SIZE];
    Sales sales[SALES_SIZE];

    // Открытие файлов для чтения данных
    FILE *f_schedule = fopen("schedule.txt", "r");
    FILE *f_sales = fopen("sales.txt", "r");

    // Открытие файла для записи результата
    FILE *f_out = fopen("out.txt", "w");

    // Переменные для подсчета количества записей о расписании и продажах
    int n_schedule = 0;
    int n_sales = 0;

    // Структуры для временного хранения данных о расписании и продажах
    Schedule sch;
    Sales sale;

    // Чтение данных из файла schedule.txt
    while (fscanf(f_schedule, "%s %s %s", sch.time, sch.hall, sch.film) == 3) {
        schedule[n_schedule++] = sch;
    }
    fclose(f_schedule);

    // Чтение данных из файла sales.txt
    while (fscanf(f_sales, "%s %s %d", sale.time, sale.film, &sale.sold_tickets) == 3) {
        sales[n_sales++] = sale;
    }
    fclose(f_sales);

    // Сортировка расписания по залам
    for (int i = 0; i < n_schedule - 1; i++) {
        for (int j = i + 1; j < n_schedule; j++) {
            if (strcmp(schedule[i].hall, schedule[j].hall) > 0) {
                Schedule temp = schedule[i];
                schedule[i] = schedule[j];
                schedule[j] = temp;
            }
        }
    }

    // Подсчет проданных билетов по каждому залу
    fprintf(f_out, "Зал\tПродано\n");
    int total_sold = 0;
    for (int i = 0; i < n_schedule; i++) {
        if (i > 0 && strcmp(schedule[i].hall, schedule[i - 1].hall) != 0) {
            fprintf(f_out, "%s\t%d\n", schedule[i - 1].hall, total_sold);
            total_sold = 0;
        }
        for (int j = 0; j < n_sales; j++) {
            if (strcmp(schedule[i].time, sales[j].time) == 0 &&
                strcmp(schedule[i].film, sales[j].film) == 0) {
                total_sold += sales[j].sold_tickets;
            }
        }
        if (i == n_schedule - 1) {
            fprintf(f_out, "%s\t%d\n", schedule[i].hall, total_sold);
        }
    }
    fclose(f_out);

    return 0;
}
