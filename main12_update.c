/*������� �12. ��������� ��������� ��������� 31��-21
��������� �������� ����� in.txt (����� ��� ����� �������)
12-00		�����	������	20
13-00		�������	������	50
14-00		�����	������ � ������	10
...
���������� ���������� ��������� ������� �� ������� ����, ���������� �� �������� ����.
��������� ��������� ����� out.txt
���	�������
�������	50
�����	30*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������� ��� �������� ���������� � ������
struct Session {
    char time[6];
    char hall[50];
    char film[50];
    int soldTickets;
};

// ������� ��� ��������� ����� (������������ ��� qsort)
int compareHalls(const void *a, const void *b) {
    return strcmp(((struct Session *)a)->hall, ((struct Session *)b)->hall);  // ���������� ������� strcmp, ����� �������� �������� �����
}

int main(void) {
    // ��� �������� �����
    char *inputFileName = "in.txt";
    // ��� ��������� �����
    char *outputFileName = "out.txt";

    // ��������� ������� ���� ��� ������
    FILE *inputFile = fopen(inputFileName, "r");
    if (!inputFile) {
        // ����� ��������� �� ������ ��� �������� �����
        printf("������ ��� �������� �������� �����\n");
        return 1;
    }

    // ��������� �������� ���� ��� ������
    FILE *outputFile = fopen(outputFileName, "w");
    if (!outputFile) {
        // ����� ��������� �� ������ ��� �������� �����
        printf("������ ��� �������� ��������� �����\n");
        fclose(inputFile);
        return 1;
    }

    // ������ ��� �������� �������
    struct Session sessions[100];
    int sessionCount = 0;


    // ��������� ������ �� �����
    while (!feof(inputFile) && fscanf(inputFile, "%s %s %s %d", sessions[sessionCount].time, sessions[sessionCount].hall,
                  sessions[sessionCount].film, &sessions[sessionCount].soldTickets) > 0) {
        sessionCount++;
    }

    // ��������� ������� ����
    fclose(inputFile);

    // ��������� ������ ������� �� �������� ����
    qsort(sessions, sessionCount, sizeof(struct Session), compareHalls);

    // ������� ��������� � �������� ����
    fprintf(outputFile, "���\t�������\n");
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

    // ������� ��������� ��� � ���������� ��������� �������
    fprintf(outputFile, "%s\t%d\n", currentHall, currentHallSold);

    // ��������� �������� ����
    fclose(outputFile);

    return 0;
}
