#include<bits/stdc++.h>
typedef long long ll;

namespace Quick {
	class InStream {
	private:
		char buf[1<<21],*p1,*p2,failed;
		inline char getc() {
			return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
		}
		template<class Type> inline int read(Type &x) {
			bool k=false;char c=getc();
			for(;!isdigit(c);c=getc()) {k|=(c=='-');if(c==EOF) return 0;}
			x=0;for(;isdigit(c);c=getc()) x=(x<<1)+(x<<3)+(c^48);
			x*=(k?-1:1); return 1;
		}
		inline int read(char *s) {
			*s=getc();
			for(;isspace(*s)||*s==EOF;*s=getc()) if(*s==EOF) return 0;
			for(;!isspace(*s)&&*s!=EOF;*s=getc()) s++;
			*s='\0'; return 1;
		}
	public:
		operator int() const {
			return ~failed;
		}
		InStream() {p1=p2=buf;failed=0x00;}
		~InStream() {}
		template<class Type> InStream& operator >> (Type &&x) {
			if(read(x)) failed=0x00;
			else failed=0xff;
			return *this;
		}
	}cin;
	class OutStream {
	private:
		char buf[1<<21];int p1;const int p2=1<<21;
		inline void flush() {
			fwrite(buf,1,p1,stdout);
			p1=0;
		}
		inline void putc(const char &c) {
			if(p1==p2) flush();
			buf[p1++]=c;
		}
		template<class Type> inline void write(Type x) {
			static char buf[25];int p=-1;
			if(x==0) putc('0');
			else for(;x;x/=10) buf[++p]=x%10+48;
			while(~p) putc(buf[p--]);
		}
		inline void write(char *s) {
			for(;*s;s++) putc(*s);
		}
		inline void write(const char *s) {
			for(;*s;s++) putc(*s);
		}
		inline void write(const char &c) {putc(c);}
	public:
		OutStream() {p1=0;}
		~OutStream() {flush();}
		template<class Type> OutStream& operator << (const Type &x) {
			write(x);return *this;
		}
	}cout;
	const char endl('\n');
	template<class Type> inline Type max(const Type &a,const Type &b) {
		if(a<b) return b;
		return a;
	}
	template<class Type> inline Type min(const Type &a,const Type &b) {
		if(a<b) return a;
		return b;
	}
	template<class Type> inline void swap(Type &a,Type &b) {
		static Type tmp;
		tmp=a;a=b;b=tmp;
	}
	template<class Type> inline Type abs(const Type &a) {
		return a>=0?a:-a;
	}
}

using namespace Quick;

inline void cMax(int &a,const int& b){
	if(a<b)
		a=b;
	return;
}

