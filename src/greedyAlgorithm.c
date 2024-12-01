#include <stdio.h>
#include <stdlib.h>

/*그리디 알고리즘
 O(t log t) */

// 회의 정보를 저장할 구조체
typedef struct
{
    int start; // 시작 시간
    int end;   // 종료 시간
} Meeting;

// 회의를 시작 시간 기준으로 정렬하는 비교 함수
int compare(const void *a, const void *b)
{
    Meeting *m1 = (Meeting *)a;
    Meeting *m2 = (Meeting *)b;

    // 시작 시간이 다르면 시작 시간 기준으로 정렬
    if (m1->start != m2->start)
    {
        return m1->start - m2->start;
    }
    // 시작 시간이 같으면 종료 시간 기준으로 정렬
    return m1->end - m2->end;
}

int main()
{
    int t;
    scanf("%d", &t); // 회의의 수 입력받기

    // 회의 정보를 저장할 배열 동적 할당
    Meeting *meetings = (Meeting *)malloc(t * sizeof(Meeting));
    if (!meetings)
    {
        perror("Memory allocation failed");
        return 1;
    }

    // 회의 정보 입력받기
    for (int i = 0; i < t; i++)
    {
        scanf("%d %d", &meetings[i].start, &meetings[i].end);
    }

    // 회의들을 시작 시간과 종료 시간 기준으로 정렬
    qsort(meetings, t, sizeof(Meeting), compare);

    // 이전 회의의 종료 시간을 추적
    int last_end_time = -1;
    int count = 0; // 선택된 회의의 수

    // 회의들을 하나씩 확인
    for (int i = 0; i < t; i++)
    {
        // 현재 회의의 시작 시간이 이전 회의의 종료 시간보다 크거나 같다면 선택
        if (meetings[i].start >= last_end_time)
        {
            count++;                         // 회의가 선택되었으므로 카운트 증가
            last_end_time = meetings[i].end; // 마지막 종료 시간을 업데이트
        }
    }

    // 결과 출력
    printf("%d\n", count);

    // 메모리 해제
    free(meetings);

    return 0;
}
