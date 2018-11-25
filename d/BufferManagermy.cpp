/************************Щ�ļ�����MiniSQL��BufferManager������ĺ���ʵ��************************************/
/************************����:�½���  ʱ�䣺2009��10��*******************************************************/

#include"stdafx.h"
#include "BufferManager.h"
#include "CatalogManager.h"
#include <iostream>
#include <string>

#define UNKNOWN_FILE 8    //����δ֪�ļ�����
#define TABLE_FILE 9      //������ļ�����
#define INDEX_FILE 10     //���������ļ�����
using namespace std;
class CatalogManager;

//ȫ�ֱ����ⲿ����
extern CatalogManager cm;

//���캯����Ԥ��Ϊ�ļ��ڵ���ļ���ڵ����ÿռ䣬��ʼ������
BufferManager::BufferManager()
	:totalBlock(0),
	 totalFile(0)
{
	for(int i=0;i<MAX_BLOCK_NUM;i++)
	{
		//�����ļ������ݴ洢�ռ䣬����0
		memset(b[i].address,0,BLOCK_SIZE);
		//Ϊ�ļ��ڵ��ļ����洢����ռ䣬����ʼ��Ϊ0
		b[i].fileName = new char[126];
		memset(b[i].fileName, 0, 126);
		//Ϊ�ļ����ʼ������
		b[i].offsetNum=-1;
		b[i].dirty=0;
		b[i].lock=0;
		b[i].lru=0;
		b[i].usage=-1;
		b[i].nextBlock=NULL;
		b[i].preBlock=NULL;
	}
	for(int i=0;i<MAX_FILE_NUM;i++)
	{
		f[i].type=-1;
		//Ϊ�ļ��ڵ��ļ����洢����ռ䣬����ʼ��Ϊ0
		memset(f[i].fileName,0,126);
		//��ʼ���ļ��ڵ����
		f[i].recordNum=-1;
		f[i].recordLength=-1;
		f[i].usage=-1;
		f[i].blockHead=NULL;
	}
}

//������������Ԥ�ȷ�����ļ��ڵ���ļ���ռ��ͷ�
BufferManager::~BufferManager()
{
��
}

//�����ļ��ڵ㣬���ҵ��Ļ����·���ʹ�õĽڵ�����ļ��ڵ�����
BufferManager::File * BufferManager::getFile(const char * fileName)
{
	string s(fileName);
	BufferManager::Block * bp = NULL;
	BufferManager::File  * fp = NULL;



//�ҵ��Ļ�
	for(int i=0; i<MAX_FILE_NUM; i++)
		if(!strcmp(f[i].fileName,fileName))         
			return &f[i];	              

//�Ҳ����Ļ�
	if(fp==NULL)
	{
		//���totalFile<MAX_FILE_NUM,ʹ�ÿ�����ļ���
		if (totalFile < MAX_FILE_NUM)
		{
			fp = &f[totalFile];
			totalFile++;
			fp->usage = 0;
			strcpy_s(fp->fileName, 127, fileName);
		}
		//���totalFile>=MAX_FILE_NUM,�滻�ļ���
		else
		{
			fp = &f[0];
			fp->usage = 0;
			memset(fp->fileName,0,126); //���ԭ�����ļ���
			strcpy_s(fp->fileName,127,fileName);
			for(bp=fp->blockHead;bp!=NULL;bp++)
			{			
				bp->usage=0;
				//���ļ�����Ŀ�ȫ��д���ļ�
				if(!flush(bp,1))
				{
					cout<<"Failed to flush block"<<endl;
					return NULL;
				}
			}
			fp->blockHead=NULL;
			//�����ļ����ڿ������е�λ�ò���
		}
	}

//���ֵ��ļ���Ϣ�ж�����Ϣ�������ļ����ж�Ӧ��������
	int n[3];
	cm.getFileInfo(s,n);
	//�������ļ����Ӧ����һ��table
	if(n[0]==TABLE_FILE)
	{
		fp->type=TABLE_FILE;
		fp->recordNum=n[1];
		fp->recordLength=n[2];
	}
	//�������ļ����Ӧ����һ��index
	else if(n[0]==INDEX_FILE)
	{
		fp->type=INDEX_FILE;
		fp->recordLength=-1;          //����������ļ��������Ǽ�¼���Ⱥͼ�¼��Ŀ
		fp->recordNum=-1;
	}
	//����ֵ���Ϣ�в���������ļ�
	else
	{
		cout<<"File not found"<<endl;
		return NULL;
	}


	return fp;
}


