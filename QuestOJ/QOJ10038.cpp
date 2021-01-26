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

inline double max(reg double a,reg double b){
	return a>b?a:b;
}

inline double min(reg double a,reg double b){
	return a<b?a:b;
}

const int MAXN=300+5;
const double inf=1e50;
const double eps=1e-8;

int n;
double x[MAXN],y[MAXN];
double k[MAXN],b[MAXN];

inline double calc(reg double x,reg double y){
	reg double res=0;
	for(reg int i=1;i<n;++i)
		res=max(res,k[i]*x+b[i]-y);
	return res;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read();
	for(reg int i=1;i<=n;++i)
		y[i]=read();
	for(reg int i=1;i<n;++i){
		k[i]=(y[i+1]-y[i])/(x[i+1]-x[i]);
		b[i]=y[i]-x[i]*k[i];
	}
	reg double ans=inf;
	for(reg int i=1;i<n;++i){
		reg double l=x[i],r=x[i+1],lmid,rmid,lval,rval;
		while(r-l>eps){
			lmid=l+(r-l)/3.0,rmid=r-(r-l)/3.0;
			lval=calc(lmid,k[i]*lmid+b[i]),rval=calc(rmid,k[i]*rmid+b[i]);
			if(lval<rval)
				r=rmid;
			else
				l=lmid;
		}
		ans=min(ans,min(lval,rval));
	}
	printf("%.3lf\n",ans);
	return 0;
}