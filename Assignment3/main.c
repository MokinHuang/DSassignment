#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10

typedef struct {
    int *base;       //栈底指针
    int *top;        //栈顶指针
    int size;       //当前栈已分配空间
}SqStack;       //栈定义

void InitSqStack(SqStack *s) {
    s->base = (int*)malloc(STACK_INIT_SIZE * sizeof(int));
    if (!s->base) exit(-1);     //内存分配失败
    s->top = s->base;
    s->size = STACK_INIT_SIZE;
}       //初始化顺序栈

void PushSqStack(SqStack *s,int n) {
    if (s->top - s->base >= s->size) {
        s->base = (int *)realloc(s->base,(s->size+STACK_INCREMENT)*(sizeof(int)));
        if (!s->base) exit(-1);
        s->top = s->base + s->size;
        s->size += STACK_INCREMENT;
    }       //若栈满则追加空间
    *s->top = n;       //将元素n添加到top所指的位置
    s->top++;
}       //将元素添加到栈中

void ShowSqStack(SqStack *s) {
    printf("栈长度: %d\n",s->size);       //输出栈长度
    if (s->top==s->base) printf("此为空栈！");
    for (int *i = s->top-1; i >= s->base; i --) {
        printf("%d\n",*i);
    }       //输出从栈顶到栈底元素
}       //输出栈相关数据

void TenToEight(SqStack *s,int n) {
    while (n) {
        PushSqStack(s,n%8);     //取余数
        n/=8;
    }
    printf("八进制结果：");
    for (int *i = s->top-1; i >=s->base; i--) {
        printf("%d",*i);
    }       //打印结果
    printf("\n");
}       //十进制向八进制实现

void TenToSix(SqStack *s,int n) {
    while (n) {
        PushSqStack(s,n%6);         //取余数
        n/=6;
    }
    printf("六进制结果：");
    for (int *i = s->top -1 ; i >=s->base; i--) {
        printf("%d",*i);
    }       //打印结果
    printf("\n");
}       //十进制向六进制实现

void ClearSqStack(SqStack *s) {
    s->top = s->base;
}

int main(void) {
    SqStack s;
    InitSqStack(&s);
    TenToEight(&s,1348);
    ClearSqStack(&s);
    TenToSix(&s,1348);
    free(s.base);
    s.base = NULL;
    s.top = NULL;
    return 0;
}