//��һ��block�ļ��ĺ���,requirement=1ʱҪ�󷵻ؿ�û��ȡ������ʱΪnull
BufferManager::Block * BufferManager::getBlock(BufferManager::File * file,int requirement)
{
	BufferManager::File  * fp = NULL;
	BufferManager::Block * bp = NULL;
//���ҿ�
	bp = findReplaceBlock();

//�ҵ�����flush
	if(bp!=NULL)
	{
		bp->fileName = file->fileName;
		if (flush(bp, 1) == 0)
			return NULL;//flushʧ����ζ�ſ첻����
	}
	else
		return NULL;//û�ҵ����ÿ�Ҳ��ζ�ſ鲻����

//���ò���
	if (file == NULL)//�ļ����ǿյĵ�Ȼ��Ҳû����
	{
		return NULL;
	}
	else
	{

		//������ҵĿ��Ƿ��ڱ�������У���ֻҪ��������ԭ���������з���
		if (bp->nextBlock||bp->nextBlock)
		{
			bp->preBlock->nextBlock = bp->nextBlock;
			bp->nextBlock->preBlock = bp->preBlock;
		}
		//������ҵĿ�û�б�ʹ��
		else
		{
			totalBlock++;
		}
		//����offsetNum,����������
		BufferManager::Block * temp;
		if (file->blockHead)
		{
			for (temp = file->blockHead; temp->nextBlock; temp = temp->nextBlock)
			{
				;
			}
			bp->offsetNum = temp->offsetNum + 1;
			temp->nextBlock = bp;
			bp->preBlock = temp;
			bp->nextBlock = NULL;
		}
		else
		{
			bp->offsetNum = 0;
			file->blockHead = bp;
			bp->nextBlock = NULL;
		}
		FILE *tempfile;
		if (!fopen_s(&tempfile, file->fileName, "rb+"))
		{
			fseek(tempfile, bp->offsetNum*BLOCK_SIZE, 0);
			//���ļ�����ʱ,����Ƕ���0���飬Ҳ�����ļ�����Ϊ��ʱ
			if(!fread(bp->address, 1, BLOCK_SIZE, tempfile))
			{
				fclose(tempfile);
				if (bp->preBlock)
				{
					bp->preBlock->nextBlock = bp->nextBlock;
				}
				if (requirement)
					return NULL;
				else
					return bp;
			}
			fclose(tempfile);
		}
		else
		{
			cout << "Fail to open the file " << file->fileName << endl;
			return NULL;
		}
		bp->usage = findUsage(bp->fileName,bp->address);
		bp->dirty = 0;
		bp->lock = 0;
		bp->lru = 0;
	}
	return bp;
}



//�����滻�Ŀ飬�����ڿ���Ŀ��в��ң��������Ŀ����ֱ꣬��ʹ��LRU�㷨���滻��
BufferManager::Block * BufferManager::findReplaceBlock()
{
	BufferManager::Block * LRUBlock;

	//�������û�б�ʹ�õ�block����ֱ�ӷ���totalBlockλ�õ�block
	if (totalBlock == 0)//new
	{
		b[0].usage = 0;
		return &b[totalBlock];
	}
	else if(totalBlock<MAX_BLOCK_NUM)
	{
		if (b[totalBlock - 1].usage != 4096)
			LRUBlock = &b[totalBlock - 1];
		else//new
		{
			b[totalBlock].usage = 0;
			LRUBlock = &b[totalBlock];
		}
		return LRUBlock;
	}
	//��������ڿ����block��ʹ��lru�㷨���п��滻,new
	else
	{
		long min = (long)INFINITY;
		//����
		for(int i=MAX_BLOCK_NUM-1; i>=0; i--)
			if (b[i].lru < min && b[i].lock != 1)
			{
				min = b[i].lru;
				LRUBlock = &b[i];
			}
		//���������ģ���Ҫ�Ƚ���д���ļ�
			if (!flush(LRUBlock, 0))
			{
				cout << "Fail to flush the block" << endl;
				return NULL;
			}
			else
			{
				LRUBlock->usage = 0;
			}
	}
	return LRUBlock;	
}

//���ݸ������ļ���������д���ļ�
int BufferManager::flush(BufferManager::Block * b,int Force)
{
	
		//���ԭ���Ŀ�û���������Ҳ�ǿ��ִ�У�����д�ļ�����ӷ���0
		if (b->usage<=0 || !b->dirty && Force==0)
			return 1;
		else
		{
			FILE * fp;
			if (fopen_s(&fp,b->fileName, "rb+"))   //���ļ�
			{
				fseek(fp, b->offsetNum*BLOCK_SIZE, 0);
				if (fwrite(b->address, BLOCK_SIZE, 1, fp) != 1)            //���д������򷵻�0
				{
					cout << "Fail to flush file " << b->fileName << endl;
					return 0;
				}
				else
				{
					b->dirty = 0;             //��������λ������Ϊ0
					b->usage = 0;             //�����������
					memset(b->address, 0, BLOCK_SIZE);
					return 1;
				}
			}
			else
			{
				cout << "Fail to open file " << b->fileName << endl;
				return 0;
			}
			
		}
}

//���ڴ��е���������д���ļ���Ҳ���Ƕ�ÿ�����ݿ�д��
int BufferManager::flushAll()
{
	BufferManager::Block * bp;
	for(int i=0; i<MAX_FILE_NUM; i++)
	{
		string s(f[i].fileName);
		if(cm.findFile(s)!=UNKNOWN_FILE)
		{
			for(bp=f[i].blockHead;bp!=NULL;bp=bp->nextBlock)
				if(flush(bp,0)==0)
					return 0;
		}

	}
	return 1;
}

//��������һ�������Ѿ�����¼ʹ�õ��ֽ���Ŀ
int BufferManager::findUsage(const char * fileName,const char * address)
{
	string s(fileName);
	int recordLen;
	recordLen=cm.calcuteLenth(s);
	const char * p;
	p=address;
	//��һ����¼�ĳ���Ϊ�������Կ����ݽ��б���
	while(p-address<BLOCK_SIZE)
	{
		const char * tmp;
		tmp=p;
		int i;
		//��ÿһ����¼��ÿ���ֽڽ��б�������������з�0Ԫ�أ��˳���
		//���һ����¼û�з�0Ԫ�أ������Ϊ������¼���Ƿ�ʹ����
		for(i=0;i<recordLen;i++)
		{
			if(*tmp!=0)
				break;
			tmp++;
		}
		if(i==recordLen)
				break;

		p=p+recordLen;
	}
	//����ֹͣ�����ʼַ֮�Ϊ��ʹ���ֽ���
	return p-address;
}

