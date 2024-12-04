#include <unistd.h>
#include <stdio.h>

int main()
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
    {
        printf("현재 작업 디렉토리: %s\n", cwd);
    }
    else
    {
        perror("getcwd() 오류");
    }
    return 0;
}
