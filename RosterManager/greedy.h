// greedy.h
#ifndef GREEDY_H
#define GREEDY_H

// Room ����ü�� ����
typedef struct {
    int start; // ���� �ð�
    int end;   // ���� �ð�
} Room;

// �׸��� �˰��� �Լ� ����
void greedyAlgorithm(Room* rooms, int room_count);


#endif // GREEDY_H
