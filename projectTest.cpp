#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>

typedef struct flightnode         //定义飞机航班数据结构体链表
{
	char flight_num[20];  //航班数量
	char start_time[20];  //航班开始时间
	char end_time[20];    //航班结束时间
	char start_place[20]; //出发地
	char end_place[20];   //目的地
	char day[20];//飞行日期（星期几）
	float price;     //价格
	float price_discount; //折扣
	int left;             //剩下的
	int isFull;           //是否满座
	struct flightnode *next;//指向下一个指针
}flightnode;//航班的数据类型的指针

typedef struct passengernode      //定义乘客数据结构体链表
{
	char name[20];             //乘客名字
	char ID_num[20];           //身份证号
	char phone_num[20];        //手机号
	char flight_num[20];       //航班号
	int order_num;             //订单票数
	int ticket_num;            //座位
	struct passengernode *next;//指向下一个指针
}passengernode;

typedef struct passengerList      //乘客链表
{
	passengernode *head;//头
	passengernode *rear;//尾
}passengerList;
typedef struct User_basicinfo//定义管理员结构体
{
	char id[15];//账号
	char paw[20];//密码
	char name[15];//名字
	char sex[5];//性别
}Users;
int Login()//登录
{
	Users a={0},b={0};//结构体重命名定义
	FILE *pf=fopen("users.txt","r");
	if(pf==NULL)
	{
		printf("文件打开失败\n");
		return 0;
	}
	printf("欢迎来到登录界面!\n");
	printf("请输入账号->");
	scanf("%s",a.id);
	fread(&b, sizeof(Users), 1, pf);//从文件流中读取数据，b是接收数据的地址
	while(1)
	{
		if(strcmp(a.id, b.id)!=0 )
		{
			if(feof(pf)==0)//未到文件尾
			{
				fread(&b, sizeof(Users), 1, pf);
			}
			else
			{
				printf("该账号不存在,请先注册\n");
				fclose(pf); pf=NULL;
				return 0 ;
			}
		}
		else//账号注册过->跳到输入密码
		{
			break; //退出无限循环，跳到输入密码
		}

	}
//【输入密码】
	printf("请输入密码->");
	do{
	scanf("%s",a.paw);
	if(strcmp(a.paw, b.paw)!=0 )
	printf("密码错误，请重新输入->");
	else break;
	}while(1);
	printf("登录成功!\n");
//	fclose(pf); pf=NULL;
	return 1;
}

void Regist()//注册
{
	Users a={0},b={0};//结构体重命名定义
	char tmp[20]={-1};
	FILE *pf=NULL;
	pf=fopen("users.txt","r");//用pf去指向文件
	if(pf==NULL)
	{
		printf("注册时打开文件失败\n");
		return ;
	}
	printf("\t\t\t欢迎来到注册界面\n\n");
	printf("\t\t\t输入账号->");
	scanf("%s",a.id);
	printf("输入成功!\n");

	fread(&b, sizeof(Users), 1, pf);
//【判断】有没有注册过-比较字符串是否相等
//不相等->是否到文件尾
while(1)
{
	if(strcmp(a.id, b.id)!=0 )
	{
		 if(feof(pf)==0 )//未到文件尾
		 fread(&b, sizeof(Users), 1, pf);
	 	 else//到了文件尾仍然没有相同的字符串-说明输入的账号使新的 可以去注册界面
		 {
		 printf("账号未注册过，将跳转到注册界面\n");
		// system("pause");
		 break;//利用break来跳出无限循环
		 }
	}
	else
	{
		 printf("该账号已注册过\n");
		 fclose(pf); pf=NULL;
		 return;
    }
}
//【注册界面】
	printf("\t\t\t请输入姓名->");
	scanf("%s",a.name);
	printf("\t\t\t请输入性别:男/女->");
	do{
		getchar();
		scanf("%s",a.sex);
		if(strcmp(a.sex, "男")!=0&&strcmp(a.sex, "女")!=0)
		printf("\t\t\t输入错误，请重新输入->");
		else break;
	     }while(1);

		printf("\t\t\t请输入密码->");
		scanf("%s",a.paw);
		printf("\t\t\t请再输入一次密码->");
		do{
		scanf("%s",tmp);
		if(strcmp(tmp,a.paw)!=0)
		printf("\t\t\t两次输入密码不一致，请再输入一次密码->");
		else break;
		}while(1);
		//两次密码一致
		fclose(pf);	pf=NULL;
		pf=fopen("users.txt","a");
		//fwrite会在当前文件指针的位置写入数据
		//"w" 打开，文件指针指到头，只写；"a" 打开，指向文件尾
		fwrite(&a, sizeof(Users) , 1, pf );
		printf("\t\t\t注册成功!\n");
		fclose(pf);	pf=NULL;
		return;
}

