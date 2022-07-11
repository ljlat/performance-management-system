#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#define maxsize 1024
typedef struct Student
{
    char SN0[10];    //学号
    char NAME[5];  //姓名
    char major[7]; //专业
    char classes[12]; //班级
    int Chinese;
    int Math;
    int English;
    int password;
} STUDENT;

int coursekey=0;
int index;
char temp1;
char temp2[20];
int select;
char studentno[20];

typedef struct   STUlist
{
    STUDENT stu[maxsize];
    int len;
} STULIST;

void initlist(STULIST *L);
void sortChinese(STULIST *L,int k);
void sortMath(STULIST *L,int k);
void sortEnglish(STULIST *L,int k);
int GetTxtLine(char *filename);
void modify(STULIST *stu,STUDENT s);
//显示所有学生信息
void ListDisplay(STULIST *L)
{
    int i,j;
    printf("学号\t\t姓名\t专业\t班级\t\t语文\t数学\t英语\t密码\n");
    for(i=0; i<L->len; i++)
    {
        printf("%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d",
               L->stu[i].SN0,L->stu[i].NAME,L->stu[i].major,L->stu[i].classes,
               L->stu[i].Chinese,L->stu[i].Math,L->stu[i].English,L->stu[i].password);
        printf("\n");
    }
}
//插入学生信息
void ListInsert(STULIST *L,STUDENT s)
{
    int len=L->len;
    L->stu[len]=s;
    L->len=L->len+1;
}
//通过专业查询
void  ListSelectByMajor(STULIST *L,char major[])
{
    printf("学号\t\t姓名\t专业\t班级\t\t语文\t数学\t英语\t密码\n");
    for (int i = 0; i < L->len; i++)
        if (!strcmp(L->stu[i].major,major))

            printf("%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d\n",
                   L->stu[i].SN0,L->stu[i].NAME,L->stu[i].major,L->stu[i].classes,
                   L->stu[i].Chinese,L->stu[i].Math,L->stu[i].English,L->stu[i].password);
}

//通过班级查询
void  ListSelectByclasses(STULIST *L,char classes[])
{
    printf("学号\t\t姓名\t专业\t班级\t\t语文\t数学\t英语\t密码\n");
    for (int i = 0; i < L->len; i++)
        if (!strcmp(L->stu[i].classes,classes))
            printf("%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d\n",
                   L->stu[i].SN0,L->stu[i].NAME,L->stu[i].major,L->stu[i].classes,
                   L->stu[i].Chinese,L->stu[i].Math,L->stu[i].English,L->stu[i].password);
}
//通过学号查询
void  ListSelectBySno(STULIST *L,char SNO[])
{
    printf("学号\t\t姓名\t专业\t班级\t\t语文\t数学\t英语\t密码\n");
    for (int i = 0; i < L->len; i++)
        if (!strcmp(L->stu[i].SN0,SNO))
            printf("%s\t%s\t%s\t%s\t%d\t%d\t%d\t%d\n",
                   L->stu[i].SN0,L->stu[i].NAME,L->stu[i].major,L->stu[i].classes,
                   L->stu[i].Chinese,L->stu[i].Math,L->stu[i].English,L->stu[i].password);
}

//通过课程查询
void  ListSelectbyCourse(STULIST *L,char course[])
{
    if (!strcmp(course,"Chinese"))
    {
        printf("学号\t\t姓名\t专业\t班级\t\t语文\n");
        for (int i = 0; i < L->len; i++)
            printf("%s\t%s\t%s\t%s\t%d\n",
                   L->stu[i].SN0,L->stu[i].NAME,L->stu[i].major,L->stu[i].classes,
                   L->stu[i].Chinese);
    }
    else if (!strcmp(course,"Math"))
    {
        printf("学号\t\t姓名\t专业\t班级\t\t数学\n");
        for (int i = 0; i < L->len; i++)
            printf("%s\t%s\t%s\t%s\t%d\n",
                   L->stu[i].SN0,L->stu[i].NAME,L->stu[i].major,L->stu[i].classes,
                   L->stu[i].Math);
    }
    else if (!strcmp(course,"English"))
    {
        printf("学号\t\t姓名\t专业\t班级\t\t英语\n");
        for (int i = 0; i < L->len; i++)
            printf("%s\t%s\t%s\t%s\t%d\n",
                   L->stu[i].SN0,L->stu[i].NAME,L->stu[i].major,L->stu[i].classes,
                   L->stu[i].English);
    }
    else
        printf("error\n");
}

