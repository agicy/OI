#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<11,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<11],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=100;

struct Segment{
	int l,mid,r;
	inline bool operator<(const Segment& a)const{
		return mid<a.mid;
	}
};

int n;
Segment a[MAXN+1];
int f[MAXN+1][MAXN*3],g[MAXN*3];

int main(void){
	n=read();
	vector<int> V;
	V.reserve(3*n);
	for(reg int i=1;i<=n;++i){
		static int p,l;
		p=read(),l=read();
		a[i].l=p-l,a[i].mid=p,a[i].r=p+l;
		V.push_back(a[i].l),V.push_back(a[i].mid),V.push_back(a[i].r);
	}
	sort(a+1,a+n+1);
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i){
		a[i].l=lower_bound(V.begin(),V.end(),a[i].l)-V.begin();
		a[i].mid=lower_bound(V.begin(),V.end(),a[i].mid)-V.begin();
		a[i].r=lower_bound(V.begin(),V.end(),a[i].r)-V.begin();
	}
	reg int m=V.size();
	for(reg int i=1;i<=n;++i){
		for(reg int j=0;j<m;++j)
			f[i][j]=f[i-1][j];
		fill(g,g+m,0);
		reg int Maxr=a[i].mid;
		g[a[i].mid]=f[i][a[i].l]+V[a[i].mid]-V[a[i].l];
		for(reg int j=i-1;j>=1;--j){
			Maxr=max(Maxr,a[j].r);
			g[Maxr]=max(g[Maxr],f[j-1][a[i].l]+V[Maxr]-V[a[i].l]);
		}
		for(reg int j=m-1;j>=0;--j){
			if(j+1<m)
				g[j]=max(g[j],g[j+1]-V[j+1]+V[j]);
			f[i][j]=max(f[i][j],g[j]);
		}
		for(reg int j=a[i].mid;j<=a[i].r;++j)
			f[i][j]=max(f[i][j],f[i-1][a[i].mid]+V[j]-V[a[i].mid]);
		for(reg int j=1;j<m;++j)
			f[i][j]=max(f[i][j],f[i][j-1]);
	}
	printf("%d\n",f[n][m-1]);
	return 0;
}