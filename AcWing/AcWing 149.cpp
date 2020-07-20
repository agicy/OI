#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

struct Node{
    ll w,h;
    inline Node(reg ll a,reg ll b){
        w=a,h=b;
		return;
    }
	inline bool operator<(const Node& a)const{
		return w!=a.w?w>a.w:h>a.h;
	}
};

const int MAXN=100000+5;

int n,k;
ll w[MAXN];

priority_queue<Node,vector<Node>,less<Node>/**/> Q;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		Q.push(Node(w[i],1));
	reg int cnt=0;
	if((n-1)%(k-1)!=0)
		cnt=(k-1)-(n-1)%(k-1);
	for(reg int i=1;i<=cnt;++i)
		Q.push(Node(0,1));
	reg ll ans=0;
	ll Max,sum;
	while(Q.size()!=1){
		Max=sum=0;
		for(reg int i=1;i<=k;++i){
			Max=max(Max,Q.top().h);
			sum+=Q.top().w;
			Q.pop();
		}
		ans+=sum;
		Q.push(Node(sum,Max+1));
	}
	printf("%lld\n%lld\n",ans,Q.top().h-1);
	return;
}
