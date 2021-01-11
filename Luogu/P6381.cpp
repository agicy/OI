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

const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int MAXW=1e5+5;
const int lim=1e5;

bool vis[MAXW];
int tot,prime[MAXW];

inline void Init(reg int n){
    for(reg int i=2;i<=n;++i){
        if(!vis[i])
            prime[tot++]=i;
        for(reg int j=0;j<tot&&i*prime[j]<=n;++j){
            vis[i*prime[j]]=true;
            if(!(i%prime[j]))
                break;
        }
    }
    return;
}

struct Edge{
    int u,v,w,l;
};

int n,m,k;
int f[MAXW];

inline void work(reg int u,reg int v,reg int w,reg int l){
    reg int res1=1,res2=1;
    for(reg int i=1;i<=tot&&prime[i]*prime[i]<=w;++i){
        reg int tmp=0;
        while(w%prime[i]==0){
            ++tmp;
            w/=prime[i];
        }
        if(tmp%k){
            for(reg int j=1;j<=tmp%k;++j){
                res1*=prime[i];
            }
            for(reg int j=1;j<=k-tmp%k;++j){
                res2*=prime[i];
                if(res2>lim)
                    return;
            }
        }
	}
    if(k!=1)
        res1*=w;
    for(reg int j=2;j<=k;++j){
        res2*=w;
        if(res2>lim)
            return;
    }
	f[res1]=res2;
    f[res2]=res1;
    g[res1].push_back(Edge(u,v,0,l));
    return;
}

int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
    Next[++cnt]=head[u];
    to[cnt]=v;
    w[cnt]=len;
    head[u]=cnt;
    return;
}

int main(void){
    n=read(),m=read(),k=read();
    Init(1e5);
    for(reg int i=1;i<=m;++i){
        static int u,v,w,l;
        u=read(),v=read(),w=read(),l=read();
        Work(u,v,w,l);
    }
    return 0;
}