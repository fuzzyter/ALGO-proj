#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include "StudentList.h"

// 학생 구조체 정의 :이름, 전화번호, 전공, 학번, 학년
struct Room
{
    char name[50];
    char phoneNumber[20];
    char department[50];
    int schoolNumber;
    int start;
    int end;
    struct Room *next; // 연결 리스트 포인터
};

// 전역 변수 정의
struct Room *head = NULL;

// 학생 생성 함수
struct Room *create_lectureRoom(char *name, char *phoneNumber, char *department, int schoolNumber, int start, int end)
{
    struct Room *new_Room = (struct Room *)malloc(sizeof(struct Room));
    if (!new_Room)
    {
        printf("메모리 할당 실패\n");
        return NULL;
    }

    strcpy(new_Room->name, name);
    strcpy(new_Room->phoneNumber, phoneNumber);
    strcpy(new_Room->department, department);
    new_Room->schoolNumber = schoolNumber;
    new_Room->start = start;
    new_Room->end = end;
    new_Room->next = NULL;

    return new_Room;
}

// 초기화 함수
void make_lectureRoom()
{
    head = (struct Room *)malloc(sizeof(struct Room));
    if (!head)
    {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    head->next = NULL; // head는 실제 데이터가 없고, 리스트의 첫 번째 노드를 가리킴
}

// 학생 추가 함수
void reserve_lectureRoom()
{
    char name[50], phoneNumber[20], department[50];
    int schoolNumber, start, end;

    // 이름 입력
    printf("이름: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    // 전화번호 입력
    printf("전화번호 (예: 010-1234-5678): ");
    fgets(phoneNumber, sizeof(phoneNumber), stdin);
    phoneNumber[strcspn(phoneNumber, "\n")] = '\0';

    // 학과 입력
    printf("학과: ");
    fgets(department, sizeof(department), stdin);
    department[strcspn(department, "\n")] = '\0';

    // 학번 입력
    printf("학번: ");
    scanf("%d", &schoolNumber);
    while (getchar() != '\n')
        ; // 버퍼 비우기

    // 시작 시간과 종료 시간 입력
    printf("시작 시간(0-23): ");
    scanf("%d", &start);
    printf("종료 시간(1-24): ");
    scanf("%d", &end);
    while (getchar() != '\n')
        ; // 버퍼 비우기

    // 새로운 강의실 예약 추가
    struct Room *new_Room = create_lectureRoom(name, phoneNumber, department, schoolNumber, start, end);
    if (!new_Room)
        return;

    // 예약 중복 확인
    struct Room *current = head->next;
    while (current)
    {
        if ((start < current->end && end > current->start))
        {
            printf("겹치는 예약이 있습니다. 다른 시간을 선택하세요.\n");
            return;
        }
        current = current->next;
    }

    // 새로운 예약 추가
    new_Room->next = head->next;
    head->next = new_Room;

    printf("\n강의실에 학생이 추가되었습니다: %s (%d시 ~ %d시)\n", name, start, end);
}

// 예약 정보 출력 함수
void print_lectureRoom_state()
{
    struct Room *current = head->next;
    if (!current)
    {
        printf("현재 등록된 예약이 없습니다.\n");
        return;
    }

    printf("\n=== 강의실 예약 상태 ===\n");
    while (current)
    {
        printf("이름: %s\n", current->name);
        printf("전화번호: %s\n", current->phoneNumber);
        printf("학과: %s\n", current->department);
        printf("학번: %d\n", current->schoolNumber);
        printf("시작 시간: %d\n", current->start);
        printf("종료 시간: %d\n", current->end);
        printf("==========================\n\n");
        current = current->next;
    }
}

// 강의실 예약 삭제 함수
void delete_lectureRoom()
{
    int schoolNumber;
    printf("삭제할 예약의 학번을 입력하세요: ");
    scanf("%d", &schoolNumber);
    while (getchar() != '\n')
        ; // 버퍼 비우기

    struct Room *current = head->next;
    struct Room *prev = NULL;

    while (current)
    {
        if (current->schoolNumber == schoolNumber)
        {
            if (prev)
                prev->next = current->next;
            else
                head->next = current->next; // 첫 번째 노드일 경우

            free(current); // 메모리 해제
            printf("예약이 삭제되었습니다.\n");
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("해당 학번이 없습니다.\n");
}

// 메인 함수
int main()
{
    char command;

    make_lectureRoom(); // 초기화

    do
    {
        printf("\n===== 메뉴 =====\n");
        printf("A. 강의실 예약\n");
        printf("L. 예약 목록\n");
        printf("U. 예약 삭제\n");
        printf("Q. 프로그램 종료\n");
        printf("=================\n");

        printf("명령어를 입력하시오: ");
        command = getchar();
        while (getchar() != '\n')
            ; // 버퍼 비우기

        switch (command)
        {
        case 'A':
        case 'a':
            reserve_lectureRoom();
            break;
        case 'L':
        case 'l':
            print_lectureRoom_state();
            break;
        case 'U':
        case 'u':
            delete_lectureRoom();
            break;
        case 'Q':
        case 'q':
            printf("프로그램을 종료합니다.\n");
            break;
        default:
            printf("잘못된 명령어입니다.\n");
            break;
        }
    } while (command != 'Q' && command != 'q');

    return 0;
}
