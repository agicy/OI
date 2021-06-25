#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=20+5;
const int MAXM=20+5;
const int MAXC=50+5;
const int inf=0x3f3f3f3f;
const long double eps=1e-15;
const long double d=0.999995;

int n,m,c;
int res,Min=inf;
int p[MAXC],cnt[MAXC];
int M[MAXN][MAXM],tmp[MAXN][MAXM];

inline int calc(reg int x1,reg int y1,reg int x2,reg int y2){
	reg int res=0;
	res-=(M[x1+1][y1]!=M[x1][y1])+(M[x1][y1+1]!=M[x1][y1])+(M[x2+1][y2]!=M[x2][y2])+(M[x2][y2+1]!=M[x2][y2])+(x1&&M[x1][y1]!=M[x1-1][y1])+(y1&&M[x1][y1]!=M[x1][y1-1])+(x2&&M[x2][y2]!=M[x2-1][y2])+(y2&&M[x2][y2]!=M[x2][y2-1]);
	swap(M[x1][y1],M[x2][y2]);
	res+=(M[x1+1][y1]!=M[x1][y1])+(M[x1][y1+1]!=M[x1][y1])+(M[x2+1][y2]!=M[x2][y2])+(M[x2][y2+1]!=M[x2][y2])+(x1&&M[x1][y1]!=M[x1-1][y1])+(y1&&M[x1][y1]!=M[x1][y1-1])+(x2&&M[x2][y2]!=M[x2-1][y2])+(y2&&M[x2][y2]!=M[x2][y2-1]);
	return res;
}

inline void SA(void){
	for(reg long double t=500;t>eps;t*=d){
		reg int x1=rand()%n,y1=rand()%m,x2=rand()%n,y2=rand()%m;
		reg int del=calc(x1,y1,x2,y2);
		if(res+del<Min){
			for(reg int i=0;i<n;++i)
				for(reg int j=0;j<m;++j)
					tmp[i][j]=M[i][j];
			res+=del,Min=res;
		}
		else if(exp(-del*1.00/t)*RAND_MAX>rand())
			res+=del;
		else
			swap(M[x1][y1],M[x2][y2]);
	}
	return;
}

int main(void){
	srand(time(0));
	n=read(),m=read(),c=read();
	for(reg int i=1;i<=c;++i)
		p[i]=read();
	reg int c=1;
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m;++j){
			if(p[c]<=cnt[c])
				++c;
			++cnt[c],M[i][j]=c;
			res+=(i&&M[i][j]!=M[i-1][j])+(j&&M[i][j]!=M[i][j-1]);
		}
	while(1.0*clock()/CLOCKS_PER_SEC<0.98)
		SA();
	for(reg int i=0;i<n;++i)
		for(reg int j=0;j<m;++j)
			write(tmp[i][j]),putchar(j==m-1?'\n':' ');
	flush();
	return 0;
}