int User()
{
	int input=-1;
    do
	{
		printf("\t\t\t----------------------------------\n");
		printf("\t\t\t|           1.登录               |\n");
		printf("\t\t\t|           2.注册               |\n");
		printf("\t\t\t|           0.退出               |\n");
		printf("\t\t\t----------------------------------\n");
		printf("请选择功能->");
		scanf("%d",&input);
		switch(input)
		{
			case 1:
				if(Login())
				return 1;
			case 2:Regist();break;
			case 0:puts("退出成功");return 0;
		}
	}while(input);

	return 1;
}



void init_flight(flightnode *&h)  //初始化航班链表为空表 定义并引用h为头结点
{
	h = (flightnode *)malloc(sizeof(flightnode));   //申请航班头储存空间
	if(h==NULL) exit(0);          //为空则退出
	h->next = NULL;               //置空表
}

void init_passengerList(passengerList *&pList)   //初始化乘客链表为带 头指针 和 尾指针 的空链表，储存乘客信息的结点
{
	pList = (passengerList *)malloc(sizeof(passengerList));//申请乘客链表储存空间
	pList->head = (passengernode *)malloc(sizeof(passengernode)); //申请头储存空间
	pList->rear = pList->head;       //头指针指向链表当前表尾，初始化首尾指针为0，队空
	pList->rear->order_num = 0;      //订单链表从0开始
	pList->head->next = NULL;        //置空表
}

void save_passenger(passengerList *PList)           //保存文件(以二进制形式保存 存到.dat文件中)   passenger.dat
{
	FILE* fp = fopen("乘客.dat","wb");
	if(fp == NULL)
		return;
	passengernode *temp = PList->head->next;        //temp指针指向链表的首节点
	while(temp!=NULL)

	{
		fwrite(temp,sizeof(passengernode),1,fp);//写入文件
		temp = temp->next;//往后走
	}
	fclose(fp);
}

void load_passenger(passengerList *PList)           //把文件中的乘客信息导入到乘客链表中
{
	FILE* fp = fopen("乘客.dat","rb");
	if(fp == NULL)
		return;
	passengernode *q;                               //乘客结点
	int n;                                          //是否成功写入的标志量
	while(!feof(fp))//feof检测流上的文件结束符，如果文件结束，返回非0，结束，返回0.
	{
		q = (passengernode *)malloc(sizeof(passengernode));
		n = fread(q,sizeof(passengernode),1,fp);//从文件流中读取数据，q是接收数据的地址
		if(n!=1)
			break;
		PList->rear->next=q;             //利用尾插法，把新乘客结点链接在尾结点后面
		PList->rear=q;                   //尾指针指向新乘客结点
	}
	PList->rear->next = NULL;
	fclose(fp);//关闭文件
}

void save_flight(flightnode *h)
{
	FILE* fp = fopen("航班.dat","wb");
	if(fp == NULL)
		return;
	flightnode *temp = h->next;
	while(temp != NULL)
	{
		fwrite(temp,sizeof(flightnode),1,fp);//写入文件
		temp = temp->next;//往后走
	}
	fclose(fp);
}

void load_flight(flightnode *&h)               //从文件中将信息导入到航班链表中
{
	flightnode *pt = h;
	FILE* fp = fopen("航班.dat","rb");
	if(fp == NULL)
		return;
	flightnode *q;
	int n;
	while(!feof(fp))//feof检测流上的文件结束符，如果文件结束，返回非0，结束，返回0.
	{
		q = (flightnode *)malloc(sizeof(flightnode));
		n = fread(q,sizeof(flightnode),1,fp);//从文件流中读取数据，q是接收数据的地址
		if(n!=1)
			break;
		pt->next = q;                 //利用尾插法，把新航班结点链接在尾结点后面
		pt = q;                       //尾指针指向新航班结点
	}
	pt->next = NULL;
	fclose(fp);
}

