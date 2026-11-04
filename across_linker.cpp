#include <stdio.h>
#include <stdlib.h>
struct node
{
    int i = 0;
    int j = 0;
    int x = 0;
    node *down = NULL;  // 也当头节点
    node *right = NULL; // 也当尾节点
};
struct matrix
{
    int m;
    int n;
    node **x = NULL;
    node **y = NULL;
};

bool init(matrix *s, int m, int n)
{
    s->m = m;
    s->n = n;
    s->x = (node **)calloc(s->m, sizeof(node *));
    s->y = (node **)calloc(s->n, sizeof(node *));
    while (1)
    {
        int i, j, x;
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
        node *p = (node *)calloc(1, sizeof(node));
        p->i = i;
        p->j = j;
        p->x = x;
        node *head;
        if (s->x[p->i] == NULL || p->j < s->x[i]->j)
        {
            p->right = s->x[p->i];
            s->x[p->i] = p;
        }
        else
        {
            head = s->x[p->i];
            while (head->right != NULL && (head->right->j < p->j))
            {
                head = head->right;
            }
            p->right = head->right;
            head->right = p;
        }
        /*------------------------------------------*/
        if (s->y[p->j] == NULL || p->i < s->y[j]->i)
        {
            p->down = s->y[p->j];
            s->y[p->j] = p;
        }
        else
        {
            head = s->y[p->j];
            while (head->down != NULL && (head->down->i < p->i))
            {
                head = head->down;
            }
            p->down = head->down;
            head->down = p;
        }
    }
    return true;
}

void print(matrix s)
{
    for (int i = 0; i <= s.m - 1; i++)
    {
        int j = 0;
        node *head = s.x[i];
        while (j < s.n)
        {
            while (j < s.n && (head == NULL || j < head->j))
            {
                printf("%3d", 0);
                j++;
            }
            if (head != NULL && j == head->j)
            {
                printf("%3d", head->x);
                head = head->right;
                j++;
            }
        }
        printf("\n");
    }
    printf("\n");
}

matrix add(matrix s1, matrix s2)
{
    if (s1.m != s2.m || s1.n != s2.n)
    {
        printf("大小不一致");
        matrix tem;
        return tem;
    }
    matrix s;
    s.m = s1.m;
    s.n = s1.n;
    s.x = (node **)calloc(s.m, sizeof(node*));
    s.y = (node **)calloc(s.n, sizeof(node*));
    int i, j, k;
    for (i = 0; i <= s.m - 1; i++)
    {
        node *a = s1.x[i];
        node *b = s2.x[i];
        node *head;
        while (a != NULL || b != NULL)
        {
            node *p = (node *)calloc(1, sizeof(node));
            if (a != NULL)
                p->i = a->i;
            else
                p->i = b->i;
            if (b == NULL || ((a != NULL) && (a->j < b->j)))
            {
                p->j = a->j;
                p->x = a->x;
                a = a->right;
            }
            else if (a == NULL || ((b != NULL) && (a->j > b->j)))
            {
                p->j = b->j;
                p->x = b->x;
                b = b->right;
            }
            else if (a->j == b->j)
            {
                p->j = a->j;
                p->x = a->x + b->x;
                a = a->right;
                b = b->right;
            }
            /*------------------------------------------------*/
            if (s.x[i] == NULL)
            {
                s.x[i] = p;
                head = s.x[i];
            }
            else
            {
                head->right = p;
                head = head->right;
            }
            /*------------------------------------------------*/
            j = p->j;
            node *down = s.y[j];
            if (s.y[j] == NULL)
            {
                s.y[j] = p;
                down = s.y[j];
            }
            else
            {
                while (down->down != NULL)
                {
                    down = down->down;
                }
                down->down = p;
                down = down->down;
            }
        }
    }
    return s;
}

