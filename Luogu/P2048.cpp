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

const int MAXN=5e5+5;
const int MAXLOG2N=19+1;

namespace ST{
	int Lg[MAXN];
	int *p;
	int pos[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg int a[]){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			Lg[i]=Lg[i>>1]+1;
		p=a;
		for(reg int i=1;i<=n;++i)
			pos[0][i]=i;
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				if(p[pos[j-1][i]]>p[pos[j-1][i+(1<<(j-1))]])
					pos[j][i]=pos[j-1][i];
				else
					pos[j][i]=pos[j-1][i+(1<<(j-1))];
		return;
	}
	inline int queryMax(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		if(p[pos[k][l]]>p[pos[k][r-(1<<k)+1]])
			return pos[k][l];
		else
			return pos[k][r-(1<<k)+1];
	}
}

int n,k,L,R;
int a[MAXN];
int sum[MAXN];

struct Node{
	int pos,l,r,p,val;
	inline Node(reg int pos=0,reg int l=0,reg int r=0):pos(pos),l(l),r(r){
		p=ST::queryMax(l,r);
		val=sum[p]-sum[pos-1];
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
	inline bool operator>(const Node& a)const{
		return val>a.val;
	}
};

priority_queue<Node,vector<Node>,less<Node>/**/> Q;

int main(void){
	n=read(),k=read(),L=read(),R=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	ST::Init(n,sum);
	for(reg int i=1;i+L-1<=n;++i)
		Q.push(Node(i,i+L-1,min(i+R-1,n)));
	reg ll ans=0;
	while(k--){
		static Node s;
		s=Q.top();
		Q.pop();
		ans+=s.val;
		if(s.p>s.l)
			Q.push(Node(s.pos,s.l,s.p-1));
		if(s.p<s.r)
			Q.push(Node(s.pos,s.p+1,s.r));
	}
	printf("%lld\n",ans);
	return 0;
}