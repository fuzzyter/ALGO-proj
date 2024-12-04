#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* file_path = "StudentList.csv";

// 학생 구조체 정의 :이름, 전화번호, 전공, 학번, 학년
struct Room
{
    char roomName[50];
    char name[50];
    char phoneNumber[20];
    char department[50];
    int schoolYear;
    int schoolNumber;
    int start;
    int end;
    struct Room *next; // 연결 리스트 포인터
};

struct DepartmentNode {
    char department[50];
    struct Room* reservations;
    struct DepartmentNode* left;
    struct DepartmentNode* right;
};


// 전역 변수 정의
struct Room *head = NULL; // 리스트 시작 더미 노드
struct Room *tail = NULL; // 리스트 끝 더미 노드

// 학생 생성 함수
struct Room* create_lectureRoom(char* name, char* roomName, char* phoneNumber, char* department, int schoolYear, int schoolNumber, int start, int end)
{
    struct Room* new_Room = (struct Room*)malloc(sizeof(struct Room));
    if (!new_Room)
    {
        printf("메모리 할당 실패\n");
        return NULL;
    }

    strcpy(new_Room->name, roomName);
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
    head = (struct Room *)malloc(sizeof(struct Room));
    tail = (struct Room *)malloc(sizeof(struct Room));
    if (!head || !tail)
    {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    head->next = tail;
    tail->next = NULL;
}

// 입력 유효성 검사 함수: 빈 입력 방지
void validate_input(const char *prompt, char *input, size_t size)
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
void validate_phone(char *phoneNumber)
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
    char name[50], phoneNumber[20], department[50], roomName[50];
    int age, schoolYear, schoolNumber, start, end;

    validate_input("강의실: ", roomName, 50);
    validate_input("이름: ", name, 50);

    printf("나이: ");
    while (scanf("%d", &age) != 1) {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n')
            ; // 버퍼 비우기
    }
    while (getchar() != '\n')
        ; // 버퍼 비우기
    validate_phone(phoneNumber);
    validate_input("학과: ", department, 50);

    printf("학년: ");
    while (scanf("%d", &schoolYear) != 1) {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n')
            ; // 버퍼 비우기
    }
    while (getchar() != '\n')
        ; // 버퍼 비우기

    printf("학번: ");
    while (scanf("%d", &schoolNumber) != 1) {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n')
            ; // 버퍼 비우기
    }
    while (getchar() != '\n')
        ; // 버퍼 비우기

    // 시작 시간과 종료 시간 입력
    printf("시작 시간(0-23): ");
    while (scanf("%d", &start) != 1 || start < 0 || start > 23) {
        printf("유효한 시작 시간을 입력하세요 (0-23): ");
        while (getchar() != '\n'); // 버퍼 비우기
    }

    printf("종료 시간(1-24): ");
    while (scanf("%d", &end) != 1 || end <= start || end > 24) {
        printf("유효한 종료 시간을 입력하세요 (종료 > 시작, 1-24): ");
        while (getchar() != '\n'); // 버퍼 비우기
    }
    while (getchar() != '\n'); // 버퍼 비우기

    // 예약 시간 겹침 확인
    struct Room* current = head->next;
    while (current != tail) {
        if (strcmp(current->roomName, roomName) == 0 &&
            ((start >= current->start && start < current->end) || (end > current->start && end <= current->end))) {
            printf("겹치는 예약이 있습니다. 다른 시간을 선택하세요.\n");
            return; // 겹치는 예약이 있을 경우 바로 종료
        }
        current = current->next; // 리스트의 다음 강의실로 이동
    }

    struct Room* new_Room = create_lectureRoom(name, roomName, phoneNumber, department, schoolYear, schoolNumber, start, end);
    if (!new_Room)
        return;

    new_Room->next = head->next;
    head->next = new_Room;
    printf("강의실에 학생이 추가되었습니다: %s (%s, %d시 ~ %d시)\n", name, roomName, start, end);
}

