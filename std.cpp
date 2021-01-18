#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int A = 1e5 + 10;
class Gra{
public:
    int v,next;
}G[A<<1];
class Trie{
public:
    int ne[2],cnt;
}T[A<<5];
int val[A],head[A],root[A],tot,twt,n,m;
int dep[A],son[A],fa[A],siz[A],top[A];

void init(){
    tot = twt = T[0].cnt = 0;
    memset(T[0].ne,0,sizeof(T[0].ne));
    memset(head,-1,sizeof(head));
}

void add(int u,int v){G[tot].v = v;G[tot].next = head[u];head[u] = tot++;}

void input(){
    for(int i=1 ;i<=n ;i++) scanf("%d",&val[i]);
    for(int i=1 ;i< n ;i++){
        int u,v;scanf("%d%d",&u,&v);
        add(u,v);add(v,u);
    }
}

void dfs(int u,int pre,int d){
    son[u] = -1;siz[u] =  1;
    dep[u] = d;fa[u] = pre;
    for(int i=head[u] ;i!=-1 ;i=G[i].next){
        int v = G[i].v;
        if(v == pre) continue;
        dfs(v,u,d+1);
        siz[u] += siz[v];
        if(son[u] == -1 || siz[son[u]] < siz[v]){
            son[u] = v;
        }
    }
}

void dfs(int u,int tp){
    top[u] = tp;
    if(son[u] == -1) return;
    dfs(son[u],tp);
    for(int i=head[u] ;i!=-1 ;i=G[i].next){
        int v = G[i].v;
        if(v == son[u] || v == fa[u]) continue;
        dfs(v,v);
    }
}

int LCA(int u,int v){
    while(top[u] != top[v]){
        if(dep[top[u]] < dep[top[v]]) swap(u,v);
        u = fa[top[u]];
    }
    return dep[u]>dep[v]?v:u;
}

int insert(int y,int v){
    int res,x;
    res = x = ++twt;T[x] = T[y];
    for(int i=16 ;i>=0 ;i--){
        int c = (v>>i)&1;
        int now = ++twt;
        T[now] = T[T[x].ne[c]];
        T[now].cnt++;
        T[x].ne[c] = now;
        x = now;
    }
    return res;
}

void dfs(int u){
    root[u] = insert(root[fa[u]],val[u]);
    for(int i=head[u] ;i!=-1 ;i=G[i].next){
        int v = G[i].v;
        if(v == fa[u]) continue;
        dfs(v);
    }
}

int query(int x,int y,int z,int v){
    int ans = val[z]^v,res = 0;z = root[z];
    for(int i=16 ;i>=0 ;i--){
        int c = (v>>i)&1;
        int num = T[T[x].ne[c^1]].cnt + T[T[y].ne[c^1]].cnt - 2*T[T[z].ne[c^1]].cnt;
        if(num>0) res |= (1<<i),c^=1;
        x = T[x].ne[c],y = T[y].ne[c],z = T[z].ne[c];
    }
    return max(ans,res);
}

void solve(){
    dfs(1,0,1);dfs(1,1);dfs(1);
    for(int i=1 ;i<=m ;i++){
        int x,y,z;scanf("%d%d%d",&x,&y,&z);
        printf("%d\n",query(root[x],root[y],LCA(x,y),z));
    }
}

int main(){
    while(~scanf("%d%d",&n,&m)){
        init();input();
        solve();
    }
    return 0;
}