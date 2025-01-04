#include <stdio.h>
#include <stdlib.h>

typedef enum { Link, Thread } PointerTag;
typedef char Datetype;

typedef struct BiThreTree {
    Datetype date;
    PointerTag LTag, RTag;
    struct BiThreTree *lchild, *rchild;
} Tree;

Tree *tree; 

Tree* CreatTree() {
    Tree *T;
    Datetype ch;
    if (tree == NULL) printf("根节点，#代表结束");
    else printf("输入节点，#代表结束");
    
    scanf(" %c", &ch);
    if (ch == '#') return NULL;

    T = (Tree*)malloc(sizeof(Tree));
    T->date = ch;
    T->LTag = Link;
    T->RTag = Link;

    printf("%c左节点", T->date);
    T->lchild = CreatTree();
    printf("%c右节点", T->date);
    T->rchild = CreatTree();

    return T;
}

void Inthread(Tree *t) {
    static Tree *pre = NULL; 
    if (t) {
        Inthread(t->lchild);
        if (t->lchild == NULL) {
            t->LTag = Thread;
            t->lchild = pre;  
        }
        if (pre && pre->rchild == NULL) {
            pre->RTag = Thread;
            pre->rchild = t;  
        }
        pre = t;  
        Inthread(t->rchild);
    }
}

Tree* InorderTree(Tree *t) {
    Tree *inodertree = (Tree *)malloc(sizeof(Tree));
    inodertree->lchild = t;
    inodertree->rchild = inodertree;  
    tree = inodertree;
    Inthread(t);
    tree->RTag = Thread;
    tree->rchild = inodertree; 
    inodertree->rchild = tree;  
    return tree;
}

void Travel(Tree *t) {
    Tree *p = t->lchild;
    while (p != t) {
        while (p->LTag == Link) {
            p = p->lchild;
        }
        printf(" %c ", p->date);
        while (p->RTag == Thread && p->rchild != t) {
            p = p->rchild;
            printf(" %c ", p->date);
        }
        p = p->rchild;
    }
}

void FreeTree(Tree *t) {
    if (t) {
        FreeTree(t->lchild);
        FreeTree(t->rchild);
        free(t);
    }
}

int main() {
    Tree *t, *Thre;
    tree = NULL;  
    t = CreatTree();
    Thre = InorderTree(t);
    printf("InOrder Traverse Binary Tree:\n");
    Travel(Thre);
    FreeTree(t);  
    free(Thre);   
    return 0;
}

