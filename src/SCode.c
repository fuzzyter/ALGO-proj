#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 구조체 정의 :이름, 전화번호, 전공, 학번, 학년
struct Room
{
    char name[50];
    char phoneNumber[20];
    char department[50];
    int schoolYear;
    int schoolNumber;
    int start;
    int end;
    struct Room* next; // 연결 리스트 포인터
};

// 전역 변수 정의
struct Room* head = NULL;
struct Room* tail = NULL; 

// 학생 생성 함수
struct Room* create_lectureRoom(char* name, char* phoneNumber, char* department, int schoolYear, int schoolNumber, int start, int end)
{
    struct Room* new_Room = (struct Room*)malloc(sizeof(struct Room));
    if (!new_Room)
    {
        printf("메모리 할당 실패\n");
        return NULL;
    }

    strcpy(new_Room->name, name);
    strcpy(new_Room->phoneNumber, phoneNumber);
    strcpy(new_Room->department, department);
    new_Room->schoolYear = schoolYear;
    new_Room->schoolNumber = schoolNumber;
    new_Room->start = start;
    new_Room->end = end;
    new_Room->next = NULL;

    return new_Room;
}

// 초기화 함수
void make_lectureRoom()
{
    head = (struct Room*)malloc(sizeof(struct Room));
    tail = (struct Room*)malloc(sizeof(struct Room));
    if (!head || !tail)
    {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    head->next = tail;
    tail->next = NULL;
}

// 입력 유효성 검사 함수: 빈 입력 방지
void validate_input(const char* prompt, char* input, size_t size)
{
    do
    {
        printf("%s", prompt);
        fgets(input, size, stdin);
        input[strcspn(input, "\n")] = '\0'; // 개행 문자 제거
        if (strlen(input) == 0)
        {
            printf("입력값이 비어 있습니다. 다시 입력해주세요.\n");
        }
    } while (strlen(input) == 0);
}

// 전화번호 유효성 검사 함수
void validate_phone(char* phoneNumber)
{
    do
    {
        validate_input("전화번호 (예: 010-1234-5678): ", phoneNumber, 20);
        if (strchr(phoneNumber, '-') == NULL)
        {
            printf("전화번호에 '-'가 포함되어야 합니다. 다시 입력해주세요.\n");
        }
    } while (strchr(phoneNumber, '-') == NULL);
}

// 학생 추가 함수
void reserve_lectureRoom() {
    char name[50], phoneNumber[20], department[50];
    int schoolYear, schoolNumber, start, end;
    char inputBuffer[50]; // 입력을 받을 버퍼

    // 이름 입력
    validate_input("이름: ", name, 50);

    // 전화번호 입력
    validate_phone(phoneNumber);

    // 학과 입력
    validate_input("학과: ", department, 50);

    printf("학년: ");
    while (scanf("%d", &schoolYear) != 1) {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n'); // 버퍼 비우기
    }
    while (getchar() != '\n'); // 버퍼 비우기

    // 학번 입력
    printf("학번: ");
    while (scanf("%d", &schoolNumber) != 1) {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n'); // 버퍼 비우기
    }
    while (getchar() != '\n'); // 버퍼 비우기

    // 시작 시간과 종료 시간 입력
    while (1) {
        printf("시작 시간(0-23): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        if (sscanf(inputBuffer, "%d", &start) == 1 && start >= 0 && start <= 23) {
            break;
        }
        else {
            printf("유효한 시간를 입력하세요.\n");
        }
    }

    while (1) {
        printf("종료 시간(0-23): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        if (sscanf(inputBuffer, "%d", &end) == 1 && end >= 0 && end <= 23) {
            break;
        }
        else {
            printf("유효한 숫자를 입력하세요.\n");
        }
    }

    // 예약 시간 겹침 확인
    struct Room* current = head->next;
    while (current != tail) {
        if ((start < current->end && end > current->start)) {
            printf("겹치는 예약이 있습니다. 다른 시간을 선택하세요.\n");
            return;
        }
        current = current->next; // 리스트의 다음 강의실로 이동
    }

    // 새로운 강의실 예약 추가
    struct Room* new_Room = create_lectureRoom(name, phoneNumber, department, schoolYear, schoolNumber, start, end);
    if (!new_Room)
        return;

    new_Room->next = head->next;
    head->next = new_Room;
    printf("강의실에 학생이 추가되었습니다: %s (%d시 ~ %d시)\n", name, start, end);
}

// 강의실 예약 삭제 함수
void delete_lectureRoom() {
    int schoolNumber;
    printf("삭제할 예약의 학번을 입력하세요: ");
    scanf("%d", &schoolNumber);
    while (getchar() != '\n'); // 입력 버퍼 비우기

    struct Room* current = head;
    struct Room* prev = NULL;

    while (current != tail) {
        if (current->schoolNumber == schoolNumber) {
            printf("예약이 삭제되었습니다.");

            if (prev) {
                prev->next = current->next;
            }
            else {
                head->next = current->next; // 헤드의 첫 번째 노드일 경우
            }

            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("해당 학번이 없습니다.\n");
}

void sort_lectureRooms() {
    struct Room* i, * j;
    for (i = head->next; i != tail; i = i->next) {
        for (j = i->next; j != tail; j = j->next) {
            if (i->start > j->start) {
                // 데이터 교환
                struct Room temp = *i;
                *i = *j;
                *j = temp;

                // 포인터 유지
                temp.next = i->next;
                i->next = j->next;
                j->next = temp.next;
            }
        }
    }
}

// 강의실 예약 상태 출력 함수
void print_lectureRoom_state() {

    struct Room* current = head->next;
    if (current == tail) {
        printf("현재 등록된 예약이 없습니다.\n");
        return;
    }

    printf("\n=== 강의실 예약 상태 ===\n");
    while (current != tail) {
        printf("이름: %s\n", current->name);
        printf("전화번호: %s\n", current->phoneNumber);
        printf("학과: %s\n", current->department);
        printf("학년: %d\n", current->schoolYear);
        printf("학번: %d\n", current->schoolNumber);
        printf("시작 시간: %d\n", current->start);
        printf("종료 시간: %d\n", current->end);
        printf("==========================\n\n");
        current = current->next;
    }
}

void insertion_sort_Rooms() {
    struct Room* sorted = NULL;
    struct Room* current = head->next;

    while (current != tail) {
        struct Room* next = current->next;

        // 정렬된 위치 찾기
        struct Room** ptr = &sorted;
        while (*ptr != NULL && (*ptr)->start < current->start) {
            ptr = &((*ptr)->next);
        }

        // 노드 삽입
        current->next = *ptr;
        *ptr = current;

        current = next;
    }

    head->next = sorted;
}

// 강의실 예약 정보 수정 함수
void modify_lectureRoom() {
    int schoolNumber;
    char choice;

    print_lectureRoom_state();
    printf("U. 예약 수정\n");
    printf("D. 예약 삭제\n");
    printf("명령어를 입력하시오: ");
    scanf(" %c", &choice);  // 앞에 공백 추가로 버퍼 문제 방지
    while (getchar() != '\n'); // 입력 버퍼 비우기

    switch (choice) {
    case 'D':
    case 'd': {
        printf("삭제할 예약의 학번을 입력하세요: ");
        scanf("%d", &schoolNumber);
        while (getchar() != '\n'); // 입력 버퍼 비우기

        struct Room* current = head->next;

        while (current != tail) {
            if (current->schoolNumber == schoolNumber) {
                printf("\n=== 현재 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("학과: %s\n", current->department);
                printf("학년: %d\n", current->schoolYear);
                printf("학번: %d\n", current->schoolNumber);
                printf("시작 시간: %d\n", current->start);
                printf("종료 시간: %d\n", current->end);
                printf("==========================\n");
                printf("해당 학생이 맞습니까? Y/N\n");
                char confirm;
                while (1) {
                    confirm = getchar();
                    while (getchar() != '\n'); // 입력 버퍼 비우기

                    if (confirm == 'Y' || confirm == 'y') {
                        delete_lectureRoom();
                        printf("삭제되었습니다.\n");
                        return; // 함수 종료
                    }
                    else if (confirm == 'N' || confirm == 'n') {
                        printf("취소되었습니다.\n");
                        return; // 함수 종료
                    }
                    else {
                        printf("잘못된 입력입니다. Y 또는 N을 입력해주세요: ");
                    }
                }
            }
            current = current->next;
        }
        printf("해당 학번의 예약이 없습니다.\n");
        break;
    }

    case 'U':
    case 'u': {
        printf("수정할 예약의 학번을 입력하세요: ");
        scanf("%d", &schoolNumber);
        while (getchar() != '\n'); // 입력 버퍼 비우기

        struct Room* current = head->next;

        while (current != tail) {
            if (current->schoolNumber == schoolNumber) {
                printf("\n=== 현재 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("학과: %s\n", current->department);
                printf("학년: %d\n", current->schoolYear);
                printf("학번: %d\n", current->schoolNumber);
                printf("시작 시간: %d\n", current->start);
                printf("종료 시간: %d\n", current->end);
                printf("==========================\n");
                printf("해당 학생이 맞습니까? Y/N\n");
                char confirm;
                while (1) {
                    confirm = getchar();
                    while (getchar() != '\n'); // 입력 버퍼 비우기

                    if (confirm == 'Y' || confirm == 'y') {
                        printf("\n새로운 정보를 입력하세요.\n");

                        // 이름 입력
                        validate_input("이름: ", current->name, 50);

                        // 전화번호 입력
                        validate_phone(current->phoneNumber);

                        // 학과 입력
                        validate_input("학과: ", current->department, 50);

                        // 학년 입력
                        printf("학년: ");
                        scanf("%d", &current->schoolYear);
                        while (getchar() != '\n'); // 입력 버퍼 비우기

                        // 시작 시간과 종료 시간 입력
                        int newStart, newEnd;
                        printf("시작 시간(0-23): ");
                        scanf("%d", &newStart);
                        printf("종료 시간(1-24): ");
                        scanf("%d", &newEnd);
                        while (getchar() != '\n'); // 입력 버퍼 비우기

                        // 예약 시간 중복 확인
                        struct Room* temp = head->next;
                        while (temp != tail) {
                            if (temp != current && (newStart < temp->end && newEnd > temp->start)) {
                                printf("겹치는 예약이 있습니다. 변경을 취소합니다.\n");
                                return;
                            }
                            temp = temp->next;
                        }

                        // 시간 업데이트
                        current->start = newStart;
                        current->end = newEnd;

                        printf("예약이 성공적으로 수정되었습니다!\n");
                        return;
                    }
                    else if (confirm == 'N' || confirm == 'n') {
                        printf("취소되었습니다.\n");
                        return;
                    }
                    else {
                        printf("잘못된 입력입니다. Y 또는 N을 입력해주세요: ");
                    }
                }
            }
            current = current->next;
        }
        printf("해당 학번의 예약이 없습니다.\n");
        break;
    }

    default:
        printf("잘못된 명령어입니다.\n");
        break;
    }
}

// 메뉴 출력 함수
void menu_display()
{
    printf("\n===== 메뉴 =====\n");
    printf("A. 강의실 예약\n");
    printf("L. 예약 목록\n");
    printf("U. 예약 정보 수정/삭제\n");
    printf("Q. 프로그램 종료\n");
    printf("=================\n");
}

// 메인 함수
int main() {
    char command;

    make_lectureRoom(); // 초기화

    do
    {
        menu_display();
        printf("명령어를 입력하시오: ");
        command = getchar();
        while (getchar() != '\n');

        if (command == ' ' || command == '\t' || command == '\n')
        {
            printf("경고: 명령어는 공백이 아닌 값을 입력해야 합니다.\n");
            continue;
        }

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
            modify_lectureRoom();
            break;

        case 'Q':
        case 'q':
            printf("프로그램을 종료합니다.\n");
            break;

        default:
            printf("잘못된 명령어입니다.\n");
            break;
        }
    } while (command != 'q' && command != 'Q');

    return 0;
}
