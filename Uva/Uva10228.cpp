#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int sqr(reg int x){
	return x*x;
}

inline double getLen(reg int dx,reg int dy){
	return sqrt(sqr(dx)+sqr(dy));
}

const int MAXN=100+5;

int n;
int x[MAXN],y[MAXN];

inline double getVal(reg int sx,reg int sy){
	reg double res=0;
	for(reg int i=1;i<=n;++i)
		res+=getLen(sx-x[i],sy-y[i]);
	return res;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			x[i]=read(),y[i]=read();
		reg int sx=5e3,sy=5e3;
		reg double ans=getVal(sx,sy),tmp;
		while(true)
			if((tmp=getVal(sx,sy-1))<ans)
				ans=tmp,--sy;
			else if((tmp=getVal(sx-1,sy))<ans)
				ans=tmp,--sx;
			else if((tmp=getVal(sx,sy+1))<ans)
				ans=tmp,++sy;
			else if((tmp=getVal(sx+1,sy))<ans)
				ans=tmp,++sx;
			else
				break;
		printf("%.0f\n",ans);
		if(t) puts("");
	}
	return 0;
}