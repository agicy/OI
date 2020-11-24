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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;

struct Node{
	int x,val;
	inline Node(reg int x=0,reg int val=0):x(x),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return x<a.x||(x==a.x&&val<a.val);
	}
};

int n;
Node a[3*MAXN];

int main(void){
	n=read();
	reg int tot=0;
	for(reg int i=1;i<=n;++i){
		static int l,r;
		l=read(),r=read();
		a[++tot]=Node(l,1),a[++tot]=Node(r,0),a[++tot]=Node(r+1,-1);
	}
	sort(a+1,a+tot+1);
	reg int sum=0;
	ll ans=0;
	for(reg int i=1;i<=tot;++i){
		sum+=a[i].val;
		ans=max(ans,1ll*sum*a[i].x);
	}
	printf("%lld\n",ans);
	return 0;
}