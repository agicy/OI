#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int ans=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))ans=10*ans+(ch^'0'),ch=getchar();
	return ans;
}

const int MAXN=1e6+5;
const int mod=1e9+7;
const int inv2=5e8+4;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,up[MAXN],dn[MAXN];

pair<int,int>p[MAXN];

int main(void){
	n=read();
	dn[0]=up[0]=n;
	for(reg int i=1;i<=n;++i)
		p[i].first=read(),p[i].second=read();
	sort(p+1,p+n+1);
	for(reg int i=n-1;i>=1;--i)
		up[i]=max(up[i+1],p[i+1].second);
	for(reg int i=1;i<n;++i)
		dn[i]=min(dn[i-1],p[i].second);
	reg int ans=0,sum=0,tag=0;
	for(reg int i=1,ptr=1;i<n;++i){
		if(up[i-1]>=dn[i]){
			tag=add(tag,up[i-1]-dn[i]);
			sum=add(sum,1ll*inv2*(up[i-1]-dn[i])%mod*(up[i-1]-dn[i]+1)%mod);
		}
		for(reg int j=up[i-1];j>up[i];--j){
			while(dn[ptr]==j)
				++ptr;
			sum=sub(sum,tag),tag=sub(tag,i-ptr+1);
		}
		ans=add(ans,sum);
	}
	printf("%d\n",ans);
	return 0;
}