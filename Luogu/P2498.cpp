#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define eps 1e-4
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=3000+10;

int n,row,line;
int x[MAXN],y[MAXN];

inline double sqr(reg double x){
	return x*x;
}

bool vis[MAXN];
queue<int> Q;

inline bool check(reg double R){
	memset(vis,false,sizeof(vis));
	while(!Q.empty())Q.pop();
	for(int i=1;i<=n;++i)
		if(x[i]<R||line-y[i]<R){
			vis[i]=true;
			Q.push(i);
		}
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		if(row-x[u]<R||y[u]<R)
			return false;
		for(int i=1;i<=n;++i)
			if(!vis[i])
				if(sqr(x[i]-x[u])+sqr(y[i]-y[u])<4.0*R*R){
					vis[i]=true;
					Q.push(i);
				}
	}
	return true;
}

int main(void){
	n=read(),row=read()-1,line=read()-1;
	for(reg int i=1;i<=n;++i)
		x[i]=read()-1,y[i]=read()-1;
	reg double l=0,r=min(row,line),mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			l=mid;
		else
			r=mid;
	}
	printf("%.2lf\n",r);
	return 0;
}
