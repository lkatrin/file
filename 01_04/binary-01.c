
/// Записываем в файл целые числа
/// Заменяем нечетные на противоположные
/// Гусятинер Л.Б., МГОТУ ККМТ, 26.11.2017 / КМПО РАНХиГС 30.03.2024
/** Задания.
1. Отсортировать файл "пузырьком"
2. Отсортировать файл "вставками"
3. Отсортировать файл "выбором"
4. Найти число в файле линейным поиском
5. Найти число в файле двоичным поиском
6. Выполнить сортировку и поиск для вещественных чисел, для строк, для структур
**/

#include <stdio.h>
int main() {
    FILE * fh = fopen("1.dat", "wb+");  /// Открытие текстового файла для чтения и записи.
    /// Если файл не существует, то он создается. Если существовал, то все его прежнее содержимое удаляется.
    int x = 0;
    long i;
    long isize = sizeof(int);
    long fsize;

    /// Запишем числа в файл
    for (i = 1; i <= 10; i++)
        fwrite(&i, isize, 1, fh);  /// size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);
        ///  Указатель, размер одного элемента, число элементов и указатель на файловый поток

    /// Определим число записей в файле
    fseek(fh, 0, SEEK_END);
    fsize = ftell(fh) / sizeof(int);

    /// Отпечатаем содержимое файла
    fseek(fh, 0, SEEK_SET);
    for (i=0; i<fsize; i++) {
        fread(&x, isize, 1, fh);
        printf("%d ", x);
    }
    putchar('\n');

    /// Заменим нечетные числа на противоположные
    fseek(fh, 0, SEEK_SET);
    for (i=0; i<fsize; i++) {
        fseek(fh, isize * i, SEEK_SET);
        fread(&x, isize, 1, fh);
        if (x % 2 != 0) {
            x = - x;
            fseek(fh, isize * i, SEEK_SET);
            fwrite(&x, isize, 1, fh);
        }
    }

    /// Отпечатаем содержимое файла
    fseek(fh, 0, SEEK_SET);
    for (i=0; i<fsize; i++) {
        fread(&x, sizeof(int), 1, fh);
        printf("%d ", x);
    }
    putchar('\n');
    fclose(fh);
    return 0;
}
