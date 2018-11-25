#include "stdlib.h"
#include <stdio.h>
void TestMaxMalloc()
{
    long long nMallocNumber = 0;
    // 限制一个数目，防止程序异常不能跳出(联想 T530 ) [12/2/2016 ZOSH];
    const long long MAX_NUMBER = 4500;
    // 1<<24 是1024M [12/2/2016 ZOSH];
    while(malloc(1<<20) && nMallocNumber < MAX_NUMBER)
    {
        nMallocNumber++;
    }

    printf("可申请内容空间：%lld M, 最多顶点数目(x, y, z分量):%lld 个\n", nMallocNumber, nMallocNumber * 1024 * (1024 / 12));
}


int main()
{
    TestMaxMalloc();
}

