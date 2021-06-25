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

const int MAXN=1e5+5;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int n,k;
int a[MAXN];
int tmp[MAXN];

int main(void){
	n=read(),k=read();
	BIT::Init(n);
	for(reg int i=1;i<=n;++i){
		a[i]=read()-k+a[i-1];
		tmp[i]=a[i];
	}
	sort(tmp,tmp+n+1);
	reg ll ans=0;
	for(reg int i=0;i<=n;++i){
		reg int pos=lower_bound(tmp,tmp+n+1,a[i])-tmp+1;
		ans+=BIT::query(pos);
		BIT::update(pos,1);
	}
	printf("%lld\n",ans);
	return 0;
}