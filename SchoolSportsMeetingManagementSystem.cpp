#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10 //学院数目
//定义一个结构体
typedef struct record
{
    char events[40];     //项目名称
    char name[N][40];     //学院名称
    float score[N];       //单项成绩
    int point[N];          //积分
    char player[N][40];        //选手
    int rank[N];            //单项名次
    struct record *next; //指向下一节点的指针
} whole;

typedef struct College
{
    char name[40]; //学院名
    float sum;      //总分
} college;
void events_rank(whole *L);
//创建链表，将新生成的节点插入到链表的表头
void create_list(whole *L, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        whole *p;
        //将新生成的节点插入到链表中
        p = NULL;
        p = (whole *)malloc(sizeof(whole));
        int j;
        FILE *file3=fopen("学院.txt","r");
        printf("请输入第%d个比赛项目名称:", i + 1);
        scanf("%s", p->events);
        for (j = 0; j < N; j++)
        {
            fscanf(file3, "%s", ((p->name) + j));
            printf("请输入%s的该项目的成绩:",(p->name) + j);
            scanf("%f", (p->score) + j);
            printf("请输入%s的参加该项目的选手:",(p->name) + j);
            scanf("%s",(p->player) + j);
        }
        p->next = L->next;
        L->next = p;
    }
}

//查找项目信息
void search_list(whole *L)
{
    int k;
    char n[40];
    whole *p = L->next;
    int item;
    if (p == NULL)
    {
        printf("数据为空，无法查找！");
        return;
    }
    printf("\n\n");
    printf("\t\t\t┌───────────────────────────────────────────────┐\n");
    printf("\t\t\t│                                               │\n");
    printf("\t\t\t│                   查找信息                    │\n");
    printf("\t\t\t│                                               │\n");
    printf("\t\t\t├┬─────────────────────────────────────────────┬┤\n");
    printf("\t\t\t││                1 按项目名                   ││\n");
    printf("\t\t\t││                2 按学院名                   ││\n");
    printf("\t\t\t││                3 按选手名                   ││\n");
    printf("\t\t\t│┼─────────────────────────────────────────────┼│\n");
    printf("\t\t\t└───────────────────────────────────────────────┘\n");
    scanf("%d",&item);
    if(item == 1)
    {
        printf("请输入您要查找的项目名称:");
        scanf("%s", n);
        while (strcmp(p->events, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到相关信息\n");
                return;
            }
        }
        printf("该项目的相关信息如下:\n");
        printf("学院名称\t单项成绩\t选手\n\n");
        for (k = 0; k < N; k++)
        {
            printf("%s\t\t", *((p->name) + k));
            printf("%.2f\t\t", *((p->score) + k));
            printf("%s\t\n", *((p->player) + k));
        }
        printf("\n\n");
    }
    if(item == 2)
    {
        printf("请输入您要查找的学院名称:");
        scanf("%s", n);
        printf("该项目的相关信息如下:\n");
        printf("学院名称\t单项成绩\t选手\n\n");
        while(p!=NULL)
        {
            for (k = 0; k<N; k++){
                if (strcmp(*((p->name)+k), n) == 0){
                    printf("%s\t\t", *((p->name) + k));
                    printf("%.2f\t\t", *((p->score) + k));
                    printf("%s\t\n", *((p->player) + k));
                }
            }
            p=p->next;
        }
        printf("\n\n");
    }
    if(item == 3)
    {
        printf("请输入您要查找的选手名称:");
        scanf("%s", n);
        printf("该项目的相关信息如下:\n");
        printf("学院名称\t单项成绩\t选手\n\n");
        while(p!=NULL)
        {
            for (k = 0; k<N; k++){
                if (strcmp(*((p->player)+k), n) == 0){
                    printf("%s\t\t", *((p->name) + k));
                    printf("%.2f\t\t", *((p->score) + k));
                    printf("%s\t\n", *((p->player) + k));
                }
            }
            p=p->next;
        }
        printf("\n\n");
    }
}

