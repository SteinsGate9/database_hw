/************************些文件包括MiniSQL中BufferManager类里面的函数实现************************************/
/************************作者:陈矫彦  时间：2009年10月*******************************************************/

#include"stdafx.h"
#include "BufferManager.h"
#include "CatalogManager.h"
#include <iostream>
#include <string>

#define UNKNOWN_FILE 8    //定义未知文件类型
#define TABLE_FILE 9      //定义表文件类型
#define INDEX_FILE 10     //定义索引文件类型
using namespace std;
class CatalogManager;

//全局变量外部声明
extern CatalogManager cm;

//构造函数，预先为文件节点和文件块节点分配好空间，初始化变量
BufferManager::BufferManager()
	:totalBlock(0),
	 totalFile(0)
{
	for(int i=0;i<MAX_BLOCK_NUM;i++)
	{
		//分配文件块数据存储空间，并置0
		memset(b[i].address,0,BLOCK_SIZE);
		//为文件节点文件名存储分配空间，并初始化为0
		b[i].fileName = new char[126];
		memset(b[i].fileName, 0, 126);
		//为文件块初始化变量
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
		//为文件节点文件名存储分配空间，并初始化为0
		memset(f[i].fileName,0,126);
		//初始化文件节点变量
		f[i].recordNum=-1;
		f[i].recordLength=-1;
		f[i].usage=-1;
		f[i].blockHead=NULL;
	}
}

//析构函数，把预先分配的文件节点和文件块空间释放
BufferManager::~BufferManager()
{
；
}

//查找文件节点，将找到的或者新分配使用的节点插入文件节点链表
BufferManager::File * BufferManager::getFile(const char * fileName)
{
	string s(fileName);
	BufferManager::Block * bp = NULL;
	BufferManager::File  * fp = NULL;



//找到的话
	for(int i=0; i<MAX_FILE_NUM; i++)
		if(!strcmp(f[i].fileName,fileName))         
			return &f[i];	              

//找不到的话
	if(fp==NULL)
	{
		//如果totalFile<MAX_FILE_NUM,使用空余的文件块
		if (totalFile < MAX_FILE_NUM)
		{
			fp = &f[totalFile];
			totalFile++;
			fp->usage = 0;
			strcpy_s(fp->fileName, 127, fileName);
		}
		//如果totalFile>=MAX_FILE_NUM,替换文件块
		else
		{
			fp = &f[0];
			fp->usage = 0;
			memset(fp->fileName,0,126); //清空原来的文件名
			strcpy_s(fp->fileName,127,fileName);
			for(bp=fp->blockHead;bp!=NULL;bp++)
			{			
				bp->usage=0;
				//将文件下面的块全部写回文件
				if(!flush(bp,1))
				{
					cout<<"Failed to flush block"<<endl;
					return NULL;
				}
			}
			fp->blockHead=NULL;
			//保留文件块在块链表中的位置不变
		}
	}

//从字典文件信息中读入信息，放入文件块中对应的属性中
	int n[3];
	cm.getFileInfo(s,n);
	//如果这个文件块对应的是一个table
	if(n[0]==TABLE_FILE)
	{
		fp->type=TABLE_FILE;
		fp->recordNum=n[1];
		fp->recordLength=n[2];
	}
	//如果这个文件块对应的是一个index
	else if(n[0]==INDEX_FILE)
	{
		fp->type=INDEX_FILE;
		fp->recordLength=-1;          //如果是索引文件，不考虑记录长度和记录数目
		fp->recordNum=-1;
	}
	//如果字典信息中不存在这个文件
	else
	{
		cout<<"File not found"<<endl;
		return NULL;
	}


	return fp;
}


//加一个block文件的后面,requirement=1时要求返回块没读取到数据时为null
BufferManager::Block * BufferManager::getBlock(BufferManager::File * file,int requirement)
{
	BufferManager::File  * fp = NULL;
	BufferManager::Block * bp = NULL;
//先找块
	bp = findReplaceBlock();

//找到的先flush
	if(bp!=NULL)
	{
		bp->fileName = file->fileName;
		if (flush(bp, 1) == 0)
			return NULL;//flush失败意味着快不能用
	}
	else
		return NULL;//没找到可用块也意味着块不能用

//设置参数
	if (file == NULL)//文件都是空的当然块也没法用
	{
		return NULL;
	}
	else
	{

		//如果查找的块是否处在别的链表中，则只要将这个块从原来的链表中分离
		if (bp->nextBlock||bp->nextBlock)
		{
			bp->preBlock->nextBlock = bp->nextBlock;
			bp->nextBlock->preBlock = bp->preBlock;
		}
		//如果查找的块没有被使用
		else
		{
			totalBlock++;
		}
		//设置offsetNum,并插入链表
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
			//当文件读完时,如果是读了0个块，也就是文件本来为空时
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



//查找替换的块，首先在空余的块中查找，如果空余的块用完，直接使用LRU算法来替换块
BufferManager::Block * BufferManager::findReplaceBlock()
{
	BufferManager::Block * LRUBlock;

	//如果还有没有被使用的block，则直接返回totalBlock位置的block
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
	//如果不存在空余的block，使用lru算法进行块替换,new
	else
	{
		long min = (long)INFINITY;
		//遍历
		for(int i=MAX_BLOCK_NUM-1; i>=0; i--)
			if (b[i].lru < min && b[i].lock != 1)
			{
				min = b[i].lru;
				LRUBlock = &b[i];
			}
		//如果块是脏的，则要先将它写回文件
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

//根据给定的文件名，将块写回文件
int BufferManager::flush(BufferManager::Block * b,int Force)
{
	
		//如果原来的块没有脏数据且不强制执行，则不用写文件，真接返回0
		if (b->usage<=0 || !b->dirty && Force==0)
			return 1;
		else
		{
			FILE * fp;
			if (fopen_s(&fp,b->fileName, "rb+"))   //打开文件
			{
				fseek(fp, b->offsetNum*BLOCK_SIZE, 0);
				if (fwrite(b->address, BLOCK_SIZE, 1, fp) != 1)            //如果写入出错，则返回0
				{
					cout << "Fail to flush file " << b->fileName << endl;
					return 0;
				}
				else
				{
					b->dirty = 0;             //将脏数据位重新设为0
					b->usage = 0;             //所有数据清空
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

//将内存中的所有数据写回文件，也就是对每个数据块写回
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

//用来查找一个块中已经被记录使用的字节数目
int BufferManager::findUsage(const char * fileName,const char * address)
{
	string s(fileName);
	int recordLen;
	recordLen=cm.calcuteLenth(s);
	const char * p;
	p=address;
	//以一条记录的长度为步长，对块内容进行遍历
	while(p-address<BLOCK_SIZE)
	{
		const char * tmp;
		tmp=p;
		int i;
		//对每一条记录的每个字节进行遍历，如果发现有非0元素，退出，
		//如果一条记录没有非0元素，则可以为这条记录区是非使用区
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
	//遍历停止点和起始址之差即为块使用字节数
	return p-address;
}

