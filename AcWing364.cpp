#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline void cMin(reg int &a,reg int b){
    if(a>b)
        a=b;
    return;
}

const int MAXN=1e5+5;
const int MAXM=2e5+5;

int n,m,Q;
int a[MAXM],b[MAXM];
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
    Next[++cnt]=head[u];
    to[cnt]=v;
    head[u]=cnt;
    return;
}

bool vis[MAXN];
int tim,dfn[MAXN],low[MAXN];
int T,S[MAXN];
int tarjan_cnt,col[MAXN];

inline void tarjan(reg int u){
    vis[u]=true;
    dfn[u]=low[u]=++tim;
    S[++T]=u;
    for(reg int i=head[u];i;i=Next[i]){
        reg int v=to[i];
        if(!dfn[v]){
            tarjan(v);
            cMin(low[u],low[v]);
        }
        else if(vis[v])
            cMin(low[u],dfn[v]);
    }
    if(dfn[u]==low[u]){
        reg int v;
        ++tarjan_cnt;
        do{
            v=S[T--];
            vis[v]=false;
            col[v]=tarjan_cnt;
        }while(u!=v);
    }
    return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(reg int u,reg int father){
    siz[u]=1;
    fa[u]=father;
    dep[u]=dep[father]+1;
    for(reg int i=head[u];i;i=Next[i]){
        reg int v=to[i];
        if(v!=father){
            dfs1(v,u);
            siz[u]+=siz[v];
            if(siz[son[u]]<siz[v])
                son[u]=v;
        }
    }
    return;
}

int top[MAXN];

inline void dfs2(reg int u,reg int father,reg int topf){
    dfn[u]=++tim;
    top[u]=topf;
    if(!son[u])
        return;
    dfs2(son[u],u,topf);
    for(reg int i=head[u];i;i=Next[i]){
        reg int v=to[i];
        if(v!=father&&v!=son[u])
            dfs2(v,u,v);
    }
    return;
}

namespace SegmentTree{
    #define lson ( (k) << 1 )
    #define rson ( (k) << 1 | 1 )
    #define mid ( ( (l) + (r) ) << 1 )
    struct Node{
        int sum;
        bool tag;
        #define sum(x) unit[(x)].sum
        #define tag(x) unit[(x)].tag
    };
    Node unit[MAXN<<2];
    inline void pushup(reg int k){
        sum(k)=sum(lson)+sum(rson);
        return;
    }
    inline void build(reg int k,reg int l,reg int r){
        if(l==r){
            sum(k)=1;
            return;
        }
        build(lson,l,mid),build(rson,mid+1,r);
        pushup(k);
        return;
    }
    inline void set0(reg int k){
        sum(k)=0,tag(k)=true;
        return;
    }
    inline void pushdown(reg int k){
        if(tag(k)){
            set0(lson);
            set0(rson);
            tag(k)=false;
        }
        return;
    }
    inline void update(reg int k,reg int l,reg int r,reg int L,reg int R){
        if(L<=l&&r<=R){
            set0(k);
            return;
        }
        pushdown(k);
        if(L<=mid)
            update(lson,l,mid,L,R);
        if(R>mid)
            update(rson,mid+1,r,L,R);
        pushup(k);
        return;
    }
    inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
        if(L<=l&&r<=R)
            return sum(k);
        pushdown(k);
        reg int res=0;
        if(L<=mid)
            res+=query(lson,l,mid,L,R);
        if(R>mid)
            res+=query(rson,mid+1,r,L,R);
        return res;
    }
    #undef lson
    #undef rson
    #undef mid
}

inline void update(int u,int v){
    while(top[u]!=top[v]){
        if(dep[top[u]]>dep[top[v]])
            swap(u,v);
        SegmentTree::update(1,1,tarjan_cnt,dfn[top[v]],dfn[v]);
    }
    if(dep[u]>dep[v])
        swap(u,v);
    if(dfn[u]<dfn[v])
        SegmentTree::update(1,1,tarjan_cnt,dfn[u]+1,dfn[v]);
    return;
}

inline int query(int u,int v){
    reg int res=0;
    while(top[u]!=top[v]){
        if(dep[top[u]]>dep[top[v]])
            swap(u,v);
        res+=SegmentTree::query(1,1,tarjan_cnt,dfn[top[v]],dfn[v]);
    }
    if(dep[u]>dep[v])
        swap(u,v);
    if(dfn[u]<dfn[v])
        res+=SegmentTree::query(1,1,tarjan_cnt,dfn[u]+1,dfn[v]);
    return;
}

int main(void){
    reg int Case=0;
    while(scanf("%d%d",&n,&m)!=EOF&&n!=0&&m!=0){
        printf("Case %d:\n",++Case);
        cnt=0,memset(head,0,sizeof(head));
        tim=0,memset(dfn,0,sizeof(dfn));
        for(reg int i=1;i<=m;++i){
            scanf("%d%d",&a[i],&b[i]);
            Add_Edge(a[i],b[i]);
            Add_Edge(b[i],a[i]);
        }
        tarjan_cnt=0;
        for(reg int i=1;i<=n;++i)
            if(!dfn[i])
                tarjan(i);
        cnt=0,memset(head,0,sizeof(head));
        tim=0,memset(dfn,0,sizeof(dfn));
        for(reg int i=1;i<=n;++i)
            if(col[a[i]]!=col[b[i]]){
                Add_Edge(col[a[i]],col[b[i]]);
                Add_Edge(col[b[i]],col[a[i]]);
            }
        dfs1(1,0);
        dfs2(1,0,1);
        SegmentTree::build(1,1,tarjan_cnt);
        SegmentTree::update(1,1,tarjan_cnt,1,0);
        scanf("%d",&Q);
        reg int ans=tarjan_cnt-1;
        while(Q--){
            static int u,v;
            scanf("%d%d",&u,&v);
            ans-=query(u,v);
            update(u,v);
            printf("%d\n",ans);
        }
    }
    return 0;
}