//修改项目
void modify_list(whole *L)
{
    int item, k, a;
    char n[40], m[40];
    whole *p = L->next;
    if (p == NULL)
        printf("数据为空，无法修改！");
    else
    {
        printf("请输入您要修改的项目名称:");
        scanf("%s", n);
        while (strcmp(p->events, n) != 0)
        {
            p = p->next;
            if (p == NULL)
            {
                printf("没有找到此项目\n");
                return;
            }
        }
        printf("您是否需要修改项目名称(是输入1，不是输入0):");
        scanf("%d", &a);
        if (a == 1)
        {
            printf("请输入您修改后的项目名称:");
            scanf("%s", m);
            strcpy(p->events, m);
            printf("修改成功！");
        }
        else if (a == 0)
        {
            printf("请输入您要修改的学院:");
            scanf("%s", n);
            for (k = 0; k < N; k++)
            {
                if (*((p->name) + k) == n)
                    printf(*((p->name) + k));
                    break;
                    if (k=N-1)
                    {
                        printf("无此学院记录");
                        return;
                    }
            }
            printf("请输入你要修改的项目信息类型:\n");
            printf("1、学院名称\n2、该学院该项目的成绩\n");
            scanf("%d", &item);
            switch (item)
            {
            case 1:
                printf("请输入修改后的学院名称:");
                scanf("%s", m);
                strcpy(*((p->name) + k), m);
                printf("修改成功");
                break;
            case 2:
                printf("请输入您修改后的该学院该项目的成绩:");
                scanf("%f", (p->score) + k);
                printf("修改成功");
                break;
            default:
                printf("您输入的指令错误!");
                break;
            }
        }
        else
            printf("您输入错误！");
    }
}

//删除项目
void delete_list(whole *L)
{
    char n[40];
    whole *p = L->next, *pre = L; //定义p指针指向头节点的指向，定义pre指向头节点，pre始终指向p的前驱节点
    if (p == NULL)
        printf("数据为空，无法删除！");
    else
    {
        printf("请输入您要删除的项目名称:");
        scanf("%s", n);
        while (strcmp(p->events, n) != 0)
        {
            pre = p;
            p = pre->next;
            if (p == NULL)
            {
                printf("没有找到相关信息，无法删除\n");
                return;
            }
        }
        pre->next = p->next;
        free(p);
        printf("删除成功");
    }
}

//项目成绩排名

void events_rank(whole *L)
{
    int i, j, k;
    float t;
    char temp1[40] = {' '};
    char temp2[40] = {' '};
    whole *p = L->next;
    if (p == NULL)
        printf("数据为空，无法排序！");
    else
    {
        while (p != NULL)
        {
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N - i - 1; j++)
                {
                    if (*((p->score) + j) < *((p->score) + j + 1))
                    {
                        t = *((p->score) + j);
                        *((p->score) + j) = *((p->score) + j + 1);
                        *((p->score) + j + 1) = t;
                        strcpy(temp1, *((p->name) + j));
                        strcpy(*((p->name) + j), *((p->name) + j + 1));
                        strcpy(*((p->name) + j + 1), temp1);
                        strcpy(temp2, *((p->player) + j));
                        strcpy(*((p->player) + j), *((p->player) + j + 1));
                        strcpy(*((p->player) + j + 1), temp2);
                    }
                }
            }
            for (k = 0; k < N; k++)
                *((p->rank) + k) = k + 1;
                if(k==N){
                    *((p->point) + 0) = 9;
                    *((p->point) + 1) = 7;
                    *((p->point) + 2) = 6;
                    *((p->point) + 3) = 5;
                    *((p->point) + 4) = 4;
                    *((p->point) + 5) = 3;
                    *((p->point) + 6) = 2;
                    *((p->point) + 7) = 1;
                    *((p->point) + 8) = 0;
                    *((p->point) + 9) = 0;
                }
            p = p->next;
        }
    }
}

