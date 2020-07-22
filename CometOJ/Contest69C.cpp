#include<cstdio>
#include<cstring>
#include<algorithm>
using std::max;
#define reg register
typedef long long ll;

const int MAXN=200000+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
ll f[MAXN],g[MAXN];
ll d[MAXN],son[MAXN],son_w[MAXN],up[MAXN];
ll pre[MAXN],las[MAXN];

void Init(void);
inline void Add_Edge(reg int u,reg int v,reg int len);
void DFS1(int ID,int fa);
void DFS2(int ID,int fa);

int main(void){
	reg int i;
    reg ll ans=0;
    scanf("%d",&n);
    for(i=1;i<n;++i){
    	static int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
		Add_Edge(x,y,z);
		Add_Edge(y,x,z);
	}
    DFS1(1,0),DFS2(1,0);
    for(i=1;i<=n;++i)
        ans=max(ans,f[i]*g[i]);
    Init();
    for(i=1;i<=cnt;++i)
        w[i]=-w[i];
    DFS1(1,0),DFS2(1,0);
    for(i=1;i<=n;++i)
        ans=max(ans,f[i]*g[i]);
    printf("%lld\n",ans);
    return 0;
}
void Init(void){
    memset(f,0,sizeof(f)),memset(d,0,sizeof(d));
    memset(pre,0,sizeof(pre)),memset(las,0,sizeof(las)),memset(up,0,sizeof(up));
    memset(g,0,sizeof(g)),memset(son,0,sizeof(son)),memset(son_w,0,sizeof(son_w));
}

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

void DFS1(int ID,int fa){
	reg int i;
    for(i=head[ID];i;i=Next[i])
        if(to[i]!=fa){
            DFS1(to[i],ID);
            f[ID]=max(d[to[i]]+d[ID]+w[i],f[ID]);
            d[ID]=max(d[ID],d[to[i]]+w[i]);
            f[ID]=max(f[ID],f[to[i]]);
        }
	return;
}

void DFS2(int ID,int fa){
    reg int i,cnt=0;
    reg ll Max=-1e15;
    for(int i=head[ID];i;i=Next[i])
        if(to[i]!=fa)
            son[++cnt]=to[i],son_w[cnt]=w[i];
    pre[0]=0,las[cnt+1]=0;
    for(i=1;i<=cnt;++i)
        pre[i]=max(pre[i-1],d[son[i]]+son_w[i]);
    for(i=cnt;i>=1;--i)
        las[i]=max(las[i+1],d[son[i]]+son_w[i]);
    for(i=1;i<=cnt;++i){
        up[son[i]]=max(up[son[i]],up[ID]+son_w[i]);
        up[son[i]]=max(up[son[i]],max(pre[i-1],las[i+1])+son_w[i]);
        g[son[i]]=max(g[son[i]],g[ID]);
        g[son[i]]=max(g[son[i]],pre[i-1]+las[i+1]);
        g[son[i]]=max(g[son[i]],max(pre[i-1],las[i+1])+up[ID]);
        g[son[i]]=max(g[son[i]],Max);
        Max=max(Max,f[son[i]]);
    }
    for(i=head[ID];i;i=Next[i])
        if(to[i]!=fa)
            DFS2(to[i],ID);
	return;
}
