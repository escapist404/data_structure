#include <stdio.h>
#include <stdlib.h>
struct node
{
    int mark = 0;
    double x = 0;
    node *next = NULL;
    node *in = NULL;
};
double read_num(char in[], int &n)
{
    char input[256] = "";
    int i = 0;
    double res = 0;
    while ((in[n] >= '0' && in[n] <= '9') || in[n] == '.')
    {
        input[i++] = in[n++];
    }
    sscanf(input, "%lf", &res);
    return res;
}

node *init(char in[], int &n)
{
    node *p = (node *)calloc(1, sizeof(node));
    if (in[n] == '(')
    {
        p->mark = 1;
        n++;
        p->in = init(in, n);
    }
    else if (in[n] >= '0' && in[n] <= '9')
    {
        p->mark = 0;
        p->x = read_num(in, n);
    }
    if (in[n] == ')')
    {
        p->next = NULL;
        return p;
    }
    else if (in[n] == ',')
    {
        n++;
        p->next = init(in, n);
        return p;
    }
    else
    {
        return p;
    }
}

void depth(node *p, int t, int &d)
{
    if (t > d)
    {
        d = t;
    }
    if (p->mark == 1)
    {
        depth(p->in, t + 1, d);
    }
    if (p->next != NULL)
    {
        depth(p->next, t, d);
    }
    return;
}
void print(node *p)
{
    if (p->mark == 1)
    {
        printf("(");
        print(p->in);
        printf(")");
    }
    if (p->mark == 0)
    {
        printf("%.3lf", p->x);
    }
    if (p->next != NULL)
    {
        printf(" , ");
        print(p->next);
    }
    return;
}

node *copy(node *a)
{
    node *p = (node *)calloc(1, sizeof(node));
    if (a->mark == 0)
    {
        p->x = a->x;
    }
    else if (a->mark == 1)
    {
        p->mark=1;
        p->in = copy(a->in);
    }
    if (a->next != NULL)
    {
        p->next = copy(a->next);
    }
    return p;
}

int main()
{
    char input[256] = "";
    scanf("%s", &input);
    int n = 0;
    node *s = init(input, n);
    print(s);
    printf("\n");
    int depth0 = 0;
    depth(s, 0, depth0);
    printf("%d", depth0);
    printf("\n");
    node* t = copy(s);
    print(t);
    printf("\n");
    return 0;
}
/*
(1,(2,3))



*/
