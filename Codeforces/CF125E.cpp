#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline void Err(void){
	puts("-1");
	exit(0);
}

const int MAXN=5e3+5;
const int MAXM=1e5+5;
const int inf=0x3f3f3f3f;

struct Edge{
	int id,u,v,w;
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

int n,m,k;
int cnt=1,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
Edge e[MAXM];
int fa[MAXN],id[MAXM<<1];
vector<int> V,E;
bool del[MAXM<<1],rem[MAXM];
ll Max[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len),Add_Edge(v,u,len);
	return;
}

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline void dfs(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[i]&&v!=1){
			if(w[i]>=w[Max[u]])
				Max[v]=i;
			else
				Max[v]=Max[u];
			dfs(v,u);
		}
	}
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i)
		e[i].id=i,e[i].u=read(),e[i].v=read(),e[i].w=read();
	for(reg int i=1;i<=n;++i)
		fa[i]=i;
	sort(e+1,e+m+1);
	for(reg int i=1;i<=m;++i){
		reg int u=find(e[i].u),v=find(e[i].v);
		if(u!=v&&u!=1&&v!=1){
			fa[u]=v;
			E.push_back(e[i].id);
			Add_Tube(e[i].u,e[i].v,e[i].w);
			id[cnt]=id[cnt^1]=e[i].id;
		}
	}
	for(reg int i=1;i<=m;++i)
		if(e[i].u==1||e[i].v==1){
			reg int u=find(e[i].u),v=find(e[i].v);
			if(u==v)
				V.push_back(i);
			else{
				fa[u]=v;
				Add_Tube(e[i].u,e[i].v,e[i].w);
				E.push_back(e[i].id);
				--k;
			}
		}
	for(reg int i=2;i<=n;++i)
		if(find(i)!=find(i-1)){
			puts("-1");
			exit(0);
		}
	if(k<0)
		Err();
	for(reg int i=1;i<=k;++i){
		if(!V.size())
			Err();
		memset(Max,0,sizeof(Max));
		for(reg int j=head[1];j;j=Next[j])
			dfs(to[j],1);
		reg int ans=inf,ptr=-1;
		for(reg int j=V.size()-1;j>=0;--j){
			reg int id=V[j],u=max(e[id].u,e[id].v);
			if(e[id].w-w[Max[u]]<ans)
				ans=e[id].w-w[Max[u]],ptr=j;
		}
		reg int x=V[ptr],u=e[x].u^e[x].v^1;
		Add_Tube(e[x].v,e[x].u,e[x].w);
		E.push_back(e[x].id);
		rem[id[Max[u]]]=true;
		del[Max[u]]=del[Max[u]^1]=true;
		V.erase(V.begin()+ptr);
	}
	write(n-1),putchar('\n');
	for(reg int i=E.size()-1;i>=0;--i)
		if(!rem[E[i]])
			write(E[i]),putchar(i==0?'\n':' ');
	flush();
	return 0;
}