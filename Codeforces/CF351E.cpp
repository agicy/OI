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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e3+5;
const int MAXA=1e5+5;

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXA];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
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

namespace BIT2{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXA];
	inline void Init(reg int s){
		n=s;
		memset(unit,0,sizeof(unit));
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

int n;
int a[MAXN];

int main(void){
	n=read();
	reg int Max=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read()+1;
		Max=max(Max,a[i]);
	}
	reg int ans=0;
	BIT1::Init(Max),BIT2::Init(Max);
	for(reg int i=1;i<=n;++i)
		BIT1::update(a[i],1);
	for(reg int i=1;i<=n;++i){
		BIT1::update(a[i],-1);
		ans+=min(BIT1::query(a[i]-1),BIT2::query(a[i]-1));
		BIT2::update(a[i],1);
	}
	printf("%d\n",ans);
	return 0;
}