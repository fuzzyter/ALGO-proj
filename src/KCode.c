#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 구조체 정의 :이름, 전화번호, 전공, 학번, 학년
struct student
{
    char name[50];
    char phoneNumber[20];
    char department[50];
    int schoolYear;
    int schoolNumber;
    struct student *next; // 연결 리스트 포인터
};

// 전역 변수 정의
struct student *head = NULL; // 리스트 시작 더미 노드
struct student *tail = NULL; // 리스트 끝 더미 노드

// 학생 생성 함수
struct student *create_student(char *name, char *phoneNumber, char *department, int schoolYear, int schoolNumber)
{
    struct student *new_student = (struct student *)malloc(sizeof(struct student));
    if (!new_student)
    {
        printf("메모리 할당 실패\n");
        return NULL;
    }

    strcpy(new_student->name, name);
    strcpy(new_student->phoneNumber, phoneNumber);
    strcpy(new_student->department, department);
    new_student->schoolYear = schoolYear;
    new_student->schoolNumber = schoolNumber;
    new_student->next = NULL;

    return new_student;
}

// 초기화 함수
void make_student()
{
    head = (struct student *)malloc(sizeof(struct student));
    tail = (struct student *)malloc(sizeof(struct student));
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
void insert_student()
{
    char name[50], phoneNumber[20], department[50];
    int age, schoolYear, schoolNumber;

    validate_input("이름: ", name, 50);

    printf("나이: ");
    while (scanf("%d", &age) != 1)
    {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n')
            ; // 버퍼 비우기
    }
    while (getchar() != '\n')
        ; // 버퍼 비우기
    validate_phone(phoneNumber);
    validate_input("학과: ", department, 50);

    printf("학년: ");
    while (scanf("%d", &schoolYear) != 1)
    {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n')
            ; // 버퍼 비우기
    }
    while (getchar() != '\n')
        ; // 버퍼 비우기

    printf("학번: ");
    while (scanf("%d", &schoolNumber) != 1)
    {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n')
            ; // 버퍼 비우기
    }
    while (getchar() != '\n')
        ; // 버퍼 비우기

    struct student *new_student = create_student(name, phoneNumber, department, schoolYear, schoolNumber);
    if (!new_student)
        return;

    new_student->next = head->next;
    head->next = new_student;
    printf("학생이 추가되었습니다: %s\n", name);
}

// 학생 삭제 함수
void delete_student()
{
    char name[50];
    printf("삭제할 학생의 이름을 입력하세요: ");
    fgets(name, 50, stdin);           // fgets로 입력 받기
    name[strcspn(name, "\n")] = '\0'; // 개행 문자 제거

    // 공백 입력 확인
    if (strlen(name) == 0)
    {
        printf("경고: 이름은 공백이 아니어야 합니다. 다시 메뉴로 돌아갑니다.\n");
        return; // 메뉴로 돌아감
    }

    struct student *prev = head;
    struct student *current = head->next;

    while (current != tail)
    {
        if (strcmp(current->name, name) == 0)
        {
            prev->next = current->next;
            free(current);
            printf("학생이 삭제되었습니다: %s\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("해당 이름의 학생을 찾을 수 없습니다: %s\n", name);
}

// 학생 검색 함수
void search_student()
{
    int choice;
    char query[50];

    printf("\n=== 학생 검색 ===\n");
    printf("1. 이름으로 검색\n");
    printf("2. 나이로 검색\n");
    printf("3. 성별로 검색\n");
    printf("4. 전화번호로 검색\n");
    printf("5. 학과로 검색\n");
    printf("원하는 검색 카테고리 번호를 입력하세요: ");
    scanf("%d", &choice);
    while (getchar() != '\n')
        ; // 입력 버퍼 비우기

    switch (choice)
    {
    case 1:
        printf("검색할 학생의 이름을 입력하세요: ");
        fgets(query, 50, stdin);            // 이름 입력
        query[strcspn(query, "\n")] = '\0'; // 개행 문자 제거
        break;
    case 2:
        printf("검색할 학생의 전화번호를 입력하세요: ");
        fgets(query, 50, stdin);            // 전화번호 입력
        query[strcspn(query, "\n")] = '\0'; // 개행 문자 제거
        break;
    case 3:
        printf("검색할 학생의 학과를 입력하세요: ");
        fgets(query, 50, stdin);            // 학과 입력
        query[strcspn(query, "\n")] = '\0'; // 개행 문자 제거
        break;
    default:
        printf("잘못된 선택입니다. 메뉴로 돌아갑니다.\n");
        return; // 메뉴로 돌아감
    }

    struct student *current = head->next;

    while (current != tail)
    {
        switch (choice)
        {
        case 1: // 이름으로 검색
            if (strcmp(current->name, query) == 0)
            {
                printf("\n=== 학생 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("학과: %s\n", current->department);
                printf("학년: %d\n", current->schoolYear);
                printf("학번: %d\n", current->schoolNumber);
                return;
            }
            break;

        case 2: // 전화번호로 검색
            if (strcmp(current->phoneNumber, query) == 0)
            {
                printf("\n=== 학생 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("학과: %s\n", current->department);
                printf("학년: %d\n", current->schoolYear);
                printf("학번: %d\n", current->schoolNumber);
                return;
            }
            break;
        case 3: // 학과로 검색
            if (strcmp(current->department, query) == 0)
            {
                printf("\n=== 학생 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("학과: %s\n", current->department);
                printf("학년: %d\n", current->schoolYear);
                printf("학번: %d\n", current->schoolNumber);
                return;
            }
            break;
        }
        current = current->next;
    }

    printf("해당 조건에 맞는 학생을 찾을 수 없습니다.\n");
}

// 학생 정보 수정 함수
void update_student()
{
    char name[50];
    printf("수정할 학생의 이름을 입력하세요: ");
    fgets(name, 50, stdin);           // fgets로 입력 받기
    name[strcspn(name, "\n")] = '\0'; // 개행 문자 제거

    // 공백 입력 확인
    if (strlen(name) == 0)
    {
        printf("경고: 이름은 공백이 아니어야 합니다. 다시 메뉴로 돌아갑니다.\n");
        return; // 메뉴로 돌아감
    }

    struct student *current = head->next;

    while (current != tail)
    {
        if (strcmp(current->name, name) == 0)
        {
            printf("\n=== 현재 정보 ===\n");
            printf("이름: %s\n", current->name);
            printf("전화번호: %s\n", current->phoneNumber);
            printf("학과: %s\n", current->department);
            printf("학년: %d\n", current->schoolYear);
            printf("학번: %d\n", current->schoolNumber);

            printf("\n=== 새 정보 입력 ===\n");
            printf("전화번호 (예: 010-0000-1111): ");
            scanf("%s", current->phoneNumber);
            printf("학과: ");
            scanf("%s", current->department);
            printf("학년: ");
            scanf("%d", &current->schoolYear);
            printf("학번: ");
            scanf("%d", &current->schoolNumber);

            printf("학생 정보가 수정되었습니다: %s\n", current->name);
            return;
        }
        current = current->next;
    }
    printf("해당 이름의 학생을 찾을 수 없습니다: %s\n", name);
}

// 학생 전체 출력 함수
void print_all_students()
{
    struct student *s = head->next;
    if (s == tail)
    {
        printf("현재 등록된 학생이 없습니다.\n");
        return;
    }

    printf("\n===== 전체 학생 목록 =====\n");
    while (s != tail)
    {
        printf("\n=== 학생 정보 ===\n");
        printf("이름: %s\n", s->name);
        printf("전화번호: %s\n", s->phoneNumber);
        printf("학과: %s\n", s->department);
        printf("학년: %d\n", s->schoolYear);
        printf("학번: %d\n", s->schoolNumber);
        s = s->next;
    }
    printf("==========================\n\n");
}

// 메뉴 출력 함수
void menu_display()
{
    printf("\n===== 메뉴 =====\n");
    printf("A. 학생 추가\n");
    printf("D. 학생 삭제\n");
    printf("S. 학생 검색\n");
    printf("U. 학생 정보 수정\n");
    printf("P. 학생 전체 출력\n");
    printf("Q. 프로그램 종료\n");
    printf("=================\n");
}

// 메인 함수
int main()
{
    char command;
    make_student(); // 초기화

    do
    {
        menu_display();
        printf("명령어를 입력하시오: ");
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
            insert_student();
            break;

        case 'D':
        case 'd':
            delete_student();
            break;

        case 'S':
        case 's':
            search_student();
            break;

        case 'U':
        case 'u':
            update_student();
            break;

        case 'P':
        case 'p':
            print_all_students();
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