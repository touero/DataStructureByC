#include "stdio.h"
#include "malloc.h"
typedef  char TelernType; 

typedef struct BTreeNode 
{	TelernType data ;//树的数据域为字符型
	struct BTreeNode *LChild ;//*左孩子指针
	struct BTreeNode *RChild ;  //*右孩子指针
	int height;
}BTree ; 

BTree *CreatBTree()
{	BTree *T;
	char x;
	scanf("%c",&x);getchar();
	if (x=='0') T=NULL;
	else 
	{	T=new BTree;
		T->data=x;
		printf(" 请输入%c结点的左孩子",T->data);
		T->LChild=CreatBTree();
		printf("请输入%c结点的右孩子",T->data);
		T->RChild=CreatBTree();
	}
	return T;
}

//前序递归遍历二叉树
/*
	步骤：
	（1）判断指针T指向的二叉树是否为空，如果为空则空操作返回；
	（2）访问根结点；
	（3）前序遍历根结点的左子树；
	（4）前序遍历根结点的右子树。
*/

void PreOrder(BTree *T)
{
	if(T==NULL){
		return;
	}
	printf("%c",T->data);
	PreOrder(T->LChild);
	PreOrder(T->RChild);
}

//中序递归遍历二叉树
/*
	步骤：
	（1）判断指针T指向的二叉树是否为空，如果为空则空操作返回；
	（2）中序遍历根结点的左子树；
	（3）访问根结点；
	（4）中序遍历根结点的右子树。
*/

void InOrder(BTree *T)
{
	if(T==NULL){
		return;
	}
	InOrder(T->LChild);
	printf("%c",T->data);
	InOrder(T->RChild);
}

//后序递归遍历二叉树
/*
	步骤：
	（1）判断指针T指向的二叉树是否为空，如果为空则空操作返回；
	（2）后序遍历根结点的左子树；
	（3）后序遍历根结点的右子树；
	（4）访问根结点。
*/

void postOrder(BTree *T)
{
	if(T==NULL){
		return;
	}
	postOrder(T->LChild);
	postOrder(T->RChild);
	printf("%c",T->data);
}

//求二叉树的高度
/*
	步骤：
	（1）判断指针T指向的二叉树是否为空，如果为空则返回0；
	（2）递归获取左子树的高度；
	（3）递归获取右子树的高度；
	（4）二叉树的高度取其左子树和右子树的高度最大值再加1。
	（5）返回二叉树的高度
*/

int TreeHeight(BTree *T)
{
	if(T==NULL){
		return 0;
	}
	int LHeight = TreeHeight(T->LChild);
	int RHeight = TreeHeight(T->RChild);
	T->height=(LHeight>RHeight)?LHeight+1:RHeight+1;
	return T->height;
}

int count=0;
void leafnum(BTree *T)
{	if(T)        //树不空
	{	if (T->LChild==NULL && T->RChild ==NULL)
		count++;
		leafnum(T->LChild );
		leafnum(T->RChild ) ;
	}
}

int main()
{	BTree *T;
	int k;	
	do
    {  
	printf("\n\n\n\n");
    printf("\t\t\t  树 子系统\n");
	printf("\t\t******************************\n");
	printf("\t\t*        1----建二叉树　 　　*\n");
	printf("\t\t*        2----前序遍历 　　　*\n");
	printf("\t\t*        3----中序遍历　 　　*\n");
	printf("\t\t*        4----后序遍历　 　　*\n");
	printf("\t\t*        5----求树高度     　*\n");
	printf("\t\t*        6----叶子个数 　   *\n");
	printf("\t\t*        0----返　　回　 　　*\n");
	printf("\t\t******************************\n");
	printf("\t\t 请选择菜单项(0－5)：");
	scanf("%d",&k);getchar();
	if (k==1)
	{	
	printf("\n请输入此树的根结点:");
	//调用创建二叉树函数，返回创建好的二叉树的指针赋值给T
	T = CreatBTree(); //建立二叉树
	}
	else if (k==2)          
	{
		printf("\n此树前序遍历的顺序:");
		PreOrder(T);//调用前序遍历函数
		                    
	}
	else if (k==3)
	{	printf("\n此树中序遍历的顺序:");
		InOrder(T);//调用中序遍历函数
		                    	
	}
	else if (k==4)       
	{	
		printf("\n此树后序遍历的顺序:");
		postOrder(T);//调用后序遍历函数
		                    
	}
	else if (k==5)      
	 {
        //调用求二叉树高度的函数，获取返回值并输出	
		int height = 0;
		height = TreeHeight(T);
		printf("\n此树的高度是：%d", height); 
	}
	 else if (k==6)       
	 {	
        //调用统计二叉树叶子结点数的函数，并输出叶子结点数
        leafnum(T);                    
		printf("\n此树叶子结点个数是：%d",count); 
	}
	}while(k!=0);
}

