#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main()
{
    // UTF-8 로케일 설정
    setlocale(LC_ALL, "ko_KR.UTF-8");

    const char *filename = "/Users/gimseohyeon/Documents/ALGO-proj/Project5/Project5/studentList.csv"; //
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        perror("파일 열기 실패");
        return 1;
    }

    printf("파일 열기 성공: %s\n", filename);

    char line[1024];
    while (fgets(line, sizeof(line), file))
    {
        printf("%s", line);
    }

    fclose(file);
    return 0;
}
