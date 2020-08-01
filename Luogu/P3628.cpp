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

const int MAXN=1e6+5;

int n,a,b,c;
int Q[MAXN];
ll f[MAXN],s[MAXN];

inline ll k(reg int i){
	return 2ll*a*s[i];
}

inline ll x(reg int i){
	return s[i];
}

inline ll y(reg int i){
	return f[i]+a*s[i]*s[i]-b*s[i];
}

inline double slope(reg int i,reg int j){
	return 1.0*(y(i)-y(j))/(x(i)-x(j));
}

int main(void){
	n=read(),a=read(),b=read(),c=read();
	s[0]=Q[0]=f[0]=0;
	for(reg int i=1;i<=n;++i)
		s[i]=s[i-1]+read();
	reg int head=0,tail=0;
	for(reg int i=1;i<=n;++i){
		while(head<tail&&slope(Q[head],Q[head+1])>k(i))
			++head;
		f[i]=-(k(i)*x(Q[head])-y(Q[head])-a*s[i]*s[i]-b*s[i]-c);
		while(head<tail&&slope(Q[tail-1],Q[tail])<=slope(Q[tail],i))
			--tail;
		Q[++tail]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}