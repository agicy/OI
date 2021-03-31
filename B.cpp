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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

const int MAXN=500+5;
const int MAXM=(MAXN*MAXN);

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace Subtask1{
	const int MAXN=10+5;
	bool vis[MAXN];
	int ptr,tot,Q[MAXN];
	bool flag;
	inline void dfs(reg int u,reg int S){
		vis[u]=true;
		if(Q[ptr+1]==u)
			++ptr;
		else if((S>>(u-1))&1){
			vis[u]=false;
			if(Q[ptr]==u)
				--ptr;
			return;
		}
		if(ptr==tot){
			flag=true;
			vis[u]=false;
			if(Q[ptr]==u)
				--ptr;
			return;
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!vis[v]){
				dfs(v,S);
				if(flag){
					vis[u]=false;
					if(Q[ptr]==u)
						--ptr;
					return;
				}
			}
		}
		if(Q[ptr]==u)
			--ptr;
		vis[u]=false;
		return;
	}
	inline void Solve(void){
		reg int ans=0;
		for(reg int S=1;S<(1<<n);++S){
			tot=0;
			for(reg int i=1;i<=n;++i)
				if((S>>(i-1))&1)
					Q[++tot]=i;
			flag=false;
			dfs(Q[1],S);
			if(flag)
				++ans;
		}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask2{
	//const int MAXN=20+5;
	bool vis[MAXN];
	int ptr,tot,Q[MAXN];
	bool flag;
	inline void dfs(reg int u,reg int S){
		vis[u]=true;
		if(Q[ptr+1]==u)
			++ptr;
		else if((S>>(u-1))&1){
			vis[u]=false;
			if(Q[ptr]==u)
				--ptr;
			return;
		}
		if(ptr==tot){
			flag=true;
			vis[u]=false;
			if(Q[ptr]==u)
				--ptr;
			return;
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!vis[v]){
				dfs(v,S);
				if(flag){
					vis[u]=false;
					if(Q[ptr]==u)
						--ptr;
					return;
				}
			}
		}
		if(Q[ptr]==u)
			--ptr;
		vis[u]=false;
		return;
	}
	inline void Solve(void){
		reg int ans=0;
		for(reg int S=1;S<(1<<n);++S){
			tot=0;
			for(reg int i=1;i<=n;++i)
				if((S>>(i-1))&1)
					Q[++tot]=i;
			flag=false;
			dfs(Q[1],S);
			if(flag)
				++ans;
		}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask3{
	inline void Solve(void){
		printf("%d\n",sub(fpow(2,n),1));
		return;
	}
}

namespace Subtask4{
	inline void Solve(void){
		reg int inv2=fpow(2,mod-2);
		reg int ans=add(1ll*n*(n-1)%mod*inv2%mod,n);
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask5{
	int f[MAXN];
	inline vector<int> dfs(int u,reg int father){
		f[u]=1;
		vector<int> son;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				vector<int> tmp=dfs(v,u);
				son.insert(son.end(),tmp.begin(),tmp.end());
				for(reg int j=0,siz=tmp.size();j<siz;++j)
					if(tmp[j]<u)
						f[u]=add(f[u],f[tmp[j]]);
			}
		}
		son.push_back(u);
		return son;
	}
	inline void Solve(void){
		reg int ans=0;
		for(reg int i=1;i<=n;++i){
			dfs(i,0);
			ans=add(ans,f[i]);
		}
		printf("%d\n",ans);
		return;
	}
}
/*
namespace Subtask6{
	bool vis[MAXN];
	int top,S[MAXN];
	int tot,cir[MAXN];
	inline bool getCir(reg int u,reg int father){
		vis[u]=true;
		S[++top]=u;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				if(!vis[v]){
					reg bool res=getCir(v,u);
					if(res)
						return true;
				}
				else if(v!=father){
					reg int x;
					do{
						x=S[top--];
						cir[++tot]=x;
					}while(x!=v);
					return true;
				}
			}
		}
		vis[u]=false;
		--top;
		return false;
	}
	bool oncir[MAXN];
	inline int getPo(reg int u,reg int father){
		if(oncir[u])
			return u;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				reg int res=getPo(v,u);
				if(res!=-1)
					return res;
			}
		}
		return -1;
	}
	inline set<pair<int,int> > dfs(int u,reg int father,reg int x){
		set<pair<int,int> > son;
		reg int sum=0;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				if((!oncir[u])||(v!=x)){
					set<pair<int,int> > tmp=dfs(v,u,x);
					son.insert(tmp.begin(),tmp.end());
					for(set<pair<int,int> >::iterator it=tmp.begin();it!=tmp.end();++it)
						if(it->first<u)
							sum=add(sum,it->second);
				}
			}
		}
		son.insert(make_pair(u,sum));
		return son;
	}
	inline void Solve(void){
		getCir(1,0);
		printf("tot=%d\n",tot);
		for(reg int i=1;i<=tot;++i){
			printf("%d%c",cir[i],i==tot?'\n':' ');
		}
		for(reg int i=1;i<=tot;++i)
			oncir[cir[i]]=true;
		for(reg int i=1;i<=n;++i){
			reg int x=getPo(i,0);
			dfs(i,0,x);
		}
		return;
	}
}*/

int main(void){
	n=read(),m=read();
	reg bool subtask3flag=(m==n-1);
	reg bool subtask4flag=(m==n-1);
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		if(a!=i||b!=i+1)
			subtask3flag=false;
		if(a!=1||b!=i+1)
			subtask4flag=false;
		Add_Edge(a,b),Add_Edge(b,a);
	}
	if(n<=10)
		//puts("S1"),
		Subtask1::Solve();
	else if(subtask3flag)
		//puts("S3"),
		Subtask3::Solve();
	else if(subtask4flag)
		//puts("S4"),
		Subtask4::Solve();
	else if(m==n-1)
		//puts("S5"),
		Subtask5::Solve();
	else if(n<=20)
		//puts("S2"),
		Subtask2::Solve();
	else
		Subtask2::Solve();
	return 0;
}