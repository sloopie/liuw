#include <stdio.h>
#define MAXE 20
typedef int KeyType;
typedef char InfoType[10];
typedef struct
{	
	KeyType key;
	InfoType data; 
} RecType;

void QuickSort(RecType R[],int s,int t) 
{
	int i=s,j=t,k;
	RecType temp;
	if (s<t) {	
		temp=R[s];     
		while (i!=j) {	
			while (j>i && R[j].key>temp.key) 
				j--;  
			if (i<j) {	
				R[i]=R[j];
				i++;  
			}
			while (i<j && R[i].key<temp.key) 
				i++;			
			if (i<j) {	
				R[j]=R[i];
				j--;  }
		}
		R[i]=temp;
		printf("             ");
		for (k=0;k<10;k++)
			if (k==i)
				printf(" [%d]",R[k].key);
			else
				printf("%4d",R[k].key);
		printf("\n");
		QuickSort(R,s,i-1); 
		QuickSort(R,i+1,t);
	}
}
void main()
{
	int i,k,n=10;
	KeyType a[]={6,8,7,9,0,1,3,2,4,5};
	RecType R[MAXE];
	for (i=0;i<n;i++)
		R[i].key=a[i];
	printf("\n");
	printf("  Init Keywords: ");
	for (k=0;k<n;k++)
		printf("%4d",R[k].key);
	printf("\n");
	QuickSort(R,0,n-1);
	printf("   result:  ");
	for (k=0;k<n;k++)
		printf("%4d",R[k].key);
	printf("\n\n");
}
