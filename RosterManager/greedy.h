// greedy.h
#ifndef GREEDY_H
#define GREEDY_H

// Room 구조체를 선언
typedef struct {
    int start; // 시작 시간
    int end;   // 종료 시간
} Room;

// 그리디 알고리즘 함수 선언
void greedyAlgorithm(Room* rooms, int room_count);


#endif // GREEDY_H
