#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

char str[1024];
int n,m;

namespace Subtask10{
	inline void Solve(void){
		const char str[]="Your program should output itself here.\nSounds very difficult, yeah?\nAnyway, good luck!";
		puts(str);
		return;
	}
}

namespace Subtask1{
	bitset<1<<22> S;
	inline void Solve(void){
		S[0]=0;
		for(reg int i=0;i<n;++i){
			reg int l=(1<<i),r=(l<<1);
			for(reg int j=l;j<r;++j)
				S[j]=(!S[j-l]);
		}
		for(reg int i=0;i<(1<<22);++i)
			putchar(S[i]+'0');
		putchar('\n');
		return;
	}
}

namespace Subtask2{
	string a="0",b="1",c;
	inline void Solve(void){
		for(reg int i=1;i<n;++i){
			c=a+b;
			a=b;
			b=c;
		}
		cout<<a<<endl;
		return;
	}
}

namespace Subtask3{
	inline void Solve(void){
		unordered_set<string> M;
		string s="000000000001",res="";
		for(;;){
			res+=s[0];
			M.insert(s);
			s+=s[0];
			s.erase(0,1);
			while(M.count(s)&&s!="000000000000"){
				++s[11];
				for(reg int i=11;i>=0&&s[i]=='3';--i){
					s[i]='0';
					if(i)
						++s[i-1];
				}
			}
			if(s=="000000000000")
				break;
		}
		cout<<0<<res<<"00000000000"<<endl;
		return;
	}
}

namespace Subtask4{
	const int p=104857601;
	inline int pow(reg int x,reg int exp,reg int mod){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			exp>>=1;
		}
		return res;
	}
	const int MAXSIZE=524288;
	int fac[MAXSIZE],invfac[MAXSIZE];
	inline int binom(reg int n,reg int m){
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
	}
	inline void Solve(void){
		fac[0]=invfac[0]=1;
		for(reg int i=1;i<MAXSIZE;++i)
			fac[i]=1ll*fac[i-1]*i%p;
		invfac[MAXSIZE-1]=pow(fac[MAXSIZE-1],p-2,p);
		for(reg int i=MAXSIZE-2;i>=1;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		reg int m=2*n;
		printf("%d\n",m);
		for(reg int i=0;i<=m;++i)
			printf("%d\n",binom(m,i));
		return;
	}
}

namespace Subtask5{
	const int p=104857601;
	inline int pow(reg int x,reg int exp,reg int mod){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			exp>>=1;
		}
		return res;
	}
	const int MAXSIZE=524288;
	int fac[MAXSIZE],invfac[MAXSIZE];
	inline int binom(reg int n,reg int m){
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
	}
	inline void Solve(void){
		fac[0]=invfac[0]=1;
		for(reg int i=1;i<MAXSIZE;++i)
			fac[i]=1ll*fac[i-1]*i%p;
		invfac[MAXSIZE-1]=pow(fac[MAXSIZE-1],p-2,p);
		for(reg int i=MAXSIZE-2;i>=1;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		reg int m=n/2;
		printf("%d\n",m);
		for(reg int i=0;i<=m;++i)
			printf("%d\n",(i&1)?(p-binom(m,i)):(binom(m,i)));
		return;
	}
}

namespace Subtask6{
	const int p=104857601;
	inline int pow(reg int x,reg int exp,reg int mod){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			exp>>=1;
		}
		return res;
	}
	const int a=23333333;
	const int b=33333333;
	const int MAXSIZE=524288;
	int fac[MAXSIZE],invfac[MAXSIZE];
	inline int binom(reg int n,reg int m){
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
	}
	inline void Solve(void){
		fac[0]=invfac[0]=1;
		for(reg int i=1;i<MAXSIZE;++i)
			fac[i]=1ll*fac[i-1]*i%p;
		invfac[MAXSIZE-1]=pow(fac[MAXSIZE-1],p-2,p);
		for(reg int i=MAXSIZE-2;i>=1;--i)
			invfac[i]=1ll*invfac[i+1]*(i+1)%p;
		reg int m=177147;
		printf("%d\n",m);
		for(reg int i=0;i<=m;++i)
			printf("%lld\n",1ll*binom(m,i)*pow(b,i,p)%p*pow(a,m-i,p)%p);
		return;
	}
}