void insert_flight(flightnode *&h,char* flight_num,char* start_place,char* end_place,char *start_time,char* day,char* end_time,float price,float price_discount,int left,int isFull)//插入航班数据
{//录入航班或者增加新航班，将新的航班结点插入航班链表中，头插法
	flightnode *q;                                      //q指向新节点（新增加的航班）
	flightnode *p = h;                                  //p指向航班链表的头节点
	q = (flightnode *)malloc(sizeof(flightnode));       //给新结点申请空间
	strcpy(q->flight_num,flight_num);                   //将把flight_num复制到q->flight_num，（strcpy）复制函数
	strcpy(q->start_place,start_place);                 //同理
	strcpy(q->end_place,end_place);
	strcpy(q->start_time,start_time);
	strcpy(q->day,day);
	strcpy(q->end_time,end_time);
	q->price = price;
	q->price_discount = price_discount;
	q->left = left;
	q->isFull = isFull;
	q->next = p->next;                              //用 头插法 把首元素结点链接在新结点之后
	p->next = q;                                    //新结点链接在头结点之后
	p = p->next;                                    //指针后移
}

void insert_passengerList(flightnode *&h,passengerList *&PList,char *name,char *ID_num,char *phone_num,char *flight_num,int ticket_num)//插入乘客数据
{//订票后，将乘客结点插入乘客链表中
	flightnode *p = h->next;                         //p指向乘客链表的首节点
    for(; p!= NULL; p=p->next)
    {
    	if(strcmp(p->flight_num,flight_num) == 0)   //用strcmp函数比较航班号
    	{
    		p->left = p->left - ticket_num;          //更新实时的剩余座位数
    		if(p->left == 0)                        //判断剩下位置
    		{
    			p->isFull = 1;
    		}
    	}
    }
    passengernode *q  = (passengernode *)malloc(sizeof(passengernode));   //新建q节点申请新空间用来存放新的乘客信息
    strcpy(q->name, name);
    strcpy(q->ID_num, ID_num);
	strcpy(q->phone_num, phone_num);
    strcpy(q->flight_num, flight_num);
    q->ticket_num = ticket_num;
    q->next = NULL;                //新结点链接在尾结点之后
    PList->rear->next = q;         // 尾插法
    q->order_num = PList->rear->order_num+1; //后移==订单号加一
    PList->rear = q;          //尾指针指向q
}

void add_flight(flightnode *&h)//录入航班数据
{
	flightnode *p = h;
    flightnode *b = h;
	char flight_num[10],start_time[10],end_time[10],start_place[20],end_place[20],day[20];
	int left,isFull,leftB,leftE,mark = 1;//mark是是否继续输入的指标
	float price,price_discount;
	while(mark == 1)
	{
		printf("\t\t 请输入您需要增加的航班号: ");
		scanf("%s",flight_num);
        for(;b!=NULL;b = b->next)//遍历航班结点
        {
            while(strcmp(b->flight_num,flight_num) == 0)
            {
                printf("\t\t 航班已存在重新请输入航班号：");
                scanf("%s",flight_num);
            }
        }
		printf("\t\t 请输入出发地: ");
		scanf("%s",start_place);
		printf("\t\t 请输入目的地: ");
		scanf("%s",end_place);
		printf("\t\t 请输入出发时间: ");
		scanf("%s",start_time);
		printf("\t\t 请输入结束时间: ");
		scanf("%s",end_time);
		printf("\t\t 请输入星期几（星期二，输入2）:");
		scanf("%s",day);
		printf("\t\t 请输入航班价格: ");
		scanf("%f",&price);
		printf("\t\t 请输入折扣信息: ");
		scanf("%f",&price_discount);
		printf("\t\t 请输入经济舱座位数: ");
		scanf("%d",&leftE);
		printf("\t\t 请输入商务舱座位数: ");
		scanf("%d",&leftB);
		left=leftB+leftE;
		printf("\t\t 请输入是否满仓:(0表示没有满仓  1表示满仓) ");
		scanf("%d",&isFull);
		insert_flight(p,flight_num,start_place,end_place,start_time,end_time,day,price,price_discount,left,isFull);//调用插入函数把信息录入
		printf("\t\t 增加航班%s 成功！\n",flight_num);
		printf("\t\t 是否继续录入航班信息(1 表示继续录入;0 表示停止录入).\n");
		printf("\t\t 请输入: ");
		scanf("%d",&mark);
	}
}

