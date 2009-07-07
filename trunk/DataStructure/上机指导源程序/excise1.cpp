/*文件名:excise1.cpp*/
#include <stdio.h>
#define MaxSize 100
typedef struct node
{
	int no;            	/*职工号*/
	char name[10];    	/*姓名*/
	int depno;         	/*部门号*/
	float salary;       /*工资数*/
	int pno;           	/*职工号指针*/
	int pdepno;         /*部门号指针*/
	int psalary;        /*工资数指针*/
} EmpType;				/*职工类型*/
void DelAll(EmpType emp[],int &n)	/*清除职工文件全部记录*/
{
	FILE *fp;
	if ((fp=fopen("emp.dat","wb"))==NULL) 
	{	
		printf("不能打开职工文件\n");
		return;
	}
	emp[0].pno=emp[0].pdepno=emp[0].psalary=-1;	/*初始化*/
	n=0;
	fclose(fp);
}
void ReadFile(EmpType emp[],int &n) /*读数据文件存入emp数组中*/
{
	FILE *fp;
	long len;
	int i;
	if ((fp=fopen("emp.dat","rb"))==NULL) 
	{	
		n=0;
		return;
	}
	fseek(fp,0,2);				/*文件位置指针移到文件尾*/
	len=ftell(fp);    			/*len求出文件长度*/
	rewind(fp);					/*文件位置指针移到文件首*/
	n=len/sizeof(EmpType); 		/*n求出文件中的记录个数*/
	if (n!=0)
		n--;					/*n不含首元素*/
	else	/*n=0时*/
		emp[0].pno=emp[0].pdepno=emp[0].psalary=-1;	/*初始化*/
	for (i=0;i<=n;i++)
		fread(&emp[i],sizeof(EmpType),1,fp);/*将文件中的数据读到emp中*/
	fclose(fp);
}
void SaveFile(EmpType emp[],int n) /*将emp数组存入数据文件*/
{
	int i;
	FILE *fp;
	if ((fp=fopen("emp.dat","wb"))==NULL) 
	{	
		printf("  >>数据文件不能打开\n");
		return;
	}
	if (n>1)
		for (i=0;i<=n;i++)
			fwrite(&emp[i],sizeof(EmpType),1,fp);
	fclose(fp);
}
void InputEmp(EmpType emp[],int &n)	/*添加一个职工记录*/
{
	printf("  >>输入职工号,姓名,部门号,工资:");
	n++;
	scanf("%d%s%d%f",&emp[n].no,emp[n].name,&emp[n].depno,&emp[n].salary);
	emp[n].pno=emp[n].pdepno=emp[n].psalary=0;
}
void OutputFile(EmpType emp[],int n)	/*输出职工文件全部记录*/
{
	int i;
	if (n<1)
	{
		printf("  >>没有任何记录\n");
		return;
	}
	for (i=1;i<=n;i++)
		printf("  >>%3d %7s %2d %g\n",emp[i].no,emp[i].name,emp[i].depno,emp[i].salary);
}
void Sortno(EmpType emp[],int n) /*采用直接插入法对emp[1..n]按no递增有序排序*/
{
	int i=2,j;
	if (n<1)	/*没有数据记录时返回*/
	{
		printf("  >>没有职工记录,不能按职工号排序\n");
		return;
	}
	emp[0].pno=1;emp[1].pno=-1;	/*建立只有一个记录的有序表*/
	while (i<=n)
	{
		j=0;
		while (emp[j].pno!=-1 && emp[emp[j].pno].no<emp[i].no)
			j=emp[j].pno;		/*找到一个位置j,在其后插入emp[i]*/
		emp[i].pno=emp[j].pno;	/*将emp[i]插入到emp[j]之后*/
		emp[j].pno=i;
		i++;					/*处理下一个记录*/
	}
}
void Dispno(EmpType emp[],int n)	/*按pno指针链输出*/
{
	int i=emp[0].pno;
	if (i==-1)
		printf("  >>尚未按no排序\n");
	while (i!=-1)		/*当未到最后一个结点时输出*/
	{
		printf("  >>%3d %7s %2d %g\n",emp[i].no,emp[i].name,emp[i].depno,emp[i].salary);
		i=emp[i].pno;	/*沿pno链递进*/
	}
}
void Sortdepno(EmpType emp[],int n) /*采用直接插入法对emp[1..n]按depno递增有序排序*/
{
	int i=2,j;
	if (n<1)	/*没有数据记录时返回*/
	{
		printf("  >>没有职工记录,不能按职工号排序\n");
		return;
	}
	emp[0].pdepno=1;emp[1].pdepno=-1;	/*建立只有一个记录的有序表*/
	while (i<=n)
	{
		j=0;
		while (emp[j].pdepno!=-1 && emp[emp[j].pdepno].depno<emp[i].depno)
			j=emp[j].pdepno;			/*找到一个位置j,在其后插入emp[i]*/
		emp[i].pdepno=emp[j].pdepno;	/*将emp[i]插入到emp[j]之后*/
		emp[j].pdepno=i;
		i++;					/*处理下一个记录*/
	}
}
void Dispdepno(EmpType emp[],int n)	/*按pdepno指针链输出*/
{
	int i=emp[0].pdepno;
	if (i==-1)
		printf("  >>尚未按depno排序\n");
	while (i!=-1)		/*当未到最后一个结点时输出*/
	{
		printf("  >>%3d %7s %2d %g\n",emp[i].no,emp[i].name,emp[i].depno,emp[i].salary);
		i=emp[i].pdepno;	/*沿pdepno链递进*/
	}
}
void Sortsalary(EmpType emp[],int n) /*采用直接插入法对emp[1..n]按salary递增有序排序*/
{
	int i=2,j;
	if (n<1)	/*没有数据记录时返回*/
	{
		printf("  >>没有职工记录,不能按职工号排序\n");
		return;
	}
	emp[0].psalary=1;emp[1].psalary=-1;	/*建立只有一个记录的有序表*/
	while (i<=n)
	{
		j=0;
		while (emp[j].psalary!=-1 && emp[emp[j].psalary].salary<emp[i].salary)
			j=emp[j].psalary;		/*找到一个位置j,在其后插入emp[i]*/
		emp[i].psalary=emp[j].psalary;	/*将emp[i]插入到emp[j]之后*/
		emp[j].psalary=i;
		i++;					/*处理下一个记录*/
	}
}
void Dispsalary(EmpType emp[],int n)	/*按psalary指针链输出*/
{
	int i=emp[0].psalary;
	if (i==-1)
		printf("  >>尚未按salary排序\n");
	while (i!=-1)		/*当未到最后一个结点时输出*/
	{
		printf("  >>%3d %7s %2d %g\n",emp[i].no,emp[i].name,emp[i].depno,emp[i].salary);
		i=emp[i].psalary;	/*沿pno链递进*/
	}
}
void main()
{
	EmpType emp[MaxSize];
	int sel,n;
	ReadFile(emp,n);
	do
	{	
		printf("1:输入 2:输出 3:按no排序 4:按no输出 5:按depno排序 6:按depno输出\n");
		printf("7:按salary排序 8.按salary输出 9:全清 0:存储退出  请选择:");
		scanf("%d",&sel);
		switch(sel)
		{
		case 9:
			DelAll(emp,n);
			break;
		case 1:
			InputEmp(emp,n);
			break;
		case 2:
			OutputFile(emp,n);
			break;
		case 3:
			Sortno(emp,n);
			break;
		case 4:
			Dispno(emp,n);
			break;
		case 5:
			Sortdepno(emp,n);
			break;
		case 6:
			Dispdepno(emp,n);
			break;
		case 7:
			Sortsalary(emp,n);
			break;
		case 8:
			Dispsalary(emp,n);
			break;
		case 0:
			SaveFile(emp,n);
			break;
		}
	} while (sel!=0);
}
