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

inline ll cost(reg int val,reg int cnt){
	reg int x=val/cnt,y=val%cnt;
	return 1ll*x*x*(cnt-y)+1ll*(x+1)*(x+1)*y;
}

struct Node{
	int a,cnt;
	ll delta;
	inline Node(reg int a=0,reg int cnt=1):a(a),cnt(cnt){
		delta=cost(a,cnt)-cost(a,cnt+1);
		return;
	}
	inline bool operator<(const Node& a)const{
		return delta<a.delta;
	}
	inline bool operator>(const Node& a)const{
		return delta>a.delta;
	}
};

int n,m,T;
priority_queue<Node,vector<Node>,less<Node>/**/> Q;

int main(void){
	n=read(),m=read(),T=read();
	while(T--){
		reg ll ans=0;
		for(reg int i=1;i<=n;++i){
			static int a;
			a=read();
			ans+=cost(a,1);
			Q.push(Node(a,1));
		}
		reg int cnt=m;
		while(cnt--){
			static Node s;
			s=Q.top();
			Q.pop();
			ans-=s.delta;
			Q.push(Node(s.a,s.cnt+1));
		}
		while(!Q.empty())
			Q.pop();
		printf("%lld\n",ans);
	}
	return 0;
}