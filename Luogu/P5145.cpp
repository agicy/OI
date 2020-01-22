#include <cstdio>
#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))

bool vis[100001];
int n, t[100001], Ans[100001];
int cnt, head[100001], to[100001], Next[100001];
int time, dfn[100001], low[100001], Tarjan_cnt, color[100001];
int Stack[100001], top;

void Add_Edge(int, int);
void Tarjan(int);

int main(void){
    register int i,ans=0;
    scanf("%d",&n);
    for (i = 1; i <= n;++i){
        static int d;
        scanf("%d%d", &d, &t[i]);
        Add_Edge(i, d);
    }
    for (i = 1; i <= n;++i)
        if(!dfn[i])
            Tarjan(i);
    for (i = 1; i <= n;++i)
        Ans[color[i]] += t[i];
    for (i = 1; i <= Tarjan_cnt;++i)
        if(Ans[i]!=1)
            ans = max(ans, Ans[i]);
    printf("%d\n", ans);
    return 0;
}

void Add_Edge(int f, int t){
    Next[++cnt] = head[f];
    to[cnt] = t;
    head[f] = cnt;
    return;
}

void Tarjan(int ID){
    register int i, To;
    vis[ID] = true;
    dfn[ID] = low[ID] = ++time;
    Stack[++top] = ID;
    for (i = head[ID]; i;i=Next[ID]){
        To = to[i];
        if(!dfn[To]){
            Tarjan(To);
            low[ID] = min(low[ID], low[To]);
        }
        else if(vis[To])
            low[ID] = min(low[ID], dfn[To]);
        else
            continue;
    }
    if(dfn[ID]==low[ID]){
        ++Tarjan_cnt;
        do{
            To = Stack[top--];
            vis[To] = false;
            color[To] = Tarjan_cnt;
        } while (To != ID);
    }
    return;
}