int flight_num_check(flightnode *h,char *flight_num)//按航班号
{
	flightnode *p=h;              //头指针h存入p所指定的内存里面
	printf("%-8s%-12s%-12s%-10s%-10s%-10s%-8s%-8s%-8s%-10s\n","航班号","起飞城市","抵达城市","起飞时间","抵达时间","星期几","价格","折扣","空座数","是否满仓");    //提示输入信息格式
	for(;p!=NULL;p = p->next)//遍历航班结点
	{
		if(strcmp(p->flight_num,flight_num) == 0)
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-8.2f%-8d%-10d\n",p->flight_num, p->start_place, p->end_place, p->start_time,p->end_time, p->day,p->price, p->price_discount, p->left, p->isFull);  //找到航班号 进行输出
			return 1;
		}
	}
	printf("\t\t  抱歉，没有航班为%s 的航班信息!\n",flight_num);
	return 0;
}
int day_num_check(flightnode *h,char *day)//按星期几
{
	flightnode *p=h;              //头指针h存入p所指定的内存里面
	printf("%-8s%-12s%-12s%-10s%-10s%-8s%-8s%-8s%-10s\n","航班号","起飞城市","抵达城市","起飞时间","抵达时间","星期几","价格","折扣","空座数","是否满仓");    //提示输入信息格式
	for(;p!=NULL;p = p->next) //遍历航班结点
	{
		if(strcmp(p->day,day) == 0)
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-8.2f%-8.2f%-8d%-10d\n",p->flight_num, p->start_place, p->end_place, p->start_time,p->end_time, p->day,p->price, p->price_discount, p->left, p->isFull);  //找到航班号 进行输出
			return 1;
		}
	}
	printf("\t\t  抱歉，没有航班为是星期%s 的航班信息!\n",day);
	return 0;
}
int place_check(flightnode *h,char *start_place,char *end_place)    //按照起始地点 结束地点查询
{
	flightnode *p = h;            //头指针h存入p所指定的内存里面
	int mark = 0;                 //判断指标
	printf("%-8s%-12s%-12s%-10s%-10s%-10s%-8s%-8s%-8s%-10s\n","航班号","起飞城市","抵达城市","起飞时间","抵达时间","星期几","价格","折扣","空座数","是否满仓");    //提示输入信息格式
	for(;p!=NULL;p = p->next)//遍历航班结点
	{
		if(strcmp(p->start_place, start_place) == 0 && (strcmp(p->end_place, end_place) == 0))
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-10s%-8.2f%-8.2f%-8d%-10d\n",p->flight_num, p->start_place, p->end_place, p->start_time,p->end_time,p->day, p->price, p->price_discount, p->left, p->isFull);    //相等 输出航班相关信息
			mark = 1;
		}
	}
	if(mark == 0)
	{
		printf("\t\t 抱歉,没有从%s 到%s 的航班信息！\n",start_place,end_place);
		return 0;
	}
	return 1;
}

void check_all_flight(flightnode *h)            //浏览所有航班
{
	flightnode *p = h;           //头指针h存入p所指定的内存里面
	int mark = 0;                       //判断指标
	printf("%-8s%-12s%-12s%-10s%-10s%-10s%-8s%-8s%-8s%-10s\n","航班号","起飞城市","抵达城市","起飞时间","抵达时间","星期几","价格","折扣","空座数","是否满仓");    //提示输入信息格式
	for(;p!=NULL; p=p->next)
	{
		printf("%-8s%-12s%-12s%-10s%-10s%-10s%-8.2f%-8.2f%-8d%-10d\n",p->flight_num, p->start_place, p->end_place, p->start_time,p->end_time,p->day, p->price, p->price_discount, p->left, p->isFull);    //输出相关信息
		mark = 1;
	}
	if(mark == 0)
		printf("\t\t  航班信息为空!\n");
}

void flight_check(flightnode *h)//航班查询函数
{
	flightnode *p=h->next;                      //p指针指向航班链表的首节点
	char flight_num[10],start_place[20],end_place[20],day[20];
	char a;
	printf("\t\t 请选择航班查询方式：\n");
	printf("\t\t 1表示按航班号进行查询;\n");
	printf("\t\t 2表示按起飞到达城市进行查询;\n");
	printf("\t\t 3表示按星期几起飞进行查询;\n");
	printf("\t\t 4表示浏览全部航班信息.\n\t\t 请选择输入：");
	a = getch();
	printf("%c\n",a);
	if(a ==  '1')
	{
		printf("\t\t 请输入航班号:");
		scanf("%s",flight_num);
		flight_num_check(p,flight_num);
	}
	else if(a == '2')
	{
		printf("\t\t 请输入出发地城市:");
		scanf("%s",start_place);
		printf("\t\t 请输入结束地城市:");
		scanf("%s",end_place);
		place_check(p,start_place,end_place);
	}
	else if(a=='3')
	{
		printf("请输入星期几起飞：");
		scanf("%s",day);
		day_num_check(p,day);
	}
	else if(a == '4')
	{
		check_all_flight(p);
	}
	else
		return;
}


