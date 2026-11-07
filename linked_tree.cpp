#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <queue>
#include <stack>
#include <vector>
using namespace std;
struct node
{
    node *left = NULL;
    node *right = NULL;
    node *father = NULL;
    char x;
};

struct forest
{
    vector<node *> data;
};

node *bt_brother(node *p);
void bt_clear(node *p);
node *bt_init(char in[], int &n, node *father);
vector<char> bt_ancestry(node *p);
vector<char> bt_cousin(node *p);
int bt_height(node *p);
int bt_leafnum(node *p);
vector<char> bt_pre_visit(node *p);
vector<char> bt_in_visit(node *p);
vector<char> bt_post_visit(node *p);
vector<char> bt_bfs(node *p);
vector<char> bt_dfs_pre(node *p);
vector<char> bt_dfs_in(node *p);
vector<char> bt_dfs_post(node *p);
node *bt_joint(char c, node *l, node *r);
forest bt_init_forest(char in[]);

/*------------------------------------------------------------函数实现------------------------------------------------------------------------*/

void print(vector<char> s)
{
    int i;
    for (i = 0; i <= s.size() - 1; i++)
    {
        printf("%c ", s[i]);
    }
    printf("\n");
    return;
}

node *bt_brother(node *p)
{
    if (p->father == NULL)
        return NULL;
    else if (p->father->left == p)
    {
        return p->father->right;
    }
    else if (p->father->right == p)
    {
        return p->father->left;
    }
    return NULL;
}

void bt_clear(node *p)
{
    if (p == NULL)
    {
        return;
    }
    bt_clear(p->left);
    bt_clear(p->right);
    return;
}

node *bt_init(char in[], int &n, node *father)
{
    node *p = (node *)calloc(1, sizeof(node));
    p->father = father;
    p->x = in[n++];
    if (in[n] == '(')
    {
        n++;
        if (in[n] != ',')
        {
            p->left = bt_init(in, n, p);
            if (in[n] != ')')
            {
                n++;
                p->right = bt_init(in, n, p);
            }
        }
        else
        {
            n++;
            p->right = bt_init(in, n, p);
        }
        n++;
    }
    return p;
}

vector<char> bt_ancestry(node *p)
{
    vector<char> res;
    while (p->father != NULL)
    {
        p = p->father;
        res.push_back(p->x);
    }
    res.reserve(res.size());
    return res;
}

vector<char> bt_cousin(node *p)
{
    vector<char> res;
    if (p->father == NULL || p->father->father == NULL || bt_brother(p->father) == NULL)
    {
        return res;
    }
    if (bt_brother(p->father)->left != NULL)
        res.push_back(bt_brother(p->father)->left->x);
    if (bt_brother(p->father)->right != NULL)
        res.push_back(bt_brother(p->father)->right->x);
    return res;
}

int bt_height(node *p)
{
    if (p == NULL)
        return 0;
    int l = bt_height(p->left) + 1;
    int r = bt_height(p->right) + 1;
    if (l > r)
        return l;
    else
        return r;
}

int bt_leafnum(node *p)
{
    if (p == NULL)
    {
        return 0;
    }
    else if (p->left == NULL & p->left == NULL)
    {
        return 1;
    }
    else
    {
        return bt_leafnum(p->left) + bt_leafnum(p->right);
    }
}

vector<char> bt_pre_visit(node *p)
{
    vector<char> res;
    if (p == NULL)
    {
        return res;
    }
    vector<char> l = bt_pre_visit(p->left);
    vector<char> r = bt_pre_visit(p->right);
    res.push_back(p->x);
    res.insert(res.end(), l.begin(), l.end());
    res.insert(res.end(), r.begin(), r.end());
    return res;
}

vector<char> bt_in_visit(node *p)
{
    vector<char> res;
    if (p == NULL)
    {
        return res;
    }
    vector<char> l = bt_in_visit(p->left);
    vector<char> r = bt_in_visit(p->right);
    res.insert(res.end(), l.begin(), l.end());
    res.push_back(p->x);
    res.insert(res.end(), r.begin(), r.end());
    return res;
}

vector<char> bt_post_visit(node *p)
{
    vector<char> res;
    if (p == NULL)
    {
        return res;
    }
    vector<char> l = bt_post_visit(p->left);
    vector<char> r = bt_post_visit(p->right);
    res.insert(res.end(), l.begin(), l.end());
    res.insert(res.end(), r.begin(), r.end());
    res.push_back(p->x);
    return res;
}

