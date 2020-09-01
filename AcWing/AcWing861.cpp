#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN1=500+5;
const int MAXN2=500+5;
const int MAXM=1e5+5;
const int MAXV=MAXN1+MAXN2;
const int MAXE=2*(MAXV+MAXM);
const int inf=0x3f3f3f3f;

int n1,n2,m;
int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
    Next[++cnt]=head[u];
    to[cnt]=v;
    w[cnt]=len;
    head[u]=cnt;
    return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
    Add_Edge(u,v,len);
    Add_Edge(v,u,0);
    return;
}

int dep[MAXV];
queue<int> Q;

inline bool bfs(reg int s,reg int t){
    memset(dep,-1,sizeof(dep));
    dep[s]=0,Q.push(s);
    while(!Q.empty()){
        reg int u=Q.front();
        Q.pop();
        for(reg int i=head[u];i;i=Next[i]){
            reg int v=to[i];
            if(dep[v]==-1&&w[i]){
                dep[v]=dep[u]+1;
                Q.push(v);
            }
        }
    }
    return dep[t]!=-1;
}

int cur[MAXV];

inline int dfs(reg int u,reg int t,reg int lim){
    if(u==t)
        return lim;
    reg int flow=0;
    for(reg int &i=cur[u];i;i=Next[i]){
        reg int v=to[i];
        if(dep[v]==dep[u]+1&&w[i]){
            reg int f=dfs(v,t,min(lim-flow,w[i]));
            if(f){
                flow+=f;
                w[i]-=f;
                w[i^1]+=f;
                if(flow==lim)
                    break;
            }
        }
    }
    return flow;
}

inline int dinic(reg int s,reg int t){
    reg int res=0;
    while(bfs(s,t)){
        memcpy(cur,head,sizeof(head));
        res+=dfs(s,t,inf);
    }
    return res;
}

int main(void){
    scanf("%d%d%d",&n1,&n2,&m);
    reg int s=0,t=n1+n2+1;
    for(reg int i=1;i<=m;++i){
        static int l,r;
        scanf("%d%d",&l,&r);
        Add_Tube(l,r+n1,1);
    }
    for(reg int i=1;i<=n1;++i)
        Add_Tube(s,i,1);
    for(reg int i=1;i<=n2;++i)
        Add_Tube(i+n1,t,1);
    printf("%d\n",dinic(s,t));
    return 0;
}
