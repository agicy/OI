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

const int MAXN=5000000+5;

int n,m;

struct Node{
	double x,r,v;
	inline void Read(void){
		x=read(),r=read(),v=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return r<a.r;
	}
};

Node p[MAXN];
double dp[MAXN];

inline double k(reg int i){return -p[i].x/2.0;}
inline double X(reg int i){return +1.0/sqrt(p[i].r);}
inline double Y(reg int i){return dp[i]-p[i].x/(2.0*sqrt(p[i].r));}
inline double slope(reg int i,reg int j){return (Y(i)-Y(j))/(X(i)-X(j));}

inline bool check(const Node& a){
	return (a.x-a.r<=m&&m<=a.x+a.r);
}

int main(void){
	n=read(),m=read();
	for(int i=1;i<=n;++i)
		p[i].Read();
	reg int head=1,tail=1;
	static int Q[MAXN];
	dp[1]=p[1].v;
	dp[2]=dp[1]+p[2].v+(p[2].x-p[1].x)/(2*sqrt(p[1].r));
	Q[tail++]=1;
	double ans=1e9;
	for(reg int i=3;i<=n;++i){
		while(head+1<tail&&slope(Q[head],Q[head+1])<k(i))
			++head;
		reg int j=Q[head];
		dp[i]=dp[j]+(p[i].x-p[j].x)/(2.0*sqrt(p[j].r))+p[i].v;
		if(check(p[i])){
			ans=min(ans,dp[i]);
		}
		while(head+1<tail&&slope(i,Q[tail-2])<slope(Q[tail-2],Q[tail-1]))
			--tail;
		Q[tail++]=i;
	}
	for(reg int i=1;i<=n;++i)
		printf("%.3f\n",dp[i]);
	printf("%.3f\n",ans);
	return 0;
}
