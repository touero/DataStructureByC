#include "stdio.h"
#include "malloc.h"
#define  MaxVertexNum 20     //定义图的最大顶点数
#define  MaxEdgeNum  50      //定义图的最大边数
#define  MaxValue  1000      //定义MaxValue为全局整型常量，作为无穷大
typedef  int  VertexType;    //定义图中顶点数据的类型VertexType为整型
typedef  VertexType  vexlist[MaxVertexNum];  //为存储顶点信息的数组类型
typedef  int adjmatrix[MaxVertexNum][MaxVertexNum]; //为存储邻接矩阵的数组类型
int n;    //实际的顶点个数
int e;    //实际的边个数
int visited [ MaxVertexNum ];  //全局数组标记置1表示已经访问，0为未访问
/* 建立图的邻接矩阵
通过从键盘上输入n个顶点信息和e条无向带权边的信息，建立邻接矩阵GA*/
void  Create(vexlist GV,adjmatrix GA,int n,int e)
{
	int  i , j, k, w;
    for (i=1;  i<=n;  i++)	 GV[i]=i;
	for (i=1;  i<=n;  i++)          /*初始化邻接矩阵数组*/
	for (j=1;  j<=n;  j++)
		GA[ i ][ j ]=MaxValue;
	printf ("输入 %d 条无向带权边\n", e);     /*建立邻接矩阵数组*/
	for (k=1; k<=e;  k++)
	{
		printf("输入第 %d 条边的两端序号及权值(i j W): ",k);
		scanf ("%d%d%d", &i, &j, &w);
		GA[i][j]=GA[j][i]=w;   //置数组中相应对称元素的值为w
	}
}

//邻接矩阵的深度遍历
void dfs(vexlist GV,adjmatrix GA,int i)   // 从顶点i出发的深度遍历
{   int j;
    printf("%d,",GV[i]);                      //输出访问顶点
    visited[i]=1;                 //全局数组访问标记置1表示已经访问
    for(j=1; j<=n; j++)
       if ((GA[i][j]!=MaxValue)&&(!visited[j]))
	dfs(GV,GA,j);
}

//邻接矩阵的广度遍历

void  bfs(vexlist GV,adjmatrix GA,int  i)  //从顶点i出发广度遍历
{
	int  q[MaxVertexNum];
	int  front,rear,j;
    front=rear=0;
    printf("%d,",GV[i]);
    visited[i]=1;
    rear++; q[rear]=i;
    while (front<rear)
    {   front++; i=q[front];
        for (j=1; j<=n; j++)
        	if ((GA[i][j]!=MaxValue)&&(!visited[j]))
            	{	printf("%d,",GV[j]);
              		visited[j]=1;
              		rear++; q[rear]=j;
          		}
    }

}

void print(adjmatrix GA)
{
	int i,j;
	for (i = 1; i<=n; i++)
	{
		for (j = 1; j<=n; j++)
		{
			printf("%d ",GA[i][j]);
		}
		printf("\n");

	}
}

int main()
{
	vexlist GV;
	adjmatrix GA;
	int i,j,k;
	do
	{
	printf("\n\n\n\n");
	printf("\t\t      图的邻接矩阵子系统\n");
	printf("\t\t*****************************\n");
	printf("\t\t*       1----更 新 图　 　  *\n");
	printf("\t\t*       2----深度遍历　　　 *\n");
	printf("\t\t*       3----广度遍历　　　 *\n");
	printf("\t\t*       0----返　　回　　 　*\n");
	printf("\t\t*****************************\n");
	printf("\t\t   请选择菜单项(0－3)：");
	scanf("%d",&k);
	switch(k)
	{
		case 1:
			printf ("\n请输入图的顶点的个数n= ");
			scanf("%d",&n);
			printf ("请输入图的边个数e= ");
			scanf("%d",&e);
			Create(GV,GA,n,e);
			printf("图的邻接矩阵如下\n");
			print(GA);
			break;
		case 2:
			for (i=0; i< MaxVertexNum;  i++)       /*标志向量初始化*/
			visited [i]=0;
			printf ("\n请输入从图的哪个顶点(1-%d)开始深度遍历:",n);
			scanf("%d",&j);
			printf("深度遍历的结果为：");
			dfs(GV,GA,j);
			break;
		case 3:
			for (i=0; i< MaxVertexNum;  i++)       /*标志向量初始化*/
			visited [i]=0;
			printf ("\n请输入从图的哪个顶点(1-%d)开始广度遍历:",n);
			scanf("%d",&j);
			printf("广度遍历的结果为：");
			bfs(GV,GA,j);
			break;
	}
	}while (k!=0);
}
