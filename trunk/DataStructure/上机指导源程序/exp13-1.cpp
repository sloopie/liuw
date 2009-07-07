/*文件名:exp13_1.cpp*/
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define MaxRec 100  		/*最多的记录个数*/
typedef struct Index 		/*定义索引文件结构*/
{
	char num[8];			/*学号*/
	long offset;			/*主文件中的记录号*/
} Index;
typedef struct sdata     	/*定义主文件结构*/
{
    char num[8];			/*学号*/
	char name[10];			/*姓名*/
	int sex;				/*性别*/
	int age;				/*年龄*/
	char addr[30];			/*地址*/
	char dep[20];			/*系别*/
	char spec[20];			/*专业*/
} Student;
void DelAll()	/*清除主文件和索引文件全部记录*/
{
	FILE *mfile,*idxfile;
	if ((mfile=fopen("main.dat","wb"))==NULL) 
	{
	    printf("  >>不能打开主文件\n");
		return;
	}
	if ((idxfile=fopen("index.dat","wb"))==NULL) 
	{
	    printf("  >>不能建立索引文件\n");
		return;
	}
	fclose(mfile);
	fclose(idxfile);
}
void InsertSort(Index R[],int n) /*对R[0..n-1]按递增有序进行直接插入排序*/
{
	int i,j;
	Index temp;
	for (i=1;i<n;i++) 
	{
		temp=R[i];
		j=i-1; 
		while (j>=0 && strcmp(temp.num,R[j].num)<0) 
		{ 	
			R[j+1]=R[j];	/*将关键字大于R[i].key的记录后移*/
			j--;
		}
		R[j+1]=temp;		/*在j+1处插入R[i]*/
	}
}
void CreatIdxFile()	/*建立索引文件*/
{
	FILE *mfile,*idxfile;
	Index idx[MaxRec];
	Student st;
	int n=0,i;
	if ((mfile=fopen("main.dat","rb"))==NULL) 
	{
	    printf("  >>不能打开主文件\n");
		return;
	}
	if ((idxfile=fopen("index.dat","wb"))==NULL) 
	{
	    printf("  >>不能建立索引文件\n");
		return;
	}
	i=0;
   	while ((fread(&st,sizeof(Student),1,mfile))!=NULL)
	{
		strcpy(idx[i].num,st.num);
		idx[i].offset=++n;
		i++;
	}
	InsertSort(idx,n);	/*对idx数组按no域值排序*/
	rewind(idxfile);
	for (i=0;i<n;i++)
		fwrite(&idx[i],sizeof(Index),1,idxfile);
	fclose(mfile);
	fclose(idxfile);
}
void InputMainFile()	/*添加一个主文件记录*/
{
	FILE *mfile;
	Student st;
	mfile=fopen("main.dat","ab+");
	if (mfile==NULL)
	{
		printf("  >>不能建立主文件\n");
		return;
	}
	printf("  >>学号,姓名,性别,年龄,地址,系别,专业:");
	scanf("%s%s%d%d%s%s%s",st.num,st.name,&st.sex,&st.age,st.addr,st.dep,st.spec);
	if (fwrite(&st,sizeof(Student),1,mfile)!=1)
	{
		printf("  >>写主文件错误\n");
		return;
	}
	fclose(mfile);
}
void OutputMainFile()	/*输出主文件全部记录*/
{
 	FILE *mfile;
	Student st;
	int i=0;
	mfile=fopen("main.dat","rb");
	if (mfile==NULL)
	{
		printf("  >>不能读主文件\n");
		return;
	}
   	while ((fread(&st,sizeof(Student),1,mfile))!=NULL)
	{
		printf("  >>记录号%d:",++i);
		printf("%s %s %d %d %s %s %s\n",st.num,st.name,st.sex,st.age,st.addr,st.dep,st.spec);
	}
	fclose(mfile);
}
void OutputIdxFile()	/*输出索引文件全部记录*/
{
 	FILE *idxfile;
	Index irec;
	int i=0;
	idxfile=fopen("index.dat","rb");
	if (idxfile==NULL)
	{
		printf("  >>不能读索引文件\n");
		return;
	}
   	while ((fread(&irec,sizeof(Index),1,idxfile))!=NULL)
		printf("  >>(学号:记录号) %s:%d\n",irec.num,irec.offset);
	fclose(idxfile);
}
void ReadIndexFile(Index idx[MaxRec],int &len)	/*读索引文件数据存入idx数组中*/
{
	int j;
	FILE *idxfile;
	if ((idxfile=fopen("index.dat","rb"))==NULL) 
	{
	    printf("  >>索引文件不能打开\n");
		return;
	}
	fseek(idxfile,0,2); 
	j=ftell(idxfile);    	/*j求出文件长度*/
	rewind(idxfile);
	len=j/sizeof(Index); 	/*len求出文件中的记录个数*/
	fread(idx,sizeof(Index),len,idxfile);
	fclose(idxfile);
}
int SearchNum(Index idx[],int len,char no[])	/*在索引文件中查找no对应的记录号*/
{
	int mid,low,high,comp;
	low=0;high=len-1;
	while (low<=high)    	/*二分查找*/
	{
		mid=(low+high)/2;
		comp=strcmp(idx[mid].num,no);
		if (comp>0) 
			high=mid-1;
		else if (comp<0) 
			low=mid+1;
		else				/*comp=0的情况*/
			return idx[mid].offset;
	}
	return -1;
}
void FindStudent() /*输出指定学号的记录*/
{
	char no[8];
	FILE *mfile;
	Index idx[MaxRec];
	Student st;
	int i,len;
	mfile=fopen("main.dat","rb+");
	if (mfile==NULL)
	{
		printf("  >>主文件中没有任何记录\n");
		return;
	}
	ReadIndexFile(idx,len);		/*读取索引数组idx*/
	printf("输入学号:");	
	scanf("%s",no);		
	i=SearchNum(idx,len,no);	/*在idx中查找*/
	if (i==-1)
		printf("  >>学号%s不存在\n",no);
	else 
	{
		fseek(mfile,(i-1)*sizeof(Student),SEEK_SET); /*由序号直接跳到主文件的这个记录*/
		fread(&st,sizeof(Student),1,mfile);
		printf("  >>%s %s %d %d %s %s %s\n",st.num,st.name,st.sex,st.age,st.addr,st.dep,st.spec);
	}
	fclose(mfile);
}
void main()
{
	int sel;
	do
	{
		printf("1:输入 2:输出主文件 3:输出索引文件 4:按学号查找 9:全清 0:退出:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 9:
			DelAll();
			break;
		case 1:
			InputMainFile();
			CreatIdxFile();	/*同步修改索引文件*/
			break;
		case 2:
			OutputMainFile();
			break;
		case 3:
			OutputIdxFile();
			break;
		case 4:
			FindStudent();
			break;
		}
	} while (sel!=0);
}
