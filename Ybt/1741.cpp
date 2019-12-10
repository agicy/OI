#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 20170927
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

const int MAXN=1000000+5;
const int MAXM=1000000+5;

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
		val%=MOD;
		while(ID<=n){
			unit[ID]=(unit[ID]+val)%MOD;
			ID+=lowbit(ID);
		}
		return;
	}
	inline ll Query(reg int ID){
		reg ll res=0;
		while(ID){
			res=(res+unit[ID])%MOD;
			ID-=lowbit(ID);
		}
		return res;
	}
	#undef lowbit
};

int n,m;
ll x[MAXN],y[MAXN],xy[MAXN];
TreeArray Tx,Ty,Txy;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),m=read();
	Tx.Init(n),Ty.Init(n),Txy.Init(n);
	for(reg int i=1;i<=n;++i){
		x[i]=read(),y[i]=read();
		xy[i]=x[i]*y[i]%MOD;
		Tx.Update(i,x[i]*x[i]);
		Ty.Update(i,y[i]*y[i]);
		Txy.Update(i,xy[i]);
	}
	return;
}

inline void Work(void){
	while(m--){
		static int opt,p,l,r;
		static ll u,v;
		opt=read();
		if(opt==1){
			p=read(),u=read(),v=read();
			Tx.Update(p,-(x[p]*x[p]%MOD)+MOD);
			Ty.Update(p,-(y[p]*y[p]%MOD)+MOD);
			Txy.Update(p,-(xy[p]%MOD)+MOD);
			x[p]=u,y[p]=v,xy[p]=u*v%MOD;
			Tx.Update(p,x[p]*x[p]);
			Ty.Update(p,y[p]*y[p]);
			Txy.Update(p,xy[p]);
		}
		if(opt==2){
			l=read(),r=read();
			ll temp1=((Tx.Query(r)-Tx.Query(l-1))%MOD+MOD)%MOD;
			ll temp2=((Ty.Query(r)-Ty.Query(l-1))%MOD+MOD)%MOD;
			ll temp3=((Txy.Query(r)-Txy.Query(l-1))%MOD+MOD)%MOD;
			temp3=temp3*temp3%MOD;
			ll ans=((temp1*temp2%MOD-temp3)%MOD+MOD)%MOD;
			printf("%lld\n",ans);
		}
	}
	return;
}