//通过课程 专业 班级
void  ListSelect(STULIST *L,char course[],char major[],char classes[],int key)
{
    STULIST *stutemp;
    stutemp=(STULIST *)malloc(sizeof(STULIST));
    initlist(stutemp);
    for(int i=0; i<L->len; i++)
        if((!strcmp(L->stu[i].major,major))&&(!strcmp(L->stu[i].classes,classes)))
            ListInsert(stutemp,L->stu[i]);
    if(stutemp->len==0)
    {
        printf("no student");
        return;
    }
    if (!strcmp(course,"Chinese"))
    {
        printf("学号\t\t姓名\t专业\t班级\t\t语文\n");
        sortChinese(stutemp,key);
        for (int i = 0; i < stutemp->len; i++)
            printf("%s\t%s\t%s\t%s\t%d\n",
                   stutemp->stu[i].SN0,stutemp->stu[i].NAME,stutemp->stu[i].major,stutemp->stu[i].classes,
                   stutemp->stu[i].Chinese);
    }
    else if (!strcmp(course,"Math"))
    {
        printf("学号\t\t姓名\t专业\t班级\t\t数学\n");
        sortMath(stutemp,key);
        for (int i = 0; i < stutemp->len; i++)
            printf("%s\t%s\t%s\t%s\t%d\n",
                   stutemp->stu[i].SN0,stutemp->stu[i].NAME,stutemp->stu[i].major,stutemp->stu[i].classes,
                   stutemp->stu[i].Math);
    }
    else if (!strcmp(course,"English"))
    {
        printf("学号\t\t姓名\t专业\t班级\t\t英语\n");
        sortEnglish(stutemp,key);
        for (int i = 0; i < stutemp->len; i++)
            printf("%s\t%s\t%s\t%s\t%d\n",
                   stutemp->stu[i].SN0,stutemp->stu[i].NAME,stutemp->stu[i].major,stutemp->stu[i].classes,
                   stutemp->stu[i].English);
    }
    else
        printf("error\n");
}
//获取最高分
int getMax(STULIST *L,int coursekey)
{
    int max=0;
    if(coursekey==1)
    {
        for(int i=0; i<L->len; i++)
            if(L->stu[i].Chinese>max)
                max=L->stu[i].Chinese;
    }
    else if(coursekey==2)
    {
        for(int i=0; i<L->len; i++)
            if(L->stu[i].Math>max)
                max=L->stu[i].Math;
    }
    else if(coursekey==3)
    {
        for(int i=0; i<L->len; i++)
            if(L->stu[i].English>max)
                max=L->stu[i].English;
    }
    return max;
}
//获取最低分
int getMin(STULIST *L,int coursekey)
{
    int max=100;
    if(coursekey==1)
    {
        for(int i=0; i<L->len; i++)
            if(L->stu[i].Chinese<max)
                max=L->stu[i].Chinese;
    }
    else if(coursekey==2)
    {
        for(int i=0; i<L->len; i++)
            if(L->stu[i].Math<max)
                max=L->stu[i].Math;
    }
    else if(coursekey==3)
    {
        for(int i=0; i<L->len; i++)
            if(L->stu[i].English>max)
                max=L->stu[i].English;
    }
    return max;
}

//获取平均分
int getAvg(STULIST *L,int coursekey)
{
    int max=0;
    if(coursekey==1)
    {
        for(int i=0; i<L->len; i++)
            max+=L->stu[i].Chinese;
    }
    else if(coursekey==2)
    {
        for(int i=0; i<L->len; i++)
            max+=L->stu[i].Math;
    }
    else if(coursekey==3)
    {
        for(int i=0; i<L->len; i++)
            max+=L->stu[i].English;
    }
    return max/L->len;
}

