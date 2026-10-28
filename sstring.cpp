#include <stdio.h>
#include <stdlib.h>
struct sst
{
    char data[256];
};
int s_len(sst s)
{
    return (int)(s.data[0]);
}
bool s_init(sst *s, int len, char *in)
{
    s->data[0] = len;
    if (len > 254)
        return false;
    for (int i = 1; i <= len; i++)
    {
        s->data[i] = in[i - 1];
    }
    return true;
}
int s_sub(sst s, sst sub)
{
    int i, j, k;
    int next[256] = {0};
    i = 1;
    j = 0;
    next[i] = 0;
    while (i < sub.data[0])
    {
        if (j == 0 || sub.data[i] == sub.data[j])
        {
            next[i + 1] = j + 1;
            if (sub.data[i + 1] == sub.data[j + 1])
            {
                next[i + 1] = next[j + 1];
            }
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    i = 1;
    j = 1;
    while (i <= s_len(s) && j <= s_len(sub))
    {
        if (j==0||s.data[i] == sub.data[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
        if (j > s_len(sub))
            return i - j+1;
    }
    return 0;
}

int main()
{
    char a[20] = "abaababaabcac";
    char b[9] = "abaabcac";
    sst s, sub;
    s_init(&s, 13, a);
    s_init(&sub, 8, b);
    printf("%d", s_sub(s, sub));
    return 0;
}