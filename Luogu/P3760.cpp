#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=res*10+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1000000+5;

int n,m;
int a[MAXN],sum[MAXN];

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	ll unit[MAXN];
	inline void Init(void){
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int ID,reg int val,reg int x){
		for(reg int i=ID;i<=x;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll Query(reg int ID){
		reg ll res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline ll Query(reg int l,reg int r){
		return Query(r+1)-Query(l);
	}
	#undef lowbit
};

TreeArray A,B;

int main(void){
	n=read();
	int Max=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
		Max=max(Max,sum[i]);
	}
	reg ll ans=0;
	for(reg int i=0;(1<<i)<=Max;++i){
		A.Init(),B.Init();
		reg ll Sum=0;
		reg ll S=(1<<i)-1;
		for(reg int j=0;j<=n;++j){
			reg ll temp=sum[j]&S;
			if((sum[j]>>i)&1){
				Sum+=A.Query(0,temp)+B.Query(temp+1,S);
				B.Update(temp+1,1,1<<i);
			}
			else{
				Sum+=B.Query(0,temp)+A.Query(temp+1,S);
				A.Update(temp+1,1,1<<i);
			}
		}
		if(Sum&1)
			ans|=(1<<i);
	}
	printf("%lld\n",ans);
	return 0;
}