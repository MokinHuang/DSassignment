#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    int data;       //数据域
    struct StackNode *next;     //指向下一节点
}*Link;     //创建链栈单个节点

typedef struct {
    Link top;
}LinkStack;     //创建链栈

void InitStack(LinkStack *s) {
    s->top = NULL;
}       //初始化链栈

void PushStack(LinkStack *s,int n) {
    Link q = (Link)malloc(sizeof(struct StackNode));        //为进栈元素分配空间
    if (!q) exit(-1);
    q->data = n;
    q->next = s->top;
    s->top = q;
}       //实现进栈

void PopStack(LinkStack *s,int *n) {
    Link q = s->top;
    if (s->top == NULL) exit(-1);        //若栈为空则退出代码-1
    *n = q->data;
    s->top = q->next;
    free(q);        //释放出栈元素空间
}       //出栈实现

void PrintStack(LinkStack *s) {
    Link p = s->top;
    while (p != NULL) {
        printf("%d ",p->data);
        p = p->next;
    }
}

void PrintTriangle(int n,LinkStack *s) {
    int rows = n;
    int triangle[rows][rows];
    for (int i = 0;i < rows; i++) {
        for (int j = 0;j <= i; j++) {
            if (j == 0 || j==i) triangle[i][j] = 1;
            else {
                triangle[i][j] = triangle[i-1][j] + triangle[i-1][j-1];
            }
            PushStack(s,triangle[i][j]);
            printf("%d ",triangle[i][j]);
        }
        printf("\n");
    }       //计算杨辉三角并打印
}

int main(void) {
    LinkStack s;
    LinkStack reserves;
    InitStack(&reserves);
    InitStack(&s);
    PrintTriangle(5,&s);
    printf("\n");
    PrintTriangle(10,&s);
    return 0;
}