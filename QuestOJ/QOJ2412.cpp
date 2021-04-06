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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=100+5;
const int MAXR=1e3+5;
const int MAXM=200+5;
const double eps=1e-4;
const double inf=1e20;

int n,m,l,r;
int x[MAXM],y[MAXM],z[MAXM];
double w[MAXM];
double f[MAXR][MAXM];

inline bool check(reg double mid){
	for(reg int i=1;i<=m;++i)
		w[i]=z[i]-mid;
	fill(f[0]+1,f[0]+n+1,-inf);
	f[0][1]=0;
	for(reg int i=1;i<=r;++i){
		fill(f[i]+1,f[i]+n+1,-inf);
		for(reg int j=1;j<=m;++j){
			if(f[i-1][x[j]]>-inf/10&&f[i][y[j]]<f[i-1][x[j]]+w[j])
				f[i][y[j]]=f[i-1][x[j]]+w[j];
			if(f[i-1][y[j]]>-inf/10&&f[i][x[j]]<f[i-1][y[j]]+w[j])
				f[i][x[j]]=f[i-1][y[j]]+w[j];
		}
		if(i>=l&&f[i][n]>0)
			return true;
	}
	return false;
}

namespace UnionFind{
	int fa[MAXN],Max[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i,Max[i]=-1;
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

int main(void){
	n=read(),m=read(),l=read(),r=read();
	UnionFind::Init(n);
	for(reg int i=1;i<=m;++i){
		x[i]=read(),y[i]=read(),z[i]=read();
		UnionFind::merge(x[i],y[i]);
		UnionFind::Max[UnionFind::find(x[i])]=max(UnionFind::Max[UnionFind::find(x[i])],z[i]);
	}
	if(UnionFind::search(1,n)){
		if(r==-1)
			printf("%.2lf\n",1.0*UnionFind::Max[UnionFind::find(1)]);
		else{
			reg double l=-1,r=1e3,mid;
			while(r-l>eps){
				mid=0.5*(l+r);
				if(check(mid))
					l=mid;
				else
					r=mid;
			}
			if(l<0)
				puts("-1");
			else
				printf("%.2lf\n",l);
		}
	}
	else
		puts("-1");
	return 0;
}