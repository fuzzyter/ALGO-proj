#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char name[50];        // 노드 이름
    struct Node *child;   // 첫번째 자식노드
    struct Node *sibling; // 다음 형제 노드
} Node;

// 새 노드 생성함수
Node *createNode(const char *name)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->child = NULL;
    newNode->sibling = NULL;
    return newNode;
}

// 자식 노드 추가함수
void addChild(Node *parent, Node *child)
{
    if (parent->child == NULL)
    {
        parent->child = child;
    }
    else
    {
        Node *temp = parent->child;
        while (temp->sibling)
        {
            temp = temp->sibling;
        }
        temp->sibling = child;
    }
}

// 트리 출력 함수
void printTree(Node *root, int depth)
{
    if (root == NULL)
        return;

    for (int i = 0; i < depth; i++)
    {
        printf("    "); // 들여쓰기
    }
    printf("ㄴ %s\n", root->name);

    printTree(root->child, depth + 1);
    printTree(root->sibling, depth);
}

// 동적 메모리 해제 함수
void freeTree(Node *root)
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
    // 동아리 구조 트리------------------
    // 트리 생성
    Node *chairman = createNode("회장");
    Node *viceChairman = createNode("부회장");
    Node *scribe = createNode("서기");
    Node *financeManager = createNode("총무");
    Node *branchHead = createNode("기장");

    addChild(chairman, viceChairman);
    addChild(chairman, scribe);
    addChild(chairman, financeManager);
    addChild(chairman, branchHead);

    Node *promotionTeam = createNode("홍보팀");
    Node *designTeam = createNode("디자인팀");
    Node *planningTeam = createNode("기획팀");

    addChild(viceChairman, promotionTeam);
    addChild(viceChairman, designTeam);
    addChild(viceChairman, planningTeam);

    Node *generalMember = createNode("일반 부원");
    Node *inactiveMember = createNode("미활동부원");

    addChild(planningTeam, generalMember);
    addChild(planningTeam, inactiveMember);

    // 트리 출력
    printf("동아리 조직도 트리 : \n");
    printTree(chairman, 0);
    printf("\n\n");

    freeTree(chairman);
    chairman = NULL; // 포인터 초기화

    // 대학 트랙 구조 트리------------------
    Node *university = createNode("대학");

    Node *creativeArtsCollege = createNode("크리에이티브인문예술대학");
    Node *socialScienceCollege = createNode("미래융합사회과학대학");
    Node *designCollege = createNode("디자인대학");
    Node *itCollege = createNode("IT공과대학");
    Node *sangsangCollege = createNode("창의융합대학");

    addChild(university, creativeArtsCollege);
    addChild(university, socialScienceCollege);
    addChild(university, designCollege);
    addChild(university, itCollege);
    addChild(university, sangsangCollege);

    // 크리에이티브 인문예술대학
    Node *creativeArtsDept = createNode("크리에이티브인문학부");
    Node *fineArtsDept = createNode("예술학부");
    addChild(creativeArtsCollege, creativeArtsDept);
    addChild(creativeArtsCollege, fineArtsDept);

    Node *ameCultureContent = createNode("영미문화콘텐츠트랙");
    Node *ameLangInformation = createNode("영미언어정보트랙");
    Node *koreanEducation = createNode("한국어교육트랙");
    Node *historyCulCuration = createNode("역사문화큐레이션트랙");
    Node *historyContent = createNode("역사콘텐츠트랙");
    Node *knowInformCulture = createNode("지식정보문화트랙");
    Node *digitHumanInform = createNode("디지털인문정보학트랙");

    addChild(creativeArtsDept, ameCultureContent);
    addChild(creativeArtsDept, ameLangInformation);
    addChild(creativeArtsDept, koreanEducation);
    addChild(creativeArtsDept, historyCulCuration);
    addChild(creativeArtsDept, historyContent);
    addChild(creativeArtsDept, knowInformCulture);
    addChild(creativeArtsDept, digitHumanInform);

    Node *orientalDraw = createNode("동양화전공");
    Node *westernDraw = createNode("서양화전공");
    Node *ballet = createNode("발레전공");
    Node *koreanDance = createNode("한국무용전공");
    Node *modernDance = createNode("현대무용전공");

    addChild(fineArtsDept, orientalDraw);
    addChild(fineArtsDept, westernDraw);
    addChild(fineArtsDept, ballet);
    addChild(fineArtsDept, koreanDance);
    addChild(fineArtsDept, modernDance);

    // 미래융합사회과학대학
    Node *socialScienceDept = createNode("사회과학부");
    Node *globalFashionDept = createNode("글로벌패션산업학부");
    addChild(socialScienceCollege, socialScienceDept);
    addChild(socialScienceCollege, globalFashionDept);

    Node *internationalTrade = createNode("국제무역트랙");
    Node *globalBusiness = createNode("글로벌비즈니스트랙");
    Node *corporEconAnal = createNode("기업경제분석트랙");
    Node *EconFinanInvest = createNode("경제금융투자트랙");
    Node *publicAdminist = createNode("공공행정트랙");
    Node *legalPolicy = createNode("법정책트랙");
    Node *realEstate = createNode("부동산트랙");
    Node *smartCity = createNode("스마트도시교통계획트랙");
    Node *corporManage = createNode("기업경영트랙");
    Node *accountFinancialManage = createNode("회계재무경영트랙");

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

    // 디자인대학
    Node *globalFasion = createNode("글로벌패션산업학부");
    Node *ictDesignDept = createNode("ICT디자인학부");
    Node *beautyDesignDept = createNode("뷰티디자인매니지먼트학과");

    addChild(designCollege, ictDesignDept);
    addChild(designCollege, beautyDesignDept);
    addChild(designCollege, globalFashionDept);

    Node *fasionDesign = createNode("패션디자인트랙");
    Node *fasionMaket = createNode("패션마케팅트랙");
    Node *fasionCreaDirect = createNode("패션크리에이티브디렉션트랙");

    addChild(globalFashionDept, fasionDesign);
    addChild(globalFashionDept, fasionMaket);
    addChild(globalFashionDept, fasionCreaDirect);

    Node *UXUI = createNode("UXUI디자인트랙");
    Node *movieAni = createNode("영상애니메이션디자인트랙");
    Node *interior = createNode("인테리어디자인트랙");
    Node *VMD = createNode("VMD전시디자인트랙");
    Node *gameGraphic = createNode("게임그래픽디자인트랙");
    Node *visual = createNode("시각디자인트랙");

    addChild(ictDesignDept, UXUI);
    addChild(ictDesignDept, movieAni);
    addChild(ictDesignDept, interior);
    addChild(ictDesignDept, VMD);
    addChild(ictDesignDept, gameGraphic);
    addChild(ictDesignDept, visual);

    // IT공과대학
    Node *computerScienceDept = createNode("컴퓨터공학부");
    Node *electronicsDept = createNode("기계전자공학부");
    Node *industrialSystemsDept = createNode("산업시스템공학부");
    Node *smartManufacturingDept = createNode("스마트제조혁신컨설팅학과");

    addChild(itCollege, computerScienceDept);
    addChild(itCollege, electronicsDept);
    addChild(itCollege, industrialSystemsDept);
    addChild(itCollege, smartManufacturingDept);

    Node *mobileSoft = createNode("모바일소프트웨어트랙");
    Node *bigData = createNode("빅데이터트랙");
    Node *digitConVirtual = createNode("디지털콘텐츠가상현실트랙");
    Node *web = createNode("웹공학트랙");

    addChild(computerScienceDept, mobileSoft);
    addChild(computerScienceDept, bigData);
    addChild(computerScienceDept, digitConVirtual);
    addChild(computerScienceDept, web);

    Node *electron = createNode("전자트랙");
    Node *sysSemiconductor = createNode("시스템반도체트랙");
    Node *machineSysDisign = createNode("기계시스템디자인트랙");
    Node *AIrobotFuse = createNode("AI로봇융합트랙");

    addChild(electronicsDept, electron);
    addChild(electronicsDept, sysSemiconductor);
    addChild(electronicsDept, machineSysDisign);
    addChild(electronicsDept, AIrobotFuse);

    Node *industrialEngin = createNode("산업공학트랙");
    Node *appIndustyDataEngin = createNode("응용산업데이터공학트랙");

    // 창의융합대학
    Node *creativeHumanitiesDept = createNode("상상력인재학부(1학년)");
    Node *generalDept = createNode("학과");

    addChild(sangsangCollege, creativeHumanitiesDept);
    addChild(sangsangCollege, generalDept);

    Node *literCurturalCon = createNode("문학문화콘텐츠학과");
    Node *AIapplication = createNode("AI응용학과");
    Node *ConverSecurity = createNode("융합보안학과");
    Node *futureMobility = createNode("미래모빌리티학과");

    printf("대학 트랙 구조 트리 : \n");
    printTree(university, 0);
    printf("\n\n");

    freeTree(university);
    university = NULL;

    return 0;
}
