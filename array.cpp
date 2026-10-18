#include <stdio.h>
#include <stdlib.h>
struct array
{
    int dim = 0;
    int *n = NULL;
    int *data;
};

bool a_init(array *s, int dim, int *n, int *data, bool to_init = true);
int a_get(array s, int *n);
void my_print(array s, int dim, int size);
void my_add(array *s, array s1, array s2, int dim, int size);
void my_minus(array *s, array s1, array s2, int dim, int size);
array *a_add(array s1, array s2);
array *a_minus(array s1, array s2);
array *a_T(array s);
/*------------------------------------------------------------函数实现------------------------------------------------------------------------*/

bool a_init(array *s, int dim, int *n, int *data, bool to_init)
{
    int i, j, k;
    int size = 1;

    s->n = (int *)calloc(dim, sizeof(int));
    s->dim = dim;
    for (i = 0; i <= dim - 1; i++)
    {
        size = size * n[i];
    }
    s->data = (int *)calloc(size, sizeof(int));
    for (i = 0; i <= dim - 1; i++)
    {
        s->n[i] = n[i];
    }
    if (s->data == NULL)
        return false;
    if (to_init == false)
    {
        return true;
    }
    for (i = 0; i <= size - 1; i++)
    {
        s->data[i] = data[i];
    }
    return true;
}
int a_get(array s, int *n)
{
    int i;
    for (i = 0; i <= s.dim - 1; i++)
    {
        if (s.n[i] <= n[i])
        {
            printf("SB,没这个数\n");
            return 0;
        }
    }
    int size = 0, j = 1;
    for (i = s.dim - 1; i >= 0; i--)
    {
        size = size + n[i] * j;
        j = j * s.n[i];
    }
    return s.data[size];
}
bool a_set(array &s, int *n, int set)
{
    int i;
    for (i = 0; i <= s.dim - 1; i++)
    {
        if (s.n[i] <= n[i])
        {
            printf("SB,没这个数\n");
            return false;
        }
    }
    int size = 0, j = 1;
    for (i = s.dim - 1; i >= 0; i--)
    {
        size = size + n[i] * j;
        j = j * s.n[i];
    }
    s.data[size] = set;
    return true;
}
void a_free(array *s)
{
    s->dim = 0;
    free(s->n);
    free(s->data);
}
void a_print(array s)
{
    my_print(s, 0, 0);
    printf("\n");
}
array *a_add(array s1, array s2)
{
    if (s1.dim != s2.dim)
        return NULL;
    for (int i = 0; i <= s1.dim - 1; i++)
    {
        if (s1.n[i] != s2.n[i])
            return NULL;
    }
    array *s = (array *)calloc(1, sizeof(array));
    a_init(s, s1.dim, s1.n, NULL, false);
    my_add(s, s1, s2, 0, 0);
    return s;
}
array *a_minus(array s1, array s2)
{
    if (s1.dim != s2.dim)
        return NULL;
    for (int i = 0; i <= s1.dim - 1; i++)
    {
        if (s1.n[i] != s2.n[i])
            return NULL;
    }
    array *s = (array *)calloc(1, sizeof(array));
    a_init(s, s1.dim, s1.n, NULL, false);
    my_minus(s, s1, s2, 0, 0);
    return s;
}
array *a_by(array s1, array s2)
{
    if (s1.dim != 2 || s2.dim != 2 || s1.n[1] != s2.n[0])
    {
        return NULL;
    }
    int n[2] = {s1.n[0], s2.n[1]};
    array *s = (array *)calloc(1, sizeof(array));
    a_init(s, 2, n, NULL, false);
    for (int i = 0; i <= s1.n[0] - 1; i++)
    {
        for (int j = 0; j <= s2.n[1] - 1; j++)
        {
            for (int k = 0; k <= s1.n[1] - 1; k++)
            {
                s->data[i * s1.n[0] + j] += (s1.data[i * s1.n[1] + k] * s2.data[k * s2.n[1] + j]);
            }
        }
    }
    return s;
}
array *a_T(array s)
{
    int n[2] = {s.n[1], s.n[0]};
    array *res;
    a_init(res, 2, n, NULL, false);
    for (int i = 0; i <= res->n[0] - 1; i++)
        for (int j = 0; j <= res->n[1] - 1; j++)
        {
            res->data[i * res->n[1] + j] = s.data[j * s.n[1] + i];
        }
    return res;
}
/*------------------------------------------------------------辅助函数------------------------------------------------------------------------*/
void my_print(array s, int dim, int size)
{
    if (dim == s.dim)
    {
        printf("%d ", s.data[size]);
        return;
    }
    printf("[");
    for (int i = 0; i <= s.n[dim] - 1; i++)
    {
        int tem = size * s.n[dim] + i;
        my_print(s, dim + 1, tem);
    }
    printf("]");
    return;
}
void my_add(array *s, array s1, array s2, int dim, int size)
{
    if (dim == s->dim)
    {
        s->data[size] = s1.data[size] + s2.data[size];
        return;
    }
    for (int i = 0; i <= s->n[dim] - 1; i++)
    {
        int tem = size * s->n[dim] + i;
        my_add(s, s1, s2, dim + 1, tem);
    }
    return;
}
void my_minus(array *s, array s1, array s2, int dim, int size)
{
    if (dim == s->dim)
    {
        s->data[size] = s1.data[size] - s2.data[size];
        return;
    }
    for (int i = 0; i <= s->n[dim] - 1; i++)
    {
        int tem = size * s->n[dim] + i;
        my_minus(s, s1, s2, dim + 1, tem);
    }
    return;
}

int main()
{
    array s;
    int dim = 2;
    int n[dim] = {2, 3};
    int data[20] = {1, 2, 3, 4, 5, 6};
    a_init(&s, dim, n, data);
    a_print(s);
    a_print(*a_add(s, s));
    a_print(*a_minus(s, s));
    a_print(*a_T(s));
    a_print(*a_by(s, *a_T(s)));
    a_free(&s);
    return 0;
}
//, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20