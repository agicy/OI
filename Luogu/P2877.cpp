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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e4+9;

struct Node{
	int t,p;
	inline bool operator<(const Node& a)const{
		return t*a.p>a.t*p;
	}
};

int n;
Node a[MAXN];
ll sumt[MAXN],sump[MAXN];
double high[MAXN],low[MAXN];

inline bool check1(reg int i,reg int j,reg int t,reg int s){
	return (a[i].t-a[j].t)*(a[t].p-a[s].p)>(a[t].t-a[s].t)*(a[i].p-a[j].p);
}

inline bool check2(reg int i,reg int j,reg ll t,reg ll p){
	return (a[i].t-a[j].t)*p>t*(a[i].p-a[j].p);
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].t=read(),a[i].p=read();
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i){
		sumt[i]=sumt[i-1]+a[i].t;
		sump[i]=sump[i-1]+a[i].p;
	}
	reg int _head=0,_tail=0;
	static int Q[MAXN];
	for(reg int i=1;i<=n;++i){
		while(_head<_tail&&a[i].p>=a[Q[_tail-1]].p)
			--_tail;
		while(_tail-_head>1&&check1(Q[_tail-1],i,Q[_tail-2],Q[_tail-1]))
			--_tail;
		Q[_tail++]=i;
		while(_tail-_head>1&&check2(Q[_head],Q[_head+1],sumt[i],sump[i]))
			++_head;
		low[i]=a[Q[_head]].t-1.0*sumt[i]/sump[i]*a[Q[_head]].p;
	}
	reg int top=0;
	static int S[MAXN];
	for(reg int i=n;i>=1;--i){
		while(top>0&&a[i].p<=a[S[top]].p)
			--top;
		while(top>1&&check1(i,S[top],S[top],S[top-1]))
			--top;
		S[++top]=i;
		while(top>1&&!check2(S[top],S[top-1],sumt[i-1],sump[i-1]))
			--top;
		high[i]=a[S[top]].t-1.0*sumt[i-1]/sump[i-1]*a[S[top]].p;
	}
	reg int tot=0;
	static int ans[MAXN];
	for(reg int i=n-1;i>=1;--i)
		if(high[i+1]>low[i])
			ans[++tot]=n-i;
	writeln(tot);
	for(reg int i=1;i<=tot;++i)
		writeln(ans[i]);
	flush();
	return 0;
}