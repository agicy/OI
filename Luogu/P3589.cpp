#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXM=1e6+5;

struct Node{
	int l,r;
	inline Node(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
	inline bool operator<(const Node& a)const{
		return l<a.l;
	}
};

int n,a,b,p,m;
char s[MAXM];
int tot;
Node I[MAXM<<2];

int main(void){
	scanf("%d%d%d%d%d%s",&n,&a,&b,&p,&m,s+1);
	for(reg int i=1,j=0;i<=m;++i,j=(j+a)%n){
		reg ll x,y;
		if(s[i]=='0')
			x=(p-j+n)%n,y=(-1-j+n)%n;
		else
			x=(0-j+n)%n,y=(p-1-j+n)%n;
		if(x<=y)
			I[++tot]=Node(x,y);
		else{
			I[++tot]=Node(0,y);
			I[++tot]=Node(x,n-1);
		}
	}
	for(reg int i=n-m+1,j=1ll*i*a%n;i<n;++i,j=(j+a)%n)
		I[++tot]=Node((j+b)%n,(j+b)%n);
	sort(I+1,I+tot+1);
	reg int ans=0;
	int Max=-1;
	for(reg int i=1;i<=tot;++i){
		if(I[i].l>Max)
			ans+=I[i].l-Max-1;
		Max=max(Max,I[i].r);
	}
	if(Max<n)
		ans+=n-Max-1;
	printf("%d\n",ans);
	return 0;
}