// 강의실 예약 삭제 함수
void delete_lectureRoom() {
    char roomName[50];
    int start, end;

    printf("삭제할 강의실 이름을 입력하세요: ");
    fgets(roomName, 50, stdin);
    roomName[strcspn(roomName, "\n")] = '\0'; // 개행 문자 제거

    // 공백 입력 확인
    if (strlen(roomName) == 0) {
        printf("경고: 강의실 이름은 공백이 아니어야 합니다.\n");
        return;
    }

    printf("삭제할 예약 시작 시간(0-23)을 입력하세요: ");
    while (scanf("%d", &start) != 1 || start < 0 || start > 23) {
        printf("유효한 시작 시간을 입력하세요 (0-23): ");
        while (getchar() != '\n'); // 버퍼 비우기
    }

    printf("삭제할 예약 종료 시간(1-24)을 입력하세요: ");
    while (scanf("%d", &end) != 1 || end <= start || end > 24) {
        printf("유효한 종료 시간을 입력하세요 (종료 > 시작, 1-24): ");
        while (getchar() != '\n'); // 버퍼 비우기
    }
    while (getchar() != '\n'); // 버퍼 비우기

    struct Room* current = head->next;
    struct Room* prev = head;  // 이전 노드를 추적하는 포인터

    // 예약 정보 삭제
    while (current != tail) {
        // 강의실 이름과 예약 시간이 일치하는 경우
        if (strcmp(current->roomName, roomName) == 0 && current->start == start && current->end == end) {
            printf("삭제할 예약을 찾았습니다: %s (%d시 ~ %d시)\n", roomName, start, end);
            prev->next = current->next;  // 해당 노드를 리스트에서 제외
            free(current);  // 메모리 해제
            printf("예약이 삭제되었습니다.\n");
            return;
        }

        prev = current;  // 이전 노드로 이동
        current = current->next;  // 다음 노드로 이동
    }

    printf("해당 예약을 찾을 수 없습니다: %s (%d시 ~ %d시)\n", roomName, start, end);
}


