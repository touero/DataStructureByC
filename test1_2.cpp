#include <stdio.h>
#include <malloc.h>
#define datatype int
typedef struct node
{  datatype data;        //链表的数据域
   struct node *next;    //链表的指针域
} LNode,*LinkList;
LinkList  Creat_LinkList1( ) //头插入法建立单链表算法
{  
   LinkList head;
   LNode * s;
   head=(LinkList)malloc(sizeof(LNode));
   head->next=NULL;
   char flag='Y';
   printf("头插入法建立单链表：\n");
   while(flag=='Y'||flag=='y') {
   	s = (LNode *)malloc(sizeof(LNode));
   	printf("请输入新节点数据:");
	scanf("%d",&s->data) ;
	s->next=head->next;
	head->next=s;
	getchar();
	printf("是否继续输入(Y/N):");
	scanf("%c",&flag);
   }
   return head;
}
/*按序号查找 Get_Linklist(L,i)
在单链表L中查找第i个元素结点，找到返回其指针，否则返回空*/
LNode *Get_LinkList(LinkList L,int i)
{
	int j=0;
	LNode * p;
	p=L;
	while((p->next!=NULL)&&(j<i)){
		p=p->next;
		j++;
	}
	if(i==j){
		return p;
	}
	else{
		return NULL;
	}
}
/*插入运算 Insert_LinkList(L,i,x)
在单链表L的第i个位置上插入值为x的元素*/
int  Insert_LinkList(LinkList  L, int i, datatype  x)     
{
	LNode * p1,* p2,*s;
	int k=1;
	p1=L;
	p2=p1->next;
	while(p2&&k<i){
		p1=p2;
		p2=p2->next;
		k++;
	}
	if(p2==NULL&&k!=i){
		printf("查找插入位置失败\n");
		return 0;
	}
	s=(LNode*)malloc(sizeof(LNode));
	s->data=x; 
	s->next=p1->next;
	p1->next=s;
	printf("插入操作成功！");
}
/*删除运算：Del_LinkList(L,i)
删除单链表L上的第i个数据结点*/
int  Del_LinkList(LinkList  L,int i)   
{
    LNode * p, *q;
	q=L;
	p=Get_LinkList(L,i);
	if(p==NULL){
		return 0;
	}
	while(q&&q->next!=p){
		q=q->next;
	}
	q->next=p->next;
	free(p);
	return 1;
}
void print(LinkList L)           //输出单链表
{   LNode *p=L;
    while(p->next!=NULL){ 
      p=p->next;
	  printf("%d->",p->data);//输出表中非最后一个元素 
	  }    	
    printf("^");      //输出表中最后一个元素    
}
int main()
{ 	LinkList  H;
    int i,j,k;
	datatype x;
	LinkList L=(LNode *)malloc(sizeof(LNode));
	do
    {  
	printf("\n\n\n\n");
    printf("\t\t\t 链表子系统\n");
	printf("\t\t*******************************\n");
	printf("\t\t*        1----建    表　  　　*\n");
	printf("\t\t*        2----插    入　　　　*\n");
	printf("\t\t*        3----删　　除　　　　*\n");
	printf("\t\t*        4----查　　找　　　　*\n");
	printf("\t\t*        5----显　　示　　　　*\n");
	printf("\t\t*        0----返　　回　　　　*\n");
	printf("\t\t*******************************\n");
	printf("\t\t 请选择菜单项(0－5)：");
	scanf("%d",&k);getchar();
	if (k==1)
    	H=Creat_LinkList1( );      //用头插入法建立单链表
	else if (k==2)       //在线性表第i位置处插入值为X的元素
	{	printf("\n   请输入插入的位置i和数据X(输入格式：i,X):");
		scanf("%d,%d",&i,&x);
		j=Insert_LinkList(H,i,x);
	}
	else if (k==3)
	{	printf("\n   请输入要删除元素的位置i:");
		scanf("%d",&i);
		j=Del_LinkList(H,i);
		if (j == 1) printf("删除成功!!");
		else printf("删除失败!!");		
	}
	else if (k==4)       //查找线性表中元素值为x的位置
	{	printf("\n   请输入要查找的序号i:");
		scanf("%d",&i);
		LNode  *p;
		p=Get_LinkList(H,i);
		if (p!=NULL) 
		{ print(H);
		printf("中序号为%d的元素值是 %d ", i, p->data);
		}
		else
		printf("链表中无此序号!!\n");
	}
	 else if (k==5)        //输出链表
	 {	printf("\n表的存储顺序为：");
        print(H);  
	}
}while(k!=0);
}
