1#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100     //线性表允许的最大长度
typedef int elemtype;
typedef struct     //定义线性表的结构
{	elemtype data[MAXSIZE];     //表示线性表（a1，a2，….,an）
	int length;    //length表示线性表的实际长度
}SeqList;
/* 线性表初始化：Init_List()
初始条件：表L不存在；
操作结果：构造一个空的线性表 */
SeqList * Init_List ()
{	SeqList *L;
	L=(SeqList *)malloc(sizeof(SeqList));
	if(!L)
		return NULL;
	else{
		L->length=0;
		return L;	}
}
/* 线性表赋值：AssignSeqList(L)
初始条件：表L不存在数据
操作结果：构造一个具体指定数值的线性表 */
void AssignSeqList(SeqList *L)   
{	int i;
	printf("请输入元素个数：");
	scanf("%d",&L->length);
	printf("按照元素个数依次输入元素值：");
	for(i=0;i<L->length;i++)
		scanf("%d",&L->data[i]);
}
void OutputSeqList(SeqList *L)   //输出线性表
{	int i;
	printf("顺序表的长度是%d\n",L->length);
	printf("顺序表的元素依次是：");
	for(i=0;i<L->length;i++)
		printf("%4d",L->data[i]);
	printf("\n");
}
/* 插入操作：Insert_List(L,i,x)
初始条件：线性表L存在，插入位置正确 (1<=i<=n+1,ｎ为插入前的表长)。
操作结果：在线性表L的第 i 个位置上插入一个值为 x 的新元素，这样使原序号为 i , i+1, ... , n 的数据元素的序号变为 i+1,i+2, ... , n+1，插入后表长=原表长+1。 */
int InsertSeqList(SeqList *L,int i,elemtype x)
{
    int j;
 	if(i<1||i>L->length+1)
        return 0;
    if(L->length>=MAXSIZE){
        printf("线性表溢出");
        return 0;}
    for(j = L->length-1;j>=i-1; --j)
        L->data[j+1]=L->data[j];
    L->data[i-1]=x;
    L->length++;

    return 1;
}
/*删除操作：Delete_SeqList(L,i)
初始条件：线性表L存在，1<=i<=n。
操作结果：在线性表L中删除序号为i的数据元素，删除后使序号为 i+1, i+2,..., n 的元素变为序号为 i, i+1,...,n-1，删除后新表长＝原表长－１。    */
int DeleteSeqList(SeqList *L,int i)     //删除
{
    int j;
	if(i<0||i>L->length)
		return 0;
    if(L->length<=0){
    	printf("线性表为空");
		return 0; 
	}
	for(j=i;j<=L->length-1;++j){
		L->data[j-1]=L->data[j];
	}		
	L->length--;
	return 1;
}
/*按值查找：Locate_SeqList(L,x)，ｘ是给定的一个数据元素。
初始条件：线性表L存在
操作结果：在表L中查找值为ｘ的数据元素，其结果返回在L中首次出现的值为ｘ的那个元素的序号或地址，称为查找成功; 否则，在L中未找到值为ｘ的数据元素，返回一特殊值表示查找失败。    */
int Location_SeqList(SeqList *L, elemtype x)
{  
    int i;
	for(i=0;i<L->length;i++)
    {
        if(L->data[i]==x)
            return i+1;
        
    }
    return -1;
}
int main(){
	SeqList *L;
	int k,i,x;
	do
    {  	printf("\n\n\n\n");
		printf("\t\t\t 链表子系统\n");
		printf("\t\t*******************************\n");
		printf("\t\t*        1----初 始 化  　　　*\n");
		printf("\t\t*        2----赋    值　　　　*\n");
		printf("\t\t*        3----插　　入　　　　*\n");
		printf("\t\t*        4----删　　除　　　　*\n");
		printf("\t\t*        5----查　　找　　　　*\n");
		printf("\t\t*        6----显　　示　　　　*\n");
		printf("\t\t*        0----返　　回　　　　*\n");
		printf("\t\t*******************************\n");
		printf("\t\t 请选择菜单项(0－6)：");
scanf("%d",&k); //getchar();
switch(k)
		{	case 1:
				L=Init_List ();
				if(L==NULL)  printf("初始化顺序表失败\n");
				else printf("初始化顺序表成功\n");
				break;
case 2:
				AssignSeqList(L);
				OutputSeqList(L);
				break;
			case 3:
				printf("请输入插入位置和插入数据：");
				scanf("%d%d",&i,&x);
				k=InsertSeqList(L,i,x);
				if(k==1){
					printf("插入操作成功！插入元素后顺序表如下\n");
					OutputSeqList(L);
				}
				else printf("插入操作失败\n");
				break;
case 4:
				printf("请输入删除元素的位置：");
				scanf("%d",&i);
				k=DeleteSeqList(L,i);
				if(k==1)
				{   printf("删除操作成功，删除元素后顺序表如下\n");
					OutputSeqList(L);	}
				else printf("删除操作失败\n");
				break;
case 5:
				printf("请输入要查找的数值x:");
				scanf("%d",&x);
				i = Location_SeqList(L,x);
				if (i != -1 ){
				 	OutputSeqList(L);printf("中值为%d所在的位置是%d\n",x,i);}
				else
					printf("线性表中无此元素!!\n");
				break;
case 6:
				OutputSeqList(L);
				break;		}
}	while(k!=0);
system("pause");
	return 0;	
}