int find_same_flight(flightnode *h,char *flight_num)  //如果没有选择的航班满了的话 提示的可选择的其他航班
{
	flightnode *t = h->next,*p = h->next;            //t，p指针指向航班链表的首节点
	int mark = 0;
	printf("%-8s%-12s%-12s%-10s%-10s%-10s%-8s%-8s%-8s%-10s\n","航班号","起飞城市","抵达城市","起飞时间","抵达时间","星期几","价格","折扣","空座数","是否满仓");        //提示输入信息格式
	while(t != NULL && strcmp(t->flight_num,flight_num)!=0)
	t=t->next;     //遍历到了最后一个节点 或者查找到第一个目标节点
	while(p != NULL)
	{
		if((strcmp(t->start_place,p->start_place) == 0) && (strcmp(t->end_place,p->end_place) == 0) && (strcmp(t->flight_num,p->flight_num)!=0))   //出发点和目的地相同 并且和那个满的航班号还不相同
		{
			printf("%-8s%-12s%-12s%-10s%-10s%-10s%-8.2f%-8.2f%-8d%-10d\n",p->flight_num, p->start_place, p->end_place, p->start_time,p->end_time,p->day,p->price, p->price_discount, p->left, p->isFull);   //输出所有可选航班
			mark = 1;
		}
		p = p->next;
	}
	if(mark == 0)             //如果其他航班的时候
	{
		printf("\t\t 抱歉, 没有可选航班!");
		return 0;
	}
	return 1;
}

int book(flightnode *&h,passengerList *&PList)//订购函数
{
	char name[20];
	char ID_num[20];
	char phone_num[20];
	char flight_num[10];
	char start_place[20];
	char end_place[20];
	int ticket_num;
	int k;                              //没票的时候 想不想买别的票的时候  标志量
	flightnode *p = h->next;            //p指向航班链表的首节点
	printf("\t\t 请根据提示输入信息:\n");
	printf("\t\t 请输入出发地城市:");
	scanf("%s",start_place);
	printf("\t\t 请输入结束地城市:");
	scanf("%s",end_place);
	if(place_check(h,start_place,end_place) == 1)          //place_check同时会输出所有符合用户需求的航班
	{
		printf("\t\t 航班号:");
		scanf("%s",flight_num);
		while(p != NULL)
		{
			if(strcmp(p->flight_num,flight_num) == 0)
			{
				printf("\t\t 姓名:");
				scanf("%s",name);
				printf("\t\t 证件号码:");
				scanf("%s",& ID_num);
				printf("\t\t 手机号码:");
				scanf("%s",& phone_num);
				printf("\t\t 订票数量:");
			    scanf("%d",&ticket_num);
				if(p->left > 0 && p->left >= ticket_num)   //判断是否剩余充足的座位
				{
					insert_passengerList(h,PList,name,ID_num,phone_num,flight_num,ticket_num);
					printf("\t\t 你应付金额￥%6.2f.\n",p->price * p->price_discount * ticket_num);
					getch();
					printf("\t\t 恭喜您，订票成功啦!\n");
					return 1;
				}
				else
				{
					printf("\t\t ***很遗憾,该航班已满:!***\n");
					printf("\t\t ***如您想要选择其他航班请输入---1\n\t\t *** 不选则输入---0***\n");
					printf("\t\t 请输入数字进行选择:");
					scanf("%d",&k);
					if(k==1)
					{
						printf("\t\t 此航线上的其他航班有:\n");
						if(find_same_flight(h,flight_num) == 1)              //该航班已经没有了座位 开始查找下一个节点 此时进行传参flight_num
						{
							printf("\t\t 请输入您选的航班:");
							scanf("%s",flight_num);
							insert_passengerList(h, PList, name, ID_num, phone_num, flight_num, ticket_num);    //选择成功进行插入操作
							printf("\t\t 恭喜你,订票成功!\n");
							return 1;
						}
					}
					return 0;
				}
			}
			else
				p = p->next;
		}
		if(p==NULL)                            //遍历到了乘客链表的尾节点
			printf("\t\t 对不起，您输入的航班不存在!\n");
	}
	return 0;
}