//获取各个分数人数
int getNum(STULIST *L,int coursekey,int max,int min)
{
    int num=0;
    if(coursekey==1)
    {
        for(int i=0; i<L->len; i++)
            if(L->stu[i].Chinese>=min&&L->stu[i].Chinese<=max)
                num++;
    }
    else if(coursekey==2)
    {
        for(int i=0; i<L->len; i++)
            if(L->stu[i].Math>=min&&L->stu[i].Math<=max)
                num++;
    }
    else if(coursekey==3)
    {
        for(int i=0; i<L->len; i++)
            if(L->stu[i].English>=min&&L->stu[i].English<=max)
                num++;
    }
    return num;
}
//指定课程，班级 统计分数
void count(STULIST *L,char course[],char classes[])
{
    STULIST *stu;
    stu=(STULIST *)malloc(sizeof(STULIST));
    initlist(stu);
    int coursekey=0;
    printf("\t\t%s\n",course);
    if(!strcmp(course,"Chinese"))
        coursekey=1;
    else if(!strcmp(course,"Math"))
        coursekey=2;
    else if(!strcmp(course,"English"))
        coursekey=3;
    for(int i=0; i<L->len; i++)
    {
        if(!strcmp(L->stu[i].classes,classes))
            ListInsert(stu,L->stu[i]);
    }

    int avg=getAvg(stu,coursekey);
    int max=getMax(stu,coursekey);
    int min=getMin(stu,coursekey);
    float num=stu->len;
    int num100_90=getNum(stu,coursekey,100,90);
    int num90_80=getNum(stu,coursekey,89,80);
    int num80_70=getNum(stu,coursekey,79,70);
    int num70_60=getNum(stu,coursekey,69,60);
    int num60_0=getNum(stu,coursekey,59,0);
    printf("分数\t100-90\t89-80\t79-70\t69-60\t60以下\n");
    printf("人数\t%d\t%d\t%d\t%d\t%d\n",num100_90,num90_80,num80_70,num70_60,num60_0);
    printf("比例\t%.2f%%\t%.2f%%\t%.2f%%\t%.2f%%\t%.2f%%\n",num100_90*100/num,num90_80*100/num,num80_70*100/num,num70_60*100/num,num60_0*100/num);
    printf("最高分：%d\t最低分：%d\t平均分：%d\n",max,min,avg);
}



//删除学生信息
void ListDelete(STULIST *L,char SNO[])
{
    int i;
    for (i = 0; i < L->len; i++)
    {
        if (!strcmp(L->stu[i].SN0,SNO))
            break;
    }
    for (int j = i; j < L->len; j++)
    {
        L->stu[j-1]=L->stu[j];
    }
    L->len--;
}
//交换位置
void Listswap(STULIST *L,int i,int j)
{
    STUDENT temp;
    temp=L->stu[i];
    L->stu[i]=L->stu[j];
    L->stu[j]=temp;
}

//按语文成绩排序
void sortChinese(STULIST *L,int k)
{
    if (k==1)
    {
        for (int i = 0; i < L->len; i++)
            for (int j = i; j < L->len; j++)
                if (L->stu[i].Chinese>L->stu[j].Chinese)
                    Listswap(L,i,j);
    }
    else
    {
        for (int i = 0; i < L->len; i++)
            for (int j = i; j < L->len; j++)
                if (L->stu[i].Chinese<L->stu[j].Chinese)
                    Listswap(L,i,j);
    }
}
//按数学成绩排序
void sortMath(STULIST *L,int k)
{
    if (k==1)
    {
        for (int i = 0; i < L->len; i++)
            for (int j = i; j < L->len; j++)
                if (L->stu[i].Math>L->stu[j].Math)
                    Listswap(L,i,j);

    }

    else
    {
        for (int i = 0; i < L->len; i++)
            for (int j = i; j < L->len; j++)
                if (L->stu[i].Math<L->stu[j].Math)
                    Listswap(L,i,j);
    }
}
//按英语成绩排序
void sortEnglish(STULIST *L,int k)
{
    if (k==1)
    {
        for (int i = 0; i < L->len; i++)
            for (int j = i; j < L->len; j++)
                if (L->stu[i].English>L->stu[j].English)
                    Listswap(L,i,j);
    }
    else
    {
        for (int i = 0; i < L->len; i++)
            for (int j = i; j < L->len; j++)
                if (L->stu[i].English<L->stu[j].English)
                    Listswap(L,i,j);
    }
}

