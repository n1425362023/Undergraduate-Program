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
};//�α�ṹ��
struct license_day
{
    struct license item[6];
};//ÿ�տα���
//char Lesson[] = "��";
struct license_day *create(struct license_day s[]);//�α�����
void print(struct license_day s[]);//��ӡ�α�
struct license_day *change( struct license_day s[]);//���Ŀα�
struct license_day *confuse( struct license_day s[]);//ȡ���γ�
void notice( struct license_day s[],struct license_day l[]);//֪ͨѧ���γ̱仯����
void copy (struct license_day s[],struct license_day l[]); //���ƿα����ڱȽϿα�ı仯
void view( struct license_day s[]);//�鿴��ϸ�ڿ���Ϣ
void seek(struct license_day s[]);//���ҹ���
void tmenu();//��ʦ��,������С����
void menu1();//��ʦ�˵�
void smenu();//ѧ����,���������
void menu2();//ѧ���˵�
void fenge();//�ָ���
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
    struct license_day old_schedule[7];//���ٿα�ռ�
    create(schedule);//�ú����ڿ��ٵĿα�ռ�������һ�ݿα�
    copy(schedule,old_schedule);//�ú�������ԭʼ�α�Ϊ��߱Ƚϸ���ǰ��Ŀα�������ĵط�׼��
    int choose ,sel;
    label2:
    {
        while (1) {
            printf("ȷ���������\n(��ʦ����1��ѧ������2)\n");
            printf("�������ǣ�");
            if (scanf("%d", &choose) != 1) {
                printf("�����������������\n");
                while (getchar() != '\n');  // �������뻺����������������ѭ��
                continue;
            }
            if (choose == 1 || choose == 2) {
                break;  // ��Ч���룬�˳�ѭ��
            } else {
                printf("�����������������\n");
                while (getchar() != '\n');  // �������뻺����
            }
        }
        if (choose == 1) {                                                  //if��ִ�еĽ�ʦϵͳ
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
                printf("�˳��ɹ�\n");           //�˳����µ�¼
                goto label2;
            }
        }else{                                                                 //else��ִ�е�ѧ��ϵͳ
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
                printf("�˳��ɹ�\n");           //�˳����µ�¼
                goto label2;
            }
        }
    }
}
//�α�����
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
            strcpy(s[i].item[j].lesson,"��");
            strcpy(s[i].item[j].local,"��");
            strcpy(s[i].item[j].teacher,"��");
        }
    }
    for(int i=0;i<5;i++){
        for(int j=0;j<6;j++){
            char *string[6]={"8:00--9:35","10:05--11:40","13:30--15:05","15:35--17:20","18:10--19:45","20:05--21:40"};
            strcpy(s[i].item[j].time,string[j]);
            random_number = rand()%8+1;
            switch(random_number){
                case 1:
                    strcpy(s[i].item[j].lesson,"��");
                    strcpy(s[i].item[j].local,"��");
                    strcpy(s[i].item[j].teacher,"��");
                    break;
                case 2:
                    strcpy(s[i].item[j].lesson,"�ߵ���ѧ");
                    strcpy(s[i].item[j].local,"(��)B203��ý��");
                    strcpy(s[i].item[j].teacher,"����");
                    break;
                case 3:
                    strcpy(s[i].item[j].lesson,"����");
                    strcpy(s[i].item[j].local,"���B409��ý��");
                    strcpy(s[i].item[j].teacher,"������");
                    break;
                case 4:
                    strcpy(s[i].item[j].lesson,"�����뷨��");
                    strcpy(s[i].item[j].local,"���D104��ý��");
                    strcpy(s[i].item[j].teacher,"���±�");
                    break;
                case 5:
                    strcpy(s[i].item[j].lesson,"�������");
                    strcpy(s[i].item[j].local,"���A407��ý��");
                    strcpy(s[i].item[j].teacher,"۬ɽȨ");
                    break;
                case 6:
                    strcpy(s[i].item[j].lesson,"��������");
                    strcpy(s[i].item[j].local,"���J206��ý��");
                    strcpy(s[i].item[j].teacher,"���鿡");
                    break;
                case 7:
                    strcpy(s[i].item[j].lesson,"����");
                    strcpy(s[i].item[j].local,"����������");
                    strcpy(s[i].item[j].teacher,"��ѧ��");
                    break;
                case 8:
                    strcpy(s[i].item[j].lesson,"ְҵ���Ĺ滮");
                    strcpy(s[i].item[j].local,"���J206��ý��");
                    strcpy(s[i].item[j].teacher,"������");
                    break;
            }
        }
    }
    return s;
}
//�鿴�α�������ӡһ�ܿα�
void print(struct license_day s[7]){
    char *day[]={"����һ","���ڶ�","������","������","������","������","������"};
    for(int i= 0;i< 7 ;i++){
        printf("%-15s",day[i]);
    }
    printf("\n");
    for(int i=0;i < 6; i++){
        for(int j= 0;j < 7 ;j++){
            printf("%-15s", s[j].item[i].lesson);              //�ṹ���Ƕ��
        }
        printf("\n");
    }
}
//���Ŀα���
struct license_day *change( struct license_day s[]){
    system("cls");
    char lesson1[20],teacher1[20],local1[20];
    print(s);
    printf("\n��������Ҫ�޸Ŀγ̵����ڶ�Ӧ������������һ��1��");
    int d1;
    d1 = check_Add_Day();
    printf("��������Ҫ�޸ĵĿνڣ�������һ�ڣ�1��");
    int d2;
    d2 = check_Add_Lesson();
    if (strcmp(s[d1-1].item[d2-1].lesson, "��") != 0){
        printf("�ÿν��ѱ�ռ�ã��Ƿ�����޸�\n");
        int d3;
        printf("ȷ����1����ȷ����2��ȡ���޸���3\n");
        d3 = check_Teacher_d3();
        if (d3 == 1) {
            printf("���������޸ĺ�γ�����");
            scanf("%s", lesson1);
            strcpy(s[d1-1].item[d2-1].lesson,lesson1);
            printf("�ڿ���ʦ��");
            scanf("%s", teacher1);
            strcpy(s[d1-1].item[d2-1].teacher,teacher1);
            printf("�ڿεص㣺");
            scanf("%s", local1);
            strcpy(s[d1-1].item[d2-1].local,local1);
            //           printf("�Ͽ�ʱ��2��");
            //          scanf("%s", s[d1-1].item[d2-1].time);
            return s;
        } else if (d3 == 2) {
            printf("������ѡ��");
            return change(s);
        }else if(d3==3){
            return 0;
        }
    }else{
        printf("���������޸ĺ�γ�����");
        scanf("%s", lesson1);
        strcpy(s[d1-1].item[d2-1].lesson,lesson1);
        printf("�ڿ���ʦ��");
        scanf("%s", teacher1);
        strcpy(s[d1-1].item[d2-1].teacher,teacher1);
        printf("�ڿεص㣺");
        scanf("%s", local1);
        strcpy(s[d1-1].item[d2-1].local,local1);
//        printf("�Ͽ�ʱ��3��");
//        scanf("%s", s[d1-1].item[d2-1].time);
        return s;
    }
}
//ȡ���α���
struct license_day *confuse( struct license_day s[]){
    system("cls");
    print(s);
    printf("\n��������Ҫȡ���γ̵����ڶ�Ӧ������������һ��1��");
    int d1;
    d1 = check_Cancel_Day();
    printf("��������Ҫȡ���Ŀνڣ�������һ�ڣ�1��");
    int d2;
    d2 = check_Cancel_Lesson();
    if (strcmp(s[d1-1].item[d2-1].lesson, "��") != 0){
        printf("�ÿν��ѱ�ռ�ã��Ƿ����ȡ��\n");
        int d3;
        printf("ȷ����1����ȷ����2��ȡ���޸���3\n");
        d3 = check_Teacher_d3();
        if (d3 == 1) {
            strcpy(s[d1-1].item[d2-1].lesson,"��");
            strcpy(s[d1-1].item[d2-1].local,"��");
            strcpy(s[d1-1].item[d2-1].teacher,"��");
            strcpy(s[d1-1].item[d2-1].time,"��");
            printf("�޸ĳɹ�\n");
            return s;
        } else if (d3 == 2) {
            printf("������ѡ��");
            return confuse(s);
        }else if(d3==3){
            return 0;
        }
    }
    else{
        printf("�ýڿ�δ��ռ�ã�����ȡ��\n");
        int d4;
        printf("����ѡ��ѡ1�������޸�ѡ2\n");
        d4 = check_Teacher_d4();
        if(d4 == 1)
            return confuse(s);
        else{
            return 0;
        }
    }
}
//���ƿα�
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
//�α�䶯֪ͨ
void notice( struct license_day s[],struct license_day l[])
{
    int count=0;
    for(int i = 0;i < 7;i++)
    {
        for(int j = 0;j < 6;j++)
        {
            if((strcmp(l[i].item[j].lesson,s[i].item[j].lesson)!=0)&&(strcmp(l[i].item[j].local,s[i].item[j].local)!=0)&&(strcmp(l[i].item[j].teacher,s[i].item[j].teacher)!=0))
            {
                printf("�������ݷ����仯\n");
                printf("����%d��%d�ڿ�\n",i+1,j+1);
                printf("�γ����ƣ� %s ����> %s\t ",l[i].item[j].lesson,s[i].item[j].lesson);
                printf("�ڿεص㣺 %s ����> %s\t ",l[i].item[j].local,s[i].item[j].local);
                printf("�ڿ���ʦ�� %s ����> %s\t\n ",l[i].item[j].teacher,s[i].item[j].teacher);
                count++;
            }
        }
    }
    if(count == 0){
        printf("û�пγ̷����䶯");
    }
}
//�鿴��ϸ�ڿ���Ϣ
void view( struct license_day s[]){
    print(s);
    printf("��������Ҫ�鿴�γ̵����ڶ�Ӧ������������һ��1��");
    int d1;
    d1 = check_View_Day();
    printf("��������Ҫ�鿴�Ŀνڣ�������һ�ڣ�1��");
    int d2;
    d2 =check_View_Lesson();
    if (strcmp(s[d1-1].item[d2-1].lesson, "��") == 0){
        printf("�ÿνڲ�û�п�\n");
    }else{
        printf("�ν����ƣ� %s\n",s[d1-1].item[d2-1].lesson);
        printf("�ڿν�ʦ�� %s\n",s[d1-1].item[d2-1].teacher);
        printf("�γ�ʱ�䣺 ����%d��%d��%s\n",d1,d2,s[d1-1].item[d2-1].time);
        printf("�Ͽεص㣺 %s\n",s[d1-1].item[d2-1].local);
    }
}
void seek(struct license_day s[])
{
    printf("��������Ҫ���ҵ�����\n(����ʦ������������1�����γ����Ʋ�������2�����ص��������3����ʱ���������4)\n");
    int section;
    int c1 = 0;
    char name[20]={0};
    section = check_seek();
    switch(section)
    {
        case 1:
            printf("��������ʦ�����֣�");
            scanf("%s",name);
            for(int i = 0;i < 7;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(strcmp(name,s[i].item[j].teacher) == 0)
                    {
                        fenge();
                        printf("�ν����ƣ� %s\n",s[i].item[j].lesson);
                        printf("�ڿν�ʦ�� %s\n",s[i].item[j].teacher);
                        printf("�γ�ʱ�䣺 ����%d��%d��%s\n",i+1,j+1,s[i].item[j].time);
                        printf("�Ͽεص㣺 %s\n",s[i].item[j].local);
                        c1++;
                    }
                }
            }
            if(c1 == 0)
                printf("�α��в����ڸ���ʦ\n");
            break;
        case 2:
            printf("������γ̵����֣�");
            scanf("%s",name);
            for(int i = 0;i < 7;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(strcmp(name,s[i].item[j].lesson) == 0)
                    {
                        fenge();
                        printf("�ν����ƣ� %s\n",s[i].item[j].lesson);
                        printf("�ڿν�ʦ�� %s\n",s[i].item[j].teacher);
                        printf("�γ�ʱ�䣺 ����%d��%d��%s\n",i+1,j+1,s[i].item[j].time);
                        printf("�Ͽεص㣺 %s\n",s[i].item[j].local);
                        c1++;
                    }
                }
            }
            if(c1 == 0)
                printf("�α��в����ڸÿγ�\n");
            break;
        case 3:
            printf("������ص�����֣�");
            scanf("%s",name);
            for(int i = 0;i < 7;i++)
            {
                for(int j = 0;j < 6;j++)
                {
                    if(strcmp(name,s[i].item[j].lesson) == 0)
                    {
                        fenge();
                        printf("�ν����ƣ� %s\n",s[i].item[j].lesson);
                        printf("�ڿν�ʦ�� %s\n",s[i].item[j].teacher);
                        printf("�γ�ʱ�䣺 ����%d��%d��%s\n",i+1,j+1,s[i].item[j].time);
                        printf("�Ͽεص㣺 %s\n",s[i].item[j].local);
                        c1++;
                    }
                }
            }
            if(c1 == 0)
                printf("�α��в����ڸõص�\n");
            break;
        case 4:
            printf("���������ʱ�䣺");
            printf("\n��������Ҫ���ҿγ̵����ڶ�Ӧ������������һ��1��");
            int d1;
            d1 = check_View_Day();
            printf("��������Ҫ���ҵĿνڣ�������һ�ڣ�1��");
            int d2;
            d2 = check_View_Lesson();
            printf("�ν����ƣ� %s\n",s[d1-1].item[d2-1].lesson);
            printf("�ڿν�ʦ�� %s\n",s[d1-1].item[d2-1].teacher);
            printf("�γ�ʱ�䣺 ����%d��%d��%s\n",d1,d2,s[d1-1].item[d2-1].time);
            printf("�Ͽεص㣺 %s\n",s[d1-1].item[d2-1].local);
            break;
    }
    return;
}
//��ʦ��
void tmenu()
{
    system("cls");    // ����Windowsϵͳʹ���������������� ����stdlibͷ�ļ�
    printf("                                                        \n");
    printf("                                                        \n");
    printf("             ======== �α������Ϣϵͳ����ʦ�棩 ========         \n");
    printf("                                                        \n");
    printf("                       0���˳�ϵͳ                      \n");
    printf("                       1���鿴�α�                      \n");
    printf("                       2����ӿγ�                      \n");
    printf("                       3��ȡ���γ�                      \n");
    printf("                       4���鿴��ϸ�Ŀγ���Ϣ                      \n");
    printf("                       5�������γ�                      \n");
    printf("                       6������ʹ��                     \n");
}
//��ʦ�˵�
void menu1(){
    printf("\n\n");
    printf("                       0���˳�ϵͳ                      \n");
    printf("                       1���鿴�α�                      \n");
    printf("                       2����ӿγ�                      \n");
    printf("                       3��ȡ���γ�                      \n");
    printf("                       4���鿴��ϸ�Ŀγ���Ϣ                      \n");
    printf("                       5�������γ�                      \n");
    printf("                       6������ʹ��                     \n");
}
//ѧ����
void smenu()
{
    system("cls");
    printf("                                                        \n");
    printf("                                                        \n");
    printf("             ======== �α������Ϣϵͳ��ѧ���棩 ========         \n");
    printf("                                                        \n");
    printf("                       0���˳�ϵͳ                      \n");
    printf("                       1���鿴�α�                      \n");
    printf("                       2���鿴��ϸ�Ŀγ���Ϣ                  \n");
    printf("                       3���α�䶯֪ͨ                  \n");
    printf("                       4�������γ�                      \n");
    printf("                       5������ʹ��                     \n");
}
//ѧ���˵�
void menu2(){
    printf("\n\n");
    printf("                       0���˳�ϵͳ                      \n");
    printf("                       1���鿴�α�                      \n");
    printf("                       2���鿴��ϸ�Ŀγ���Ϣ                      \n");
    printf("                       3���α�䶯֪ͨ                  \n");
    printf("                       4�������γ�                      \n");
    printf("                       5������ʹ��                     \n");
}
void fenge()
{
    printf("(*******************************************************************)\n");
}
int check_TeacherSel(){
    int sel;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &sel) != 1) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (sel < 0 || sel > 6) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return sel;
}
int check_StudentSel(){
    int sel;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &sel) != 1) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (sel < 0 || sel > 5) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return sel;
}
int check_Add_Day(){
    int d1;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &d1) != 1) {
            printf("�����������������\n");
            printf("\n��������Ҫ�޸Ŀγ̵����ڶ�Ӧ������������һ��1��");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (d1 < 1 ||d1 > 7) {
            printf("�����������������\n");
            printf("\n��������Ҫ�޸Ŀγ̵����ڶ�Ӧ������������һ��1��");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return d1;
}
int check_Add_Lesson(){
    int d2;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &d2) != 1) {
            printf("�����������������\n");
            printf("��������Ҫ�޸ĵĿνڣ�������һ�ڣ�1��");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (d2 < 1 ||d2 > 6) {
            printf("�����������������\n");
            printf("��������Ҫ�޸ĵĿνڣ�������һ�ڣ�1��");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ����
        }
    }
    return d2;
}
int check_Cancel_Day(){
    int d1;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &d1) != 1) {
            printf("�����������������\n");
            printf("\n��������Ҫȡ���γ̵����ڶ�Ӧ������������һ��1��");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (d1 < 1 ||d1 > 7) {
            printf("�����������������\n");
            printf("\n��������Ҫȡ���γ̵����ڶ�Ӧ������������һ��1��");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return d1;
}
int check_Cancel_Lesson(){
    int d2;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &d2) != 1) {
            printf("�����������������\n");
            printf("��������Ҫȡ���Ŀνڣ�������һ�ڣ�1��");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (d2 < 1 ||d2 > 6) {
            printf("�����������������\n");
            printf("��������Ҫȡ���Ŀνڣ�������һ�ڣ�1��");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return d2;
}
int check_View_Day(){
    int d1;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &d1) != 1) {
            printf("�����������������\n");
            printf("\n��������Ҫ�鿴�γ̵����ڶ�Ӧ������������һ��1��");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (d1 < 1 ||d1 > 7) {
            printf("�����������������\n");
            printf("\n��������Ҫ�鿴�γ̵����ڶ�Ӧ������������һ��1��");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return d1;
}
int check_View_Lesson(){
    int d2;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &d2) != 1) {
            printf("�����������������\n");
            printf("��������Ҫ�鿴�Ŀνڣ�������һ�ڣ�1��");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (d2 < 1 ||d2 > 6) {
            printf("�����������������\n");
            printf("��������Ҫ�鿴�Ŀνڣ�������һ�ڣ�1��");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return d2;
}
int check_Teacher_d3(){
    int d3;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &d3) != 1) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (d3 < 1 || d3 > 3) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return d3;
}
int check_Teacher_d4() {
    int d4;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &d4) != 1) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (d4 < 1 || d4 > 2) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return d4;
}
int check_seek()
{
    int section;
    while (1) {
        printf("�������ѡ�");
        if (scanf("%d", &section) != 1) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
            continue;
        }
        if (section < 1 || section >4 ) {
            printf("�����������������\n");
            while (getchar() != '\n');  // �������뻺����
        } else {
            break;  // ��Ч���룬�˳�ѭ��
        }
    }
    return section;
}




