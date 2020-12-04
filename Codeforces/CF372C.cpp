#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1.5e5+5;
const int MAXM=300+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

int n,m,d;
ll a[MAXM],b[MAXM],t[MAXM];
ll f[2][MAXN];
int ptr;
int Q[MAXN];

inline void dp(void){
	memset(f,207,sizeof(f));
	for(reg int i=1;i<=n;++i)
		f[0][i]=0;
	ptr=1;
	for(reg int i=1;i<=m;++i){
		reg int head=1,tail=0;
		reg int k=1;
		for(reg int j=1;j<=n;++j){
			for(;k<=min(1ll*n,j+1ll*d*(t[i]-t[i-1]));++k){
				while(head<=tail&&f[ptr^1][Q[tail]]<=f[ptr^1][k])
					--tail;
				Q[++tail]=k;
			}
			while(head<=tail&&Q[head]<max(1ll,j-1ll*d*(t[i]-t[i-1])))
				++head;
			f[ptr][j]=f[ptr^1][Q[head]]-abs(a[i]-j)+b[i];
		}
		ptr^=1;
	}
}

int main(void){
	cin>>n>>m>>d;
	for(reg int i=1;i<=m;++i)
		cin>>a[i]>>b[i]>>t[i];
	dp();
	ll ans=-inf;
	for(reg int i=1;i<=n;++i)
		ans=max(ans,f[ptr^1][i]);
	cout<<ans<<endl;
	return 0;
}