//初始化
void initlist(STULIST *L)
{
    L->len=0;
}

//保存某个学生
void write(STUDENT *stu)
{
    FILE *fp;
    int i;
    fp=fopen("test1.txt","a");
    if(fp==NULL)
    {
        printf("not file\n");
        return;
    }
    fprintf(fp,"\n%s\t",stu->SN0);
    fprintf(fp,"%s\t",stu->NAME);
    fprintf(fp,"%s\t",stu->major);
    fprintf(fp,"%s\t\t",stu->classes);
    fprintf(fp,"%d\t",stu->Chinese);
    fprintf(fp,"%d\t",stu->Math);
    fprintf(fp,"%d\t",stu->English);
    fprintf(fp,"%d",stu->password);
    fclose(fp);

}


//保存学生数据
void save( STULIST *L)
{
    FILE *fp;
    int i;
    fp=fopen("test1.txt","w");
    if(fp==NULL)
    {
        printf("not file\n");
        return;
    }
    fprintf(fp,"学号\t\t姓名\t专业\t班级\t\t语文\t数学\t英语\t密码");
    fclose(fp);
    for(i=0; i<L->len; i++)
        write(&L->stu[i]);
}



STULIST *  open()
{
    int n;
    n=GetTxtLine("test1.txt");
    FILE *fp;
    STULIST *stu;
    stu=(STULIST *)malloc(sizeof(STULIST));
    initlist(stu);
    fp=fopen("test1.txt","r");
    if(fp==NULL)
    {
        printf("not file\n");
        return NULL;
    }
    char temp[20];
    fscanf(fp,"%s\t\t%s\t%s\t%s\t\t%s\t%s\t%s\%s\n",temp,temp,temp,temp,temp,temp,temp,temp);
    for(int i=0; i<n-1; i++)
    {
        fscanf(fp,"%s",stu->stu[i].SN0);
        fscanf(fp,"%s",stu->stu[i].NAME);
        fscanf(fp,"%s",stu->stu[i].major);
        fscanf(fp,"%s",stu->stu[i].classes);
        fscanf(fp,"%d",&stu->stu[i].Chinese);
        fscanf(fp,"%d",&stu->stu[i].Math);
        fscanf(fp,"%d",&stu->stu[i].English);
        fscanf(fp,"%d",&stu->stu[i].password);
        fscanf(fp,"\n",temp);
    }
    fclose(fp);
    stu->len=n-1;
    ListDisplay(stu);
    return stu;
}

//得到学生个数
int GetTxtLine(char *filename)
{
    FILE *fp;
    int n = 1;
    int ch;
    if((fp = fopen(filename,"r")) == NULL)
        fprintf(stderr,"open file  error! %s\n",strerror(errno));
    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n')
            n++;
    }

    fclose(fp);
    return n;
}
STULIST * create()
{
    STUDENT student1= {"118000001","jake","major1","classes11",82,81,63,123};
    STUDENT student2= {"118000002","Bill","major1","classes11",71,92,75,123};
    STUDENT student3= {"118000003","jack","major2","classes21",63,22,55,123};
    STUDENT student4= {"118000004","mark","major2","classes22",56,73,66,123};
    STUDENT student5= {"118000005","Jame","major1","classes12",85,81,84,123};
    STUDENT student6= {"118000006","jake","major1","classes11",82,87,92,123};
    STUDENT student7= {"118000007","Jsep","major1","classes11",90,65,73,123};
    STUDENT student8= {"118000008","Gary","major1","classes11",87,90,67,123};
    STUDENT student9= {"118000009","Lili","major1","classes11",85,74,78,123};
    STULIST *stu;
    stu=(STULIST *)malloc(sizeof(STULIST));
    initlist(stu);
    ListInsert(stu,student1);
    ListInsert(stu,student2);
    ListInsert(stu,student3);
    ListInsert(stu,student4);
    ListInsert(stu,student5);
    ListInsert(stu,student6);
    ListInsert(stu,student7);
    ListInsert(stu,student8);
    ListInsert(stu,student9);
    return stu;
}

