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

const int MAXN=4e4+5;

struct Node{
	int x,y,v;
	inline bool operator<(const Node& a)const{
		return v<a.v;
	};
};

int n;
Node a[MAXN];
int p[MAXN<<1];
priority_queue<Node> Q;

inline bool cmp(const Node& a,const Node& b){
	return a.x<b.x;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i].x=read(),a[i].y=read(),a[i].v=read();
		p[i*2-1]=a[i].x,p[i*2]=a[i].y;
	}
	sort(a+1,a+n+1,cmp);
	sort(p+1,p+(n<<1)+1);
	reg int tot=0;
	reg ll ans=0;
	for(reg int i=1;i<(n<<1);++i){
		while(!Q.empty()&&Q.top().y<=p[i])
			Q.pop();
		while(p[i]<=a[tot+1].x&&a[tot+1].x<p[i+1])
			Q.push(a[++tot]);
		if(!Q.empty())
			ans+=1ll*(p[i+1]-p[i])*Q.top().v;
	}
	printf("%lld\n",ans);
	return 0;
}