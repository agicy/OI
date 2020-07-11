#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 16777216
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

const int MAXN=200000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	ll unit[MAXN];
	inline void Init(reg int size){
		n=size;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int ID,reg ll val){
		for(reg int i=ID;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll Query(reg int ID){
		reg ll res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
};

int n;
int a[MAXN];
TreeArray T;

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

int l[MAXN],r[MAXN];

inline void Work(void){
	T.Init(n);
	for(reg int i=1;i<=n;++i){
		l[i]=T.Query(a[i]);
		r[i]=a[i]-1-l[i];
		T.Update(a[i],1);
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		reg int x=n-i-r[i];
		ans=(ans-((ll)x*(x-1)*(x-2)/6)%MOD+MOD)%MOD;
	}
	T.Init(n);
	for(reg int i=1;i<=n;++i){
		ans=(ans+(n-i-r[i])*T.Query(a[i]))%MOD;
		T.Update(a[i],l[i]);
	}
	T.Init(n);
	for(reg int i=1;i<=n;++i){
		ans=(ans+(l[i]*(i-1)-T.Query(a[i])-(ll)l[i]*(l[i]-1)/2)*(n-i-r[i])%MOD+MOD)%MOD;
		T.Update(a[i],i);
	}
	T.Init(n);
	for(reg int i=n;i>=1;--i){
		ans=(ans+(T.Query(a[i])-(ll)r[i]*(r[i]+1)/2)*(n-i-r[i])%MOD+MOD)%MOD;
		T.Update(a[i],a[i]);
	}
	printf("%d\n",ans);
	return;
}
