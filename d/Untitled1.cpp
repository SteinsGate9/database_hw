#include "stdlib.h"
#include <stdio.h>
void TestMaxMalloc()
{
    long long nMallocNumber = 0;
    // ����һ����Ŀ����ֹ�����쳣��������(���� T530 ) [12/2/2016 ZOSH];
    const long long MAX_NUMBER = 4500;
    // 1<<24 ��1024M [12/2/2016 ZOSH];
    while(malloc(1<<20) && nMallocNumber < MAX_NUMBER)
    {
        nMallocNumber++;
    }

    printf("���������ݿռ䣺%lld M, ��ඥ����Ŀ(x, y, z����):%lld ��\n", nMallocNumber, nMallocNumber * 1024 * (1024 / 12));
}


int main()
{
    TestMaxMalloc();
}

