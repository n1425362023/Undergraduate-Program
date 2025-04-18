#include <stdio.h> 
#include <malloc.h> 
typedef enum{Link,Thread} PointerTag;  /*指针标志*/ 
typedef char DataType; 
typedef struct BiThreTree{               /*定义结点元素*/ 
        PointerTag LTag,RTag; 
        DataType data; 
        struct BiThreTree *lchild,*rchild; 
        }BiThreTree; 
BiThreTree *pre;                   /*全局变量，用于二叉树的线索化*/ 
int f;
BiThreTree *CreateTree()            /*按前序输入建立二叉树*/ 
{ 
        BiThreTree *T; 
        DataType ch;
		if(f==1)printf("根结点，#表示结束:\n");
		else printf("输入结点，#表示结束");
        scanf("\n%c",&ch); 
		f=f+1;
        if(ch=='#') 
           T=NULL; 
        else 
           {T=(BiThreTree *)malloc(sizeof(BiThreTree)); 
            T->data=ch; 
            T->LTag=Link;          /*初始化时指针标志均为Link*/ 
            T->RTag=Link; 
			printf("%c左孩子",T->data);
            T->lchild=CreateTree(); 
			printf("%c右孩子",T->data);
            T->rchild=CreateTree(); 
           } 
        return T; 
} 
void InThread(BiThreTree *T) 
{ 
     BiThreTree *p; 
     p=T; 
     if(p) 
    { 
     InThread(p->lchild); 
     if(p->lchild==NULL) 
        { p->LTag=Thread; 
          p->lchild=pre; 
        } 
     if(pre->rchild==NULL) 
        { pre->RTag=Thread; 
          pre->rchild=p; 
        } 
     pre=p; 
     InThread(p->rchild); 
    } 
} 
BiThreTree *InOrderThrTree(BiThreTree *T) /*中序线索化二叉树*/ 
{ 
     BiThreTree *Thre;                 /*Thre为头结点的指针*/ 
     Thre=(BiThreTree *)malloc(sizeof(BiThreTree)); 
     Thre->lchild=T; 
     Thre->rchild=Thre; 
     pre=Thre; 
     InThread(T); 
     pre->RTag=Thread; 
     pre->rchild=Thre; 
     Thre->rchild=pre; 
     return Thre; 
} 
void InThrTravel(BiThreTree *Thre)    /*中序遍历二叉树*/ 
{ 
     BiThreTree *p; 
     p=Thre->lchild; 
     while(p!=Thre)                  /*指针回指向头结点时结束*/ 
     { 
       while(p->LTag==Link) 
          p=p->lchild; 
       printf("%4c",p->data); 
       while(p->RTag==Thread&&p->rchild!=Thre) 
         {p=p->rchild; 
          printf("%4c",p->data); 
         } 
       p=p->rchild; 
     }
} 

int  main() 
{   BiThreTree *T,*Thre;
    f=1;
    T=CreateTree(); 
    Thre=InOrderThrTree(T); 
    printf("InOrder Traverse Binary Tree:\n");
    InThrTravel(Thre); 
}