inline void cMin(int &a,const int& b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;

struct Circle{
	int x[2],r,id;
	inline void Read(int i){
		id=i;
		cin>>x[0]>>x[1]>>r;
		return;
	}
	inline bool operator<(const Circle& a)const{
		return r<a.r;
	}
};

int n,q;
Circle p[MAXN];

int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(int u,int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN];
int siz[MAXN],son[MAXN];

inline void dfs1(int u,int father){
	siz[u]=1;
	fa[u]=father;
	dep[u]=dep[father]+1;
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
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

inline void dfs2(int u,int father,int topf){
	top[u]=topf;
	if(!son[u])
		return;
	dfs2(son[u],u,topf);
	for(int i=head[u];i;i=Next[i]){
		int v=to[i];
		if(v!=father&&v!=son[u])
			dfs2(v,u,v);
	}
	return;
}

inline int lca(int x,int y){
	while(top[x]!=top[y]){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=fa[top[y]];
	}
	return dep[x]<dep[y]?x:y;
}

bool vis[MAXN];

inline bool contain(const Circle& big,const Circle& small){
	ll dx=small.x[0]-big.x[0],dy=small.x[1]-big.x[1];
	ll dx2=dx*dx,dy2=dy*dy;
	return (dx2+dy2<=1ll*big.r*big.r);
}

namespace kD_Tree{
	const double alpha=0.95;
	const int MAXWD=2;
	
	struct Node{
		int lson,rson;
		int siz;
		int Max[MAXWD],Min[MAXWD];
		Circle p;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define siz(x) unit[(x)].siz
		#define Max(x) unit[(x)].Max
		#define Min(x) unit[(x)].Min
		#define p(x) unit[(x)].p
	};

	int WD,tot;
	int root;
	int top,S[MAXN];
	Node unit[MAXN];
	Circle dustbin[MAXN];

	inline bool operator<(const Circle& a,const Circle& b){
		return a.x[WD]<b.x[WD];
	}
	inline int NewNode(void){
		return top?S[top--]:++tot;
	}
	inline void pushup(const int& k){
		Max(k)[0]=Min(k)[0]=p(k).x[0];
		Max(k)[1]=Min(k)[1]=p(k).x[1];
		int l=lson(k),r=rson(k);
		if(l){
			cMax(Max(k)[0],Max(l)[0]);
			cMax(Max(k)[1],Max(l)[1]);
			cMin(Min(k)[0],Min(l)[0]);
			cMin(Min(k)[1],Min(l)[1]);
		}
		if(r){
			cMax(Max(k)[0],Max(r)[0]);
			cMax(Max(k)[1],Max(r)[1]);
			cMin(Min(k)[0],Min(r)[0]);
			cMin(Min(k)[1],Min(r)[1]);
		}
		siz(k)=siz(l)+siz(r)+1;
		return;
	}
	inline int Build(int l,int r,const int& wd){
		if(l>r)
			return 0;
		int mid=(l+r)>>1;
		int k=NewNode();
		WD=wd;
		std::nth_element(p+l,p+mid,p+r+1);
		p(k)=dustbin[mid];
		lson(k)=Build(l,mid-1,wd^1),rson(k)=Build(mid+1,r,wd^1);
		pushup(k);
		return k;
	}
	inline void ReBuild(const int& k,const int& num){
		if(lson(k))
			ReBuild(lson(k),num);
		dustbin[siz(lson(k))+num+1]=p(k);
		S[++top]=k;
		if(rson(k))
			ReBuild(rson(k),num+siz(lson(k))+1);
		return;
	}
	inline void check(int &k,const int& wd){
		if(siz(k)*alpha<max(siz(lson(k)),siz(rson(k)))){
			ReBuild(k,0);
			k=Build(1,siz(k),wd);
		}
		return;
	}
	inline void Insert(int &k,const Circle& P,const int& wd){
		if(!k){
			k=NewNode();
			lson(k)=rson(k)=0;
			p(k)=P;
			pushup(k);
			return;
		}
		if(P.x[wd]<=p(k).x[wd])
			Insert(lson(k),P,wd^1);
		else
			Insert(rson(k),P,wd^1);
		pushup(k);
		check(k,wd);
		return;
	}
	inline bool out(const int& x1,const int& y1,const int& x2,const int& y2,const int& X1,const int& Y1,const int& X2,const int& Y2) {
		return (x1>X2||x2<X1||y1>Y2||y2<Y1);
	}
	inline void query(const int& k,const Circle& a){
		if(!k)
			return;
		if(out(a.x[0]-a.r,a.x[1]-a.r,a.x[0]+a.r,a.x[1]+a.r,Min(k)[0],Min(k)[1],Max(k)[0],Max(k)[1]))
			return;
		if(!vis[p(k).id]&&contain(a,p(k))){
			Add_Edge(a.id,p(k).id);
			vis[p(k).id]=true;
		}
		query(lson(k),a),query(rson(k),a);
		return;
	}
}

int main(void){
	cin>>n;
	for(int i=1;i<=n;++i)
		p[i].Read(i);
	std::sort(p+1,p+n+1);
	for(int i=1;i<=n;++i){
		kD_Tree::query(kD_Tree::root,p[i]);
		kD_Tree::Insert(kD_Tree::root,p[i],0);
	}
	int Vit=n+1;
	for(int i=1;i<=n;++i)
		if(!vis[i])
			Add_Edge(Vit,i);
	dfs1(Vit,0);
	dfs2(Vit,0,Vit);
	cin>>q;
	while(q--){
		static int u,v,l,ans;
		cin>>u>>v;
		l=lca(u,v);
		ans=max(dep[u]-dep[l]-1,0)+max(dep[v]-dep[l]-1,0);
		cout<<ans<<endl;
	}
	return 0;
}