void delete_flight(flightnode *&h, passengerList *&PList)
{
	flightnode *p,*pr;    //p指向航班链表的首节点 pr指向航班链表的头结点 定义的p即为需要删除的节点 下同
	passengernode *q,*qr;
	char flight_num[10];
	int mark = 1;
	qr = PList->head;//乘客链表头指针
	q = qr->next;//q作中间指针对乘客链表中要删除的乘客结点进行查找
	pr = h;//航班链表头结点
	p = pr->next;//p作中间指针对航班链表中要删除的航班结点进行查找
	printf("\t\t 请输入您要删除的航班号:");
	scanf("%s",flight_num);
	while(p != NULL)
	{
		if(strcmp(flight_num, p->flight_num) == 0)
		{
			pr->next = p->next;   //需要删除的节点 的前一个节点直接指向 需要删除节点的后一个节点
			free(p);
 			printf("\t\t 删除%s 航班成功!\n",flight_num);
 			mark = 0;
 			p = NULL;
		}
		if(pr->next != NULL)
		{
			pr = pr->next;
			p = pr->next;
		}
	}
	if(mark == 1)
		printf("\t\t 无此航班,无法删除!\n");
	else                         //删除顾客链表中的信息  删除了航班信息同时还需要删除
 	{
		while(q != NULL)
		{
			if(strcmp(flight_num, q->flight_num) == 0)
			{
				qr->next = q->next;     //要删除的乘客节点的前一个节点 直接指向要删除节点的后一个节点 进行删除操作
				free(q);
				q = NULL;
			}
			if(qr->next != NULL)
			{
				qr = qr->next;
				q = qr->next;
			}
		}
	}
}

int delete_passenger(passengerList *&PList, flightnode *&h, char *name,char *ID_num,char *phone_num)      //退票  删除顾客信息
{///按照乘客姓名查找该乘客结点，进行删除
	passengernode *p, *q = PList->head;     //p指向乘客链表的首节点 pr相当于乘客链表的头指针
	p = q->next;
	while(p!=NULL)
	{
		if((stricmp(name, p->name)==0) && (stricmp(ID_num,p->ID_num)==0) && stricmp(phone_num,p->phone_num)==0)//区别大小写
		{
			for(flightnode *f=h->next; f!=NULL; f=f->next)
			{
				if(strcmp(p->flight_num,f->flight_num) == 0)
				{
					f->left = f->left + p->ticket_num;
					f->isFull = 0;
					break;
				}
			}
			q->next = p->next;              //链表中删除顾客节点
			free(p);                         //释放结点
			printf("\t\t 乘客名字%s,身份证%s 手机号 %s退票成功!\n",name,ID_num,phone_num);
			return 1;
		}
		q = q->next;
		p = q->next;
	}
	printf("\t\t 无此顾客,无法退票!\n");
	return 0;
}

int check_passenger(passengerList *&PList, char *name, char *ID_num,char *phone_num)
{
	passengernode *p, *q = PList->head;         //p指针指向乘客链表的首节点 pr相当乘客链表的头指针
	p = q->next;
	while(p != NULL)
	{
		if((stricmp(name, p->name)==0) && (stricmp(ID_num,p->ID_num)==0) && (stricmp(phone_num,p->phone_num)==0))//区别大小写
		{
			printf("\n\t\t %s你已成功购买过票,您购买的航班号为:%s,您的订单号为:%d",p->name, p->flight_num, p->order_num);
			return 0;
		}
		else
		{
			q = q->next;
			p = q->next;
		}
	}
	printf("\n\t\t %s你没有购票记录,谢谢您的查询", name);
	return 0;
}

void cancel(passengerList *&PList,flightnode *&h)//删除函数调用
{
	char name[20],ID_num[20],phone_num[20];
	printf("\t\t 请输入您的姓名:");
	scanf("%s",name);
	printf("\t\t 请输入您的证件号:");
	scanf("%s",ID_num);
	printf("\t\t 请输入您的手机号:");
	scanf("%s",phone_num);
	delete_passenger(PList, h, name, ID_num,phone_num);
}

void passenger_check(passengerList *&PList)//订票函数调用
{
	char name[20],ID_num[20],phone_num[20];
	printf("\t\t 请输入您的名字:");
	scanf("%s",name);
	printf("\t\t 请输入您的证件号:");
	scanf("%s",ID_num);
	printf("\t\t 请输入您的手机号:");
	scanf("%s",phone_num);
	check_passenger(PList, name, ID_num,phone_num);
}

