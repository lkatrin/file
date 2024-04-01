#include <stdio.h>
#include <stdlib.h> // Для использования rand() и srand()
#include <time.h>   // Для использования time()

// Функция сортировки вставками
void insertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        /* Перемещаем элементы arr[0..i-1], которые больше, чем key, на одну позицию вперед */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    // Инициализация генератора случайных чисел с использованием текущего времени в качестве "зерна"
    srand((unsigned int)time(NULL));

    FILE *fh = fopen("1.dat", "wb+");
    if (fh == NULL) {
        printf("Не удалось открыть файл.\n");
        return 1;
    }

    int x = 0;
    long i;
    long isize = sizeof(int);
    long fsize;

    // Записываем случайные числа в файл
    for (i = 0; i < 10; i++) {
        x = rand() % 100; // Генерируем случайное число от 0 до 99
        fwrite(&x, isize, 1, fh);
    }

    // Определяем количество записей в файле
    fseek(fh, 0, SEEK_END);
    fsize = ftell(fh) / sizeof(int);

    // Выводим содержимое файла до замены нечетных чисел на противоположные
    fseek(fh, 0, SEEK_SET);
    int *numbers = malloc(fsize * sizeof(int));
    printf("Исходные числа в файле: ");
    for (i = 0; i < fsize; i++) {
        fread(&numbers[i], isize, 1, fh);
        printf("%d ", numbers[i]);
    }
    putchar('\n');

    // Заменяем нечетные числа на противоположные
    fseek(fh, 0, SEEK_SET);
    for (i = 0; i < fsize; i++) {
        fseek(fh, isize * i, SEEK_SET);
        fread(&x, isize, 1, fh);
        if (x % 2 != 0) {
            x = -x;
            fseek(fh, isize * i, SEEK_SET);
            fwrite(&x, isize, 1, fh);
        }
    }

    // Считываем числа снова для сортировки
    fseek(fh, 0, SEEK_SET);
    for (i = 0; i < fsize; i++) {
        fread(&numbers[i], sizeof(int), 1, fh);
    }

    // Сортируем числа методом вставок
    insertionSort(numbers, fsize);

    // Выводим отсортированные числа в консоль и записываем их обратно в файл
    printf("Отсортированные числа: ");
    fseek(fh, 0, SEEK_SET);
    for (i = 0; i < fsize; i++) {
        fwrite(&numbers[i], isize, 1, fh);
        printf("%d ", numbers[i]);
    }
    putchar('\n');

    // Освобождаем выделенную память и закрываем файл
    free(numbers);
    fclose(fh);
    return 0;
}
