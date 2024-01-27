#include "stdio.h"
#include "malloc.h"
typedef  int datatype;                  
typedef  struct node   //定义链式栈结构
{	datatype data;
	struct node *next;
}StackNode,*LinkStack;

//置空栈 
LinkStack  Init_LinkStack()
{	
	return NULL;		
}

//入栈   
LinkStack  Push_LinkStack(LinkStack  top, datatype x)         
{
	StackNode *s;
	s=(StackNode*)malloc(sizeof(StackNode));
	s->data=x;
	s->next=top;
	top=s;
	return top;
}

//出栈
LinkStack   Pop_LinkStack (LinkStack  top, datatype  *x)
{
	StackNode *p;
	if(top==NULL)return NULL;
	else
	{
		*x=top->data;
		p=top;
		top=top->next;
		free(p);
		return top;
	}
		
}

void print(LinkStack  top)
{	StackNode  *p=top;
	while(p != NULL) 
	{	printf("%d->",p->data);
		p=p->next;
	}
}

//顺序栈
#define MAXSIZE  1024   
typedef  struct
{	datatype  data[MAXSIZE];
	int  top;
}SeqStack;
//顺序栈置空栈：首先建立栈空间，然后初始化栈顶指针。
SeqStack  *Init_SeqStack()
{	SeqStack  *s;
	s=(SeqStack*)malloc(sizeof(SeqStack));
	s->top= -1;  
	return s;
}
//顺序栈判空栈
int Empty_SeqStack(SeqStack *s)
{	if (s->top == -1)  return 1;
    else  return 0;
}
//顺序栈入栈
int Push_SeqStack (SeqStack *s, datatype  x){
	if (s->top == MAXSIZE-1)  return 0; //栈满不能入栈
	else {	s->top++;
			s->data[s->top]=x;
			return 1;
	}
}
//顺序栈出栈
int  Pop_SeqStack(SeqStack *s, datatype *x)
{  	if  (Empty_SeqStack(s))  return 0; //栈空不能出栈 
    else  { *x=s->data[s->top];
			s->top--;  return 1;        //栈顶元素存入*x，返回
		  }
}
void conversion(int N,int r)
{	SeqStack  *s;
	datatype   x;                         
	s=Init_SeqStack();		//初始化栈
	printf("\n %d 的十进制数转换成 %d 进制为: ",N,r);
	while ( N )                            
	{	Push_SeqStack (s,N%r);     //余数入栈 
		N=N/r ;				//商作为被除数继续 
	}   
	while  ( !Empty_SeqStack(s))  
	{	Pop_SeqStack (s,&x) ;   
		printf(" %d ",x) ;  }         
}  

int main(){   
	LinkStack  top;
	top=Init_LinkStack();
    int i,j,k; 
	datatype x;
    do{   
	printf("\n\n\n\n");
    printf("\t\t\t 栈的应用子系统\n");
	printf("\t\t*******************************\n");
	printf("\t\t*        1----链式进栈　  　　*\n");
	printf("\t\t*        2----链式出栈　　　　*\n");
	printf("\t\t*        3----链栈显示　　　　*\n");
	printf("\t\t*        4----进制转换　　　　*\n");
	printf("\t\t*        0----返　　回　　　　*\n");
	printf("\t\t*******************************\n");
	printf("\t\t 请选择菜单项(0－4)：");
	scanf("%d",&k);getchar();
	switch(k){
	  case 1:         //进栈
			printf("\n   请输入要进栈的数据X:");
			scanf("%d",&x);
			top=Push_LinkStack(top,x);
			break;
			                      			                    
      case 2:          //出栈
			top=Pop_LinkStack(top,&x);
			break;	                    
 			                    
	  case 3:          //打印链式栈中的元素 
			printf("\n 链式栈的元素有：");
 			print(top);
			break;                    
	  case 4:{     //进制转换
			int N,r;
			printf("\n   请输入一个整数N=");
			scanf("%d",&N);
			printf("\n   请输入一个要转换的进制数r=");
			scanf("%d",&r);
			conversion(N,r);
			break;}
			
    }  
	}while(k!=0);
}