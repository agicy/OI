#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 1e10
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

const int MAXN=35000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

ll n;
ll a[MAXN];

inline void Read(void){
	n=read();
	for(reg ll i=1;i<=n;++i)
		a[i]=read()-i;
	return;
}

inline ll abss(reg ll x){
	return x>0?x:-x;
}

ll len,b[MAXN];
ll last[MAXN];
ll f[MAXN];
ll cost[2][MAXN];
vector<ll> V[MAXN];

inline void Work(void){
	a[++n]=INF;
	b[++len]=a[1];
	last[1]=1;
	for(reg ll i=2;i<=n;++i){
		if(a[i]>=b[len]){
			b[++len]=a[i];
			last[i]=len;
		}
		else{
			reg ll pos=upper_bound(b+1,b+len+1,a[i])-b;
			b[pos]=a[i];
			last[i]=pos;
		}
	}
	printf("%lld\n",n-len);
	a[0]=-INF;
	V[0].push_back(0);
	for(reg ll i=1;i<=n;++i){
		f[i]=INF;
		for(reg ll j=0;j<(ll)V[last[i]-1].size();++j){
			reg ll las=V[last[i]-1][j];
			if(a[las]>a[i])
				continue;
			cost[0][las-1]=cost[1][las-1]=0;
			for(reg ll k=las;k<=i;++k){
				cost[0][k]=abss(a[k]-a[las]);
				cost[1][k]=abss(a[k]-a[i]);
			}
			for(reg ll k=las;k<=i;++k){
				cost[0][k]+=cost[0][k-1];
				cost[1][k]+=cost[1][k-1];
			}
			for(reg ll k=las;k<=i;++k){
				reg ll now=cost[0][k]-cost[0][las]+cost[1][i]-cost[1][k];
				f[i]=min(f[i],f[las]+now);
			}
		}
		V[last[i]].push_back((ll)i);
	}
	printf("%lld\n",f[n]);
	return;
}