void load_reservations() {
    FILE* file = fopen(file_path, "StudentList");
    if (!file) {
        printf("CSV 파일을 열 수 없습니다.\n");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        struct Room* new_room = (struct Room*)malloc(sizeof(struct Room));
        if (!new_room) {
            printf("메모리 할당 실패\n");
            fclose(file);
            return;
        }

        // CSV 포맷: roomName,name,phoneNumber,department,schoolYear,schoolNumber,start,end
        scanf(line, "%[^,],%[^,],%[^,],%[^,],%d,%d,%d,%d",
            new_room->roomName, new_room->name, new_room->phoneNumber,
            new_room->department, &new_room->schoolYear, &new_room->schoolNumber,
            &new_room->start, &new_room->end);

        new_room->next = head->next;
        head->next = new_room;
    }

    fclose(file);
    printf("CSV 파일에서 예약 정보를 불러왔습니다.\n");
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

struct DepartmentNode* insert_department(struct DepartmentNode* root, char* department, struct Room* reservation) {
    if (!root) {
        struct DepartmentNode* new_node = (struct DepartmentNode*)malloc(sizeof(struct DepartmentNode));
        strcpy(new_node->department, department);
        new_node->reservations = reservation;
        new_node->left = new_node->right = NULL;
        return new_node;
    }

    int cmp = strcmp(department, root->department);
    if (cmp < 0) {
        root->left = insert_department(root->left, department, reservation);
    }
    else if (cmp > 0) {
        root->right = insert_department(root->right, department, reservation);
    }
    else {
        // 같은 학과라면 연결 리스트로 추가
        reservation->next = root->reservations;
        root->reservations = reservation;
    }
    return root;
}

void print_lectureRoom_state() {
    sort_lectureRooms();

    struct Room* current = head->next;
    if (current == tail) {
        printf("현재 등록된 예약이 없습니다.\n");
        return;
    }

    printf("\n=== 강의실 예약 상태 ===\n");
    while (current != tail) {
        printf("강의실: %s | 예약자: %s | 시간: %d시 ~ %d시\n",
            current->roomName, current->name, current->start, current->end);
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
void update_lectureRoom() {
    char roomName[50];
    int start, end;
    printf("수정할 강의실 이름을 입력하세요: ");
    fgets(roomName, 50, stdin);           // fgets로 입력 받기
    roomName[strcspn(roomName, "\n")] = '\0'; // 개행 문자 제거

    // 공백 입력 확인
    if (strlen(roomName) == 0) {
        printf("경고: 강의실 이름은 공백이 아니어야 합니다. 다시 메뉴로 돌아갑니다.\n");
        return; // 메뉴로 돌아감
    }

    printf("수정할 예약 시작 시간(0-23)을 입력하세요: ");
    while (scanf("%d", &start) != 1 || start < 0 || start > 23) {
        printf("유효한 시작 시간을 입력하세요 (0-23): ");
        while (getchar() != '\n'); // 버퍼 비우기
    }
    while (getchar() != '\n'); // 버퍼 비우기

    printf("수정할 예약 종료 시간(1-24)을 입력하세요: ");
    while (scanf("%d", &end) != 1 || end <= start || end > 24) {
        printf("유효한 종료 시간을 입력하세요 (종료 > 시작, 1-24): ");
        while (getchar() != '\n'); // 버퍼 비우기
    }
    while (getchar() != '\n'); // 버퍼 비우기

    struct Room* current = head->next;

    // 강의실 예약 정보 수정
    while (current != tail) {
        if (strcmp(current->roomName, roomName) == 0 && current->start == start) {
            printf("\n=== 현재 예약 정보 ===\n");
            printf("강의실: %s\n", current->roomName);
            printf("예약자: %s\n", current->name);
            printf("예약 시간: %d시 ~ %d시\n", current->start, current->end);

            printf("\n=== 새 정보 입력 ===\n");
            printf("새 예약자 이름: ");
            fgets(current->name, 50, stdin);
            current->name[strcspn(current->name, "\n")] = '\0'; // 개행 문자 제거

            printf("새 예약 전화번호 (예: 010-0000-1111): ");
            fgets(current->phoneNumber, 20, stdin);
            current->phoneNumber[strcspn(current->phoneNumber, "\n")] = '\0'; // 개행 문자 제거

            printf("새 예약 학과: ");
            fgets(current->department, 50, stdin);
            current->department[strcspn(current->department, "\n")] = '\0'; // 개행 문자 제거

            printf("새 예약 학년: ");
            while (scanf("%d", &current->schoolYear) != 1) {
                printf("숫자로 입력해주세요. 다시 입력: ");
                while (getchar() != '\n'); // 버퍼 비우기
            }

            printf("새 예약 학번: ");
            while (scanf("%d", &current->schoolNumber) != 1) {
                printf("숫자로 입력해주세요. 다시 입력: ");
                while (getchar() != '\n'); // 버퍼 비우기
            }
            while (getchar() != '\n'); // 버퍼 비우기

            // 수정된 예약 정보 출력
            printf("강의실 예약 정보가 수정되었습니다: %s\n", current->roomName);
            return;
        }
        current = current->next;
    }
    printf("해당 강의실 예약을 찾을 수 없습니다: %s, %d시 ~ %d시\n", roomName, start, end);
}

// 메뉴 출력 함수
void menu_display()
{
    printf("\n===== 메뉴 =====\n");
    printf("A. 강의실 예약\n");
    printf("D. 예약 취소\n");
    printf("U. 예약 정보 수정\n");
    printf("Q. 프로그램 종료\n");
    printf("=================\n");
}

// 메인 함수
int main()
{
    char command;
    make_lectureRoom(); // 초기화

    do
    {
        menu_display();
        printf("명령어를 입 력하시오: ");
        command = getchar();
        while (getchar() != '\n')
            ; // 입력 버퍼 비우기

        // 공백으로 명령어가 입력된 경우 경고 메시지 출력
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

        case 'D':
        case 'd':
            delete_lectureRoom();
            break;

        case 'U':
        case 'u':
            update_lectureRoom();
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
