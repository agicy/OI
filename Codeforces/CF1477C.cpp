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

const int MAXN=5e3+5;

int n;
int x[MAXN],y[MAXN];
int fa[MAXN];
bool vis[MAXN];

inline double sqr(reg double x){
	return x*x;
}

inline double getDis(reg int i,reg int j){
	return sqrt(sqr(x[i]-x[j])+sqr(y[i]-y[j]));
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),y[i]=read();
	reg int top=0;
	static int S[MAXN];
	reg int p=1;
	for(reg int i=1;i<=n;++i){
		vis[p]=true;
		reg int ptr=0;
		reg double dis=0;
		for(reg int j=1;j<=n;++j)
			if(!vis[j]&&getDis(p,j)>dis){
				ptr=j;
				dis=getDis(p,j);
			}
		S[++top]=p;
		p=ptr;
	}
	for(reg int i=1;i<=top;++i)
		printf("%d%c",S[i],i==top?'\n':' ');
	return 0;
}