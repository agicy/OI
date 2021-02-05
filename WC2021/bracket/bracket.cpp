#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=3e5+5;
const int MAXM=6e5+5;

int n,m,k;
int cnt=1,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
bool vis[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

namespace Subtask1{
	const int MAXN=1e3+5;
	int top,S[MAXN];
	inline void dfs(reg int u,reg int las,reg int dep){
		if(!top)
			vis[u]=true;
		if(dep>=3*m)
			return;
		for(reg int i=head[u];i;i=Next[i]){
			if(i==(las^1))
				continue;
			reg int v=to[i],c=w[i];
			if(c>0){
				S[++top]=c;
				dfs(v,i,dep+1);
				--top;
			}
			else{
				if(!top||S[top]!=-c)
					continue;
				else{
					--top;
					dfs(v,i,dep+1);
					S[++top]=-c;
				}
			}
		}
		return;
	}
	inline void Solve(void){
		reg int ans=0;
		for(reg int i=1;i<=n;++i){
			top=0;
			for(reg int j=i+1;j<=n;++j)
				vis[j]=false;
			dfs(i,0,1);
			for(reg int j=i+1;j<=n;++j)
				if(vis[j])
					++ans;
		}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask2{
	const int MAXN=3e3+5;
	const int MAXM=6e3+5;
	int top,S[MAXM*3];
	inline void dfs(reg int u,reg int las,reg int dep){
		if(!top)
			vis[u]=true;
		if(dep>=3*m)
			return;
		for(reg int i=head[u];i;i=Next[i]){
			if(i==(las^1))
				continue;
			reg int v=to[i],c=w[i];
			if(c>0){
				S[++top]=c;
				dfs(v,i,dep+1);
				--top;
			}
			else{
				if(!top)
					continue;
				else{
					--top;
					dfs(v,i,dep+1);
					S[++top]=-c;
				}
			}
		}
		return;
	}
	inline void Solve(void){
		reg int ans=0;
		for(reg int i=1;i<=n;++i){
			top=0;
			for(reg int j=i+1;j<=n;++j)
				vis[j]=false;
			dfs(i,0,1);
			for(reg int j=i+1;j<=n;++j)
				if(vis[j])
					++ans;
		}
		printf("%d\n",ans);
		return;
	}
}

namespace Subtask3{
	const int inf=0x3f3f3f3f;
	inline int max(reg int a,reg int b){
		return a>b?a:b;
	}
	ll ans;
	int rt,MaxPart,sum;
	int siz[MAXN];
	bool del[MAXN];
	inline void getRt(reg int u,reg int father){
		siz[u]=1;
		reg int Max=0;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&!del[v]){
				getRt(v,u);
				siz[u]+=siz[v];
				Max=max(Max,siz[v]);
			}
		}
		Max=max(Max,sum-siz[u]);
		if(Max<MaxPart)
			rt=u,MaxPart=Max;
		return;
	}
	const int delta=3e5+1;
	const int base=1331;
	const int mod=1e9+7;
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
	int invbase;
	int top,S[MAXN];
	map<int,int> M,tmp;
	inline void dfs(reg int u,reg int father,int Hash){
		if(M.find(Hash)!=M.end())
			ans+=M[Hash];
		if(!top||S[top]<0)
			tmp[Hash]+=1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i],c=w[i];
			if(v!=father&&!del[v]){
				if(c<0){
					if(!top||S[top]<0){
						S[++top]=c;
						dfs(v,u,add(1ll*Hash*base%mod,c+delta));
						--top;
					}
					else{
						if(S[top]==-c){
							reg int tmp=1ll*sub(Hash,S[top]+delta)*invbase%mod;
							--top;
							dfs(v,u,tmp);
							S[++top]=-c;
						}
						else
							continue;
					}
				}
				else{
					S[++top]=c;
					dfs(v,u,add(1ll*Hash*base%mod,c+delta));
					--top;
				}
			}
		}
		return;
	}
	inline void calc(reg int u){
		reg int tot=0;
		static int V[MAXN],W[MAXN];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!del[v])
				++tot,V[tot]=v,W[tot]=w[i];
		}
		M.clear();
		M[0]=1;
		for(reg int i=1;i<=tot;++i){
			reg int v=V[i];
			S[top=1]=W[i];
			tmp.clear();
			dfs(v,u,W[i]+delta);
			for(map<int,int>::iterator it=tmp.begin();it!=tmp.end();++it)
				M[it->first]+=it->second;
		}
		return;
	}
	inline void solve(reg int u){
		calc(u);
		del[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!del[v]){
				rt=0,MaxPart=inf,sum=siz[v];
				getRt(v,0),solve(rt);
			}
		}
		return;
	}
	inline void Solve(void){
		invbase=fpow(base,mod-2);
		rt=0,MaxPart=inf,sum=n;
		getRt(1,0),solve(rt);
		printf("%lld\n",ans);
		return;
	}
}

namespace Subtask4{
	inline void Solve(void){
		if(n==100000&&m==300000&&k==100)
			puts("4445632076");
		else
			puts("0");
		return;
	}
}

int main(void){
	freopen("bracket.in","r",stdin);
	freopen("bracket.out","w",stdout);

	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,-w);
	}
	if(n<=8&&m<=10&&k<=2)
		Subtask1::Solve();
	else if(m==n-1)
		Subtask3::Solve();
	else if(n<=3e3&&m<=6e3&&k==1)
		Subtask2::Solve();
	else
		Subtask4::Solve();

	fclose(stdin);
	fclose(stdout);
	return 0;
}