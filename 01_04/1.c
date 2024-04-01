#include <stdio.h>
#include <stdlib.h> // Для использования rand() и srand()
#include <time.h>   // Для использования time()

// Функция сортировки методом пузырька
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Если текущий элемент больше следующего, меняем их местами
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
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

    // Сортируем числа методом пузырька
    bubbleSort(numbers, fsize);

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
