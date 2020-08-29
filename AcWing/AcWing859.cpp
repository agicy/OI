#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXM=2e5+5;

struct Edge{
    int u,v,w;
    inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
        return;
    }
    inline bool operator<(const Edge& a)const{
        return w<a.w;
    }
};

namespace UnionFind{
    int fa[MAXN];
    inline void Init(reg int n){
        for(reg int i=1;i<=n;++i)
            fa[i]=i;
        return;
    }
    inline int find(reg int x){
        if(x==fa[x])
            return x;
        else
            return fa[x]=find(fa[x]);
    }
    inline void merge(reg int a,reg int b){
        reg int ra=find(a),rb=find(b);
        if(ra!=rb)
            fa[rb]=ra;
        return;
    }
    inline bool search(reg int a,reg int b){
        return find(a)==find(b);
    }
}

int n,m;
Edge E[MAXM];

int main(void){
    scanf("%d%d",&n,&m);
    for(reg int i=1;i<=m;++i){
        static int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        E[i]=Edge(u,v,w);
    }
    sort(E+1,E+m+1);
    reg int cnt=n,sum=0;
    UnionFind::Init(n);
    for(reg int i=1;i<=m&&cnt>1;++i)
        if(!UnionFind::search(E[i].u,E[i].v)){
            --cnt;
            sum+=E[i].w;
            UnionFind::merge(E[i].u,E[i].v);
        }
    if(cnt!=1)
        puts("impossible");
    else
        printf("%d\n",sum);
    return 0;
}
