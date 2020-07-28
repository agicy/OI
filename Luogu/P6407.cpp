#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=8e4+5;

char N[MAXSIZE],M[MAXSIZE];
int K;
char type[1024];

namespace SolveA{
	const int MAXN=100+5;
	const int MAXM=100+5;
	const int MAXK=MAXN*MAXM;
	const int MAXV=MAXN*MAXM;
	const int MAXE=2*(MAXN*MAXM*2+MAXN*MAXM);
	const int dx[]={-1,0,0,1};
	const int dy[]={0,-1,1,0};
	const int INF=0X3F3F3F3F;

	int n,m;
	bool G[MAXN][MAXM];
	int id[MAXN][MAXM];

	int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int vis,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=vis;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	inline void Add_Tube(reg int u,reg int vis,reg int len){
		Add_Edge(u,vis,len);
		Add_Edge(vis,u,0);
		return;
	}
	int dep[MAXV];
	queue<int> Q;
	inline bool BFS(int s,reg int t){
		memset(dep,-1,sizeof(dep));
		while(!Q.empty())Q.pop();
		dep[s]=1,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=head[u];i;i=Next[i]){
				int vis=to[i];
				if(dep[vis]==-1&&w[i]>0){
					dep[vis]=dep[u]+1;
					Q.push(vis);
				}
			}
		}
		return dep[t]!=-1;
	}
	int cur[MAXV];
	inline int DFS(reg int u,reg int t,reg int lim){
		if(u==t)
			return lim;
		reg int flow=0;
		for(reg int &i=cur[u];i;i=Next[i]){
			reg int vis=to[i];
			if(dep[vis]==dep[u]+1&&w[i]>0){
				reg int f=DFS(vis,t,min(lim-flow,w[i]));
				if(f){
					flow+=f;
					w[i]-=f;
					w[i^1]+=f;
					if(flow==lim)
						break;
				}
			}
		}
		return flow;
	}
	inline int Dinic(reg int s,reg int t){
		reg int res=0;
		while(BFS(s,t)){
			memcpy(cur,head,sizeof(head));
			res+=DFS(s,t,INF);
		}
		return res;
	}
	inline bool check(reg int x,reg int y){
		return 1<=x&&x<=n&&1<=y&&y<=m;
	}
	inline void Solve(void){
		sscanf(N,"%d",&n);
		sscanf(M,"%d",&m);
		for(reg int i=1;i<=K;++i){
			static int x,y;
			scanf("%d%d",&x,&y);
			G[x][y]=true;
		}
		reg int cnt=0;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j)
				id[i][j]=++cnt;
		reg int s=0,t=n*m+1;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j)
				if(!G[i][j]){
					if(!((i+j)&1)){
						Add_Tube(s,id[i][j],1);
						for(reg int k=0;k<4;++k){
							reg int fx=i+dx[k],fy=j+dy[k];
							if(check(fx,fy))
								Add_Tube(id[i][j],id[fx][fy],1);
						}
					}
					else
						Add_Tube(id[i][j],t,1);
				}
		reg int ans=Dinic(s,t);
		printf("%d\n",ans);
		return;
	}
}

namespace SolveB{
	const int MAXSIZE=4e5+5;
	namespace Poly{
		const int p=998244353;
		const int g=3;
		const int invg=332748118;
		int r[MAXSIZE<<2];
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
		inline int Init(reg int len){
			reg int limit=1,l=0;
			while(limit<len)
				limit<<=1,++l;
			for(reg int i=1;i<limit;++i)
				r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
			return limit;
		}
		inline void NTT(reg int a[],reg int limit,reg int type){
			for(reg int i=0;i<limit;++i)
				if(i<r[i])
					swap(a[i],a[r[i]]);
			for(reg int i=1;i<limit;i<<=1){
				reg int w=pow(type==1?g:invg,(p-1)/(i<<1),p);
				for(reg int j=0;j<limit;j+=(i<<1)){
					reg int e=1;
					for(reg int k=0;k<i;++k,e=1ll*e*w%p){
						reg int x=a[j+k],y=1ll*e*a[j+k+i]%p;
						a[j+k]=(x+y)%p,a[j+k+i]=(x-y+p)%p;
					}
				}
			}
			if(type==-1){
				reg int inv=pow(limit,p-2,p);
				for(reg int i=0;i<limit;++i)
					a[i]=1ll*a[i]*inv%p;
			}
			return;
		}
	}
	const int Base=10;
	const int LgBase=1;
	struct BigNumber{
		int l;
		int unit[MAXSIZE];
		inline BigNumber(void){
			l=0;
			memset(unit,0,sizeof(unit));
			return;
		}
		inline void GetVal(reg char str[],reg int len){
			memset(unit,0,sizeof(unit));
			for(reg int i=len-1;i>=0;i-=LgBase){
				for(reg int j=max(i-LgBase+1,0);j<=i;++j)
					unit[l]=10*unit[l]+str[j]-'0';
				++l;
			}
			return;
		}
		inline BigNumber operator*(const BigNumber& a){
			static int A[MAXSIZE<<2],B[MAXSIZE<<2];
			memset(A,0,sizeof(A)),memset(B,0,sizeof(B));
			BigNumber res;
			for(reg int i=0;i<l;++i)
				A[i]=unit[i];
			for(reg int i=0;i<a.l;++i)
				B[i]=a.unit[i];
			reg int limit=Poly::Init(l+a.l);
			Poly::NTT(A,limit,1),Poly::NTT(B,limit,1);
			for(reg int i=0;i<limit;++i)
				A[i]=1ll*A[i]*B[i]%Poly::p;
			Poly::NTT(A,limit,-1);
			for(reg int i=0;i<l+a.l;++i)
				res.unit[i]=A[i];
			res.l=l+a.l;
			for(reg int i=0;i<res.l;++i)
				if(res.unit[i]>=Base){
					res.unit[i+1]+=res.unit[i]/Base;
					res.unit[i]%=Base;
				}
			while(!res.unit[res.l-1])
				--res.l;
			if(res.l==0)
				res.l=1;
			return res;
		}
		inline void Div(reg int a){
			reg int tmp=0;
			for(reg int i=l-1;i>=0;--i){
				unit[i]=unit[i]+tmp*Base;
				tmp=unit[i]%a;
				unit[i]/=a;
			}
			while(!unit[l-1])
				--l;
			if(l==0)
				l=1;
			return;
		}
		inline void Print(void){
			printf("%d",unit[l-1]);
			for(reg int i=l-2;i>=0;--i)
				printf("%0*d",LgBase,unit[i]);
			putchar('\n');
			return;
		}
	};
	BigNumber a,b,ans;
	inline void Solve(void){
		a.GetVal(N,strlen(N)),b.GetVal(M,strlen(M));
		ans=a*b;
		--ans.unit[0];
		ans.Div(3);
		ans.Print();
		return;
	}
}

