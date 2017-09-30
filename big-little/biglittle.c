#include <stdio.h>

// 检测系统大端小端

int main(int argc, char *argv[])
{
    int p = 0x1234;
    char *c = (char *) &p;
    if (*c == 0x34 && *(c+1) == 0x12) {
        printf("little endian\n");
    }

    return 0;
}
