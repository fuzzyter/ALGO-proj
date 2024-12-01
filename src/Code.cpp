#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �л� ����ü ����
struct student
{
    char name[50];
    int age;
    char sex[3];
    char phoneNumber[20];
    char position[30];
    char birth[11];
    char department[50];
    int schoolYear;
    int schoolNumber;
    struct student *next; // ���� ����Ʈ ������
};

// ���� ���� ����
struct student *head = NULL; // ����Ʈ ���� ���� ���
struct student *tail = NULL; // ����Ʈ �� ���� ���

// �л� ���� �Լ�
struct student *create_student(char *name, int age, char *sex, char *phoneNumber,
                               char *position, char *birth, char *department,
                               int schoolYear, int schoolNumber)
{
    struct student *new_student = (struct student *)malloc(sizeof(struct student));
    if (!new_student)
    {
        printf("�޸� �Ҵ� ����\n");
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

// �ʱ�ȭ �Լ�
void make_student()
{
    head = (struct student *)malloc(sizeof(struct student));
    tail = (struct student *)malloc(sizeof(struct student));
    if (!head || !tail)
    {
        printf("�޸� �Ҵ� ����\n");
        exit(1);
    }
    head->next = tail;
    tail->next = NULL;
}

// �Է� ��ȿ�� �˻� �Լ�: �� �Է� ����
void validate_input(const char *prompt, char *input, size_t size)
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
void validate_phone(char *phoneNumber)
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

// ������� ��ȿ�� �˻� �Լ�
void validate_birth(char *birth)
{
    do
    {
        validate_input("���� (��: 2004.01.01 or 2004/01/01): ", birth, 11);
        if (strchr(birth, '.') == NULL && strchr(birth, '/') == NULL)
        {
            printf("���Ͽ� '.' �Ǵ� '/'�� ���ԵǾ�� �մϴ�. �ٽ� �Է����ּ���.\n");
        }
    } while (strchr(birth, '.') == NULL && strchr(birth, '/') == NULL);
}

// �л� �߰� �Լ�
void insert_student()
{
    char name[50], sex[3], phoneNumber[20], position[30], birth[11], department[50];
    int age, schoolYear, schoolNumber;

    validate_input("�̸�: ", name, 50);

    printf("����: ");
    while (scanf("%d", &age) != 1)
    {
        printf("���ڷ� �Է����ּ���. �ٽ� �Է�: ");
        while (getchar() != '\n')
            ; // ���� ����
    }
    while (getchar() != '\n')
        ; // ���� ����

    validate_input("���� (��/��): ", sex, 3);
    validate_phone(phoneNumber);
    validate_input("����: ", position, 30);
    validate_birth(birth);
    validate_input("�а�: ", department, 50);

    printf("�г�: ");
    while (scanf("%d", &schoolYear) != 1)
    {
        printf("���ڷ� �Է����ּ���. �ٽ� �Է�: ");
        while (getchar() != '\n')
            ; // ���� ����
    }
    while (getchar() != '\n')
        ; // ���� ����

    printf("�й�: ");
    while (scanf("%d", &schoolNumber) != 1)
    {
        printf("���ڷ� �Է����ּ���. �ٽ� �Է�: ");
        while (getchar() != '\n')
            ; // ���� ����
    }
    while (getchar() != '\n')
        ; // ���� ����

    struct student *new_student = create_student(name, age, sex, phoneNumber, position, birth, department, schoolYear, schoolNumber);
    if (!new_student)
        return;

    new_student->next = head->next;
    head->next = new_student;
    printf("�л��� �߰��Ǿ����ϴ�: %s\n", name);
}

// �л� ���� �Լ�
void delete_student()
{
    char name[50];
    printf("������ �л��� �̸��� �Է��ϼ���: ");
    fgets(name, 50, stdin);           // fgets�� �Է� �ޱ�
    name[strcspn(name, "\n")] = '\0'; // ���� ���� ����

    // ���� �Է� Ȯ��
    if (strlen(name) == 0)
    {
        printf("���: �̸��� ������ �ƴϾ�� �մϴ�. �ٽ� �޴��� ���ư��ϴ�.\n");
        return; // �޴��� ���ư�
    }

    struct student *prev = head;
    struct student *current = head->next;

    while (current != tail)
    {
        if (strcmp(current->name, name) == 0)
        {
            prev->next = current->next;
            free(current);
            printf("�л��� �����Ǿ����ϴ�: %s\n", name);
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("�ش� �̸��� �л��� ã�� �� �����ϴ�: %s\n", name);
}

// �л� �˻� �Լ�
void search_student()
{
    int choice;
    char query[50];

    printf("\n=== �л� �˻� ===\n");
    printf("1. �̸����� �˻�\n");
    printf("2. ���̷� �˻�\n");
    printf("3. ������ �˻�\n");
    printf("4. ��ȭ��ȣ�� �˻�\n");
    printf("5. �а��� �˻�\n");
    printf("���ϴ� �˻� ī�װ��� ��ȣ�� �Է��ϼ���: ");
    scanf("%d", &choice);
    while (getchar() != '\n')
        ; // �Է� ���� ����

    switch (choice)
    {
    case 1:
        printf("�˻��� �л��� �̸��� �Է��ϼ���: ");
        fgets(query, 50, stdin);            // �̸� �Է�
        query[strcspn(query, "\n")] = '\0'; // ���� ���� ����
        break;
    case 2:
        printf("�˻��� �л��� ���̸� �Է��ϼ���: ");
        fgets(query, 50, stdin);            // ���� �Է�
        query[strcspn(query, "\n")] = '\0'; // ���� ���� ����
        break;
    case 3:
        printf("�˻��� �л��� ������ �Է��ϼ��� (��/��): ");
        fgets(query, 50, stdin);            // ���� �Է�
        query[strcspn(query, "\n")] = '\0'; // ���� ���� ����
        break;
    case 4:
        printf("�˻��� �л��� ��ȭ��ȣ�� �Է��ϼ���: ");
        fgets(query, 50, stdin);            // ��ȭ��ȣ �Է�
        query[strcspn(query, "\n")] = '\0'; // ���� ���� ����
        break;
    case 5:
        printf("�˻��� �л��� �а��� �Է��ϼ���: ");
        fgets(query, 50, stdin);            // �а� �Է�
        query[strcspn(query, "\n")] = '\0'; // ���� ���� ����
        break;
    default:
        printf("�߸��� �����Դϴ�. �޴��� ���ư��ϴ�.\n");
        return; // �޴��� ���ư�
    }

    struct student *current = head->next;

    while (current != tail)
    {
        switch (choice)
        {
        case 1: // �̸����� �˻�
            if (strcmp(current->name, query) == 0)
            {
                printf("\n=== �л� ���� ===\n");
                printf("�̸�: %s\n", current->name);
                printf("����: %d\n", current->age);
                printf("����: %s\n", current->sex);
                printf("��ȭ��ȣ: %s\n", current->phoneNumber);
                printf("����: %s\n", current->position);
                printf("����: %s\n", current->birth);
                printf("�а�: %s\n", current->department);
                printf("�г�: %d\n", current->schoolYear);
                printf("�й�: %d\n", current->schoolNumber);
                return;
            }
            break;
        case 2: // ���̷� �˻�
            if (current->age == atoi(query))
            {
                printf("\n=== �л� ���� ===\n");
                printf("�̸�: %s\n", current->name);
                printf("����: %d\n", current->age);
                printf("����: %s\n", current->sex);
                printf("��ȭ��ȣ: %s\n", current->phoneNumber);
                printf("����: %s\n", current->position);
                printf("����: %s\n", current->birth);
                printf("�а�: %s\n", current->department);
                printf("�г�: %d\n", current->schoolYear);
                printf("�й�: %d\n", current->schoolNumber);
                return;
            }
            break;
        case 3: // ������ �˻�
            if (strcmp(current->sex, query) == 0)
            {
                printf("\n=== �л� ���� ===\n");
                printf("�̸�: %s\n", current->name);
                printf("����: %d\n", current->age);
                printf("����: %s\n", current->sex);
                printf("��ȭ��ȣ: %s\n", current->phoneNumber);
                printf("����: %s\n", current->position);
                printf("����: %s\n", current->birth);
                printf("�а�: %s\n", current->department);
                printf("�г�: %d\n", current->schoolYear);
                printf("�й�: %d\n", current->schoolNumber);
                return;
            }
            break;
        case 4: // ��ȭ��ȣ�� �˻�
            if (strcmp(current->phoneNumber, query) == 0)
            {
                printf("\n=== �л� ���� ===\n");
                printf("�̸�: %s\n", current->name);
                printf("����: %d\n", current->age);
                printf("����: %s\n", current->sex);
                printf("��ȭ��ȣ: %s\n", current->phoneNumber);
                printf("����: %s\n", current->position);
                printf("����: %s\n", current->birth);
                printf("�а�: %s\n", current->department);
                printf("�г�: %d\n", current->schoolYear);
                printf("�й�: %d\n", current->schoolNumber);
                return;
            }
            break;
        case 5: // �а��� �˻�
            if (strcmp(current->department, query) == 0)
            {
                printf("\n=== �л� ���� ===\n");
                printf("�̸�: %s\n", current->name);
                printf("����: %d\n", current->age);
                printf("����: %s\n", current->sex);
                printf("��ȭ��ȣ: %s\n", current->phoneNumber);
                printf("����: %s\n", current->position);
                printf("����: %s\n", current->birth);
                printf("�а�: %s\n", current->department);
                printf("�г�: %d\n", current->schoolYear);
                printf("�й�: %d\n", current->schoolNumber);
                return;
            }
            break;
        }
        current = current->next;
    }

    printf("�ش� ���ǿ� �´� �л��� ã�� �� �����ϴ�.\n");
}

// �л� ���� ���� �Լ�
void update_student()
{
    char name[50];
    printf("������ �л��� �̸��� �Է��ϼ���: ");
    fgets(name, 50, stdin);           // fgets�� �Է� �ޱ�
    name[strcspn(name, "\n")] = '\0'; // ���� ���� ����

    // ���� �Է� Ȯ��
    if (strlen(name) == 0)
    {
        printf("���: �̸��� ������ �ƴϾ�� �մϴ�. �ٽ� �޴��� ���ư��ϴ�.\n");
        return; // �޴��� ���ư�
    }

    struct student *current = head->next;

    while (current != tail)
    {
        if (strcmp(current->name, name) == 0)
        {
            printf("\n=== ���� ���� ===\n");
            printf("�̸�: %s\n", current->name);
            printf("����: %d\n", current->age);
            printf("����: %s\n", current->sex);
            printf("��ȭ��ȣ: %s\n", current->phoneNumber);
            printf("����: %s\n", current->position);
            printf("����: %s\n", current->birth);
            printf("�а�: %s\n", current->department);
            printf("�г�: %d\n", current->schoolYear);
            printf("�й�: %d\n", current->schoolNumber);

            printf("\n=== �� ���� �Է� ===\n");
            printf("����: ");
            scanf("%d", &current->age);
            printf("���� (��/��): ");
            scanf("%s", current->sex);
            printf("��ȭ��ȣ (��: 010-0000-1111): ");
            scanf("%s", current->phoneNumber);
            printf("����: ");
            scanf("%s", current->position);
            printf("���� (��: 2004.07.25): ");
            scanf("%s", current->birth);
            printf("�а�: ");
            scanf("%s", current->department);
            printf("�г�: ");
            scanf("%d", &current->schoolYear);
            printf("�й�: ");
            scanf("%d", &current->schoolNumber);

            printf("�л� ������ �����Ǿ����ϴ�: %s\n", current->name);
            return;
        }
        current = current->next;
    }
    printf("�ش� �̸��� �л��� ã�� �� �����ϴ�: %s\n", name);
}

// �л� ��ü ��� �Լ�
void print_all_students()
{
    struct student *s = head->next;
    if (s == tail)
    {
        printf("���� ��ϵ� �л��� �����ϴ�.\n");
        return;
    }

    printf("\n===== ��ü �л� ��� =====\n");
    while (s != tail)
    {
        printf("\n=== �л� ���� ===\n");
        printf("�̸�: %s\n", s->name);
        printf("����: %d\n", s->age);
        printf("����: %s\n", s->sex);
        printf("��ȭ��ȣ: %s\n", s->phoneNumber);
        printf("����: %s\n", s->position);
        printf("����: %s\n", s->birth);
        printf("�а�: %s\n", s->department);
        printf("�г�: %d\n", s->schoolYear);
        printf("�й�: %d\n", s->schoolNumber);
        s = s->next;
    }
    printf("==========================\n\n");
}

// �޴� ��� �Լ�
void menu_display()
{
    printf("\n===== �޴� =====\n");
    printf("A. �л� �߰�\n");
    printf("D. �л� ����\n");
    printf("S. �л� �˻�\n");
    printf("U. �л� ���� ����\n");
    printf("P. �л� ��ü ���\n");
    printf("Q. ���α׷� ����\n");
    printf("=================\n");
}

// ���� �Լ�
int main()
{
    char command;
    make_student(); // �ʱ�ȭ

    do
    {
        menu_display();
        printf("���ɾ �Է��Ͻÿ�: ");
        command = getchar();
        while (getchar() != '\n')
            ; // �Է� ���� ����

        // �������� ���ɾ �Էµ� ��� ��� �޽��� ���
        if (command == ' ' || command == '\t' || command == '\n')
        {
            printf("���: ���ɾ�� ������ �ƴ� ���� �Է��ؾ� �մϴ�.\n");
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
            printf("���α׷��� �����մϴ�.\n");
            break;

        default:
            printf("�߸��� ���ɾ��Դϴ�.\n");
            break;
        }
    } while (command != 'q' && command != 'Q');

    return 0;
}
