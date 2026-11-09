#include <stdio.h>
#include <stdlib.h>
#define NUM 5

/*------------------------------------------------------------函数实现------------------------------------------------------------------------*/

struct node
{
    int i = 0;
    int j = 0;
    int x = 0;
};
struct matrix
{
    int m = 0;
    int n = 0;
    int size = 0;
    int place = 0;
    int *head = NULL;
    node *data = NULL;
};
int cmp(const void *a, const void *b)
{
    node *x = (node *)a;
    node *y = (node *)b;
    if (x->i > y->i || ((x->i == y->i) && (x->j > y->j)))
    {
        return 1;
    }
    return 0;
}
void sort(matrix *s)
{
    qsort(s->data, s->size, sizeof(node), cmp);
}

void set_head(matrix *s)
{
    for (int i = s->size - 1; i >= 0; i--)
    {
        s->head[s->data[i].i] = i;
    }
}

bool init(matrix *s, int m, int n)
{
    int i, j, x;
    s->place = NUM;
    s->m = m;
    s->n = n;
    s->head = (int *)calloc(m, sizeof(int));
    s->data = (node *)calloc(s->place , sizeof(node));
    s->size = 0;
    if (s->head == NULL || s->data == NULL)
        return false;
    while (1)
    {
        char in[256] = "";
        fgets(in, sizeof(in) - 3, stdin);
        if (in[0] == '#')
            break;
        sscanf(in, "%d %d %d", &i, &j, &x);
        if (i > m - 1 || j > n - 1)
        {
            printf("矩阵超界，重新输入");
            continue;
        }
        if (s->size >= s->place)
        {
            s->place = s->place + NUM;
            s->data = (node *)realloc(s->data, (s->place) * sizeof(node));
        }
        s->data[s->size].i = i;
        s->data[s->size].j = j;
        s->data[s->size].x = x;
        s->size++;
    }
    sort(s);
    set_head(s);
    return true;
}

void print(matrix s)
{
    int i = 0, j, k1 = 0, k2 = 0;
    while (k1 != s.m)
    {
        while (k1 * s.n + k2 < s.data[i].i * s.n + s.data[i].j)
        {
            if (k2 == s.n)
            {
                k2 = 0;
                k1++;
                printf("\n");
                continue;
            }
            printf("%-3d", 0);
            k2++;
        }
        printf("%-3d", s.data[i++].x);
        k2++;
        if (k2 == s.n)
        {
            k2 = 0;
            k1++;
            printf("\n");
        }
    }
}
matrix T(matrix s)
{
    matrix res;
    res.m = s.n;
    res.n = s.m;
    res.place = s.place;
    res.size = s.size;
    res.head = (int *)calloc(res.n, sizeof(int));
    res.data = (node *)calloc(res.place, sizeof(node));
    int tem[s.n];
    int mark[s.n];
    for (int i = 0; i <= s.n - 1; i++)
    {
        tem[i] = 0;
    }
    for (int i = 0; i <= s.size - 1; i++)
    {
        tem[s.data[i].j]++;
    }
    mark[0] = 0;
    for (int i = 0; i <= s.n - 2; i++)
    {
        mark[i + 1] = mark[i] + tem[i];
    }
    for (int i = 0; i <= s.size - 1; i++)
    {
        res.data[mark[s.data[i].j]].x = s.data[i].x;
        res.data[mark[s.data[i].j]].i = s.data[i].j;
        res.data[mark[s.data[i].j]].j = s.data[i].i;
        mark[s.data[i].j]++;
    }
    set_head(&res);
    return res;
}

matrix by(matrix s1, matrix s2)
{
    int i, j, k;
    int tem[s2.n];
    i = 0;     // s1中的行
    j = 0;     // s2中的行
    int x = 0; // 当下s1节点
    int y = 0; // 当下s2节点
    matrix s;
    s.m = s1.m;
    s.n = s2.n;
    s.place = 100;
    s.data = (node *)calloc(s.place, sizeof(node));
    s.size = 0;
    while (i != s1.m)
    {
        x = s1.head[i];
        for (k = 0; k <= s2.n - 1; k++)
        {
            tem[k] = 0;
        }
        while (x < s1.size && s1.data[x].i == i)
        {
            j = s1.data[x].j;
            y = s2.head[j];
            while (y < s2.size && s2.data[y].i == j)
            {
                tem[s2.data[y].j] = tem[s2.data[y].j] + s1.data[x].x * s2.data[y].x;
                y++;
            }
            x++;
        }
        for (k = 0; k <= s2.n - 1; k++)
        {
            if (tem[k] != 0)
            {
                s.data[s.size].i = i;
                s.data[s.size].j = k;
                s.data[s.size++].x = tem[k];
            }
        }
        i++;
    }
    return s;
}

int main()
{
    matrix s;
    init(&s, 3, 3);
    print(s);
    print(T(s));
    return 0;
}
/*
0 0 5
1 2 10
2 2 8
2 0 -9
#
*/