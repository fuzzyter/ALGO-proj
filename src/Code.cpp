#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 학생 구조체 정의
struct student {
    char name[50];
    int age;
    char sex[3];
    char phoneNumber[20];
    char position[30];
    char birth[11];
    char department[50];
    int schoolYear;
    int schoolNumber;
    struct student* next; // 연결 리스트 포인터
};

// 전역 변수 정의
struct student* head = NULL; // 리스트 시작 더미 노드
struct student* tail = NULL; // 리스트 끝 더미 노드

// 학생 생성 함수
struct student* create_student(char* name, int age, char* sex, char* phoneNumber,
    char* position, char* birth, char* department,
    int schoolYear, int schoolNumber) {
    struct student* new_student = (struct student*)malloc(sizeof(struct student));
    if (!new_student) {
        printf("메모리 할당 실패\n");
        return NULL;
    }

    strcpy(new_student->name, name);
    new_student->age = age;
    strcpy(new_student->sex, sex);
    strcpy(new_student->phoneNumber, phoneNumber);
    strcpy(new_student->position, position);
    strcpy(new_student->birth, birth);
    strcpy(new_student->department, department);
    new_student->schoolYear = schoolYear;
    new_student->schoolNumber = schoolNumber;
    new_student->next = NULL;

    return new_student;
}

// 초기화 함수
void make_student() {
    head = (struct student*)malloc(sizeof(struct student));
    tail = (struct student*)malloc(sizeof(struct student));
    if (!head || !tail) {
        printf("메모리 할당 실패\n");
        exit(1);
    }
    head->next = tail;
    tail->next = NULL;
}

// 입력 유효성 검사 함수
void validate_input(const char* prompt, char* input, int size) {
    while (1) {
        printf("%s", prompt);
        if (fgets(input, size, stdin) != NULL) {
            // 개행 문자 제거
            input[strcspn(input, "\n")] = '\0';
            // 비어 있는 입력 확인
            if (strlen(input) == 0) {
                printf("입력 중 오류가 발생했습니다. 다시 시도해주세요.\n");
                continue;  // 빈 입력은 다시 받음
            }
            return; // 유효한 입력
        }
        else {
            // fgets 실패 시, 입력 버퍼 정리
            while (getchar() != '\n');
        }
    }
}

// 성별 함수
void insert_sex(char* sex) {
    while (1) {
        validate_input("성별 (남/여): ", sex, 3);
        if (strcmp(sex, "남") == 0 || strcmp(sex, "여") == 0) {
            return; // 유효한 입력
        }
        printf("잘못된 입력입니다. 성별은 '남' 또는 '여'만 입력 가능합니다.\n");
    }
}

