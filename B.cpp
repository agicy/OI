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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e6+5;

struct Node{
	int id,k;
	inline Node(reg int id=0,reg int k=0):id(id),k(k){
		return;
	}
	inline bool operator<(const Node& a)const{
		return k<a.k;
	}
};

int n;
Node a[MAXN];

int main(void){
	n=read();
	reg ll ans=0;
	for(reg int i=1,k;i<=n;++i){
		a[i]=Node(i,k=read());
		ans=max(ans,1ll*k*i);
	}
	sort(a+1,a+n+1);
	reg int Max=0;
	for(reg int i=n;i>=1;--i){
		ans=max(ans,1ll*a[i].k*(a[i].id+Max));
		Max=max(Max,a[i].id);
	}
	printf("%lld\n",ans);
	return 0;
}