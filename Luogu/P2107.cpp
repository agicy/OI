#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e5+5;

struct Node{
	ll x;
	int t;
	inline void Read(void){
		x=readll(),t=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return x<a.x;
	}
};

int n;
ll m;
Node a[MAXN];
priority_queue<int> Q;

int main(void){
	n=read(),m=readll();
	for(reg int i=1;i<=n;++i)
		a[i].Read();
	sort(a+1,a+n+1);
	reg int cnt=0;
	int ans=0;
	reg ll sum=0;
	for(reg int i=1;i<=n;++i){
		sum+=a[i].x-a[i-1].x+a[i].t;
		Q.push(a[i].t);
		while(!Q.empty()&&sum>m){
			sum-=Q.top();
			Q.pop();
			--cnt;
		}
		if(sum>m)
			break;
		cMax(ans,++cnt);
	}
	printf("%d\n",ans);
	return 0;
}