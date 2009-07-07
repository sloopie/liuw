/*文件名:exp10-2.cpp*/
#include <stdio.h>
#define MAXL 100					/*定义表中最多记录个数*/
typedef int KeyType;
typedef char InfoType[10];
typedef struct 
{	
	KeyType key;                	/*KeyType为关键字的数据类型*/
    InfoType data;              	/*其他数据*/
} NodeType;
typedef NodeType SeqList[MAXL];		/*顺序表类型*/
int BinSearch(SeqList R,int n,KeyType k)  /*二分查找算法*/
{
	int low=0,high=n-1,mid,count=0;
	while (low<=high) 
	{	
		mid=(low+high)/2;
		printf("第%d次查找:在[%d,%d]中查找到元素R[%d]:%d\n",++count,low,high,mid,R[mid].key);
		if (R[mid].key==k)   	/*查找成功返回*/
			return mid;
		if (R[mid].key>k)     	/*继续在R[low..mid-1]中查找*/
			high=mid-1;
		else
			low=mid+1;       	/*继续在R[mid+1..high]中查找*/
	}
	return -1;
}
void main()
{
	SeqList R;
	KeyType k=9;
	int a[]={1,2,3,4,5,6,7,8,9,10},i,n=10;
	for (i=0;i<n;i++)				/*建立顺序表*/
		R[i].key=a[i];
	printf("\n");
	if ((i=BinSearch(R,n,k))!=-1)
		printf("元素%d的位置是%d\n",k,i);
	else
		printf("元素%d不在表中\n",k);
	printf("\n");
}
