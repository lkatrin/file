/*В базе данных лесного колледжа содержатся сведения об успеваемости студентов.
Структура входного файла in.txt (Студент Группа Дисциплина Оценки)
Тигра Г1 Физика 3.5
Винни_Пух Г2 Пчеловодство 5.0
Винни_Пух Г2 Русский_язык 3.0
Кролик Г1 Русский_язык 4.75
Тигра Г1 Химия 3.67

…
Сформировать список студентов с любимыми дисциплинами, исходя из среднего балла (гарантируется, что для
каждого студента только одна любимая дисциплина). Список упорядочить по названию группы и по фамилии студента
Структура выходного файла out.txt
Г1 Кролик Русский_язык
Г1 Тигра Химия
Г2 Винни_Пух Пчеловодство*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define COLLEGE_SIZE 1000

typedef struct {
    char gr[20];
    char st[20];
    char disc[20];
    double mark;
} Record;

int main(void) {
    char *locale = setlocale(LC_ALL, "");

    Record v[COLLEGE_SIZE];
    int n = 0;

    FILE *in = fopen("in.txt", "r");
    if (in == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }

    // Считываем данные из файла
    while (fscanf(in, "%s %s %s %lf", v[n].st, v[n].gr, v[n].disc, &v[n].mark) == 4) {
        n++;
    }
    fclose(in);

    // Сортируем записи по группе и имени студента
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(v[i].gr, v[j].gr) > 0 || (strcmp(v[i].gr, v[j].gr) == 0 && strcmp(v[i].st, v[j].st) > 0)) {
                Record temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }

    // Записываем информацию о студентах с любимыми дисциплинами в файл
    FILE *out = fopen("out.txt", "w");
    if (out == NULL) {
        printf("Ошибка при создании файла.\n");
        return 1;
    }

    // Проходим по отсортированному списку студентов
    for (int i = 0; i < n; i++) {
        char fav_disc[20];
        strcpy(fav_disc, v[i].disc); // Пусть первая встреченная дисциплина будет считаться любимой
        double max_mark = v[i].mark;

        // Поиск любимой дисциплины студента
        for (int j = i + 1; j < n; j++) {
            if (strcmp(v[i].gr, v[j].gr) == 0 && strcmp(v[i].st, v[j].st) == 0) {
                if (v[j].mark > max_mark) {
                    strcpy(fav_disc, v[j].disc);
                    max_mark = v[j].mark;
                }
            }
        }

        // Записываем информацию о студенте в файл, только если её ещё нет
        int already_written = 0;
        for (int k = 0; k < i; k++) {
            if (strcmp(v[i].gr, v[k].gr) == 0 && strcmp(v[i].st, v[k].st) == 0) {
                already_written = 1;
                break;
            }
        }

        if (!already_written) {
            fprintf(out, "%s %s %s\n", v[i].gr, v[i].st, fav_disc);
        }
    }
    fclose(out);

    return 0;
}
