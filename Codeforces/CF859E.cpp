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

const int MAXN=1e5+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

namespace UnionFind{
	int fa[MAXN<<1],siz[MAXN<<1];
	bool cir[MAXN<<1];
	bool del[MAXN<<1];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,siz[i]=1,cir[i]=false,del[i]=false;
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
			del[ra]=del[ra]||del[rb];
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

using namespace UnionFind;

int n;

int main(void){
	n=read();
	Init(n<<1);
	for(reg int i=1;i<=n;++i){
		static int x,y;
		x=read(),y=read();
		if(x==y)
			del[find(x)]=true;
		else if(search(x,y))
			cir[find(x)]=true;
		else
			merge(x,y);
	}
	reg int ans=1;
	for(reg int i=1;i<=(n<<1);++i)
		if(find(i)==i&&!del[find(i)]){
			if(cir[find(i)])
				ans=add(ans,ans);
			else
				ans=1ll*ans*siz[find(i)]%mod;
		}
	printf("%d\n",ans);
	return 0;
}