//查询
void menu_3(STULIST *stu)
{
    printf("1:按专业查询\t2:按班级查询\t3:按学号查询\t4:按指定课程查询\t 0:返回主菜单\n");
    scanf("%d",&select);
    getchar();
    switch(select)
    {
    case 1:
        printf("请输入专业(如:major1)\n");
        char major[10];
        scanf("%s",major);
        getchar();
        ListSelectByMajor(stu,major);
        printf("按任意键返回主菜单\n");
        gets(temp2);
        break;

    case 2:
        printf("请输入班级(如:classes11)\n");
        char classes[10];
        scanf("%s",classes);
        getchar();
        ListSelectByclasses(stu,classes);
        printf("按任意键返回主菜单\n");
        gets(temp2);
        break;

    case 3:
        printf("请输入学号(如:118000001)\n");
        char sno[10];
        scanf("%s",sno);
        getchar();
        ListSelectBySno(stu,sno);
        printf("按任意键返回主菜单\n");
        gets(temp2);
        break;

    case 4:
        printf("请输入课程(如:Math)\n");
        char course[10];
        scanf("%s",course);
        getchar();
        ListSelectbyCourse(stu,course);
        printf("按任意键返回主菜单\n");
        gets(temp2);
        break;

    case 5:
        return;
    }

}

//浏览
void menu_4(STULIST *stu)
{
    char course[20];
    char major[20];
    char classes[20];
    int keyword;
    printf("请输入课程 专业 班级 排序方式(1：升序\t2：降序)\n");
    scanf("%s %s %s %d",course,major,classes,&keyword);
    gets(temp2);
    ListSelect(stu,course,major,classes,keyword);

}

//统计
void menu_5(STULIST *stu)
{
    char course[20];
    char classes[20];
    printf("请输入课程 班级\n");
    scanf("%s %s",course,classes);
    gets(temp2);
    count(stu,course,classes);
}

//修改功能
void menu_6(STULIST *stu)
{
    char sno[20];
    printf("请输入学生学号\n");
    scanf("%s",sno);
    ListSelectBySno(stu,sno);
    char name[20];
    char major[20];
    char classes[20];
    int Chinese;
    int math;
    int english;
    int password;
    printf("请输入学生信息\n");
    printf("姓名 专业 班级 语文 数学 英语 密码\n");
    scanf("%s %s %s %d %d %d %d",name,major,classes,&Chinese,&math,&english,&password);
    gets(temp2);
    STUDENT s;
    strcpy(s.SN0,sno);
    strcpy(s.NAME,name);
    strcpy(s.major,major);
    strcpy(s.classes,classes);
    s.Chinese=Chinese;
    s.Math=math;
    s.English=english;
    s.password=password;
    modify(stu,s);
}

//删除学生
void menu_7(STULIST *stu)
{
    char sno[20];
    printf("请输入学生学号\n");
    scanf("%s",sno);
    gets(temp2);
    ListDelete(stu,sno);
}
//修改学生信息
void modify(STULIST *stu,STUDENT s)
{
    int i;
    for(i=0;i<stu->len;i++)
    {
        if(!strcmp(stu->stu[i].SN0,s.SN0))
        {
            strcpy( stu->stu[i].NAME,s.NAME);
            strcpy( stu->stu[i].major,s.major);
            strcpy( stu->stu[i].classes,s.classes);
            stu->stu[i].Chinese=s.Chinese;
            stu->stu[i].Math=s.Math;
            stu->stu[i].English=s.English;
            stu->stu[i].password=s.password;

        }
    }
    ListDisplay(stu);

}

