#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char name[50];        // ��� �̸�
    struct Node* child;   // ù��° �ڽĳ��
    struct Node* sibling; // ���� ���� ���
} Node;

// �� ��� �����Լ�
Node* createNode(const char* name)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// �ڽ� ��� �߰��Լ�
void addChild(Node* parent, Node* child)
{
    if (parent->child == NULL)
    {
        parent->child = child;
    }
    else
    {
        Node* temp = parent->child;
        while (temp->sibling)
        {
            temp = temp->sibling;
        }
        temp->sibling = child;
    }
}

// Ʈ�� ��� �Լ�
void printTree(Node* root, int depth)
{
    if (root == NULL)
        return;

    for (int i = 0; i < depth; i++)
    {
        printf("    "); // �鿩����
    }
    printf("�� %s\n", root->name);

    printTree(root->child, depth + 1);
    printTree(root->sibling, depth);
}

// ���� �޸� ���� �Լ�
void freeTree(Node* root)
{
    if (root == NULL)
        return;

    freeTree(root->child);
    freeTree(root->sibling);

    free(root);
}

//
int main()
{
    // ���Ƹ� ���� Ʈ��------------------
    // Ʈ�� ����
    Node* chairman = createNode("ȸ��");
    Node* viceChairman = createNode("��ȸ��");
    Node* scribe = createNode("����");
    Node* financeManager = createNode("�ѹ�");
    Node* branchHead = createNode("����");

    addChild(chairman, viceChairman);
    addChild(chairman, scribe);
    addChild(chairman, financeManager);
    addChild(chairman, branchHead);

    Node* promotionTeam = createNode("ȫ����");
    Node* designTeam = createNode("��������");
    Node* planningTeam = createNode("��ȹ��");

    addChild(viceChairman, promotionTeam);
    addChild(viceChairman, designTeam);
    addChild(viceChairman, planningTeam);

    Node* generalMember = createNode("�Ϲ� �ο�");
    Node* inactiveMember = createNode("��Ȱ���ο�");

    addChild(planningTeam, generalMember);
    addChild(planningTeam, inactiveMember);

    // Ʈ�� ���
    printf("���Ƹ� ������ Ʈ�� : \n");
    printTree(chairman, 0);
    printf("\n\n");

    freeTree(chairman);
    chairman = NULL; // ������ �ʱ�ȭ

    // ���� Ʈ�� ���� Ʈ��------------------
    Node* university = createNode("����");

    Node* creativeArtsCollege = createNode("ũ������Ƽ���ι���������");
    Node* socialScienceCollege = createNode("�̷����ջ�ȸ���д���");
    Node* designCollege = createNode("�����δ���");
    Node* itCollege = createNode("IT��������");
    Node* sangsangCollege = createNode("â�����մ���");

    addChild(university, creativeArtsCollege);
    addChild(university, socialScienceCollege);
    addChild(university, designCollege);
    addChild(university, itCollege);
    addChild(university, sangsangCollege);

    // ũ������Ƽ�� �ι���������
    Node* creativeArtsDept = createNode("ũ������Ƽ���ι��к�");
    Node* fineArtsDept = createNode("�����к�");
    addChild(creativeArtsCollege, creativeArtsDept);
    addChild(creativeArtsCollege, fineArtsDept);

    Node* ameCultureContent = createNode("���̹�ȭ������Ʈ��");
    Node* ameLangInformation = createNode("���̾������Ʈ��");
    Node* koreanEducation = createNode("�ѱ����Ʈ��");
    Node* historyCulCuration = createNode("���繮ȭť���̼�Ʈ��");
    Node* historyContent = createNode("����������Ʈ��");
    Node* knowInformCulture = createNode("����������ȭƮ��");
    Node* digitHumanInform = createNode("�������ι�������Ʈ��");

    addChild(creativeArtsDept, ameCultureContent);
    addChild(creativeArtsDept, ameLangInformation);
    addChild(creativeArtsDept, koreanEducation);
    addChild(creativeArtsDept, historyCulCuration);
    addChild(creativeArtsDept, historyContent);
    addChild(creativeArtsDept, knowInformCulture);
    addChild(creativeArtsDept, digitHumanInform);

    Node* orientalDraw = createNode("����ȭ����");
    Node* westernDraw = createNode("����ȭ����");
    Node* ballet = createNode("�߷�����");
    Node* koreanDance = createNode("�ѱ���������");
    Node* modernDance = createNode("���빫������");

    addChild(fineArtsDept, orientalDraw);
    addChild(fineArtsDept, westernDraw);
    addChild(fineArtsDept, ballet);
    addChild(fineArtsDept, koreanDance);
    addChild(fineArtsDept, modernDance);

    // �̷����ջ�ȸ���д���
    Node* socialScienceDept = createNode("��ȸ���к�");
    Node* globalFashionDept = createNode("�۷ι��мǻ���к�");
    addChild(socialScienceCollege, socialScienceDept);
    addChild(socialScienceCollege, globalFashionDept);

    Node* internationalTrade = createNode("��������Ʈ��");
    Node* globalBusiness = createNode("�۷ι�����Ͻ�Ʈ��");
    Node* corporEconAnal = createNode("��������м�Ʈ��");
    Node* EconFinanInvest = createNode("������������Ʈ��");
    Node* publicAdminist = createNode("��������Ʈ��");
    Node* legalPolicy = createNode("����åƮ��");
    Node* realEstate = createNode("�ε���Ʈ��");
    Node* smartCity = createNode("����Ʈ���ñ����ȹƮ��");
    Node* corporManage = createNode("����濵Ʈ��");
    Node* accountFinancialManage = createNode("ȸ���繫�濵Ʈ��");

    addChild(socialScienceDept, internationalTrade);
    addChild(socialScienceDept, globalBusiness);
    addChild(socialScienceDept, corporEconAnal);
    addChild(socialScienceDept, EconFinanInvest);
    addChild(socialScienceDept, publicAdminist);
    addChild(socialScienceDept, legalPolicy);
    addChild(socialScienceDept, realEstate);
    addChild(socialScienceDept, smartCity);
    addChild(socialScienceDept, corporManage);
    addChild(socialScienceDept, accountFinancialManage);

    // �����δ���
    Node* globalFasion = createNode("�۷ι��мǻ���к�");
    Node* ictDesignDept = createNode("ICT�������к�");
    Node* beautyDesignDept = createNode("��Ƽ�����θŴ�����Ʈ�а�");

    addChild(designCollege, ictDesignDept);
    addChild(designCollege, beautyDesignDept);
    addChild(designCollege, globalFashionDept);

    Node* fasionDesign = createNode("�мǵ�����Ʈ��");
    Node* fasionMaket = createNode("�мǸ�����Ʈ��");
    Node* fasionCreaDirect = createNode("�м�ũ������Ƽ��𷺼�Ʈ��");

    addChild(globalFashionDept, fasionDesign);
    addChild(globalFashionDept, fasionMaket);
    addChild(globalFashionDept, fasionCreaDirect);

    Node* UXUI = createNode("UXUI������Ʈ��");
    Node* movieAni = createNode("����ִϸ��̼ǵ�����Ʈ��");
    Node* interior = createNode("���׸��������Ʈ��");
    Node* VMD = createNode("VMD���õ�����Ʈ��");
    Node* gameGraphic = createNode("���ӱ׷��ȵ�����Ʈ��");
    Node* visual = createNode("�ð�������Ʈ��");

    addChild(ictDesignDept, UXUI);
    addChild(ictDesignDept, movieAni);
    addChild(ictDesignDept, interior);
    addChild(ictDesignDept, VMD);
    addChild(ictDesignDept, gameGraphic);
    addChild(ictDesignDept, visual);

    // IT��������
    Node* computerScienceDept = createNode("��ǻ�Ͱ��к�");
    Node* electronicsDept = createNode("������ڰ��к�");
    Node* industrialSystemsDept = createNode("����ý��۰��к�");
    Node* smartManufacturingDept = createNode("����Ʈ���������������а�");

    addChild(itCollege, computerScienceDept);
    addChild(itCollege, electronicsDept);
    addChild(itCollege, industrialSystemsDept);
    addChild(itCollege, smartManufacturingDept);

    Node* mobileSoft = createNode("����ϼ���Ʈ����Ʈ��");
    Node* bigData = createNode("������Ʈ��");
    Node* digitConVirtual = createNode("��������������������Ʈ��");
    Node* web = createNode("������Ʈ��");

    addChild(computerScienceDept, mobileSoft);
    addChild(computerScienceDept, bigData);
    addChild(computerScienceDept, digitConVirtual);
    addChild(computerScienceDept, web);

    Node* electron = createNode("����Ʈ��");
    Node* sysSemiconductor = createNode("�ý��۹ݵ�üƮ��");
    Node* machineSysDisign = createNode("���ý��۵�����Ʈ��");
    Node* AIrobotFuse = createNode("AI�κ�����Ʈ��");

    addChild(electronicsDept, electron);
    addChild(electronicsDept, sysSemiconductor);
    addChild(electronicsDept, machineSysDisign);
    addChild(electronicsDept, AIrobotFuse);

    Node* industrialEngin = createNode("�������Ʈ��");
    Node* appIndustyDataEngin = createNode("�����������Ͱ���Ʈ��");

    // â�����մ���
    Node* creativeHumanitiesDept = createNode("���������к�(1�г�)");
    Node* generalDept = createNode("�а�");

    addChild(sangsangCollege, creativeHumanitiesDept);
    addChild(sangsangCollege, generalDept);

    Node* literCurturalCon = createNode("���й�ȭ�������а�");
    Node* AIapplication = createNode("AI�����а�");
    Node* ConverSecurity = createNode("���պ����а�");
    Node* futureMobility = createNode("�̷������Ƽ�а�");

    printf("���� Ʈ�� ���� Ʈ�� : \n");
    printTree(university, 0);
    printf("\n\n");

    freeTree(university);
    university = NULL;

    return 0;
}