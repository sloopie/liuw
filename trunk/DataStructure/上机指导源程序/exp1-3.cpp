/*文件名：exp1-3.cpp*/
#include <stdio.h>
#include <string.h>
#define MAX 100					/*字符串的最大长度*/
int func(char s[])
{
	int flag=1;
	int i,j,slen=strlen(s);		/*slen为字符串s的长度*/
	for (i=0,j=slen-1;i<j;i++,j--)
		if (s[i]!=s[j])
		{	
			flag=0;
			break;
		}
	return(flag);
}
void main()
{
	char s[MAX];
	printf("输入一字符串:");
	scanf("%s",s);
	if (func(s)==1)
		printf("%s字符串是回文\n",s);
	else
		printf("%s字符串不是回文\n",s);
}
