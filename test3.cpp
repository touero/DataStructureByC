#include "stdio.h"
#include "malloc.h"
typedef  int datatype;   
#define  MAXSIZE  50  //队列的最大容量
//定义队列的结构体，包含三个成员变量：data数组、队头、队尾
typedef  struct       
{
	datatype data[MAXSIZE];
	int front,rear;
}c_Sesqueue;  
//置空队 等价于 初始化队列
/*
	初始化循环队列的步骤：
	（1）定义指向循环队列的指针变量；
	（2）申请分配循环队列的存储空间；
	（3）判断是否申请空间成功，不成功返回NULL，函数结束，否则继续（4）；
	（4）使队头指针和队尾指针指向同一个数组元素，一般都赋初值为0；
	（5）返回指向循环队列的指针变量。
*/
c_Sesqueue * Init_Sesqueue(){
	c_Sesqueue * sq;
	sq=(c_Sesqueue*)malloc(sizeof(c_Sesqueue));
	if(sq!=NULL){
		sq->front=sq->rear=0;
		return sq;
	}
	else{
		return NULL;
	}
}
//入队 等价于 在循环队列队尾插入新元素
/*
	循环队列入队的步骤：
	（1）判断当前循环队列是否已满，如果已满，返回0，表示入队失败，否则继续（2）；
	（2）将新元素x赋值给队尾指针指向的数组元素；
	（3）队尾指针向后移动一位；
	（4）返回1，表示入队成功。
*/
int Ensqueue(c_Sesqueue *sq,datatype x){
	if((sq->rear+1)%MAXSIZE==sq->front){
		printf("队列已满，无法入队\n");
		return 0;
	}
	else{
		sq->data[sq->rear]=x;
		sq->rear = (sq->rear + 1) % MAXSIZE;
		printf("入队成功");
        return 1;
	}
}
//出队 等价于 删除循环队列的队头元素
/*
	循环队列出队的步骤：
	（1）判断当前循环队列是否为空，如果为空，返回0，表示出队失败，否则继续（2）；
	（2）保存待删除的队头元素的值；
	（3）队头指针向后移动一位；
	（4）返回1，表示出队成功。*/
int DeQueue(c_Sesqueue *sq,datatype * x){
	if(sq->rear==sq->front){
		printf("队列为空，无法出队\n");
		return 1;
	}
	else{
		*x = sq->data[sq->front];
        sq->front = (sq->front + 1) % MAXSIZE;
		printf("出队成功！出队元素为%d\n",*x);
        return 0;

}
}
//判队空：当队头指针和队尾指针指向同一个位置时表示队空
int isEmpty(c_Sesqueue *sq){
	if(sq->rear==sq->front){
		return 1;
	}
    else{
		return 0;
	}
}
//显示队列
/*
	循环队列显示的步骤：
	（1）计算循环队列的长度=（队尾-队头+队列的最大容量）%队列的最大容量；
	（2）从队头开始循环输出队列元素，不超过循环队列的长度 
*/

void showQueue(c_Sesqueue *sq){
	int length=(sq->rear-sq->front+MAXSIZE)%MAXSIZE;
	int i = sq->front;
	while( i<length){
	printf("%d ",sq->data[i]);
	i = i+1;
	}
	return;	 
}
int main()
{	c_Sesqueue  *sq;
	int j,k;
	datatype x;
	sq=Init_Sesqueue();
	do
    { printf("\n\n\n\n");
    printf("\t\t\t 队列子系统\n");
	printf("\t\t*******************************\n");
	printf("\t\t*        1----进 队 列　  　　*\n");
	printf("\t\t*        2----出 队 列　　　　*\n");
	printf("\t\t*        3----队列空否　　　　*\n");
	printf("\t\t*        4----显示队列　　　　*\n");
	printf("\t\t*        0----返　　回　　　　*\n");
	printf("\t\t*******************************\n");
	printf("\t\t 请选择菜单项(0－4)：");
	scanf("%d",&k);getchar();
	switch(k)
    { case 1:         //进队列
			printf("\n   请输入要进队列的数据:");
			//输入一个入队数据，然后调用入队函数，若函数返回结果为1，则输出“入队成功！”并打印输出循环队列的所有元素，否则提示入队失败
			scanf("%d",&x);
			j=Ensqueue(sq,x);
			break;
 
      case 2:          //出队列
			//调用出队函数，若函数返回结果为1，则输出“出队成功！出队元素为**（出队元素具体的值）”，否则输出“出队失败……”
			j=DeQueue(sq,&x);
			break;
			
	  case 3:          //判断队列空否 
			//调用判队空函数赋值给变量j
			j=isEmpty(sq);
			if (j==1) printf("此队列为空!!!");
			else printf("此队列不空。");
			break;
			
	  case 4:       //显示队列
			printf("\n   此队列有数据：");
//调用队列打印函数
			showQueue(sq);
			break;		
	 }
	}while(k!=0);  
 }