void modify_flight(flightnode *&h,passengerList *&PList)
{//通过复制函数把数据覆盖修改。
	flightnode *p=h->next;                                    //p指针航班链表的首节点
	char flight_num[10],start_time[10],end_time[10],day[10];
	char a;
	printf("\t\t********欢迎选乘翱安航班***************\n");
	printf("\t\t********航班信息修改*******************\n");
	printf("\t\t***************************************\n");
	printf("\t\t*         增加航班信息---1            *\n");
	printf("\t\t*         删除航班信息---2            *\n");
	printf("\t\t*         修改航班时间---3            *\n");
	printf("\t\t*         修改航班星期---4            *\n");
	printf("\t\t*****************************************");
	printf("\t\t 请管理员选择:");
	a = getch();
	printf("%c\n",a);
	if(a == '1')
		add_flight(h);
	else if(a == '2')
		delete_flight(h,PList);
	else if(a == '3')
	{
		printf("\t\t 请输入要修改的航班的航班号:");
		scanf("%s",flight_num);
		if(flight_num_check(p, flight_num) == 1)
		{
			printf("\t\t 请输入修改后的起飞时间:");
			scanf("%s",start_time);
			printf("\t\t 请输入修改后的抵达时间:");
			scanf("%s",end_time);
			for(; p!=NULL; p=p->next)
			{
				if(strcmp(flight_num, p->flight_num) == 0)
				{
					strcpy(p->start_time, start_time);
					strcpy(p->end_time, end_time);
					strcpy(p->day, day);
					printf("\t\t 航班%s 时间修改成功!\n",flight_num);
				}
			}
		}
	}
	else if(a == '4')
	{
		printf("\t\t 请输入要修改的航班的航班号:");
		scanf("%s",flight_num);
		if(flight_num_check(p, flight_num) == 1)
		{
			printf("\t\t 请输入修改后的星期:");
			scanf("%s",day);
			for(; p!=NULL; p=p->next)
			{
				if(strcmp(flight_num, p->flight_num) == 0)
				{
					strcpy(p->day, day);
					printf("\t\t 航班%s 星期几修改成功!\n",flight_num);
				}
			}
		}
	}
	else
		return;
}

enum Color//颜色常量定义
{
      black, blue, green, lakeBlue, red, purple, yellow, white, gray,
      lightBlue, lightGreen, lightSimpleGreen, lightRed, lightPurple, lightYellow, brightWhite
};

void setColor(unsigned short textColor=0, unsigned short backColor=7){
	char command[9]="color 07";		//默认颜色
	command[6]='0'+backColor;		//将backColor变量改为字符型
	command[7]='0'+textColor;		//将textColor变量改为字符型
	system(command);				//调用系统函数
}

