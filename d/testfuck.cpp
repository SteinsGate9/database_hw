
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <windows.h>
typedef unsigned int UINT;
void WriteFromStream(char * buf,char * filename,UINT size)
{
    FILE * f = fopen(filename,"wb+");
    if (f)
    {
        fwrite(buf,1,size,f);
        fclose(f);
    }
}

void ReadToStream(char * filename)
{
    FILE * f = fopen(filename,"rb");
    if (f)
    {
        fseek(f,0,SEEK_END);
        int size = ftell(f);
        char * buf = new char[size];
        fseek(f,0,SEEK_SET);
        memset(buf,0,size);
        int nRead = fread(buf,sizeof(char),size,f);
        fclose(f);
        if (nRead > 0)
        {
            //将二进制流打印成16进制字符串
            for(unsigned int i = 0; i < nRead;i++)
            {
                printf("%02X ",(unsigned char)buf[i]);
                if (i%16 == 15)
                {
                    printf("\n");
                }
            }
        }

        char new_file[MAX_PATH] = "";
        sprintf(new_file,"new_%s",filename);
        WriteFromStream(buf,new_file,size);
        WinExec("explorer .",SW_SHOW);
        delete buf;
    }
}
int main()
{
   ReadToStream("t.txt");
   return 0;
}
