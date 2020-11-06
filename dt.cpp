#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val>a.val;
	}
};

Node p[MAXN];
ll val[MAXN];
bool vis[MAXN];

int main(void){
	//freopen("dt.in","r",stdin);
	//freopen("dt.out","w",stdout);

	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		p[i]=Node(i,a);
	}
	for(reg int i=1;i<=m;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
		val[x]+=p[y].val,val[y]+=p[x].val;
	}

	sort(p+1,p+n+1);

	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		reg int id=p[i].id;
		ans+=val[id];
		vis[id]=true;
		for(reg int j=head[id];j;j=Next[j]){
			reg int v=to[j];
			if(!vis[v])
				val[v]-=p[i].val;
		}
	}
	printf("%lld\n",ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}