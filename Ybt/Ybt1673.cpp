#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1e6+5;

int n;
ll m;
int h[MAXN];
ll v[MAXN];
ll sum[MAXN];
priority_queue<pair<int,int>,vector<pair<int,int>/**/>,greater<pair<int,int>/**/>/**/> Q;

signed main(void){
	n=read(),m=read()+1;
	for(reg int i=1;i<=n;++i){
		h[i]=read(),v[i]=read();
		sum[i]=sum[i-1]+v[i];
	}
	reg ll ans=0,sum=0;
	for(reg int i=1;i<=n;++i){
		m-=h[i];
		Q.push(make_pair(v[i],h[i]-1));
		sum+=1ll*v[i]*h[i];
		while(!Q.empty()&&m<0){
			reg int x=Q.top().first;
			reg ll y=Q.top().second;
			Q.pop();
			if(m+y<=0){
				sum-=1ll*x*y;
				m+=y;
			}
			else{
				Q.push(make_pair(x,y+m));
				sum+=1ll*x*m;
				m=0;
			}
		}
		ans=max(ans,sum);
	}
	printf("%lld\n",ans);
	return 0;
}