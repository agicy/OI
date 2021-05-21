#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5+5;

struct Interval{
	int l,r;
	inline Interval(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
	inline bool in(reg int x){
		return l<=x&&x<=r;
	}
	inline bool operator<(const Interval& a)const{
		return r<a.r;
	}
	inline bool operator>(const Interval& a)const{
		return r>a.r;
	}
};

inline bool cmp(const Interval& a,const Interval& b){
	return a.l<b.l;
}

int n;
int u[MAXN],d[MAXN];
int cnt,p[MAXN];
int tot;
Interval inv[MAXN<<1];

inline void calc(reg int a[],reg int n){
	reg int top=0;
	static int S[MAXN];
	for(reg int i=1;i<=n;++i){
		if(a[i]==a[i-1])
			continue;
		if(a[i]>a[i-1])
			S[++top]=i-1;
		else{
			while(top&&a[S[top]]>a[i])
				--top;
			if(top&&a[S[top]]==a[i])
				inv[++tot]=Interval(S[top--]+1,i);
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		u[i]=read(),d[i]=read();
	calc(u,n),calc(d,n);
	reg int ans=0;
	for(reg int i=2;i<=n;++i){
		if(u[i]!=u[i-1]&&d[i]!=d[i-1])
			p[++cnt]=i;
		ans+=(u[i]!=u[i-1])+(d[i]!=d[i-1]);
	}
	sort(inv+1,inv+tot+1,cmp);
	priority_queue<Interval,vector<Interval>,greater<Interval>/**/> Q;
	ans-=cnt+tot;
	for(reg int i=1,j=1;i<=cnt;++i){
		while(j<=tot&&inv[j].l<=p[i])
			Q.push(inv[j++]);
		while(!Q.empty()&&Q.top().r<p[i])
			Q.pop();
		if(!Q.empty())
			++ans,Q.pop();
	}
	printf("%d\n",ans);
	return 0;
}