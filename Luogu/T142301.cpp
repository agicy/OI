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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=5e5+5;

int n;
int a[MAXN],x[MAXN];

namespace Subtask2{
	const ll inf=0x3f3f3f3f3f3f3f3f;
	bool vis[MAXN];
	int p[MAXN];
	struct Node{
		int A,B;
		inline Node(reg int A=0,reg int B=0):A(A),B(B){
			return;
		}
		inline bool operator<(const Node& x)const{
			return min(a[A],a[B])>min(a[x.A],a[x.B]);
		}
	};
	Node unit[MAXN];
	bool flag;
	ll ans=inf;
	Node Ans[MAXN];
	inline void check(void){
		reg int tot=0;
		for(reg int i=1;i<=n;i+=2){
			reg int a=p[i],b=p[i+1];
			if(x[a]==b||x[b]==a)
				return;
			else
				unit[++tot]=Node(a,b);
		}
		flag=true;
		sort(unit+1,unit+tot+1);
		reg ll sum=0;
		for(reg int i=1;i<=tot;++i)
			sum+=1ll*i*min(a[unit[i].A],a[unit[i].B]);
		if(sum<ans){
			for(reg int i=1;i<=tot;++i)
				Ans[i]=unit[i];
			ans=sum;
		}
		return;
	}
	inline void dfs(reg int dep){
		if(dep>n){
			check();
			return;
		}
		for(reg int i=1;i<=n;++i){
			if(!vis[i]){
				vis[i]=true;
				p[dep]=i;
				dfs(dep+1);
				vis[i]=false;
			}
		}
		return;
	}
	inline void Solve(void){
		flag=false;
		dfs(1);
		if(!flag)
			puts("-1");
		else{
			printf("%lld\n",ans);
			for(reg int i=1;i<=n/2;++i)
				printf("%d %d\n",Ans[i].A,Ans[i].B);
		}
		return;
	}
}

namespace Subtask3{
	struct Node{
		int l,r;
		inline Node(reg int l=0,reg int r=0):l(l),r(r){
			return;
		}
	};
	Node unit[MAXN];
	int id[MAXN];
	inline bool cmp(reg int x,reg int y){
		return a[x]<a[y];
	}
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			id[i]=i;
		sort(id+1,id+n+1,cmp);
		reg int m=n/2;
		for(reg int i=1;i<=m;++i){
			unit[m-i+1]=Node(id[i],id[n-i+1]);
		}
		reg ll sum=0;
		for(reg int i=1;i<=m;++i)
			sum+=1ll*i*min(a[unit[i].l],a[unit[i].r]);
		printf("%lld\n",sum);
		for(reg int i=1;i<=m;++i)
			printf("%d %d\n",unit[i].l,unit[i].r);
		return;
	}
}

namespace Subtask6{
	vector<int> V;
	int val[MAXN],ag[MAXN];
	pair<int,int> Ans[MAXN];
	int fa[MAXN];
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
	bool vis[MAXN];
	int id[MAXN];
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			V.push_back(a[i]);
		sort(V.begin(),V.end());
		V.erase(unique(V.begin(),V.end()),V.end());
		for(reg int i=1;i<=n;++i){
			reg int pos=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
			val[pos]=a[i];
			id[pos]=i;
			if(x[i]!=-1){
				reg int xpos=lower_bound(V.begin(),V.end(),a[x[i]])-V.begin()+1;
				ag[pos]=xpos;
			}
		}/*
		for(reg int i=1;i<=n;++i)
			printf("val=%d ag=%d\n",val[i],ag[i]);*/
		for(reg int i=1;i<=n+1;++i)
			fa[i]=i;
		reg int m=n/2;
		reg int tot=m;
		for(int i=1;i<=n;++i){
			if(!vis[i]){
				vis[i]=true;
				merge(i+1,i);
				int ptr=1;
				reg bool flag=false;
				while(ptr<=n){
					ptr=find(ptr);
					if(ptr>n)
						break;
					if(ag[i]!=ptr&&ag[ptr]!=i){
						flag=true;
						vis[ptr]=true;
						merge(ptr+1,ptr);
						break;
					}
					else
						++ptr;
				}
				if(!flag){
					puts("-1");
					exit(0);
				}
				else{
					Ans[tot--]=make_pair(i,ptr);
				}
			}
		}
		reg ll sum=0;
		for(reg int i=1;i<=m;++i){
			sum+=1ll*i*val[Ans[i].first];
		}
		printf("%lld\n",sum);
		for(reg int i=1;i<=m;++i)
			printf("%d %d\n",id[Ans[i].first],id[Ans[i].second]);
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg bool S3=true;
	for(reg int i=1;i<=n;++i){
		x[i]=read();
		if(x[i]!=-1)
			S3=false;
	}
	if(n<=10)
		Subtask2::Solve();
	else if(S3)
		Subtask3::Solve();
	else
		Subtask6::Solve();
	return 0;
}