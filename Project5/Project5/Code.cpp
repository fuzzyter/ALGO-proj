#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �л� ����ü ���� :�̸�, ��ȭ��ȣ, ����, �й�, �г�
struct Room
{
    char name[50];
    char phoneNumber[20];
    char department[50];
    int schoolYear;
    int schoolNumber;
    int start;
    int end;
    struct Room* next; // ���� ����Ʈ ������
};

// ���� ���� ����
struct Room* head = NULL;
struct Room* tail = NULL; 

// �л� ���� �Լ�
struct Room* create_lectureRoom(char* name, char* phoneNumber, char* department, int schoolYear, int schoolNumber, int start, int end)
{
    struct Room* new_Room = (struct Room*)malloc(sizeof(struct Room));
    if (!new_Room) {
        printf("�޸� �Ҵ� ����\n");
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

// �ʱ�ȭ �Լ�
void make_lectureRoom()
{
    head = (struct Room*)malloc(sizeof(struct Room));
    if (!head)
    {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    head->next = NULL; // �ʱ�ȭ �� head->next�� NULL�� ����
}

// �Է� ��ȿ�� �˻� �Լ�: �� �Է� ����
void validate_input(const char* prompt, char* input, size_t size)
{
    do
    {
        printf("%s", prompt);
        fgets(input, size, stdin);
        input[strcspn(input, "\n")] = '\0'; // ���� ���� ����
        if (strlen(input) == 0)
        {
            printf("�Է°��� ��� �ֽ��ϴ�. �ٽ� �Է����ּ���.\n");
        }
    } while (strlen(input) == 0);
}

// ��ȭ��ȣ ��ȿ�� �˻� �Լ�
void validate_phone(char* phoneNumber)
{
    do
    {
        validate_input("��ȭ��ȣ (��: 010-1234-5678): ", phoneNumber, 20);
        if (strchr(phoneNumber, '-') == NULL)
        {
            printf("��ȭ��ȣ�� '-'�� ���ԵǾ�� �մϴ�. �ٽ� �Է����ּ���.\n");
        }
    } while (strchr(phoneNumber, '-') == NULL);
}

// �л� �߰� �Լ�
void reserve_lectureRoom() {
    char name[50], phoneNumber[20], department[50];
    int schoolYear, schoolNumber, start, end;
    char inputBuffer[50]; // �Է��� ���� ����

    // �̸� �Է�
    validate_input("�̸�: ", name, 50);

    // ��ȭ��ȣ �Է�
    validate_phone(phoneNumber);

    // �а� �Է�
    validate_input("�а�: ", department, 50);

    printf("�г�: ");
    while (scanf("%d", &schoolYear) != 1) {
        printf("���ڷ� �Է����ּ���. �ٽ� �Է�: ");
        while (getchar() != '\n'); // ���� ����
    }
    while (getchar() != '\n'); // ���� ����

    // �й� �Է�
    printf("�й�: ");
    while (scanf("%d", &schoolNumber) != 1) {
        printf("���ڷ� �Է����ּ���. �ٽ� �Է�: ");
        while (getchar() != '\n'); // ���� ����
    }
    while (getchar() != '\n'); // ���� ����

    // ���� �ð��� ���� �ð� �Է�
    while (1) {
        printf("���� �ð�(0-23): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        if (sscanf(inputBuffer, "%d", &start) == 1 && start >= 0 && start <= 23) {
            break;
        }
        else {
            printf("��ȿ�� �ð��� �Է��ϼ���.\n");
        }
    }

    while (1) {
        printf("���� �ð�(0-23): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        if (sscanf(inputBuffer, "%d", &end) == 1 && end >= 0 && end <= 23) {
            break;
        }
        else {
            printf("��ȿ�� ���ڸ� �Է��ϼ���.\n");
        }
    }

    // ���� �ð� ��ħ Ȯ��
    struct Room* current = head->next;
    while (current != tail) {
        if ((start < current->end && end > current->start)) {
            printf("��ġ�� ������ �ֽ��ϴ�. �ٸ� �ð��� �����ϼ���.\n");
            return;
        }
        current = current->next; // ����Ʈ�� ���� ���ǽǷ� �̵�
    }

    // ���ο� ���ǽ� ���� �߰�
    struct Room* new_Room = create_lectureRoom(name, phoneNumber, department, schoolYear, schoolNumber, start, end);
    if (!new_Room) {
        printf("���ǽ� ���� �߰��� �����߽��ϴ�.\n");
        return; // �޸� �������� ������ �ߴ�
    }

    // �� ��带 ����Ʈ�� �߰�
    new_Room->next = head->next;
    head->next = new_Room;
    printf("���ǽǿ� �л��� �߰��Ǿ����ϴ�: %s (%d�� ~ %d��)\n", name, start, end);
}

// ���ǽ� ���� ���� �Լ�
void delete_lectureRoom() {
    int schoolNumber;
    printf("������ ������ �й��� �Է��ϼ���: ");
    scanf("%d", &schoolNumber);
    while (getchar() != '\n'); // �Է� ���� ����

    struct Room** indirect = &head->next; // head->next���� Ž�� ����
    while (*indirect != NULL) {
        struct Room* current = *indirect;
        if (current->schoolNumber == schoolNumber) {
            printf("������ �����Ǿ����ϴ�: %s (%d�� ~ %d��)\n", current->name, current->start, current->end);

            *indirect = current->next; // ��带 ����Ʈ���� ����
            free(current); // �޸� ����
            return;
        }
        indirect = &(*indirect)->next; // ���� ���� �̵�
    }

    printf("�ش� �й��� ������ �����ϴ�.\n");
}

void sort_lectureRooms() {
    struct Room* i;
    struct Room* j;

    for (i = head->next; i != NULL && i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->start > j->start) {
                // ������ ��ȯ
                char temp_name[50], temp_phone[20], temp_department[50];
                int temp_schoolYear, temp_schoolNumber, temp_start, temp_end;

                // ������ ��ȯ
                strcpy(temp_name, i->name);
                strcpy(temp_phone, i->phoneNumber);
                strcpy(temp_department, i->department);
                temp_schoolYear = i->schoolYear;
                temp_schoolNumber = i->schoolNumber;
                temp_start = i->start;
                temp_end = i->end;

                strcpy(i->name, j->name);
                strcpy(i->phoneNumber, j->phoneNumber);
                strcpy(i->department, j->department);
                i->schoolYear = j->schoolYear;
                i->schoolNumber = j->schoolNumber;
                i->start = j->start;
                i->end = j->end;

                strcpy(j->name, temp_name);
                strcpy(j->phoneNumber, temp_phone);
                strcpy(j->department, temp_department);
                j->schoolYear = temp_schoolYear;
                j->schoolNumber = temp_schoolNumber;
                j->start = temp_start;
                j->end = temp_end;
            }
        }
    }
}

// ���ǽ� ���� ���� ��� �Լ�
void print_lectureRoom_state() {

    struct Room* current = head->next;
    if (current == tail) {
        printf("���� ��ϵ� ������ �����ϴ�.\n");
        return;
    }

    printf("\n=== ���ǽ� ���� ���� ===\n");
    while (current != tail) {
        printf("�̸�: %s\n", current->name);
        printf("��ȭ��ȣ: %s\n", current->phoneNumber);
        printf("�а�: %s\n", current->department);
        printf("�г�: %d\n", current->schoolYear);
        printf("�й�: %d\n", current->schoolNumber);
        printf("���� �ð�: %d\n", current->start);
        printf("���� �ð�: %d\n", current->end);
        printf("==========================\n\n");
        current = current->next;
    }
}

void insertion_sort_Rooms() {
    struct Room* sorted = NULL;
    struct Room* current = head->next;

    while (current != tail) {
        struct Room* next = current->next;

        // ���ĵ� ��ġ ã��
        struct Room** ptr = &sorted;
        while (*ptr != NULL && (*ptr)->start < current->start) {
            ptr = &((*ptr)->next);
        }

        // ��� ����
        current->next = *ptr;
        *ptr = current;

        current = next;
    }

    head->next = sorted;
}

// ���ǽ� ���� ���� ���� �Լ�
void modify_lectureRoom() {
    int schoolNumber;
    char choice;

    print_lectureRoom_state();
    printf("U. ���� ����\n");
    printf("D. ���� ����\n");
    printf("��ɾ �Է��Ͻÿ�: ");
    scanf(" %c", &choice);  // �տ� ���� �߰��� ���� ���� ����
    while (getchar() != '\n'); // �Է� ���� ����

    switch (choice) {
    case 'D':
    case 'd': {
        printf("������ ������ �й��� �Է��ϼ���: ");
        scanf("%d", &schoolNumber);
        while (getchar() != '\n'); // �Է� ���� ����

        struct Room* current = head->next;

        while (current != tail) {
            if (current->schoolNumber == schoolNumber) {
                printf("\n=== ���� ���� ===\n");
                printf("�̸�: %s\n", current->name);
                printf("��ȭ��ȣ: %s\n", current->phoneNumber);
                printf("�а�: %s\n", current->department);
                printf("�г�: %d\n", current->schoolYear);
                printf("�й�: %d\n", current->schoolNumber);
                printf("���� �ð�: %d\n", current->start);
                printf("���� �ð�: %d\n", current->end);
                printf("==========================\n");
                printf("�ش� �л��� �½��ϱ�? Y/N\n");
                char confirm;
                while (1) {
                    confirm = getchar();
                    while (getchar() != '\n'); // �Է� ���� ����

                    if (confirm == 'Y' || confirm == 'y') {
                        delete_lectureRoom();
                        printf("�����Ǿ����ϴ�.\n");
                        return; // �Լ� ����
                    }
                    else if (confirm == 'N' || confirm == 'n') {
                        printf("��ҵǾ����ϴ�.\n");
                        return; // �Լ� ����
                    }
                    else {
                        printf("�߸��� �Է��Դϴ�. Y �Ǵ� N�� �Է����ּ���: ");
                    }
                }
            }
            current = current->next;
        }
        printf("�ش� �й��� ������ �����ϴ�.\n");
        break;
    }

    case 'U':
    case 'u': {
        printf("������ ������ �й��� �Է��ϼ���: ");
        scanf("%d", &schoolNumber);
        while (getchar() != '\n'); // �Է� ���� ����

        struct Room* current = head->next;

        while (current != tail) {
            if (current->schoolNumber == schoolNumber) {
                printf("\n=== ���� ���� ===\n");
                printf("�̸�: %s\n", current->name);
                printf("��ȭ��ȣ: %s\n", current->phoneNumber);
                printf("�а�: %s\n", current->department);
                printf("�г�: %d\n", current->schoolYear);
                printf("�й�: %d\n", current->schoolNumber);
                printf("���� �ð�: %d\n", current->start);
                printf("���� �ð�: %d\n", current->end);
                printf("==========================\n");
                printf("�ش� �л��� �½��ϱ�? Y/N\n");
                char confirm;
                while (1) {
                    confirm = getchar();
                    while (getchar() != '\n'); // �Է� ���� ����

                    if (confirm == 'Y' || confirm == 'y') {
                        printf("\n���ο� ������ �Է��ϼ���.\n");

                        // �̸� �Է�
                        validate_input("�̸�: ", current->name, 50);

                        // ��ȭ��ȣ �Է�
                        validate_phone(current->phoneNumber);

                        // �а� �Է�
                        validate_input("�а�: ", current->department, 50);

                        // �г� �Է�
                        printf("�г�: ");
                        scanf("%d", &current->schoolYear);
                        while (getchar() != '\n'); // �Է� ���� ����

                        // ���� �ð��� ���� �ð� �Է�
                        int newStart, newEnd;
                        printf("���� �ð�(0-23): ");
                        scanf("%d", &newStart);
                        printf("���� �ð�(1-24): ");
                        scanf("%d", &newEnd);
                        while (getchar() != '\n'); // �Է� ���� ����

                        // ���� �ð� �ߺ� Ȯ��
                        struct Room* temp = head->next;
                        while (temp != tail) {
                            if (temp != current && (newStart < temp->end && newEnd > temp->start)) {
                                printf("��ġ�� ������ �ֽ��ϴ�. ������ ����մϴ�.\n");
                                return;
                            }
                            temp = temp->next;
                        }

                        // �ð� ������Ʈ
                        current->start = newStart;
                        current->end = newEnd;

                        printf("������ ���������� �����Ǿ����ϴ�!\n");
                        return;
                    }
                    else if (confirm == 'N' || confirm == 'n') {
                        printf("��ҵǾ����ϴ�.\n");
                        return;
                    }
                    else {
                        printf("�߸��� �Է��Դϴ�. Y �Ǵ� N�� �Է����ּ���: ");
                    }
                }
            }
            current = current->next;
        }
        printf("�ش� �й��� ������ �����ϴ�.\n");
        break;
    }

    default:
        printf("�߸��� ��ɾ��Դϴ�.\n");
        break;
    }
}

void free_lectureRooms() {
    struct Room* current = head;
    while (current != NULL) {
        struct Room* temp = current;
        current = current->next;
        free(temp);
    }
}


// �޴� ��� �Լ�
void menu_display()
{
    printf("\n===== �޴� =====\n");
    printf("A. ���ǽ� ����\n");
    printf("L. ���� ���\n");
    printf("U. ���� ���� ����/����\n");
    printf("Q. ���α׷� ����\n");
    printf("=================\n");
}

// ���� �Լ�
int main() {
    char command;

    make_lectureRoom(); // �ʱ�ȭ

    do
    {
        menu_display();
        printf("��ɾ �Է��Ͻÿ�: ");
        command = getchar();
        while (getchar() != '\n');

        if (command == ' ' || command == '\t' || command == '\n')
        {
            printf("���: ��ɾ�� ������ �ƴ� ���� �Է��ؾ� �մϴ�.\n");
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
            printf("���α׷��� �����մϴ�.\n");
            free_lectureRooms();
            break;

        default:
            printf("�߸��� ��ɾ��Դϴ�.\n");
            break;
        }
    } while (command != 'q' && command != 'Q');

    return 0;
}