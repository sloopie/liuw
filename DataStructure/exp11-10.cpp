#include <stdio.h>
#include <malloc.h>
#include <string.h>
#define MaxLen 9
#define Radix  27
typedef char String[MaxLen+1];

typedef struct node
{	String word;
	struct node *next;
} LinkNode;

void DispWord(String R[], int n);
void PreProcess(String R[],int n);
void EndProcess(String R[],int n);
void Distribute(String R[],LinkNode *head[],LinkNode *tail[],int j,int n);
void Collect(String R[],LinkNode *head[]);
void RadixSort(String R[],int n);

void main()
{
	int n=6;
	String R[]={"hello","no","hi all","hhkk","sorry","nnk"};
	printf("step 1:\n");DispWord(R,n);
	PreProcess(R,n);
	printf("step 2:\n");DispWord(R,n);
	RadixSort(R,n);
	printf("step 3:\n");DispWord(R,n);
	EndProcess(R,n);
	printf("result:\n");DispWord(R,n);
	printf("\n");
}

void DispWord(String R[],int n)	
{
	int i;
	printf("  ");
	for (i=0;i<n;i++)
		printf("[%s] ",R[i]);
	printf("\n");
}

void PreProcess(String R[],int n)	
{
	int i,j;
	for (i=0;i<n;i++)
	{	if (strlen(R[i])<MaxLen)
		{	for (j=strlen(R[i]);j<MaxLen;j++)
				R[i][j]=' ';
			R[i][j]='\0';
		}
	}
}

void EndProcess(String R[],int n)		
{
	int i,j;
	for (i=0;i<n;i++)
	{	for (j=MaxLen-1;R[i][j]==' ';j--);
		R[i][j+1]='\0';
	}
}

void Distribute(String R[],LinkNode *head[],LinkNode *tail[],int j,int n)  
{
	int i,k;
	LinkNode *p;
	for (i=0;i<n;i++)			
	{	if (R[i][j]==' ')	
			k=0;
		else
			k=R[i][j]-'a'+1;
		p=(LinkNode *)malloc(sizeof(LinkNode));	
		strcpy(p->word,R[i]);
		p->next=NULL;
		if (head[k]==NULL)
		{	head[k]=p;
			tail[k]=p;
		}
		else
		{	tail[k]->next=p;
			tail[k]=p;
		}
	}
}

void Collect(String R[],LinkNode *head[])  
{
	int k=0,i;
	LinkNode *p;
	for (i=0;i<Radix;i++)			
		for (p=head[i];p!=NULL;p=p->next)
			strcpy(R[k++],p->word);
}

void RadixSort(String R[],int n)	
{
	LinkNode *head[Radix],*tail[Radix];	
    	int i,j;
	for (i=MaxLen-1;i>=0;i--)				
	{	for (j=0;j<Radix;j++)
			head[j]=tail[j]=NULL;		
		Distribute(R,head,tail,i,n);	
		Collect(R,head);	
	}
}