namespace Subtask7{
	const int MAXV=1e5+5;
	const int MAXE=1e5+5;
	const int MAXQ=2e5+5;
	const int inf=0X7F7F7F7F;
	namespace UnionFind{
		int fa[MAXV];
		inline void Init(reg int S){
			for(reg int i=1;i<=S;++i)
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
	int q;
	inline void Solve(void){
		using namespace UnionFind;
		Init(n);
		q=read();
		for(reg int i=1;i<=m;++i){
			static int a,b;
			a=read(),b=read();
			merge(a,b);
		}
		for(reg int i=1;i<=q;++i){
			static int a,b;
			a=read(),b=read();
			printf("%d\n",search(a,b)?0:inf);
		}
		return;
	}
}

namespace Subtask8{
	const int MAXV=1e5+5;
	const int MAXE=2e5+5;
	const int MAXQ=2e5+5;
	const int MAXLOG2V=17+1;
	int q;
	int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int fa[MAXV][MAXLOG2V],Max[MAXV][MAXLOG2V];
	int dep[MAXV];
	inline void DFS(reg int u,reg int father){
		fa[u][0]=father;
		dep[u]=dep[father]+1;
		for(reg int i=1;i<MAXLOG2V;++i){
			fa[u][i]=fa[fa[u][i-1]][i-1];
			Max[u][i]=max(Max[u][i-1],Max[fa[u][i-1]][i-1]);
			if(!fa[u][i])
				break;
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				Max[v][0]=w[i];
				DFS(v,u);
			}
		}
		return;
	}
	inline int LCA(int x,int y){
		int res=0;
		if(dep[x]>dep[y])
			swap(x,y);
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(dep[fa[y][i]]>=dep[x]){
				res=max(res,Max[y][i]);
				y=fa[y][i];
			}
		if(x==y)
			return res;
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i]){
				res=max(res,max(Max[x][i],Max[y][i]));
				x=fa[x][i],y=fa[y][i];
			}
		return max(res,max(Max[x][0],Max[y][0]));
	}
	inline void Solve(void){
		q=read();
		for(reg int i=1;i<=m;++i){
			static int u,v,w;
			u=read(),v=read(),w=read();
			Add_Edge(u,v,w);
			Add_Edge(v,u,w);
		}
		DFS(1,0);
		for(reg int i=1;i<=q;++i){
			static int u,v;
			u=read(),v=read();
			printf("%d\n",LCA(u,v));
		}
		return;
	}
}

namespace Subtask9{
	const int MAXV=5e4+5;
	const int MAXLOG2V=16+1;
	const int MAXE=1e5+5;
	const int MAXQ=2e5+5;
	struct Edge{
		int u,v,len;
		inline void Read(void){
			u=read(),v=read(),len=read();
			return;
		}
		inline bool operator<(const Edge& a)const{
			return len<a.len;
		}
	};
	namespace UnionFind{
		int fa[MAXV];
		inline void Init(reg int S){
			for(reg int i=1;i<=S;++i)
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
	int cnt,head[MAXV],to[MAXV<<1],w[MAXV<<1],Next[MAXV<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int fa[MAXV][MAXLOG2V],Max[MAXV][MAXLOG2V];
	int dep[MAXV];
	inline void DFS(reg int u,reg int father){
		fa[u][0]=father;
		dep[u]=dep[father]+1;
		for(reg int i=1;i<MAXLOG2V;++i){
			fa[u][i]=fa[fa[u][i-1]][i-1];
			Max[u][i]=max(Max[u][i-1],Max[fa[u][i-1]][i-1]);
			if(!fa[u][i])
				break;
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				Max[v][0]=w[i];
				DFS(v,u);
			}
		}
		return;
	}
	inline int LCA(int x,int y){
		int res=0;
		if(dep[x]>dep[y])
			swap(x,y);
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(dep[fa[y][i]]>=dep[x]){
				res=max(res,Max[y][i]);
				y=fa[y][i];
			}
		if(x==y)
			return res;
		for(reg int i=MAXLOG2V-1;i>=0;--i)
			if(fa[x][i]!=fa[y][i]){
				res=max(res,max(Max[x][i],Max[y][i]));
				x=fa[x][i],y=fa[y][i];
			}
		return max(res,max(Max[x][0],Max[y][0]));
	}
	int m,q;
	Edge E[MAXE];
	inline void Solve(void){
		UnionFind::Init(n);
		m=read(),q=read();
		for(reg int i=1;i<=m;++i)
			E[i].Read();
		sort(E+1,E+m+1);
		for(reg int i=1;i<=m;++i){
			reg int u=E[i].u,v=E[i].v;
			if(!UnionFind::search(u,v)){
				UnionFind::merge(u,v);
				Add_Edge(u,v,E[i].len);
				Add_Edge(v,u,E[i].len);
			}
		}
		DFS(1,0);
		for(reg int i=1;i<=q;++i){
			static int u,v;
			u=read(),v=read();
			if(!UnionFind::search(u,v))
				printf("%d\n",0x7f7f7f7f);
			else
				printf("%d\n",LCA(u,v));
		}
		return;
	}
}

int main(void){
	scanf("%s",str);
	if(str[0]=='M')
		Subtask10::Solve();
	else{
		sscanf(str,"%d",&n);
		switch(n){
			case 22:{
				Subtask1::Solve();
				break;
			}
			case 33:{
				Subtask2::Solve();
				break;
			}
			case 12:{
				Subtask3::Solve();
				break;
			}
			case 131072:{
				Subtask4::Solve();
				break;
			}
			case 262144:{
				Subtask5::Solve();
				break;
			}
			case 531441:{
				Subtask6::Solve();
				break;
			}
			case 50000:{
				Subtask9::Solve();
				break;
			}
			default:{
				m=read();
				switch(m){
					case 100000:{
						Subtask7::Solve();
						break;
					}
					case 99999:{
						Subtask8::Solve();
						break;
					}
					default:break;
				}
			}
		}
	}
	return 0;
}