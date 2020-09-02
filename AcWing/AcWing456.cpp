#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e3+5;
const int MAXM=1e3+5;
const int MAXE=MAXN*MAXN;

int n,m;
bool vis[MAXN];
bool G[MAXN][MAXN];
int cnt,head[MAXN],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
    Next[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
    return;
}

int inDeg[MAXN],f[MAXN];
queue<int> Q;

inline void topo(void){
    for(reg int i=1;i<=n;++i){
        f[i]=1;
        if(!inDeg[i])
            Q.push(i);
    }
    while(!Q.empty()){
        reg int u=Q.front();
        Q.pop();
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
        static int s,p[MAXN];
        scanf("%d",&s);
        for(reg int j=1;j<=s;++j){
            scanf("%d",&p[j]);
            vis[p[j]]=true;
        }
        for(reg int k=p[1];k<=p[s];++k)
            if(!vis[k])
                for(reg int j=1;j<=s;++j)
                    if(!G[k][p[j]]){
                        G[k][p[j]]=true;
                        ++inDeg[p[j]];
                        Add_Edge(k,p[j]);
                    }
        for(reg int j=1;j<=s;++j)
            vis[p[j]]=false;
    }
    topo();
    reg int ans=1;
    for(reg int i=1;i<=n;++i)
        ans=max(ans,f[i]);
    printf("%d\n",ans);
    return 0;
}
