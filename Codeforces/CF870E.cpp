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
const int mod=1e9+7;

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

namespace UnionFind{
	int fa[MAXN<<1],siz[MAXN<<1];
	bool cir[MAXN<<1];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,siz[i]=1,cir[i]=false;
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
		if(ra!=rb){
			fa[rb]=ra;
			siz[ra]+=siz[rb];
			cir[ra]=cir[ra]||cir[rb];
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

using namespace UnionFind;

int n;
int x[MAXN],y[MAXN];
vector<int> Vx,Vy;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		x[i]=read(),y[i]=read();
		Vx.push_back(x[i]),Vy.push_back(y[i]);
	}
	sort(Vx.begin(),Vx.end()),Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
	sort(Vy.begin(),Vy.end()),Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
	for(reg int i=1;i<=n;++i)
		x[i]=lower_bound(Vx.begin(),Vx.end(),x[i])-Vx.begin()+1;
	for(reg int i=1;i<=n;++i)
		y[i]=lower_bound(Vy.begin(),Vy.end(),y[i])-Vy.begin()+1;
	reg int m1=Vx.size(),m2=Vy.size();
	Init(m1+m2);
	for(reg int i=1;i<=n;++i)
		if(search(x[i],y[i]+m1))
			cir[find(x[i])]=true;
		else
			merge(x[i],y[i]+m1);
	reg int ans=1;
	for(reg int i=1;i<=m1+m2;++i)
		if(find(i)==i){
			if(cir[i])
				ans=1ll*ans*fpow(2,siz[i])%mod;
			else
				ans=1ll*ans*sub(fpow(2,siz[i]),1)%mod;
		}
	printf("%d\n",ans);
	return 0;
}