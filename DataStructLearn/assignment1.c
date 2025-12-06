#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define List_init_size 100
#define ListIncreasement 10

typedef struct {
    int coef;       //定义系数
    int exp;        //定义指数
}Term;      //定义多项式中的项

typedef struct {
    Term* terms;
    int len;        //定义多项式长度
    int size;       //定义多项式大小
}Poly;      //定义多项式poly

void poly_init(Poly* poly) {
    poly->terms = (Term*)malloc(sizeof(Term) * List_init_size);     //为多项式中的项动态分配内存
    if (!poly->terms) exit(ERROR);      //若失败则退出代码1
    poly->len = 0;
    poly->size = List_init_size;
}       //初始化多项式

void insertTerm(Poly* poly,int coef,int exp,int i) {
    if (i<1||i>poly->len+1) exit(1);        //若i超过多项式的长度则退出代码1
    if (poly->len>=poly->size) {
        int new_size = poly->size + ListIncreasement;
        Term* new_term = (Term*)realloc(poly->terms ,new_size * sizeof(Term) );
        if (!new_term) exit(ERROR);
        poly->terms = new_term;
        poly->size = new_size;
    }       //如果大小不够则要增加
    for (int j=poly->len;j>=i;j--) {
        poly->terms[j] = poly->terms[j-1];
    }       //将i以后的每一项都往后移
    poly->terms[i-1].coef = coef;
    poly->terms[i-1].exp = exp;     //将新值插入i的位置
    poly->len++;
}       //在多项式i的位置插入值

void printPoly(Poly* poly) {
        for (int i = poly->len; i>=0;i--) {
            if (poly->terms[i].coef) {
                printf("%dx%d",poly->terms[i].coef,poly->terms[i].exp);
                if (i!=0) printf(" + ");
            }
        }
    printf("\n");
}       //打印多项式的值

void plusPoly(Poly* poly1 , Poly* poly2 , Poly* polyplus) {
    if (poly1->len>poly2->len) {
        polyplus->len=poly1->len;
        for (int i = 0; i< poly1->len; i++) {
            polyplus->terms[i].exp = poly1->terms[i].exp;
        }
    }       //判断poly1，poly2的长度并写入polyplus的指数
    else {
        polyplus->len=poly2->len;
        for (int i = 0; i< poly2->len; i++) {
            polyplus->terms[i].exp = poly2->terms[i].exp;
        }
    }
    for (int i = 0; i< polyplus->len;i++) {
        polyplus->terms[i].coef = poly1->terms[i].coef + poly2->terms[i].coef;
    }
}       //使多项式相加并使结果存于polyplus便于输出

void minusPoly(Poly* poly1 , Poly* poly2 , Poly* polyminus) {
    if (poly1->len>poly2->len) {
        polyminus->len=poly1->len;
        for (int i = 0; i< poly1->len; i++) {
            polyminus->terms[i].exp = poly1->terms[i].exp;
        }
    }       //判断poly1，poly2的长度并写入polyminus的指数
    else {
        polyminus->len=poly2->len;
        for (int i = 0; i< poly2->len; i++) {
            polyminus->terms[i].exp = poly2->terms[i].exp;
        }
    }
    for (int i = 0; i< polyminus->len;i++) {
        polyminus->terms[i].coef = poly1->terms[i].coef - poly2->terms[i].coef;
    }
}       //使多项式相加并存储到polyminus中

void multiplyPoly(Poly* poly1 , Poly* poly2 , Poly* polymult) {
    polymult->len=poly1->len*poly2->len;
    for (int i = 0; i< poly1->len; i++) {
        for (int j = 0; j< poly2->len; j++) {
            int coef = poly1->terms[i].coef * poly2->terms[j].coef;
            int exp = poly1->terms[i].exp + poly2->terms[j].exp;
            if (coef!=0) {
                insertTerm(polymult,coef,exp,i+1);
            }
        }
    }       //计算多项式相乘
    for (int i = 0; i< polymult->len;i++) {
        for (int j = 0; j< polymult->len; j++) {
            if (polymult->terms[i].exp == polymult->terms[j].exp) {
                polymult->terms[i].coef += polymult->terms[j].coef;
                for (int k=j;k<=polymult->len;k++) {
                    polymult->terms[k]= polymult->terms[k+1];
                }
            }
        }
    }       //使多项式的同类项合并
}       //使多项式相乘并存储到polymuti中

int main() {
    int n;
    printf("请输入多项式1的项数：");
    scanf("%d",&n);
    Poly* poly1 = (Poly*)malloc(sizeof(Poly));
    poly_init(poly1);
    printf("\n");
    printf("请按顺序输入多项式1的系数及指数：");
    for (int i=0;i<n;i++) {
        int coef;       //输入的系数
        int exp;        //输入的指数
        scanf("%d %d",&coef,&exp);
        insertTerm(poly1,coef,exp,i+1);
    }
    printPoly(poly1);

    int m;
    printf("请输入多项式2的项数：");
    scanf("%d",&m);
    Poly* poly2 = (Poly*)malloc(sizeof(Poly));
    poly_init(poly2);
    printf("\n");
    printf("请按顺序输入多项式2的系数及指数：");
    for (int i=0;i<m;i++) {
        int coef;       //输入的系数
        int exp;        //输入的指数
        scanf("%d %d",&coef,&exp);
        insertTerm(poly2,coef,exp,i+1);
    }
    printPoly(poly2);

    printf("相加后到结果：");
    Poly* polyplus = (Poly*)malloc(sizeof(Poly));
    poly_init(polyplus);
    plusPoly(poly1,poly2,polyplus);
    printPoly(polyplus);        //多项式相加实现

    printf("相减后的结果: ");
    Poly* polyminus = (Poly*)malloc(sizeof(Poly));
    poly_init(polyminus);
    minusPoly(poly1,poly2,polyminus);
    printPoly(polyminus);       //多项式实现

    printf("相乘后的结果：");
    Poly* polymult = (Poly*)malloc(sizeof(Poly));
    poly_init(polymult);
    multiplyPoly(poly1,poly2,polymult);
    printPoly(polymult);

    free(poly1->terms);free(poly1);
    free(poly2->terms);free(poly2);
    free(polymult->terms);free(polymult);
    free(polyplus->terms);free(polyplus);
    free(polyminus->terms);free(polyminus);
    return 0;
}