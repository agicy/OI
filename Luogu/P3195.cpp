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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50000+5;

int n,L;
double sum[MAXN],dp[MAXN];

inline double a(reg int i){return sum[i]+i;}
inline double b(reg int i){return a(i)+L+1;}
inline double X(reg int i){return b(i);}
inline double Y(reg int i){return dp[i]+b(i)*b(i);}
inline double slope(reg int i,reg int j){return (Y(i)-Y(j))/(X(i)-X(j));}

int main(void){
	n=read(),L=read();
	for(int i=1;i<=n;++i){
		static int c;
		c=read();
		sum[i]=sum[i-1]+c;
	}
	reg int head=1,tail=2;
	static int Q[MAXN];
	for(reg int i=1;i<=n;++i){
		while(head+1<tail&&slope(Q[head],Q[head+1])<2*a(i))
			++head;
		dp[i]=dp[Q[head]]+(a(i)-b(Q[head]))*(a(i)-b(Q[head]));
		while(head+1<tail&&slope(i,Q[tail-2])<slope(Q[tail-2],Q[tail-1]))
			--tail;
		Q[tail++]=i;
	}
	printf("%lld\n",(ll)dp[n]);
	return 0;
}