void sum(flightnode *h,passengerList *&PList)
{
	flightnode *p = h;
	passengernode *q, *pr = PList->head;     //p指向乘客链表的首节点 pr相当于乘客链表的头指针
	q = pr->next;
	int mark = 0;
	printf("%-8s%-12s%-12s%-10s%-10s%-10s%-8s%-8s%-8s%-10s\n","航班号","起飞城市","抵达城市","起飞时间","抵达时间","星期几","价格","折扣","空座数","是否满仓");    //提示输入信息格式
	for(;p!=NULL; p=p->next)
	{
		printf("%-8s%-12s%-12s%-10s%-10s%-10s%-8.2f%-8.2f%-8d%-10d\n",p->flight_num, p->start_place, p->end_place, p->start_time,p->end_time,p->day, p->price, p->price_discount, p->left, p->isFull);    //输出相关信息
		mark = 1;
	}
	if(mark == 0)
		printf("\t\t  航班信息为空!\n");

	printf("%-8s%-8s%-8s%-8s%-8s%-8s\n","姓名","证件号","手机号","航班号","订单号","座位数");
	for(;q!=NULL; q=q->next)
	{
		printf("%-8s%-8s%-8s%-8s%-8d%-8d\n",q->name,q->ID_num,q->phone_num,q->flight_num,q->order_num,q->ticket_num);
		mark = 1;
	}
	if(mark == 0)
		printf("\t\t  乘客信息为空!\n");
}
int main()
{
	setColor(7,8);
	int t = 1;
	char c;
	flightnode *flight;    //定义航班链表的结构体指针
	passengernode *q;
	passengerList *PList;
	init_flight(flight);
	init_passengerList(PList);
	load_flight(flight);//文件
	load_passenger(PList);//文件
	while(t==1)
	{
	printf("\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◇◇◆◆◇◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◆◆◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◇◆◆◇◇◇◇◆◆◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◆◆◆◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◇◇◆◆◇◇◇◇◆◆◆◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◆◆◆◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◆◆◇◆◆◆◇◇◇◇◆◆◇◇◇◇◇◇◇◇◇◇◇◇◇◆◇◇◇◇◇◆◆◇◇◇◇◆◆◆◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◆◆◆◆◆◆◆◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇◇◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◆◆◆◆◆◆◇◇◆◆◆◆◆◆◆◇◇◇◇◇◇◇◇◆◆◆◆◆◆◆◆◆◆◇◇◇◆◆◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◆◆◆◇◆◆◆◆◆◆◆◆◆◆◇◇◇◇◇◇◇◇◇◆◆◇◇◇◆◇◇◆◆◇◇◆◆◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◆◆◆◆◆◇◇◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◆◆◆◇◇◆◆◆◇◇◆◆◆◆◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◆◆◆◆◆◇◆◆◇◆◆◆◇◇◇◇◇◇◇◇◇◇◇◆◇◇◆◆◆◇◇◇◇◆◆◆◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◆◆◆◇◆◇◇◆◆◆◆◆◇◇◇◇◇◇◇◇◇◇◇◇◇◆◆◆◇◇◇◇◇◇◆◆◆◆◇◇◇◇◇\n");
    printf("\t\t◇◇◆◆◆◆◆◆◆◆◇◇◆◇◇◆◆◇◇◇◇◇◇◇◇◇◇◇◇◆◆◆◇◇◇◇◇◇◇◇◆◆◆◇◇◇◇◇\n");
    printf("\t\t◇◇◆◆◆◆◆◆◇◆◇◇◆◇◇◆◆◇◇◇◇◇◇◇◇◇◇◇◆◆◆◇◇◇◆◆◆◆◆◆◆◆◆◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◆◆◆◆◇◆◇◇◆◇◇◆◆◇◇◇◇◇◇◇◇◇◇◇◆◇◆◆◆◆◆◆◆◆◆◆◆◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◆◆◇◆◆◆◇◇◆◇◇◆◆◇◇◇◇◇◇◇◇◇◇◇◇◇◇◆◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◆◆◇◆◇◆◇◆◆◇◇◆◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◆◆◇◇◇◆◇◆◆◇◇◆◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◆◆◇◆◆◇◆◇◆◆◇◇◆◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◆◆◇◇◆◆◆◆◆◇◇◇◆◆◇◆◆◇◇◇◇◇◇◇◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◇◇◇◇\n");
    printf("\t\t◇◇◆◆◇◇◇◇◆◆◆◆◇◇◇◆◆◆◆◆◆◇◇◇◇◇◇◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◇◇◇◇\n");
    printf("\t\t◇◇◆◆◇◇◇◇◆◆◆◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◇◇◇◇◆◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇◇\n");
    printf("\t\t\t*****************航班订票系统主菜单*********************\n");
    printf("\t\t\t*                录入航班信息请选择1                   *\n");
    printf("\t\t\t*                查询航班信息请选择2                   *\n");
    printf("\t\t\t*                乘客订购机票请选择3                   *\n");
    printf("\t\t\t*                乘客退订机票请选择4                   *\n");
    printf("\t\t\t*                查询订票信息请选择5                   *\n");
	printf("\t\t\t*          航班和乘客信息汇总请选择6                   *\n");
    printf("\t\t\t*                管理人员登录请选择7                   *\n");
    printf("\t\t\t*               退出航班系统请选择 0                   *\n");
	printf("\t\t\t*****************##################*********************\n");
    	c = getch();
    	printf("%c\n",c);
    	system("cls");
    	if(c == '1')
    	{
    		add_flight(flight);
    		getch();
    		system("cls");
		}
		else if(c == '2')
		{
			flight_check(flight);
			getch();
			system("cls");
		}
		else if(c == '3')
		{
			book(flight,PList);
			getch();
			system("cls");
		}
		else if(c == '4')
		{
			cancel(PList,flight);
			getch();
			system("cls");
		}
		else if(c == '5')
		{
			passenger_check(PList);
			getch();
			system("cls");
		}
		else if(c == '6')
		{
			sum(flight,PList);
			getch();
			system("cls");
		}
		else if(c == '7')
		{
			if( User()==1)
			 {modify_flight(flight,PList);
			 getch();
			 system("cls");}
			else
				system("cls");
		}
		else if(c == '0')
		{
			printf("\t\t\t 欢迎您使用本系统  再见");
			t = 0;
		}
	}
	save_flight(flight);//保存到航班文件
	save_passenger(PList);//保存到乘客文件
	return 0;
}
