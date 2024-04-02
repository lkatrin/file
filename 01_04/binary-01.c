
/// ���������� � ���� ����� �����
/// �������� �������� �� ���������������
/// ��������� �.�., ����� ����, 26.11.2017 / ���� ������� 30.03.2024
/** �������.
1. ������������� ���� "���������"
2. ������������� ���� "���������"
3. ������������� ���� "�������"
4. ����� ����� � ����� �������� �������
5. ����� ����� � ����� �������� �������
6. ��������� ���������� � ����� ��� ������������ �����, ��� �����, ��� ��������
**/

#include <stdio.h>
int main() {
    FILE * fh = fopen("1.dat", "wb+");  /// �������� ���������� ����� ��� ������ � ������.
    /// ���� ���� �� ����������, �� �� ���������. ���� �����������, �� ��� ��� ������� ���������� ���������.
    int x = 0;
    long i;
    long isize = sizeof(int);
    long fsize;

    /// ������� ����� � ����
    for (i = 1; i <= 10; i++)
        fwrite(&i, isize, 1, fh);  /// size_t fwrite(const void * restrict ptr, size_t size, size_t nmemb, FILE * restrict stream);
        ///  ���������, ������ ������ ��������, ����� ��������� � ��������� �� �������� �����

    /// ��������� ����� ������� � �����
    fseek(fh, 0, SEEK_END);
    fsize = ftell(fh) / sizeof(int);

    /// ���������� ���������� �����
    fseek(fh, 0, SEEK_SET);
    for (i=0; i<fsize; i++) {
        fread(&x, isize, 1, fh);
        printf("%d ", x);
    }
    putchar('\n');

    /// ������� �������� ����� �� ���������������
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

    /// ���������� ���������� �����
    fseek(fh, 0, SEEK_SET);
    for (i=0; i<fsize; i++) {
        fread(&x, sizeof(int), 1, fh);
        printf("%d ", x);
    }
    putchar('\n');
    fclose(fh);
    return 0;
}