namespace SolveC{
	const int MAXN=11+5;
	const int MAXM=11+5;
	int n,m;
	bool G[MAXN][MAXM];
	int R[210000],c[210000];
	int now,f[2][210000];
	int C[15],D[15];
	int plen[2],p[2][210000];
	bool vis[210000];
	inline void back(reg int x){
		reg int num=0;
		while(x){
			C[++num]=x%3;
			x/=3;
		}
		return;
	}
	inline int get(reg int a[]){
		reg int res=0;
		for(reg int i=m;i>=1;--i)
			res=3*res+a[i];
		return res;
	}
	inline void DFS(reg int dep1,reg int dep2,reg int s){
		if(dep1>m){
			reg int p1=get(C),p2=get(D);
			if(!vis[p2])
				vis[p2]=true,p[now][++plen[now]]=p2;
			f[now][p2]=max(f[now][p2],f[now^1][p1]+s);
			return;
		}
		if(C[dep1]==2){
			D[dep1]=1;
			DFS(dep1+1,dep2,s);
			D[dep1]=0;
			return;
		}
		if(dep2<=n-2&&!G[dep2][dep1]&&!G[dep2+1][dep1]&&!G[dep2+2][dep1]&&!C[dep1]&&!D[dep1]){
			D[dep1]=2,DFS(dep1+1,dep2,s+1),D[dep1]=0;
		}
		if(dep1<=m-2&&!C[dep1]&&!C[dep1+1]&&!C[dep1+2]&&!G[dep2][dep1]&&!G[dep2][dep1+1]&&!G[dep2][dep1+2]){
			DFS(dep1+3,dep2,s+1);
			D[dep1]=0;
		}
		if(dep1<=m-1&&dep2<n){
			if(!C[dep1]&&!C[dep1+1]&&!G[dep2][dep1]&&!G[dep2][dep1+1]){
				if(!D[dep1]&&!G[dep2+1][dep1])
					D[dep1]=1,DFS(dep1+2,dep2,s+1),D[dep1]=0;
				if(!G[dep2+1][dep1+1]) D[dep1+1]=1,DFS(dep1+2,dep2,s+1),D[dep1+1]=0;
			}
			if(!D[dep1]&&C[dep1]!=2&&C[dep1+1]!=2&&!G[dep2+1][dep1]&&!G[dep2+1][dep1+1]){
				if(!C[dep1]&&!G[dep2][dep1]){
					D[dep1]=D[dep1+1]=1;
					DFS(dep1+2,dep2,s+1);
					D[dep1]=D[dep1+1]=0;
				}
				else if(!C[dep1+1]&&!G[dep2][dep1+1]){
					D[dep1]=D[dep1+1]=1;
					DFS(dep1+2,dep2,s+1);
					D[dep1]=D[dep1+1]=0;
				}
			}
		}
		DFS(dep1+1,dep2,s);
		return;
	}
	inline void Solve(void){
		sscanf(N,"%d",&n);
		sscanf(M,"%d",&m);
		for(reg int i=1;i<=K;++i){
			static int x,y;
			scanf("%d%d",&x,&y);
			G[x][y]=true;
		}
		now=0;
		p[0][plen[0]=1]=0;
		f[0][0]=0;
		for(reg int i=1;i<=n;++i){
			memset(vis,false,sizeof(vis));
			now^=1;
			memset(f[now],-1,sizeof(f[now]));
			plen[now]=0;
			for(reg int j=1;j<=plen[now^1];++j){
				memset(C,0,sizeof(C));
				memset(D,0,sizeof(D));
				back(p[now^1][j]);
				DFS(1,i,0);
			}
		}
		int ans=0;
		for(reg int i=1;i<=plen[now];++i)
			ans=max(ans,f[now][p[now][i]]);
		printf("%d\n",ans);
		return;
	}

}

int main(void){
	scanf("%s%s%d%s",N,M,&K,type);
	switch(type[0]){
		case 'A':{
			SolveA::Solve();
			break;
		}
		case 'B':{
			SolveB::Solve();
			break;
		}
		case 'C':{
			SolveC::Solve();
			break;
		}
		default:break;
	}
	return 0;
}