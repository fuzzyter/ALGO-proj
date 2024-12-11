#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "greedy.h"
// #include "StudentList.h"

// �л� ����ü ���� :�̸�, ��ȭ��ȣ, ����, �й�, �г�
struct Room
{
    char name[50];
    char phoneNumber[20];
    char department[50];
    int schoolNumber;
    int start;
    int end;
    struct Room* next; // ���� ����Ʈ ������
};

// ���� ���� ����
struct Room* head = NULL;
struct Room* tail = NULL;

// �л� ���� �Լ�
struct Room* create_lectureRoom(char* name, char* phoneNumber, char* department, int schoolNumber, int start, int end)
{
    struct Room* new_Room = (struct Room*)malloc(sizeof(struct Room));
    if (!new_Room)
    {
        printf("�޸� �Ҵ� ����\n");
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

// �ʱ�ȭ �Լ�
void make_lectureRoom()
{
    head = (struct Room*)malloc(sizeof(struct Room));
    tail = (struct Room*)malloc(sizeof(struct Room));
    if (!head || !tail)
    {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    head->next = tail;
    tail->next = NULL;
}

// �Է� ��ȿ�� �˻� �Լ�: �� �Է� ����
void validate_input(const char* prompt, char* input, size_t size)
{
    while (1)
    {
        printf("%s", prompt);
        if (fgets(input, size, stdin) == NULL)
        {
            printf("�Է��� �д� �� ������ �߻��߽��ϴ�. �ٽ� �õ����ּ���.\n");
            continue;
        }

        input[strcspn(input, "\n")] = '\0'; // ���� ���� ����
        if (strlen(input) == 0)
        {
            printf("�Է°��� ��� �ֽ��ϴ�. �ٽ� �Է����ּ���.\n");
        }
        else
        {
            break;
        }
    }
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
void reserve_lectureRoom()
{
    char name[50], phoneNumber[20], department[50];
    int schoolNumber, start, end;
    char inputBuffer[50]; // �Է��� ���� ����

    // �̸� �Է�
    validate_input("�̸�: ", name, sizeof(name));

    // ��ȭ��ȣ �Է�
    validate_phone(phoneNumber);

    // �а� �Է�
    validate_input("�а�: ", department, sizeof(department));

    // �й� �Է�
    printf("�й�: ");
    while (scanf("%d", &schoolNumber) != 1)
    {
        printf("���ڷ� �Է����ּ���. �ٽ� �Է�: ");
        while (getchar() != '\n')
            ; // ���� ����
    }
    while (getchar() != '\n')
        ; // ���� ����

    // ���� �ð��� ���� �ð� �Է�
    while (1)
    {
        // ����� �ð��� Ȯ���ؼ� ���
        printf("����� �ð�: ");
        struct Room* current = head->next;
        int hasReservations = 0; // ������ �����ϴ��� Ȯ���ϴ� �÷���

        while (current != tail)
        {
            printf("(%d~%d�� ���� ����) ", current->start, current->end);
            current = current->next;
            hasReservations = 1;
        }

        if (!hasReservations)
        {
            printf("����");
        }
        printf("\n");

        // ���� �ð� �Է�
        printf("���� �ð�(0-23): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        if (sscanf(inputBuffer, "%d", &start) == 1 && start >= 0 && start <= 23)
        {
            break;
        }
        else
        {
            printf("��ȿ�� �ð��� �Է��ϼ���.\n");
        }
    }

    while (1)
    {
        // ���� �ð� �Է�
        printf("���� �ð�(0-23): ");
        fgets(inputBuffer, sizeof(inputBuffer), stdin);
        if (sscanf(inputBuffer, "%d", &end) == 1 && end >= 0 && end <= 23)
        {
            break;
        }
        else
        {
            printf("��ȿ�� �ð��� �Է��ϼ���.\n");
        }
    }

    // ���� �ð� ��ħ Ȯ��
    struct Room* current = head->next;
    while (current != tail)
    {
        if ((start < current->end && end > current->start))
        {
            printf("��ġ�� ������ �ֽ��ϴ�. �ٸ� �ð��� �����ϼ���.\n");
            // �ð��� �ٽ� �Է¹ޱ� ���� �ݺ���
            while (1)
            {
                printf("���ο� ���� �ð�(0-23): ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                if (sscanf(inputBuffer, "%d", &start) == 1 && start >= 0 && start <= 23)
                {
                    break;
                }
                else
                {
                    printf("��ȿ�� �ð��� �Է��ϼ���.\n");
                }
            }

            while (1)
            {
                printf("���ο� ���� �ð�(0-23): ");
                fgets(inputBuffer, sizeof(inputBuffer), stdin);
                if (sscanf(inputBuffer, "%d", &end) == 1 && end >= 0 && end <= 23)
                {
                    break;
                }
                else
                {
                    printf("��ȿ�� ���ڸ� �Է��ϼ���.\n");
                }
            }

            // ���� �ð� ��ħ Ȯ���� �ٽ� ����
            current = head->next;
            continue; // �ٽ� �ð��� �Է¹޵���
        }
        current = current->next;
    }

    // ���ο� ���ǽ� ���� �߰�
    struct Room* new_Room = create_lectureRoom(name, phoneNumber, department, schoolNumber, start, end);
    if (!new_Room)
        return;

    new_Room->next = head->next;
    head->next = new_Room;
    printf("\n���ǽǿ� �л��� �߰��Ǿ����ϴ�: %s (%d�� ~ %d��)\n", name, start, end);
}

// ���ǽ� ���� ���� ���� (�׸��� �˰���)
void insertion_sort_Rooms()
{
    struct Room* sorted = NULL;
    struct Room* current = head->next;

    while (current != tail)
    {
        struct Room* next = current->next;

        // ���ĵ� ��ġ ã�� (���� �ð� ���� �������� ����)
        struct Room** ptr = &sorted;
        while (*ptr != NULL && (*ptr)->start < current->start)
        {
            ptr = &((*ptr)->next);
        }

        // ��� ����
        current->next = *ptr;
        *ptr = current;

        current = next;
    }

    // ��� ���� ����Ʈ�� ���ĵ� ����Ʈ�� ����
    head->next = sorted;
}

// ���ǽ� ���� ���� �Լ�
void delete_lectureRoom()
{
    int schoolNumber;
    printf("������ ������ �й��� �Է��ϼ���: ");
    scanf("%d", &schoolNumber);
    while (getchar() != '\n')
        ; // �Է� ���� ����

    struct Room* current = head->next;
    struct Room* prev = NULL;

    while (current != tail)
    {
        if (current->schoolNumber == schoolNumber)
        {
            // ������ ã���� ���� ���� �޽����� ���
            printf("������ �����Ǿ����ϴ�.\n");

            if (prev)
            {
                prev->next = current->next;
            }
            else
            {
                head->next = current->next; // ����� ù ��° ����� ���
            }

            free(current); // �޸� ����
            return;
        }
        prev = current;
        current = current->next;
    }

    printf("�ش� �й��� �����ϴ�.\n");
}

void sort_lectureRooms()
{
    struct Room* i, * j;
    for (i = head->next; i != tail; i = i->next)
    {
        for (j = i->next; j != tail; j = j->next)
        {
            if (i->start > j->start)
            {
                // ������ ��ȯ
                struct Room temp = *i;
                *i = *j;
                *j = temp;

                // ������ ����
                temp.next = i->next;
                i->next = j->next;
                j->next = temp.next;
            }
        }
    }
}

// ���ǽ� ���� ���� ��� �Լ�
void print_lectureRoom_state()
{
    // ���ǽ� ������� ����  �ð� �������� ����
    insertion_sort_Rooms();

    struct Room* current = head->next;
    if (current == tail)
    {
        printf("���� ��ϵ� ������ �����ϴ�.\n");
        return;
    }

    printf("\n=== ���ǽ� ���� ���� ===\n");
    while (current != tail)
    {
        printf("�̸�: %s\n", current->name);
        printf("��ȭ��ȣ: %s\n", current->phoneNumber);
        printf("�а�: %s\n", current->department);
        printf("�й�: %d\n", current->schoolNumber);
        printf("���� �ð�: %d\n", current->start);
        printf("���� �ð�: %d\n", current->end);
        printf("==========================\n\n");
        current = current->next;
    }
}

// ���ǽ� ���� ���� ���� �Լ�
void modify_lectureRoom()
{
    int schoolNumber;
    char choice;

    print_lectureRoom_state();
    printf("U. ���� ����\n");
    printf("D. ���� ����\n");
    printf("��ɾ �Է��Ͻÿ�: ");
    scanf(" %c", &choice); // �տ� ���� �߰��� ���� ���� ����
    while (getchar() != '\n')
        ; // �Է� ���� ����

    switch (choice)
    {
    case 'D':
    case 'd':
    {
        printf("������ ������ �й��� �Է��ϼ���: ");
        scanf("%d", &schoolNumber);
        while (getchar() != '\n')
            ; // �Է� ���� ����

        struct Room* current = head->next;

        while (current != tail)
        {
            if (current->schoolNumber == schoolNumber)
            {
                printf("\n=== ���� ���� ===\n");
                printf("�̸�: %s\n", current->name);
                printf("��ȭ��ȣ: %s\n", current->phoneNumber);
                printf("�а�: %s\n", current->department);
                printf("�й�: %d\n", current->schoolNumber);
                printf("���� �ð�: %d\n", current->start);
                printf("���� �ð�: %d\n", current->end);
                printf("==========================\n");
                printf("�ش� �л��� �½��ϱ�? Y/N\n");
                char confirm;
                while (1)
                {
                    confirm = getchar();
                    while (getchar() != '\n')
                        ; // �Է� ���� ����

                    if (confirm == 'Y' || confirm == 'y')
                    {
                        delete_lectureRoom();
                        printf("�����Ǿ����ϴ�.\n");
                        return; // �Լ� ����
                    }
                    else if (confirm == 'N' || confirm == 'n')
                    {
                        printf("��ҵǾ����ϴ�.\n");
                        return; // �Լ� ����
                    }
                    else
                    {
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
    case 'u':
    {
        printf("������ ������ �й��� �Է��ϼ���: ");
        scanf("%d", &schoolNumber);
        while (getchar() != '\n')
            ; // �Է� ���� ����

        struct Room* current = head->next;

        while (current != tail)
        {
            if (current->schoolNumber == schoolNumber)
            {
                printf("\n=== ���� ���� ===\n");
                printf("�̸�: %s\n", current->name);
                printf("��ȭ��ȣ: %s\n", current->phoneNumber);
                printf("�а�: %s\n", current->department);
                printf("�й�: %d\n", current->schoolNumber);
                printf("���� �ð�: %d\n", current->start);
                printf("���� �ð�: %d\n", current->end);
                printf("==========================\n");
                printf("�ش� �л��� �½��ϱ�? Y/N\n");
                char confirm;
                while (1)
                {
                    confirm = getchar();
                    while (getchar() != '\n')
                        ; // �Է� ���� ����

                    if (confirm == 'Y' || confirm == 'y')
                    {
                        printf("\n���ο� ������ �Է��ϼ���.\n");

                        // �̸� �Է�
                        validate_input("�̸�: ", current->name, 50);

                        // ��ȭ��ȣ �Է�
                        validate_phone(current->phoneNumber);

                        // �а� �Է�
                        validate_input("�а�: ", current->department, 50);

                        // ���� �ð��� ���� �ð� �Է�
                        int newStart, newEnd;
                        printf("���� �ð�(0-23): ");
                        scanf("%d", &newStart);
                        printf("���� �ð�(1-24): ");
                        scanf("%d", &newEnd);
                        while (getchar() != '\n')
                            ; // �Է� ���� ����

                        // ���� �ð� �ߺ� Ȯ��
                        struct Room* temp = head->next;
                        while (temp != tail)
                        {
                            if (temp != current && (newStart < temp->end && newEnd > temp->start))
                            {
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
                    else if (confirm == 'N' || confirm == 'n')
                    {
                        printf("��ҵǾ����ϴ�.\n");
                        return;
                    }
                    else
                    {
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

// �޴� ��� �Լ�
void menu_display()
{
    printf("\n===== �޴� =====\n");
    printf("A. ���ǽ� ������ �߰�\n");
    printf("L. ������ ���\n");
    printf("U. ������ ���� ����/����\n\n");
    printf("S. ���ǽ� ���� ��� Ȯ��\n\n");
    printf("H. ���α׷� ����\n");
    printf("Q. ���α׷� ����\n");
    printf("=================\n");
}

void help_display()
{
    printf("\n\n    << ���ǽ� ���� ���α׷� ���� >>\n");
    printf("    ���ǽ� ������ �߰�(A): ���ǽ��� �����ϰ� ���� �л��� ������ �Է��ϴ� ���\n");
    printf("    ������ ���(L): ���� �ԷµǾ� �ִ� �л� ����� �˷��ִ� ���\n");
    printf("    ������ ���� ����/����(U): AŰ�� ���� �Է��� �л��� ������ ������ �� �ִ� ���\n");
    printf("                              �����Ϸ��� �й��� �˾ƾ� �մϴ�.\n\n");
    printf("    ���ǽ� ���� ��� Ȯ��(S): ���ǽ� ������ �����ϰ�, �ڽ��� ������ ���ǽ��� Ȯ���� �� �ֽ��ϴ�.\n\n");
    printf("    ���α׷� ����(Q): ���ǽ� ���� ���α׷��� �����մϴ�.\n\n");
}

// CSV ���Ͽ��� �����͸� �ҷ��� ����Ʈ�� �߰��ϴ� �Լ�

void load_csv(const char* filename)
{
    FILE* file = fopen(filename, "r");
    if (!file)
    {
        printf("CSV ������ �� �� �����ϴ�: %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        // ù ��° ���� ������ �ǳʶٱ�
        if (strstr(line, "name,phoneNumber,department"))
        {
            continue;
        }

        char name[50], phoneNumber[20], department[50];
        int schoolYear, schoolNumber, start, end;

        // CSV ���� ���Ŀ� ���� sscanf�� �� ����
        if (sscanf(line, "%49[^,],%19[^,],%49[^,],%d,%d,%d,%d", name, phoneNumber, department, &schoolYear, &schoolNumber, &start, &end) == 7)
        {
            struct Room* new_Room = create_lectureRoom(name, phoneNumber, department, schoolYear, schoolNumber, start, end);
            if (!new_Room)
            {
                printf("���ο� �л� �����͸� �߰����� ���߽��ϴ�.\n");
                continue;
            }

            // ����Ʈ�� �߰�
            new_Room->next = head->next;
            head->next = new_Room;
        }
        else
        {
            printf("CSV ������ ������ �ùٸ��� �ʽ��ϴ�: %s\n", line);
        }
    }

    fclose(file);
    printf("CSV ���Ͽ��� �����͸� ���������� �ε��߽��ϴ�.\n");
}

// ���� �Լ�
int main()
{
    char command;

    make_lectureRoom(); // �ʱ�ȭ
    load_csv("studentList.csv"); //csv���� �ҷ�����

    do
    {
        menu_display();
        printf("��ɾ �Է��Ͻÿ�: ");
        command = getchar();
        while (getchar() != '\n')
            ;

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

        case 'S':
        case 's':
            //greedyAlgorithm(Room);
            break;

        case 'H':
        case 'h':
            help_display();
            break;

        case 'Q':
        case 'q':
            printf("���α׷��� �����մϴ�.\n");
            break;

        default:
            printf("�߸��� ��ɾ��Դϴ�.\n");
            break;
        }
    } while (command != 'q' && command != 'Q');

    return 0;
}