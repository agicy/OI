#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e4+5;
const int MAXM=2e4+5;

int n,m;
int inDeg[MAXN];
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
    Next[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
    return;
}

bool vis[MAXN];
int f[MAXN];
int sum;
queue<int> Q;

inline void topo(void){
    for(reg int i=1;i<=n;++i){
        vis[i]=false;
        f[i]=100;
    }
    for(reg int i=1;i<=n;++i)
        if(!inDeg[i])
            Q.push(i);
    while(!Q.empty()){
        reg int u=Q.front();
        Q.pop();
        vis[u]=true,sum+=f[u];
        for(reg int i=head[u];i;i=Next[i]){
            reg int v=to[i];
            f[v]=max(f[v],f[u]+1);
            --inDeg[v];
            if(!inDeg[v])
                Q.push(v);
        }
    }
    return;
}

int main(void){
    scanf("%d%d",&n,&m);
    for(reg int i=1;i<=m;++i){
        static int a,b;
        scanf("%d%d",&a,&b);
        ++inDeg[a];
        Add_Edge(b,a);
    }
    topo();
    for(reg int i=1;i<=n;++i)
        if(!vis[i]){
            puts("Poor Xed");
            return 0;
        }
    printf("%d\n",sum);
    return 0;
}
