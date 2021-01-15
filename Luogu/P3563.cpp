#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
    reg char ch=getchar();
    reg int res=0;
    while(!isdigit(ch))ch=getchar();
    while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
    return res;
}

const int MAXN=2.5e5+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
    Next[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
    return;
}

int siz[MAXN];
int MaxP=MAXN,rt=0;

inline void dfs(reg int u,reg int father){
    int Max=0;
    siz[u]=1;
    for(reg int i=head[u];i;i=Next[i]){
        reg int v=to[i];
        if(v!=father){
            dfs(v,u);
            siz[u]+=siz[v];
            Max=max(Max,siz[v]);
        }
    }
    Max=max(Max,n-siz[u]);
    if(MaxP>Max)
        rt=u,MaxP=Max;
    return;
}

ll ans;

inline void dp(reg int u,reg int father){
    siz[u]=1;
    for(reg int i=head[u];i;i=Next[i]){
        reg int v=to[i];
        if(v!=father){
            dp(v,u);
            siz[u]+=siz[v];
            ans+=siz[v];
        }
    }
    return;
}

int main(void){
    n=read();
    for(reg int i=1;i<n;++i){
        static int u,v;
        u=read(),v=read();
        Add_Edge(u,v),Add_Edge(v,u);
    }
    dfs(1,0);
    dp(rt,0);
    printf("%d %lld\n",n-1,ans);
    return 0;
}