//管理员功能
void  manage(STULIST *stu)
{
      while(1)
    {
        system("cls");
        printf("================================\n");
        printf("请选择操作：\n");
        printf("            1.数据保存\n");
        printf("            2.数据读取\n");
        printf("            3.查询\n");
        printf("            4.浏览\n");
        printf("            5.统计\n");
        printf("            6.修改\n");
        printf("            7.删除\n");
        printf("            8.显示所有数据\n");
        printf("            9.退出系统\n");
        printf("================================\n");
        scanf("%d",&select);
        getchar();
        switch(select)
        {
        case 1 :              //数据保存
            // addrecord(&L);
            save(stu);
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 2 :              //数据读取
            stu=open();
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 3 :              //查询
            menu_3(stu);

            break;
        case 4 :              //浏览
            menu_4(stu);
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 5 :
            menu_5(stu);            //统计
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 6 :                //修改
            menu_6(stu);
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 7:                 //删除
            menu_7(stu);
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 8 :            //显示所有数据
            ListDisplay(stu);
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 9 :
           return;
        }
    }
}

//查找某个课程分数
void findone(STULIST *stu)
{
    printf("================================\n");
    printf("请选择操作：\n");
    printf("\t1.语文\n");
    printf("\t2.数学\n");
    printf("\t3.英语\n");
    printf("================================\n");

    scanf("%d",&select);
    getchar();
    switch(select)
    {
    case 1:
        printf("语文:%d\n",stu->stu[index].Chinese);
        break;
    case 2:
        printf("数学:%d\n",stu->stu[index].Math);
        break;
    case 3:
        printf("英语:%d\n",stu->stu[index].English);
        break;
    }
}

void findall(STULIST *stu)
{
    printf("语文:%d\t数学:%d\t英语:%d\n",stu->stu[index].Chinese,stu->stu[index].Math,stu->stu[index].English);
}
//判断学生登录
int login(STULIST *stu,char stuno[],int password)
{
    for(int i=0;i<stu->len;i++)
    {
        if((!strcmp(stu->stu[i].SN0,stuno))&stu->stu[i].password==password)
        {
            index=i;
            return 1;
        }
    }
    return 0;
}
//学生修改密码
void  modifypassword(STULIST *stu)
{
    int newpwd;
    printf("请输入新密码\n");
    scanf("%d",&newpwd);
    getchar();
    stu->stu[index].password=newpwd;
    save(stu);
}


//学生界面
void stuuser(STULIST *stu)
{

    while(1)
    {
        system("cls");
        printf("================================\n");
        printf("请选择操作：\n");
        printf("\t1.查询某门课程得分\n");
        printf("\t2.查询所有课程得分\n");
        printf("\t3.修改密码\n");
        printf("\t4.退出\n");
        printf("================================\n");
        scanf("%d",&select);
        getchar();
        switch(select)
        {
        case 1:
            findone(stu);
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 2:

            findall(stu);
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 3:
            modifypassword(stu);
            printf("按任意键返回主菜单\n");
            gets(temp2);
            break;
        case 4:
            return;
        }
    }

}

int main()
{

    STULIST *stu=create();
    printf("\nlen:%d\n",stu->len);
    while(1)
    {
        system("cls");
        printf("================================\n");
        printf("请选择操作：\n");
        printf("\t1.管理员登录\n");
        printf("\t2.学生登录\n");
        printf("\t3.退出\n");
        printf("================================\n");
        scanf("%d",&select);
        getchar();
        char adname[20];
        int adpassword;
        switch(select)
        {
        case 1:
            system("cls");
            printf("================================\n");
            printf("请输入账号'1'\n");
            scanf("%s",adname);
            printf("请输入密码'1'\n");
            scanf("%d",&adpassword);
            getchar();
            if((!strcmp(adname,"1"))&&(adpassword==1))
                manage(stu);
            else
            {
                printf("账号或密码错误");
                printf("按任意键返回主菜单\n");
                gets(temp2);
            }
            break;

        case 2:
            system("cls");
            printf("================================\n");
            printf("请输入学号\n");
            scanf("%s",adname);
            printf("请输入密码\n");
            scanf("%d",&adpassword);
            if(login(stu,adname,adpassword)==1)
            {
                stuuser(stu);
            }
            else
            {
                printf("账号或密码错误");
                printf("按任意键返回主菜单\n");
                gets(temp2);

            }
            break;
        case 3:
            exit(0);
        }
        return 0;
    }
}