vector<char> bt_bfs(node *p)
{
    vector<char> res;
    queue<node *> s;
    if (p == NULL)
        return res;
    s.push(p);
    while (s.empty() == false)
    {
        res.push_back(s.front()->x);
        if (s.front()->left != NULL)
        {
            s.push(s.front()->left);
        }
        if (s.front()->right != NULL)
        {
            s.push(s.front()->right);
        }
        s.pop();
    }
    return res;
}

vector<char> bt_dfs_pre(node *p)
{
    vector<char> res;
    stack<node *> s;

    while (!s.empty() || p != NULL)
    {
        if (p != NULL)
        {
            res.push_back(p->x);
            s.push(p);
            p = p->left;
        }
        else
        {
            p = s.top();
            s.pop();
            p = p->right;
        }
    }
    return res;
}

vector<char> bt_dfs_in(node *p)
{
    vector<char> res;
    stack<node *> s;

    while (!s.empty() || p != NULL)
    {
        if (p != NULL)
        {
            s.push(p);
            p = p->left;
        }
        else
        {
            p = s.top();
            s.pop();
            res.push_back(p->x);
            p = p->right;
        }
    }
    return res;
}

vector<char> bt_dfs_post(node *p)
{
    vector<char> res;
    stack<node *> s;
    if (p == NULL)
        return res;
    node *last = NULL;

    while (!s.empty() || p != NULL)
    {
        if (p != NULL)
        {
            s.push(p);
            p = p->left;
        }
        else
        {
            node *now = s.top();
            if (now->right != NULL && now->right != last)
            {
                p = now->right;
            }
            else
            {
                res.push_back(now->x);
                s.pop();
                last = now;
            }
        }
    }
    return res;
}

node *bt_joint(char c, node *l, node *r)
{
    node *p = (node *)calloc(1, sizeof(node));
    p->x = c;
    if (l != NULL)
    {
        p->left = l;
        l->father = p;
    }
    if (r != NULL)
    {
        p->right = r;
        r->father = p;
    }
    return p;
}

forest bt_init_forest(char in[])
{
    int len = strlen(in), i, j, k, m = 0;
    vector<int> t;
    t.push_back(-1);
    for (i = 0; i <= len - 1; i++)
    {
        if (in[i] == '(')
        {
            m++;
        }
        if (in[i] == ')')
        {
            m--;
        }
        if (m < 0)
        {
            printf("格式错误");
        }
        if (m == 0 && in[i] == ',')
        {
            t.push_back(i);
        }
    }
    t.push_back(len - 1);
    forest res;
    for (i = 0; i <= t.size() - 2; i++)
    {
        int l = t[i + 1] - t[i] - 1;
        char s[l + 3] = "";
        memcpy(s, &in[t[i] + 1], l);
        int n = 0;
        res.data.push_back(bt_init(s, n, NULL));
    }
    return res;
}

void bt_clear_forest(forest s)
{
    for (int i = 0; i <= s.data.size() - 1; i++)
    {
        bt_clear(s.data[i]);
        s.data.pop_back();
    }
    return;
}

int main()
{
    char in1[] = "A(B(E(K,L),F),D(H(M),I))";
    char in2[] = "A(B,D(H,I)),A(B,D(H,I)),A(B,D(H,I))";
    int n = 0;
    node *p = bt_init(in1, n, NULL);
    print(bt_ancestry(p->left->left->left));
    print(bt_cousin(p->left->left));
    printf("%d\n", bt_height(p));
    printf("%d\n", bt_leafnum(p));
    print(bt_pre_visit(p));
    print(bt_dfs_pre(p));
    print(bt_in_visit(p));
    print(bt_dfs_in(p));
    print(bt_post_visit(p));
    print(bt_dfs_post(p));
    print(bt_bfs(p));
    print(bt_dfs_in(bt_joint('s', p, p)));
    forest s = bt_init_forest(in2);
    bt_clear_forest(s);

    bt_clear(p);

    return 0;
}

/*

A(B(E(K,L),F),D(H(M),I))

前序遍历（根左右）：
A B E K L F D H M I

中序遍历（左根右）：
K E L B F A M H D I

后序遍历（左右根）：
K L E F B M H I D A

*/
