#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=100000+5;
const int MAXLOG2N=17+1;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int q;

inline void Read(void){
	q=read();
	return;
}

struct TreeD{
	int l,r;
	inline TreeD(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
};

int n;
int dep[MAXN];
int color[MAXN];
int fa[MAXN][MAXLOG2N];
TreeD a[MAXN];

inline int LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x])
			y=fa[y][i];
	if(x==y)
		return x;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i])
			x=fa[x][i],y=fa[y][i];
	return fa[x][0];
}

inline int GetDis(reg int x,reg int y){
	reg int lca=LCA(x,y);
	return dep[x]+dep[y]-(dep[lca]<<1);
}

inline void Work(void){
	while(q--){
		static char opt;
		do
			opt=getchar();
		while(opt!='B'&&opt!='Q');
		if(opt=='B'){
			static int p;
			p=read();
			++n;
			if(p==-1){
				fa[n][0]=0;
				dep[n]=0;
				color[n]=n;
				a[n]=TreeD(n,n);
			}
			else{
				fa[n][0]=p;
				dep[n]=dep[p]+1;
				color[n]=color[p];
				for(reg int i=1;i<MAXLOG2N;++i)
					fa[n][i]=fa[fa[n][i-1]][i-1];
				reg int temp=color[p];
				reg int dis1=GetDis(n,a[temp].l);
				reg int dis3=GetDis(a[temp].l,a[temp].r);
				if(dis1>dis3)
					a[temp].r=n;
				reg int dis2=GetDis(n,a[temp].r);
				if(dis2>dis3)
					a[temp].l=n;
			}
		}
		else if(opt=='Q'){
			static int k;
			k=read();
			reg int temp=color[k];
			int dis1=GetDis(a[temp].l,k);
			int dis2=GetDis(a[temp].r,k);
			printf("%d\n",max(dis1,dis2));
		}
	}
	return;
}
