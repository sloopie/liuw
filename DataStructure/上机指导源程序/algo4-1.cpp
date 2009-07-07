/*�ļ���:algo4-1.cpp*/
#include <stdio.h>
#define MaxSize 100    		/*�����ַ�����*/
typedef struct
{   char ch[MaxSize];     	/*���������MaxSize���ַ��Ŀռ�*/
    int len;             	/*��ǵ�ǰʵ�ʴ���*/
} SqString;
void StrAssign(SqString &str,char cstr[])	/*strΪ�����Ͳ���*/
{
    int i;
    for (i=0;cstr[i]!='\0';i++)
         str.ch[i]=cstr[i];
    str.len=i;
}
void StrCopy(SqString &s,SqString t)		/*sΪ�����Ͳ���*/
{
    int i;
    for (i=0;i<t.len;i++)
        s.ch[i]=t.ch[i];
    s.len=t.len;
}
int StrEqual(SqString s,SqString t)
{
    int same=1,i;
    if (s.len!=t.len)      		/*���Ȳ����ʱ����0*/
        same=0;
    else 
	{
        for (i=0;i<s.len;i++)
            if (s.ch[i]!=t.ch[i])	/*��һ����Ӧ�ַ�����ͬʱ����0*/
                same=0;
    }
    return same;
}
int StrLength(SqString s)
{
    return s.len;
}
SqString Concat(SqString s,SqString t)
{
    SqString str;
    int i;
    str.len=s.len+t.len;
    for (i=0;i<s.len;i++)   	/*��s.ch[0]��s.ch[s.len-1]���Ƶ�str*/
        str.ch[i]=s.ch[i]; 
    for (i=0;i<t.len;i++)   	/*��t.ch[0]��t.ch[t.len-1]���Ƶ�str*/
        str.ch[s.len+i]=t.ch[i];
    return str;
}
SqString SubStr(SqString s,int i,int j)
{
    SqString str;
    int k;
    str.len=0;
    if (i<=0 || i>s.len || j<0 || i+j-1>s.len)
	{
		printf("��������ȷ\n");
        return str;          			/*��������ȷʱ���ؿմ�*/
	}
    for (k=i-1;k<i+j-1;k++)  			/*��s.ch[i]��s.ch[i+j]���Ƶ�str*/
        str.ch[k-i+1]=s.ch[k];
    str.len=j;
    return str;
} 
SqString InsStr(SqString s1,int i,SqString s2)
{
    int j;
    SqString str;
    str.len=0;
    if (i<=0 || i>s1.len+1)      		/*��������ȷʱ���ؿմ�*/
	{
		printf("��������ȷ\n");
        return s1;
	}
    for (j=0;j<i-1;j++)          		/*��s1.ch[0]��s1.ch[i-2]���Ƶ�str*/
        str.ch[j]=s1.ch[j];
    for (j=0;j<s2.len;j++)     			/*��s2.ch[0]��s2.ch[s2.len-1]���Ƶ�str*/
        str.ch[i+j-1]=s2.ch[j];
    for (j=i-1;j<s1.len;j++)     		/*��s1.ch[i-1]��s.ch[s1.len-1]���Ƶ�str*/
        str.ch[s2.len+j]=s1.ch[j];
    str.len=s1.len+s2.len;
    return str;
}
SqString DelStr(SqString s,int i,int j)
{
    int k;
    SqString str;
    str.len=0;
    if (i<=0 || i>s.len || i+j>s.len+1) 		/*��������ȷʱ���ؿմ�*/
	{
		printf("��������ȷ\n");
        return str;
	}
    for (k=0;k<i-1;k++)       /*��s.ch[0]��s.ch[i-2]���Ƶ�str*/
        str.ch[k]=s.ch[k];
    for (k=i+j-1;k<s.len;k++)/*��s.ch[i+j-1]��ch[s.len-1]���Ƶ�str*/
        str.ch[k-j]=s.ch[k];
    str.len=s.len-j;
    return str;
}
SqString RepStr(SqString s,int i,int j,SqString t)
{
    int k;
    SqString str;
    str.len=0;
    if (i<=0 || i>s.len || i+j-1>s.len) /*��������ȷʱ���ؿմ�*/
	{
		printf("��������ȷ\n");
        return str;
	}
    for (k=0;k<i-1;k++)				/*��s.ch[0]��s.ch[i-2]���Ƶ�str*/
        str.ch[k]=s.ch[k];
    for (k=0;k<t.len;k++)      		/*��t.ch[0]��t.ch[t.len-1]���Ƶ�str*/
         str.ch[i+k-1]=t.ch[k];  
    for (k=i+j-1;k<s.len;k++)		/*��s.ch[i+j-1]��ch[s.len-1]���Ƶ�str*/
        str.ch[t.len+k-j]=s.ch[k];
    str.len=s.len-j+t.len;
    return str;
}
void DispStr(SqString str)
{
    int i;
    if (str.len>0)
	{
        for (i=0;i<str.len;i++)
            printf("%c",str.ch[i]);
		printf("\n");
    }
}
