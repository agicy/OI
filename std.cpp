#include<bits/stdc++.h>
using namespace std;
 
template<typename T>
inline void Read(T &n){
    char ch; bool flag=false;
    while(!isdigit(ch=getchar()))if(ch=='-')flag=true;
    for(n=ch^48;isdigit(ch=getchar());n=(n<<1)+(n<<3)+(ch^48));
    if(flag)n=-n;
}
 
enum{
    MAXN = 200005
};
 
int n, ans[MAXN];
 
int fa[MAXN], sz[MAXN];
int Find(int x){return fa[x]==x?x:fa[x]=Find(fa[x]);}
set<int>::iterator it;
set<int>p[MAXN], st1, st2;
/*
    1 all
    2 sz>1
*/
 
inline void merge(int u, int v){
/*
    i in u, ans[i] in v
*/
    // printf("merge(%d %d)\n",u,v);
    if(!p[u].empty()){
        st1.erase(*p[u].begin());
        if(sz[u]>1) st2.erase(*p[u].begin());
    }
    if(!p[v].empty()){
        st1.erase(*p[v].begin());
        if(sz[v]>1) st2.erase(*p[v].begin());
    }
    p[v].erase(p[v].begin());
    if(p[u].size() > p[v].size()) swap(p[u],p[v]);
    for(it=p[u].begin(); it!=p[u].end(); it++) p[v].insert(*it);
    p[u].clear();
    fa[u] = v; sz[v] += sz[u]-2;
    if(!p[v].empty()){
        st1.insert(*p[v].begin());
        if(sz[v]>1) st2.insert(*p[v].begin());
    }
}
 
inline void check(){
    for(int i=1; i<=2*n; i++) if(Find(i)==i){
        printf("%d sz=%d ",i,sz[i]);
        for(it=p[i].begin(); it!=p[i].end(); it++) printf("%d ",*it);
        puts("");
    }
    for(it=st1.begin(); it!=st1.end(); it++) printf("%d ",*it); puts("");
    for(it=st2.begin(); it!=st2.end(); it++) printf("%d ",*it); puts("");
}
 
int main(){
    // freopen("3.in","r",stdin);
    // freopen("333.out","w",stdout);
    Read(n);
    for(int i=1; i<=2*n; i++) fa[i] = i, sz[i] = 1;
    for(int i=n+1; i<=2*n; i++) p[i].insert(i);
    for(int i=1; i<n; i++){
        int x, y;
        Read(x); Read(y);
        x = Find(x); y = Find(y);
        sz[y] += sz[x];
        fa[x] = y;
        if(p[x].size() > p[y].size()) swap(p[x],p[y]);
        for(it=p[x].begin(); it!=p[x].end(); it++) p[y].insert(*it);
        p[x].clear();
    }
    for(int i=1; i<=2*n; i++) if(Find(i)==i and !p[i].empty()){
        st1.insert(*p[i].begin());
        if(sz[i]>1) st2.insert(*p[i].begin());
    }
    // check();
    for(int i=n; i; i--){
        // for(int j=n+1; j<=2*n; j++) if(vis[j]==false and Find(i)!=Find(j) and (i==1 or sz[Find(i)]+sz[Find(j)]>2)){
        //     ans[i] = j;
        //     sz[Find(i)] += sz[Find(j)]-2;
        //     fa[Find(j)] = Find(i);
        //     break;
        // }
        // vis[ans[i]] = true;
 
        if(sz[Find(i)]==1 and i!=1){
            assert(!st2.empty());
            int cur = *st2.begin();
            if(Find(cur)!=Find(i)) ans[i] = cur;
            else st2.erase(cur), assert(!st2.empty()), ans[i] = *st2.begin(), st2.insert(cur);
        }
        else{
            assert(!st1.empty());
            int cur = *st1.begin();
            if(Find(cur)!=Find(i)) ans[i] = cur;
            else st1.erase(cur), assert(!st1.empty()), ans[i] = *st1.begin(), st1.insert(cur);
        }
        merge(Find(i),Find(ans[i]));
        // check();
    }
    for(int i=1; i<=n; i++) printf("%d\n",i);
    for(int i=n; i; i--) printf("%d\n",ans[i]);
    return 0;
}