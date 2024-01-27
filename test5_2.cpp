#include "stdio.h"
#define  MaxVertexNum  20    //定义图的最大顶点数
#define  MaxEdgeNum  50      //定义图的最大边数
typedef  int  VertexType;    //定义图中顶点数据的类型VertexType为整型
typedef  VertexType  vexlist[MaxVertexNum]; //定义存储顶点信息的数组类型

struct  edgenode   //定义邻接表中边结点类型
{   int  adjvex;           //邻接点域
	int  weight;           //权值域，对无权图可省略
	struct  edgenode* next;    //指向下一个边结点的链域
};
int n;    //图中实际顶点的个数
int e;    //图中实际边的个数
int visited [ MaxVertexNum ];  //全局数组标记置1表示已经访问，0为未访问

//定义adjlist 为存储n个表头指针的数组类型
typedef  struct  edgenode* adjlist[MaxVertexNum];

//通过从键盘上输入e条有向无权边的信息，建立顶点数组GV和邻接表GL
void  Create(vexlist GV,  adjlist GL,  int n,  int e)
{
	int  i , j, k;
	for (i=1;  i<=n;  i++)      GV[i]=i;  //建立顶点数组
	for (i=1;  i<=n;  i++)   //初始化邻接表，即将表头向量中的每个域置空
		GL[ i ] =NULL;
	printf ("\n输入 %d 条有向无权边\n\n", e);     //建立邻接表
	for (k=1; k<=e;  k++)
	{	struct  edgenode *p;
		printf("输入第 %d 条边的两端序号(i j): ",k);
		scanf ("%d%d", &i, &j);      //输入一条边的两端序号i和j
        p = new struct edgenode;     //由系统分配一个新结点
		p->adjvex = j;               //将j的值赋给新结点的邻接点域
		p->next = GL[ i ];           //将新结点插入到vi邻接表的表头
		GL[ i ] = p;
	}
}
void print(adjlist GL)
{   struct  edgenode *p;
    for(int i=1;i<=n;i++)
    {	p=GL[i];
		printf("%d: ",i);
		while(p)
		{	printf("%d->",p->adjvex);
			p=p->next;
		}
		printf("^\n");
    }
}
//邻接表的深度遍历，从初始点vi出发深度优先搜索由邻接表GL表示的图
void  DFS(adjlist GL,  int i)
{
	struct  edgenode *p;
	printf ("%d ", i);         //假定访问顶点vi以输出该顶点的序号代之
    visited [i]=1;             //标记 vi已被访问过
    p= GL[i];                 //取vi邻接表的表头指针
    while (p !=NULL)
	{
		int  j = p->adjvex;         // j为vi的一个邻接点序号
		if ( !visited [j] )
DFS(GL,j);        //若vj未被访问过,则从vj出发进行递归调用
		p = p->next;          //使p指向vi单链表的下一个边结点
	}
}
//邻接表的广度遍历
void  BFS(adjlist GL, int  i , int n)
{
	int  q[MaxVertexNum] ;           //定义队列
    int  f,r ;
	struct  edgenode *p ;            //P为搜索指针
    f=r=0 ;
	printf("%d ",i) ;
    visited[i]=1 ; r++; q[r]=i ;           //进队
    while (f<r)
    { f++ ; i=q[f] ;                       //出队
      p=GL[i] ;
      while  (p!=NULL)
      { if  (!visited[p->adjvex])
		{	printf("%d ",p->adjvex);
			visited[p->adjvex]=1 ;
			r++;q[r]=p->adjvex ;
		}
      p=p->next;
	  }
    }
}
int main()
{
	vexlist GV;
	adjlist GL;
	int i,j,k;
	do
	{
	printf("\n\n\n\n");
	printf("\t\t      图的邻接表子系统\n");
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
			Create(GV,GL,n,e);
			printf("图的邻接矩阵如下\n");
			print(GL);
			break;
		case 2:
			for (i=0; i< MaxVertexNum;  i++)       /*标志向量初始化*/
			visited [i]=0;
			printf ("\n请输入从图的哪个顶点(1-%d)开始深度遍历:",n);
			scanf("%d",&j);
			printf("深度遍历的结果为：");
			DFS(GL,j);
			break;
		case 3:
			for (i=0; i< MaxVertexNum;  i++)       /*标志向量初始化*/
			visited [i]=0;
			printf ("\n请输入从图的哪个顶点(1-%d)开始广度遍历:",n);
			scanf("%d",&j);
			printf("广度遍历的结果为：");
			BFS(GL,j,n);
			break;
	}
	}while (k!=0);
}
