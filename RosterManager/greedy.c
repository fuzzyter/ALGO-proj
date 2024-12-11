#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "greedy.h"

// �� �Լ�: ���� �ð� ���� ���� (������ ���� �ð� ����)
int compare(const void* a, const void* b) {
    Room* r1 = (Room*)a;
    Room* r2 = (Room*)b;

    if (r1->start != r2->start) {
        return r1->start - r2->start;
    }
    return r1->end - r2->end;
}

// �׸��� �˰��� ���� �Լ�
void executeGreedyAlgorithm(Room* rooms, int room_count) {
    // Room �����͸� ����
    qsort(rooms, room_count, sizeof(Room), compare);

    // ȸ�� ���� �˰���
    int last_end_time = -1;
    int count = 0;

    printf("Selected meetings:\n");
    for (int i = 0; i < room_count; i++) {
        if (rooms[i].start >= last_end_time) {
            count++;
            last_end_time = rooms[i].end;
            printf("Meeting Start: %d, End: %d\n", rooms[i].start, rooms[i].end);
        }
    }

    printf("Maximum number of meetings: %d\n", count);
}
