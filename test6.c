#include "stdio.h"
#include "iostream"
#include "stdlib.h"
#include "time.h"
const int size=1000;
typedef long RecType;
typedef struct
{	RecType rec[size+1];
	int  n;
} SqTable;

//顺序查找
int SeqSearch(SqTable R,RecType k,int &i,int &j)
{
	for ( i = 0,j = 1; i < R.n; i++,j++){
		if (R.rec[i] == k)
		{
			return i+1;
		}
	}
	i = 0;
	return i;
}
void print(SqTable R,int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d->",R.rec[i]);
	}

}

//排序
void sort(SqTable &R,int n)
{
	int t;
	for (int i = n-1; i >= 0 ; i--)
	{
		for (int j = 0; j <= i; j++)
		{
			if (R.rec[j]>R.rec[j+1])
			{
				t=R.rec[j];
				R.rec[j]=R.rec[j+1];
				R.rec[j+1]=t;
			}

		}

	}

}

//折半查找
int BinSearch(SqTable R,RecType k,int &j)
{
	int low,high,mid;
	low = 0;
	high=R.n-1;
	j=0;
	while (low<=high)
	{
		mid = (low+high)/2;
		j++;
		if (k == R.rec[mid])
		{
			return mid;
		}
		else if (k<R.rec[mid])
		{
			high=mid-1;
		}
		else{
			low=mid+1;
		}
		j++;
	}
	return 0;

}
int main()
{
	SqTable R,A;
	RecType x;
	int i,j,n;
	int k;
	do
	{
	printf("\n\n\n\n");
	printf("\t\t         查找子系统\n");
	printf("\t\t*****************************\n");
	printf("\t\t*       1----产生数据　 　  *\n");
	printf("\t\t*       2----顺序查找　　　 *\n");
	printf("\t\t*       3----二分查找　　　 *\n");
	printf("\t\t*       4----打印数据　　　 *\n");
	printf("\t\t*       0----返　　回　　 　*\n");
	printf("\t\t*****************************\n");
	printf("\t\t   请选择菜单项(0－4)：");
	scanf("%d",&k);
	switch(k)
	{
		case 1://随机产生数据
			printf("请输入要产生随机数的个数(n<=%d)n= ",size);
			scanf("%d",&n);
			srand((unsigned)time( NULL ));
			for (i=1;i<=n;i++)
				A.rec[i]=R.rec[i]=rand();
			A.n=R.n=n;
			break;
		case 2://顺序查找
			printf("请输入要查找的关键字：");
			scanf("%ld",&x);
			SeqSearch(R,x,i,j);
			if (i==0)	printf("没有此数据!!!");
			else	printf("在 %d 个下标，第 %d 次找到。",i,j);
			break;
		case 3://二分查找
			sort(A,n);
			print(A,n);
			printf("\n请输入要查找的关键字：");
			scanf("%ld",&x);
			j=0;
			i=BinSearch(A,x,j);
			if (i==0)	printf("没有此数据!!!");
			else	printf("在 %d 个下标，第 %d 次找到。",i,j);
			    break;
	    case 4:
			print(A,n);
	}
	}while (k!=0);
}
