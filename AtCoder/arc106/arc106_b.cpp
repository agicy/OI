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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;

namespace UnionFind{
	int fa[MAXN];
	ll sum[MAXN];
	inline void Init(reg int n,reg int a[],reg int b[]){
		for(reg int i=1;i<=n;++i){
			fa[i]=i;
			sum[i]=a[i]-b[i];
		}
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
			sum[ra]+=sum[rb];
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m;
int a[MAXN],b[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	UnionFind::Init(n,a,b);
	for(reg int i=1;i<=m;++i){
		static int c,d;
		c=read(),d=read();
		UnionFind::merge(c,d);
	}
	reg bool flag=true;
	for(reg int i=1;i<=n&&flag;++i){
		reg int r=UnionFind::find(i);
		if(UnionFind::sum[r])
			flag=false;
	}
	puts(flag?"Yes":"No");
	return 0;
}