matrix minus(matrix s1, matrix s2)
{
    if (s1.m != s2.m || s1.n != s2.n)
    {
        printf("大小不一致");
        matrix tem;
        return tem;
    }
    matrix s;
    s.m = s1.m;
    s.n = s1.n;
    s.x = (node **)calloc(s.m, sizeof(node*));
    s.y = (node **)calloc(s.n, sizeof(node*));
    int i, j, k;
    for (i = 0; i <= s.m - 1; i++)
    {
        node *a = s1.x[i];
        node *b = s2.x[i];
        node *head;
        while (a != NULL || b != NULL)
        {
            node *p = (node *)calloc(1, sizeof(node));
            if (a != NULL)
                p->i = a->i;
            else
                p->i = b->i;
            if (b == NULL || (a != NULL && a->j < b->j))
            {
                p->j = a->j;
                p->x = a->x;
                a = a->right;
            }
            else if (a == NULL || (b != NULL && a->j > b->j))
            {
                p->j = b->j;
                p->x = -b->x;
                b = b->right;
            }
            else if (a->j == b->j)
            {
                p->j = a->j;
                p->x = a->x - b->x;
                if(p->x == 0)
                {
                    a = a->right;
                    b = b->right;
                    continue;
                }
                a = a->right;
                b = b->right;
            }
            /*------------------------------------------------*/
            if (s.x[i] == NULL)
            {
                s.x[i] = p;
                head = s.x[i];
            }
            else
            {
                head->right = p;
                head = head->right;
            }
            /*------------------------------------------------*/
            j = p->j;
            node *down = s.y[j];
            if (s.y[j] == NULL)
            {
                s.y[j] = p;
                down = s.y[j];
            }
            else
            {
                while (down->down != NULL)
                {
                    down = down->down;
                }
                down->down = p;
                down = down->down;
            }
        }
    }
    return s;
}

matrix by(matrix s1, matrix s2)
{
    if (s1.n != s2.m)
    {
        printf("大小不一致");
        matrix tem;
        return tem;
    }
    int i, j, k;
    matrix s;
    s.m = s1.m;
    s.n = s2.n;
    s.x = (node **)calloc(s.m, sizeof(node *));
    s.y = (node **)calloc(s.n, sizeof(node *));
    for (i = 0; i <= s1.m - 1; i++)
    {
        for (j = 0; j <= s2.n - 1; j++)
        {
            int sum = 0;
            node *a = s1.x[i];
            node *b = s2.y[j];
            while (a != NULL && b != NULL)
            {
                if (a->j < b->i)
                {
                    a = a->right;
                }
                else if (a->j > b->i)
                {
                    b = b->down;
                }
                else
                {
                    sum = sum + a->x * b->x;
                    a = a->right;
                    b = b->down;
                }
            }
            if (sum == 0)
                continue;
            a = s.x[i];
            b = s.y[j];
            node *p = (node *)calloc(1, sizeof(node));
            p->i = i;
            p->j = j;
            p->x = sum;
            if (s.x[i] == NULL)
            {
                s.x[i] = p;
            }
            else
            {
                while (a->right != NULL)
                {
                    a = a->right;
                }
                a->right = p;
            }
            /*---------------------------------------------*/
            if (s.y[j] == NULL)
            {
                s.y[j] = p;
            }
            else
            {
                while (b->down != NULL)
                {
                    b = b->down;
                }
                b->down = p;
            }
        }
    }
    return s;
}

int main()
{
    matrix s1;
    matrix s2;
    init(&s1, 3, 3);
    init(&s2, 3, 3);
    print(s1);
    print(s2);
    print(add(s1, s2));
    print(by(s1, s2));
    print(minus(s1, by(s1, s2)));
    return 0;
}
/*
0 0 5
1 2 10
2 2 8
2 0 -9
#
0 0 5
1 2 10
2 1 50
2 0 -9
#
1 0 1
0 1 1
2 2 1
#
1 0 1
0 1 1
2 2 1
#





*/