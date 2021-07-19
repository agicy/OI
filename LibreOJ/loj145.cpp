#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=1e6+5;

int n,m,r;
int v[MAXN];
int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int siz[MAXN];
int tim,dfn[MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	dfn[u]=++tim;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
	return;
}

namespace BIT{
	struct Data{
		ll v,vi;
		inline Data(void){return;}
		inline Data(const ll& v,const ll& vi):v(v),vi(vi){return;}
		inline Data operator+(const Data& a)const{return Data(v+a.v,vi+a.vi);}
	};
	int n;
	Data unit[MAXN];
	inline void init(reg int s){
		n=s;
		return;
	}
	inline void __update(reg int id,const Data& val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=unit[i]+val;
		return;
	}
	inline ll __query(reg int id){
		Data res(0ll,0ll);
		for(reg int i=id;i;i^=lowbit(i))
			res=res+unit[i];
		return 1ll*(id+1)*res.v-res.vi;
	}
	inline void update(reg int l,reg int r,reg ll val){
		__update(l,Data(val,val*l)),__update(r+1,Data(-val,-val*(r+1)));
		return;
	}
	inline ll query(reg int l,reg int r){
		return __query(r)-__query(l-1);
	}
}

bool ed;

int main(void){
	n=read(),m=read(),r=read();
	for(reg int i=1;i<=n;++i)
		v[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs(r,0);
	BIT::init(n);
	for(reg int i=1;i<=n;++i)
		BIT::update(dfn[i],dfn[i],v[i]);
	while(m--){
		static int a;
		switch(read()){
			case 1:{
				a=read();
				BIT::update(dfn[a],dfn[a]+siz[a]-1,read());
				break;
			}
			case 2:{
				a=read();
				writeln(BIT::query(dfn[a],dfn[a]+siz[a]-1));
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}