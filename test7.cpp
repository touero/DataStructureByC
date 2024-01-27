#include  "iostream"
#include  "stdio.h"
#include  "stdlib.h"
#include  "iomanip"
#include  "time.h"
const   int  N=50000;
#define  ElemType  int
void insertsort(ElemType R[],int n)      //直接插入排序
{
    int t,j;
    for (int i = 1; i < n; i++)
    {
        t=R[i];
        j=i-1;
        while (t<R[j]&&j>=0)
        {
            R[j+1]=R[j];
            j--;
        }
        R[j+1]=t;
    }

}

void BinaryInsertSort(ElemType R[],int n)    //二分插入排序
{
    int start;
        int end;
        int temp=0;
        int mid,j;

        for(int i=1;i<n;i++)
        {
            start=0;
            end=i-1;
            temp=R[i];

            while(start<=end)
            {
                mid=(start+end)/2;
                if (temp<R[mid])
                {
                    end=mid-1;
                }
                else
                {
                    start=mid+1;
                }
            }
            for( j = i-1;j >= start;j-- )
            {
                R[j+1] = R[j];
            }
            R[start] = temp;
        }
}

void Bubblesort(ElemType R[],int n)          //冒泡排序
{
    int t;
	for (int i = n-1; i > 0 ; i--)
	{
		for (int j = 0; j < i; j++)
		{
			if (R[j]>R[j+1])
			{
				t=R[j];
				R[j]=R[j+1];
				R[j+1]=t;
			}

		}

	}
}

void   selectsort(ElemType R[],int n)      //直接选择排序
{
    int min,t;
    for (int i = 0; i < n; i++)
    {
        min = i;
        for (int j = i+1; j < n; j++)
        {
            if (R[j]<R[min])
            {
                min=j;
            }
        }
            if (min!=i)
            {
                t=R[i];
                R[i]=R[min];
                R[min]=t;
            }


    }

}

void print(ElemType R[],int n)            //打印数组
{
   for(int i=0;i<n;i++)
   {  if (i%10==0)  printf("\n");
      printf("%7d",R[i]);
   }
   printf("\n");
}
int main()
{   int sele;
    ElemType R[N],T[N];
    int n,k;
    long  t1,t2;
    double  tt;
    srand(1);
    for(int i=0;i<N;i++)  T[i]=rand();     //产生10000个随机数
    print(T,N);
	printf("\n\n\n\n");
	printf("\t\t       排序 子系统\n");
	printf("\t\t*****************************\n");
	printf("\t\t*     1----直接插入排序　   *\n");
	printf("\t\t*     2----二分插入排序　　 *\n");
	printf("\t\t*     3----冒 泡 排 序 　　 *\n");
	printf("\t\t*     4----直接选择排序　　 *\n");
	printf("\t\t*     0----返　　回　　   　*\n");
	printf("\t\t*****************************\n");
    do
    {  	printf("\t\t   请选择菜单项(0－4)：");
		scanf("%d",&k);
	   	for(int i=0;i<N;i++)  R[i]=T[i];
        t1=time(NULL);
        switch(k)
		{	case 1:
			insertsort(R,N);
			t2=time(NULL);
			tt=difftime(t2,t1);
			printf("直接插入排序的时间为：%lf\n", tt);
	        break;
		case 2:
			BinaryInsertSort(R,N);
			t2=time(NULL);
			tt=difftime(t2,t1);
 			printf("二分插入排序的时间为：%lf\n", tt);
			break;
		case 3:
			Bubblesort(R,N);
			t2=time(NULL);
			tt=difftime(t2,t1);
 			printf("冒泡排序的时间为：%lf\n", tt);
			break;
		case 4:
			selectsort(R,N);
			t2=time(NULL);tt=difftime(t2,t1);
 			printf("直接选择排序的时间为：%lf\n", tt);
       }
	}while(k);
}