//总成绩和排名;
void sum_rank(whole *L)
{
    int i, j, k;
    float t;
    college s[N],s0;

    whole *p = L->next;
    if (p == NULL)
        printf("数据为空！");
    else{
        for (i = 0; i < N; i++)
        {
            strcpy(s[i].name, *((p->name) + N - i - 1));
            s[i].sum = 0;
        }
        while (p != NULL)
        {
            for(i=0;i<N;i++)
                s[i].sum += *((p->score) + i);
            p = p->next;
        }
        for (j = 0; j < N; j++)
        {
            for (k = 0; k < N - j - 1; k++)
            {
                if(s[k].sum>s[k+1].sum){
                    s0 = s[k];
                    s[k] = s[k + 1];
                    s[k + 1]= s0;
                }
            }
        }
        p = L->next;
        printf("学院名称\t总成绩\t\t总排名\n");
        for (i = N - 1; i >= 0; i--)
        {
            printf("%s\t\t", s[i].name);
            printf("%.2f\t\t", s[i].sum);
            printf("%d\t\t", N - i);
            printf("\n");

        }
        printf("是否写入总成绩排名排名.txt(是输入1，不是输入0):");
        int a;
        scanf("%d",&a);
        if (a == 1)
        {
            FILE *file2=fopen("总成绩排名.txt","w");
            if(file2==NULL)
            {
                return;
            }
            fprintf(file2, "学院名称\t总成绩\t\t总排名\n");
            for (i = N - 1; i >= 0; i--)
            {
                fprintf(file2, "%s\t\t", s[i].name);
                fprintf(file2, "%.2f\t\t", s[i].sum);
                fprintf(file2, "%d\t\t", N - i);
                fprintf(file2,"\n");
            }
            printf("写入完成！！！");
            fclose(file2);
        }
        else
        {
            return;
        }
    }
}
//输出全部项目信息
void output(whole *L)
{
    int k,a;
    whole *p = L->next;
    while (p != NULL)
    {
        printf("\t\t\t项目:%s\n\n", p->events);
        printf("学院名称\t积分\t\t单项成绩\t单项名次\t选手\n\n");
        for (k = 0; k < N; k++)
        {
            printf("%s\t\t", *((p->name) + k));
            printf("%d\t\t", *((p->point) + k));
            printf("%.2f\t\t", *((p->score) + k));
            printf("%d\t\t", *((p->rank) + k));
            printf("%s\t\n", *((p->player) + k));
        }
        printf("\n\n");
        p = p->next;
    }
}
//写入文件
void write(whole *L)
{
    int k;
    whole *p = L->next;
    FILE *file1=fopen("全部项目信息.txt","w");
    if(file1==NULL || L == NULL)
	{
		return;
	}
    while (p != NULL)
    {
        fprintf(file1, "\t\t\t项目:%s\n\n", p->events);
        fprintf(file1, "学院名称\t积分\t\t单项成绩\t单项名次\t选手\n\n");
        for (k = 0; k < N; k++)
        {
            fprintf(file1, "%s\t\t", *((p->name) + k));
            fprintf(file1, "%s\t\t", *((p->player) + k));
            fprintf(file1, "%.2f\t\t", *((p->score) + k));
            fprintf(file1, "%d\t\t", *((p->rank) + k));
            fprintf(file1,"%s\t\n", *((p->player) + k));
        }
        fprintf(file1, "\n\n");
        p = p->next;
    }
    fclose(file1);
}
//校运动会项目管理系统的菜单
void menu();
void menu()
{
    printf("\n\n");
    printf("\t\t\t┌───────────────────────────────────────────────┐\n");
    printf("\t\t\t│                                               │\n");
    printf("\t\t\t│         桂林航天工业学院校运会管理系统        │\n");
    printf("\t\t\t│                                               │\n");
    printf("\t\t\t├┬─────────────────────────────────────────────┬┤\n");
    printf("\t\t\t││             1 录入项目信息                  ││\n");
    printf("\t\t\t││             2 查找项目信息                  ││\n");
    printf("\t\t\t││             3 修改项目信息                  ││\n");
    printf("\t\t\t││             4 删除项目信息                  ││\n");
    printf("\t\t\t││             5 项目成绩排名                  ││\n");
    printf("\t\t\t││             6 总成绩和排名                  ││\n");
    printf("\t\t\t││             7 导出项目信息                  ││\n");
    printf("\t\t\t││             0 退出管理系统                  ││\n");
    printf("\t\t\t│┼─────────────────────────────────────────────┼│\n");
    printf("\t\t\t└───────────────────────────────────────────────┘\n");
}
//校运动会项目管理系统的主函数入口
int main()
{
    int item, n;  //item用于接收输入的命令，n用于接收输入的项目数
    whole *L = NULL;  //初始化一个头节点
    L = (whole *)malloc(sizeof(whole)); //为头节点开辟内存空间
    L->next = NULL;                   //将头节点的指针域置空
    do
    {
        system("cls");
        menu(); //菜单
        printf("\t\t\t请输入相应的数字，进行相应的操作:");
        scanf("%d", &item);
        system("cls");
        switch (item)
        {
        case 1:
            printf("请输入您要录入的项目数目:");
            scanf("%d", &n);
            create_list(L, n); //创建项目链表节点
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 2:
            search_list(L); //查找项目的相关信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 3:
            modify_list(L); //修改项目信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 4:
            delete_list(L); //删除项目的信息
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 5:
            events_rank(L); //学院成绩排名
            output(L);  //输出学院成绩排名
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 6:
            sum_rank(L); //总成绩和排名
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 7:
            events_rank(L);
            write(L);
            getchar();
            printf("\n请按任意键返回主菜单\n");
            getchar();
            system("cls");
            break;
        case 0:
            printf("\t\t\t┌───────────────────────────────────────────────┐\n");
            printf("\t\t\t│                                               │\n");
            printf("\t\t\t│                   校运会管理系统                │\n");
            printf("\t\t\t│                                               │\n");
            printf("\t\t\t├┬─────────────────────────────────────────────┬┤\n");
            printf("\t\t\t││                   已退出                    ││\n");
            printf("\t\t\t│┼─────────────────────────────────────────────┼│\n");
            printf("\t\t\t└───────────────────────────────────────────────┘\n");
            exit(0);
        default:
            printf("您输入的指令不正确，请重新输入");
        }
        printf("\n\n");
    } while (item);
    return 0;
}