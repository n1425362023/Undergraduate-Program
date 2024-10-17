#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct license
{
    char lesson[20];
    char time[20];
    char teacher[20];
    char local[20];
};//课表结构体
struct license_day
{
    struct license item[6];
};//每日课表结点
//char Lesson[] = "无";
struct license_day *create(struct license_day s[]);//课表生成
void print(struct license_day s[]);//打印课表
struct license_day *change( struct license_day s[]);//更改课表
struct license_day *confuse( struct license_day s[]);//取消课程
void notice( struct license_day s[],struct license_day l[]);//通知学生课程变化函数
void copy (struct license_day s[],struct license_day l[]); //复制课表用于比较课表的变化
void view( struct license_day s[]);//查看详细授课信息
void seek(struct license_day s[]);//查找功能
void tmenu();//教师端,共六个小功能
void menu1();//教师菜单
void smenu();//学生端,共五个功能
void menu2();//学生菜单
void fenge();//分割线
int check_TeacherSel();
int check_StudentSel();
int check_Add_Day();
int check_Add_Lesson();
int check_Cancel_Day();
int check_Cancel_Lesson();
int check_View_Day();
int check_View_Lesson();
int check_Teacher_d3();
int check_Teacher_d4();
int check_seek();
int main()
{
    struct license_day schedule[7];
    struct license_day old_schedule[7];//开辟课表空间
    create(schedule);//用函数在开辟的课表空间中生成一份课表
    copy(schedule,old_schedule);//用函数拷贝原始课表，为后边比较更改前后的课表，输出更改地方准备
    int choose ,sel;
    label2:
    {
        while (1) {
            printf("确认您的身份\n(教师输入1，学生输入2)\n");
            printf("你的身份是：");
            if (scanf("%d", &choose) != 1) {
                printf("输入错误，请重新输入\n");
                while (getchar() != '\n');  // 清理输入缓冲区，避免陷入死循环
                continue;
            }
            if (choose == 1 || choose == 2) {
                break;  // 有效输入，退出循环
            } else {
                printf("输入错误，请重新输入\n");
                while (getchar() != '\n');  // 清理输入缓冲区
            }
        }
        if (choose == 1) {                                                  //if里执行的教师系统
            tmenu();
            sel = check_TeacherSel();
            while(sel!=0){
                switch (sel) {
                    case 1:
                        print(schedule);
                        menu1();
                        sel = check_TeacherSel();
                        break;
                    case 2:
                        change(schedule);
                        menu1();
                        sel = check_TeacherSel();
                        break;
                    case 3:
                        confuse(schedule);
                        menu1();
                        sel = check_TeacherSel();
                        break;
                    case 4:
                        view(schedule);
                        menu1();
                        sel = check_TeacherSel();
                        break;
                    case 5:
                        seek(schedule);
                        menu1();
                        sel = check_TeacherSel();
                        break;
                    case 6:
                        return 0;
                }
            }
            if(sel==0){
                printf("退出成功\n");           //退出重新登录
                goto label2;
            }
        }else{                                                                 //else里执行的学生系统
            smenu();
            sel = check_StudentSel();
            while(sel!=0){
                switch (sel) {
                    case 1:
                        print(schedule);
                        menu2();
                        sel = check_StudentSel();
                        break;
                    case 2:
                        view(schedule);
                        menu2();
                        sel = check_StudentSel();
                        break;
                    case 3:
                        notice(schedule,old_schedule );
                        menu2();
                        sel = check_StudentSel();
                        break;
                    case 4:
                        seek(schedule);
                        menu2();
                        sel = check_TeacherSel();
                        break;
                    case 5:
                        return 0;
                }
            }
            if(sel==0) {
                printf("退出成功\n");           //退出重新登录
                goto label2;
            }
        }
    }
}
//课表生成
struct license_day *create(struct license_day s[7]){
    int random_number;
    srand(time(NULL));
    for(int i=0;i<7;i++){
        for(int j=0;j<6;j++){
            char *string[6]={"8:00--9:35","10:05--11:40","13:30--15:05","15:35--17:20","18:10--19:45","20:05--21:40"};
            strcpy(s[i].item[j].time,string[j]);
        }
    }
    for(int i=5;i<7;i++){
        for(int j=0;j<6;j++){
            strcpy(s[i].item[j].lesson,"无");
            strcpy(s[i].item[j].local,"无");
            strcpy(s[i].item[j].teacher,"无");
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            char *string[6]={"8:00--9:35","10:05--11:40","13:30--15:05","15:35--17:20","18:10--19:45","20:05--21:40"};
            strcpy(s[i].item[j].time,string[j]);
            random_number = rand()%8+1;
            switch(random_number){
                case 1:
                    strcpy(s[i].item[j].lesson,"无");
                    strcpy(s[i].item[j].local,"无");
                    strcpy(s[i].item[j].teacher,"无");
                    break;
                case 2:
                    strcpy(s[i].item[j].lesson,"高等数学");
                    strcpy(s[i].item[j].local,"(里)B203多媒体");
                    strcpy(s[i].item[j].teacher,"鱼龙");
                    break;
                case 3:
                    strcpy(s[i].item[j].lesson,"外语");
                    strcpy(s[i].item[j].local,"（里）B409多媒体");
                    strcpy(s[i].item[j].teacher,"张玉玺");
                    break;
                case 4:
                    strcpy(s[i].item[j].lesson,"道德与法治");
                    strcpy(s[i].item[j].local,"（里）D104多媒体");
                    strcpy(s[i].item[j].teacher,"杨新宾");
                    break;
                case 5:
                    strcpy(s[i].item[j].lesson,"程序设计");
                    strcpy(s[i].item[j].local,"（里）A407多媒体");
                    strcpy(s[i].item[j].teacher,"郜山权");
                    break;
                case 6:
                    strcpy(s[i].item[j].lesson,"军事理论");
                    strcpy(s[i].item[j].local,"（里）J206多媒体");
                    strcpy(s[i].item[j].teacher,"郭祥俊");
                    break;
                case 7:
                    strcpy(s[i].item[j].lesson,"体育");
                    strcpy(s[i].item[j].local,"里仁体育场");
                    strcpy(s[i].item[j].teacher,"崔学臣");
                    break;
                case 8:
                    strcpy(s[i].item[j].lesson,"职业生涯规划");
                    strcpy(s[i].item[j].local,"（里）J206多媒体");
                    strcpy(s[i].item[j].teacher,"王恩福");
                    break;
            }
        }
    }
    return s;
}
//查看课表函数，打印一周课表
void print(struct license_day s[7]){
    char *day[]={"星期一","星期二","星期三","星期四","星期五","星期六","星期天"};
    for(int i= 0;i< 7 ;i++){
        printf("%-15s",day[i]);
    }
    printf("\n");
    for(int i=0;i < 6; i++){
        for(int j= 0;j < 7 ;j++){
            printf("%-15s", s[j].item[i].lesson);              //结构体的嵌套
        }
        printf("\n");
    }
}
//更改课表函数
struct license_day *change( struct license_day s[]){
    system("cls");
    char lesson1[20],teacher1[20],local1[20];
    print(s);
    printf("\n请输入你要修改课程的星期对应天数，例：周一（1）");
    int d1;
    d1 = check_Add_Day();
    printf("请输入你要修改的课节，例：第一节（1）");
    int d2;
    d2 = check_Add_Lesson();
    if (strcmp(s[d1-1].item[d2-1].lesson, "无") != 0){
        printf("该课节已被占用，是否进行修改\n");
        int d3;
        printf("确认填1，不确认填2，取消修改填3\n");
        d3 = check_Teacher_d3();
        if (d3 == 1) {
            printf("请输入你修改后课程名：");
            scanf("%s", lesson1);
            strcpy(s[d1-1].item[d2-1].lesson,lesson1);
            printf("授课老师：");
            scanf("%s", teacher1);
            strcpy(s[d1-1].item[d2-1].teacher,teacher1);
            printf("授课地点：");
            scanf("%s", local1);
            strcpy(s[d1-1].item[d2-1].local,local1);
            //           printf("上课时间2：");
            //          scanf("%s", s[d1-1].item[d2-1].time);
            return s;
        } else if (d3 == 2) {
            printf("请重新选择");
            return change(s);
        }else if(d3==3){
            return 0;
        }
    }else{
        printf("请输入你修改后课程名：");
        scanf("%s", lesson1);
        strcpy(s[d1-1].item[d2-1].lesson,lesson1);
        printf("授课老师：");
        scanf("%s", teacher1);
        strcpy(s[d1-1].item[d2-1].teacher,teacher1);
        printf("授课地点：");
        scanf("%s", local1);
        strcpy(s[d1-1].item[d2-1].local,local1);
//        printf("上课时间3：");
//        scanf("%s", s[d1-1].item[d2-1].time);
        return s;
    }
}
//取消课表函数
struct license_day *confuse( struct license_day s[]){
    system("cls");
    print(s);
    printf("\n请输入你要取消课程的星期对应天数，例：周一（1）");
    int d1;
    d1 = check_Cancel_Day();
    printf("请输入你要取消的课节，例：第一节（1）");
    int d2;
    d2 = check_Cancel_Lesson();
    if (strcmp(s[d1-1].item[d2-1].lesson, "无") != 0){
        printf("该课节已被占用，是否进行取消\n");
        int d3;
        printf("确认填1，不确认填2，取消修改填3\n");
        d3 = check_Teacher_d3();
        if (d3 == 1) {
            strcpy(s[d1-1].item[d2-1].lesson,"无");
            strcpy(s[d1-1].item[d2-1].local,"无");
            strcpy(s[d1-1].item[d2-1].teacher,"无");
            strcpy(s[d1-1].item[d2-1].time,"无");
            printf("修改成功\n");
            return s;
        } else if (d3 == 2) {
            printf("请重新选择");
            return confuse(s);
        }else if(d3==3){
            return 0;
        }
    }
    else{
        printf("该节课未被占用，无需取消\n");
        int d4;
        printf("重新选择选1，放弃修改选2\n");
        d4 = check_Teacher_d4();
        if(d4 == 1)
            return confuse(s);
        else{
            return 0;
        }
    }
}
//复制课表
void copy (struct license_day s[],struct license_day l[])
{
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            strcpy(l[i].item[j].lesson,s[i].item[j].lesson);
            strcpy(l[i].item[j].local,s[i].item[j].local);
            strcpy(l[i].item[j].teacher,s[i].item[j].teacher);
        }
    }
}
//课表变动通知
void notice( struct license_day s[],struct license_day l[])
{
    int count=0;
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if((strcmp(l[i].item[j].lesson,s[i].item[j].lesson)!=0)&&(strcmp(l[i].item[j].local,s[i].item[j].local)!=0)&&(strcmp(l[i].item[j].teacher,s[i].item[j].teacher)!=0))
            {
                printf("以下内容发生变化\n");
                printf("星期%d第%d节课\n",i+1,j+1);
                printf("课程名称： %s ——> %s\t ",l[i].item[j].lesson,s[i].item[j].lesson);
                printf("授课地点： %s ——> %s\t ",l[i].item[j].local,s[i].item[j].local);
                printf("授课老师； %s ——> %s\t\n ",l[i].item[j].teacher,s[i].item[j].teacher);
                count++;
            }
        }
    }
    if(count == 0){
        printf("没有课程发生变动");
    }
}
//查看详细授课信息
void view( struct license_day s[]){
    print(s);
    printf("请输入你要查看课程的星期对应天数，例：周一（1）");
    int d1;
    d1 = check_View_Day();
    printf("请输入你要查看的课节，例：第一节（1）");
    int d2;
    d2 =check_View_Lesson();
    if (strcmp(s[d1-1].item[d2-1].lesson, "无") == 0){
        printf("该课节并没有课\n");
    }else{
        printf("课节名称： %s\n",s[d1-1].item[d2-1].lesson);
        printf("授课教师： %s\n",s[d1-1].item[d2-1].teacher);
        printf("课程时间： 星期%d第%d节%s\n",d1,d2,s[d1-1].item[d2-1].time);
        printf("上课地点： %s\n",s[d1-1].item[d2-1].local);
    }
}
void seek(struct license_day s[])
{
    printf("请输入你要查找的内容\n(按老师姓名查找输入1，按课程名称查找输入2，按地点查找输入3，按时间查找输入4)\n");
    int section;
    int c1 = 0;
    char name[20]={0};
    section = check_seek();
    switch(section)
    {
        case 1:
            printf("请输入老师的名字：");
            scanf("%s",name);
            for(int i = 0;i < 7;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(strcmp(name,s[i].item[j].teacher) == 0)
                    {
                        fenge();
                        printf("课节名称： %s\n",s[i].item[j].lesson);
                        printf("授课教师： %s\n",s[i].item[j].teacher);
                        printf("课程时间： 星期%d第%d节%s\n",i+1,j+1,s[i].item[j].time);
                        printf("上课地点： %s\n",s[i].item[j].local);
                        c1++;
                    }
                }
            }
            if(c1 == 0)
                printf("课表中不存在该老师\n");
            break;
        case 2:
            printf("请输入课程的名字：");
            scanf("%s",name);
            for(int i = 0;i < 7;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(strcmp(name,s[i].item[j].lesson) == 0)
                    {
                        fenge();
                        printf("课节名称： %s\n",s[i].item[j].lesson);
                        printf("授课教师： %s\n",s[i].item[j].teacher);
                        printf("课程时间： 星期%d第%d节%s\n",i+1,j+1,s[i].item[j].time);
                        printf("上课地点： %s\n",s[i].item[j].local);
                        c1++;
                    }
                }
            }
            if(c1 == 0)
                printf("课表中不存在该课程\n");
            break;
        case 3:
            printf("请输入地点的名字：");
            scanf("%s",name);
            for(int i = 0;i < 7;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(strcmp(name,s[i].item[j].lesson) == 0)
                    {
                        fenge();
                        printf("课节名称： %s\n",s[i].item[j].lesson);
                        printf("授课教师： %s\n",s[i].item[j].teacher);
                        printf("课程时间： 星期%d第%d节%s\n",i+1,j+1,s[i].item[j].time);
                        printf("上课地点： %s\n",s[i].item[j].local);
                        c1++;
                    }
                }
            }
            if(c1 == 0)
                printf("课表中不存在该地点\n");
            break;
        case 4:
            printf("请输入具体时间：");
            printf("\n请输入你要查找课程的星期对应天数，例：周一（1）");
            int d1;
            d1 = check_View_Day();
            printf("请输入你要查找的课节，例：第一节（1）");
            int d2;
            d2 = check_View_Lesson();
            printf("课节名称： %s\n",s[d1-1].item[d2-1].lesson);
            printf("授课教师： %s\n",s[d1-1].item[d2-1].teacher);
            printf("课程时间： 星期%d第%d节%s\n",d1,d2,s[d1-1].item[d2-1].time);
            printf("上课地点： %s\n",s[d1-1].item[d2-1].local);
            break;
    }
    return;
}
//教师端
void tmenu()
{
    system("cls");    // 对于Windows系统使用这个命令，清屏代码 属于stdlib头文件
    printf("                                                        \n");
    printf("                                                        \n");
    printf("             ======== 课表管理信息系统（教师版） ========         \n");
    printf("                                                        \n");
    printf("                       0、退出系统                      \n");
    printf("                       1、查看课表                      \n");
    printf("                       2、添加课程                      \n");
    printf("                       3、取消课程                      \n");
    printf("                       4、查看详细的课程信息                      \n");
    printf("                       5、搜索课程                      \n");
    printf("                       6、结束使用                     \n");
}
//教师菜单
void menu1(){
    printf("\n\n");
    printf("                       0、退出系统                      \n");
    printf("                       1、查看课表                      \n");
    printf("                       2、添加课程                      \n");
    printf("                       3、取消课程                      \n");
    printf("                       4、查看详细的课程信息                      \n");
    printf("                       5、搜索课程                      \n");
    printf("                       6、结束使用                     \n");
}
//学生端
void smenu()
{
    system("cls");
    printf("                                                        \n");
    printf("                                                        \n");
    printf("             ======== 课表管理信息系统（学生版） ========         \n");
    printf("                                                        \n");
    printf("                       0、退出系统                      \n");
    printf("                       1、查看课表                      \n");
    printf("                       2、查看详细的课程信息                  \n");
    printf("                       3、课表变动通知                  \n");
    printf("                       4、搜索课程                      \n");
    printf("                       5、结束使用                     \n");
}
//学生菜单
void menu2(){
    printf("\n\n");
    printf("                       0、退出系统                      \n");
    printf("                       1、查看课表                      \n");
    printf("                       2、查看详细的课程信息                      \n");
    printf("                       3、课表变动通知                  \n");
    printf("                       4、搜索课程                      \n");
    printf("                       5、结束使用                     \n");
}
void fenge()
{
    printf("(*******************************************************************)\n");
}
int check_TeacherSel(){
    int sel;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &sel) != 1) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (sel < 0 || sel > 6) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return sel;
}
int check_StudentSel(){
    int sel;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &sel) != 1) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (sel < 0 || sel > 5) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return sel;
}
int check_Add_Day(){
    int d1;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &d1) != 1) {
            printf("输入错误，请重新输入\n");
            printf("\n请输入你要修改课程的星期对应天数，例：周一（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (d1 < 1 ||d1 > 7) {
            printf("输入错误，请重新输入\n");
            printf("\n请输入你要修改课程的星期对应天数，例：周一（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return d1;
}
int check_Add_Lesson(){
    int d2;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &d2) != 1) {
            printf("输入错误，请重新输入\n");
            printf("请输入你要修改的课节，例：第一节（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (d2 < 1 ||d2 > 6) {
            printf("输入错误，请重新输入\n");
            printf("请输入你要修改的课节，例：第一节（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环·
        }
    }
    return d2;
}
int check_Cancel_Day(){
    int d1;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &d1) != 1) {
            printf("输入错误，请重新输入\n");
            printf("\n请输入你要取消课程的星期对应天数，例：周一（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (d1 < 1 ||d1 > 7) {
            printf("输入错误，请重新输入\n");
            printf("\n请输入你要取消课程的星期对应天数，例：周一（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return d1;
}
int check_Cancel_Lesson(){
    int d2;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &d2) != 1) {
            printf("输入错误，请重新输入\n");
            printf("请输入你要取消的课节，例：第一节（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (d2 < 1 ||d2 > 6) {
            printf("输入错误，请重新输入\n");
            printf("请输入你要取消的课节，例：第一节（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return d2;
}
int check_View_Day(){
    int d1;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &d1) != 1) {
            printf("输入错误，请重新输入\n");
            printf("\n请输入你要查看课程的星期对应天数，例：周一（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (d1 < 1 ||d1 > 7) {
            printf("输入错误，请重新输入\n");
            printf("\n请输入你要查看课程的星期对应天数，例：周一（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return d1;
}
int check_View_Lesson(){
    int d2;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &d2) != 1) {
            printf("输入错误，请重新输入\n");
            printf("请输入你要查看的课节，例：第一节（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (d2 < 1 ||d2 > 6) {
            printf("输入错误，请重新输入\n");
            printf("请输入你要查看的课节，例：第一节（1）");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return d2;
}
int check_Teacher_d3(){
    int d3;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &d3) != 1) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (d3 < 1 || d3 > 3) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return d3;
}
int check_Teacher_d4() {
    int d4;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &d4) != 1) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (d4 < 1 || d4 > 2) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return d4;
}
int check_seek()
{
    int section;
    while (1) {
        printf("输入操作选项：");
        if (scanf("%d", &section) != 1) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
            continue;
        }
        if (section < 1 || section >4 ) {
            printf("输入错误，请重新输入\n");
            while (getchar() != '\n');  // 清理输入缓冲区
        } else {
            break;  // 有效输入，退出循环
        }
    }
    return section;
}