// 이름 함수
void insert_name(char* name) {
    while (1) {
        validate_input("이름: ", name, 50);

        int valid = 1; // 초기값: 유효함
        for (int i = 0; name[i] != '\0'; i++) {
            unsigned char ch = name[i];
            // 아스키 문자 또는 한글(UTF-8 범위) 확인
            if (!((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') ||
                (ch >= 0x80 && ch <= 0xFF) || ch == ' ')) {
                valid = 0;
                break;
            }
        }
        if (valid) {
            return; // 유효한 입력
        }
        printf("잘못된 입력입니다. 이름에는 문자(한글 포함)와 공백만 입력 가능합니다.\n");
    }
}

// 나이 함수
void insert_age(int* age) {
    char input[100]; // 나이 입력을 받을 버퍼
    while (1) {
        validate_input("나이: ", input, sizeof(input));

        // 입력받은 값이 숫자만 포함하는지 확인
        char* endptr;
        *age = strtol(input, &endptr, 10);

        // strtol을 사용하여 숫자 변환을 시도
        if (*endptr == '\0' && *age > 0) {
            return; // 유효한 나이
        }
        else {
            printf("1 이상의 숫자로 입력해주세요.\n");
        }
    }
}

// 전화번호 함수
void insert_phone(char* phoneNumber) {
    int firstTry = 1;  // 첫 번째 시도인지 여부를 체크하는 변수
    while (1) {
        // 전화번호 입력 받기
        validate_input("전화번호 (예: 010-1234-5678): ", phoneNumber, 20);
        // 전화번호에 '-'가 포함되어 있으면 유효한 입력으로 처리
        if (strchr(phoneNumber, '-') != NULL) {
            return; // 유효한 전화번호
        }
        // 첫 번째 시도에서만 경고 메시지 출력
        if (firstTry) {
            printf("전화번호에 '-'가 포함되어야 합니다. 다시 입력해주세요.\n");
            firstTry = 0;  // 첫 번째 시도 후에 경고 메시지를 한번만 출력
        }
    }
}

// 생년월일 함수
void insert_birth(char* birth) {
    while (1) {
        validate_input("생일 (예: 2004.01.01 or 2004/01/01): ", birth, 11);
        if (strchr(birth, '.') != NULL || strchr(birth, '/') != NULL) {
            return; // 유효한 입력
        }
        printf("생일에 '.' 또는 '/'가 포함되어야 합니다. 다시 입력해주세요.\n");
    }
}

// 학생 추가 함수
void insert_student() {
    char name[50], sex[3], phoneNumber[20], position[30], birth[11], department[50];
    int age, schoolYear, schoolNumber;

    insert_name(name); // 이름 입력
    insert_age(&age);
    insert_sex(sex); // 성별 입력
    insert_phone(phoneNumber);
    validate_input("직위: ", position, 30);
    insert_birth(birth);
    validate_input("학과: ", department, 50);

    printf("학년: ");
    while (scanf("%d", &schoolYear) != 1) {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n'); // 버퍼 비우기
    }
    while (getchar() != '\n'); // 버퍼 비우기

    printf("학번: ");
    while (scanf("%d", &schoolNumber) != 1) {
        printf("숫자로 입력해주세요. 다시 입력: ");
        while (getchar() != '\n'); // 버퍼 비우기
    }
    while (getchar() != '\n'); // 버퍼 비우기

    struct student* new_student = create_student(name, age, sex, phoneNumber, position, birth, department, schoolYear, schoolNumber);
    if (!new_student) return;

    new_student->next = head->next;
    head->next = new_student;
    printf("학생이 추가되었습니다: %s\n", name);
}

// 학생 삭제 함수
void delete_student() {
    char name[50];
    printf("삭제할 학생의 이름을 입력하세요: ");
    fgets(name, 50, stdin);  // fgets로 입력 받기
    name[strcspn(name, "\n")] = '\0';  // 개행 문자 제거

    // 공백 입력 확인
    if (strlen(name) == 0) {
        printf("경고: 이름은 공백이 아니어야 합니다. 다시 메뉴로 돌아갑니다.\n");
        return;  // 메뉴로 돌아감
    }

    struct student* prev = head;
    struct student* current = head->next;

    while (current != tail) {
        if (strcmp(current->name, name) == 0) {
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
void search_student() {
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
    while (getchar() != '\n'); // 입력 버퍼 비우기

    switch (choice) {
    case 1:
        printf("검색할 학생의 이름을 입력하세요: ");
        fgets(query, 50, stdin);  // 이름 입력
        query[strcspn(query, "\n")] = '\0';  // 개행 문자 제거
        break;
    case 2:
        printf("검색할 학생의 나이를 입력하세요: ");
        fgets(query, 50, stdin);  // 나이 입력
        query[strcspn(query, "\n")] = '\0';  // 개행 문자 제거
        break;
    case 3:
        printf("검색할 학생의 성별을 입력하세요 (남/여): ");
        fgets(query, 50, stdin);  // 성별 입력
        query[strcspn(query, "\n")] = '\0';  // 개행 문자 제거
        break;
    case 4:
        printf("검색할 학생의 전화번호를 입력하세요: ");
        fgets(query, 50, stdin);  // 전화번호 입력
        query[strcspn(query, "\n")] = '\0';  // 개행 문자 제거
        break;
    case 5:
        printf("검색할 학생의 학과를 입력하세요: ");
        fgets(query, 50, stdin);  // 학과 입력
        query[strcspn(query, "\n")] = '\0';  // 개행 문자 제거
        break;
    default:
        printf("잘못된 선택입니다. 메뉴로 돌아갑니다.\n");
        return;  // 메뉴로 돌아감
    }

    struct student* current = head->next;

    while (current != tail) {
        switch (choice) {
        case 1:  // 이름으로 검색
            if (strcmp(current->name, query) == 0) {
                printf("\n=== 학생 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("나이: %d\n", current->age);
                printf("성별: %s\n", current->sex);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("직위: %s\n", current->position);
                printf("생일: %s\n", current->birth);
                printf("학과: %s\n", current->department);
                printf("학년: %d\n", current->schoolYear);
                printf("학번: %d\n", current->schoolNumber);
                return;
            }
            break;
        case 2:  // 나이로 검색
            if (current->age == atoi(query)) {
                printf("\n=== 학생 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("나이: %d\n", current->age);
                printf("성별: %s\n", current->sex);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("직위: %s\n", current->position);
                printf("생일: %s\n", current->birth);
                printf("학과: %s\n", current->department);
                printf("학년: %d\n", current->schoolYear);
                printf("학번: %d\n", current->schoolNumber);
                return;
            }
            break;
        case 3:  // 성별로 검색
            if (strcmp(current->sex, query) == 0) {
                printf("\n=== 학생 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("나이: %d\n", current->age);
                printf("성별: %s\n", current->sex);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("직위: %s\n", current->position);
                printf("생일: %s\n", current->birth);
                printf("학과: %s\n", current->department);
                printf("학년: %d\n", current->schoolYear);
                printf("학번: %d\n", current->schoolNumber);
                return;
            }
            break;
        case 4:  // 전화번호로 검색
            if (strcmp(current->phoneNumber, query) == 0) {
                printf("\n=== 학생 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("나이: %d\n", current->age);
                printf("성별: %s\n", current->sex);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("직위: %s\n", current->position);
                printf("생일: %s\n", current->birth);
                printf("학과: %s\n", current->department);
                printf("학년: %d\n", current->schoolYear);
                printf("학번: %d\n", current->schoolNumber);
                return;
            }
            break;
        case 5:  // 학과로 검색
            if (strcmp(current->department, query) == 0) {
                printf("\n=== 학생 정보 ===\n");
                printf("이름: %s\n", current->name);
                printf("나이: %d\n", current->age);
                printf("성별: %s\n", current->sex);
                printf("전화번호: %s\n", current->phoneNumber);
                printf("직위: %s\n", current->position);
                printf("생일: %s\n", current->birth);
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

// 학생 정보를 출력하는 함수
void print_student_info(struct student* student) {
    if (student == NULL) {
        printf("학생 정보가 없습니다.\n");
        return;
    }

    printf("\n=== 현재 정보 ===\n");
    printf("이름: %s\n", student->name);
    printf("나이: %d\n", student->age);
    printf("성별: %s\n", student->sex);
    printf("전화번호: %s\n", student->phoneNumber);
    printf("직위: %s\n", student->position);
    printf("생일: %s\n", student->birth);
    printf("학과: %s\n", student->department);
    printf("학년: %d\n", student->schoolYear);
    printf("학번: %d\n", student->schoolNumber);
}


// 학생 정보 수정 함수
void update_student() {
    char name[50];
    printf("수정할 학생의 이름을 입력하세요: ");
    fgets(name, 50, stdin);  // fgets로 입력 받기
    name[strcspn(name, "\n")] = '\0';  // 개행 문자 제거

    // 공백 입력 확인
    if (strlen(name) == 0) {
        printf("경고: 이름은 공백이 아니어야 합니다. 다시 메뉴로 돌아갑니다.\n");
        return;  // 메뉴로 돌아감
    }

    struct student* current = head->next;

    while (current != tail) {
        if (strcmp(current->name, name) == 0) {
            print_student_info(current);

            printf("\n=== 새 정보 입력 ===\n");

            printf("나이: ");
            scanf("%d", &current->age);
            insert_age(&current->age);

            printf("성별 (남/여): ");
            scanf("%s", current->sex);
            insert_sex(current->sex);

            printf("전화번호 (예: 010-0000-1111): ");
            scanf("%s", current->phoneNumber);
            insert_phone(current->phoneNumber);

            printf("직위: ");
            scanf("%s", current->position);

            printf("생일 (예: 2004.07.25): ");
            scanf("%s", current->birth);
            insert_birth(current->birth);

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
void print_all_students() {
    struct student* s = head->next;
    if (s == tail) {
        printf("현재 등록된 학생이 없습니다.\n");
        return;
    }

    printf("\n===== 전체 학생 목록 =====\n");
    while (s != tail) {
        printf("\n=== 학생 정보 ===\n");
        printf("이름: %s\n", s->name);
        printf("나이: %d\n", s->age);
        printf("성별: %s\n", s->sex);
        printf("전화번호: %s\n", s->phoneNumber);
        printf("직위: %s\n", s->position);
        printf("생일: %s\n", s->birth);
        printf("학과: %s\n", s->department);
        printf("학년: %d\n", s->schoolYear);
        printf("학번: %d\n", s->schoolNumber);
        s = s->next;
    }
    printf("==========================\n\n");
}

// 메뉴 출력 함수
void menu_display() {
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
int main() {
    char command;
    make_student(); // 초기화

    do {
        menu_display();
        printf("명령어를 입력하시오: ");
        command = getchar();
        while (getchar() != '\n'); // 입력 버퍼 비우기

        // 공백으로 명령어가 입력된 경우 경고 메시지 출력
        if (command == ' ' || command == '\t' || command == '\n') {
            printf("경고: 명령어는 공백이 아닌 값을 입력해야 합니다.\n");
            continue;
        }

        switch (command) {
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