/*文件名:exp4-1.cpp*/
#include <stdio.h>
#define MaxSize 100 
typedef struct
{   char ch[MaxSize]; 
    int len;
} SqString;
extern void StrAssign(SqString &str,char cstr[]);
extern void StrCopy(SqString &s,SqString t);
extern int StrEqual(SqString s,SqString t);
extern int StrLength(SqString s);
extern SqString Concat(SqString s,SqString t);
extern SqString SubStr(SqString s,int i,int j);
extern SqString InsStr(SqString s1,int i,SqString s2);
extern SqString DelStr(SqString s,int i,int j);
extern SqString RepStr(SqString s,int i,int j,SqString t);
extern void DispStr(SqString str);
void main()
{
	SqString s,s1,s2,s3,s4;
	printf("(1)建立串s和串s1\n");
	StrAssign(s,"abcdefghefghijklmn");
	StrAssign(s1,"xyz");
	printf("(2)输出串s:");DispStr(s);
	printf("(3)串s的长度:%d\n",StrLength(s));
	printf("(4)在串s的第9个字符位置插入串s1而产生串s2\n");
	s2=InsStr(s,9,s1);
	printf("(5)输出串s2:");DispStr(s2);
	printf("(6)删除串s第2个字符开始的5个字符而产生串s2\n");
	s2=DelStr(s,2,3);
	printf("(7)输出串s2:");DispStr(s2);
	printf("(8)将串s第2个字符开始的5个字符替换成串s1而产生串s2\n");
	s2=RepStr(s,2,5,s1);
	printf("(9)输出串s2:");DispStr(s2);
	printf("(10)提取串s的第2个字符开始的10个字符而产生串s3\n");
	s3=SubStr(s,2,10);
	printf("(11)输出串s3:");DispStr(s3);
	printf("(12)将串s1和串s2连接起来而产生串s4\n");
	s4=Concat(s1,s2);
	printf("(13)输出串s4:");DispStr(s4);
}