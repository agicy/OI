#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=1000+5;

struct Node{
	double l,r;
	inline Node(void){
		l=r=0;
		return;
	}
	inline Node(reg double a,reg double b){
		l=a,r=b;
		return;
	}
	inline bool operator<(const Node& a)const{
		return r<a.r;
	}
};

int n;
double d;
double x[MAXN],y[MAXN];
int cnt;
Node I[MAXN];

int main(void){
	n=read(),d=read();
	for(reg int i=1;i<=n;++i){
		x[i]=read(),y[i]=read();
		if(y[i]>d)
			return puts("-1"),0;
		reg double temp=sqrt(d*d-y[i]*y[i]);
		I[++cnt]=Node(x[i]-temp,x[i]+temp);
	}
	sort(I+1,I+cnt+1);
	reg int ans=0;
	reg double now=-1e36;
	for(reg int i=1;i<=cnt;++i)
		if(now<I[i].l){
			++ans;
			now=I[i].r;
		}
	printf("%d\n",ans);
	return 0;
}
