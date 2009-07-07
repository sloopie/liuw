/*�ļ���:exp4-4.cpp*/
#include <stdio.h>
#include <string.h>
#define MaxSize 100
typedef struct
{	char ch[MaxSize];
	int len;			/*����*/
} SqString;
extern void StrAssign(SqString &,char []); /*��algo4-1.cpp�ļ���*/
extern void DispStr(SqString);
SqString A,B;			/*ȫ�ִ�*/
SqString EnCrypt(SqString p)
{
	int i=0,j;
	SqString q;
	while (i<p.len) 
	{
		for (j=0;p.ch[i]!=A.ch[j];j++);	
		if (j>=p.len)			/*��A����δ�ҵ�p.ch[i]��ĸ*/
			q.ch[i]=p.ch[i];
		else					/*��A�����ҵ�p.ch[i]��ĸ*/
			q.ch[i]=B.ch[j];
		i++;
	}
	q.len=p.len;
	return q;
}
SqString UnEncrypt(SqString q)
{
	int i=0,j;
	SqString p;
	while (i<q.len) 
	{	
		for (j=0;q.ch[i]!=B.ch[j];j++);
		if (j>=q.len)			/*��B����δ�ҵ�q.ch[i]��ĸ*/
			p.ch[i]=q.ch[i];
		else					/*��B�����ҵ�q.ch[i]��ĸ*/
			p.ch[i]=A.ch[j];
		i++;
	}
	p.len=q.len;
	return p;
}
void main()
{
	SqString p,q;
	int ok=1;
	StrAssign(A,"abcdefghijklmnopqrstuvwxyz");	/*����A��*/
	StrAssign(B,"ngzqtcobmuhelkpdawxfyivrsj");	/*����B��*/
	char str[MaxSize];
	printf("\n");
	printf("����ԭ�Ĵ�:");
	gets(str);									/*��ȡ�û������ԭ�Ĵ�*/
	StrAssign(p,str);							/*����p��*/
	printf("���ܽ�������:\n");
	printf("  ԭ�Ĵ�:");DispStr(p);
	q=EnCrypt(p);								/*p�����ܲ���q��*/
	printf("  ���ܴ�:");DispStr(q);
    	p=UnEncrypt(q);							/*q�����ܲ���p��*/
	printf("  ���ܴ�:");DispStr(p);
	printf("\n");
}
