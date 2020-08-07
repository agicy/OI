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
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXSIZE=1e5+1;

bitset<MAXSIZE> vis;
int tot,prime[9593];
int mu[MAXSIZE];

inline void Init(reg int n){
	mu[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			mu[i]=-1;
			prime[++tot]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
			mu[i*prime[j]]=-mu[i];
		}
	}
	return;
}

int n;

inline bool check(reg int x){
	reg int res=0;
	for(reg int i=1;i*i<=x;++i)
		res+=mu[i]*(x/(i*i));
	return res>=n;
}

int main(void){
	Init(1e5);
	reg int T=read();
	while(T--){
		n=read();
		reg int l=n,r=2*n,mid;
		while(l<=r){
			mid=(0ll+l+r)>>1;
			if(check(mid))
				r=mid-1;
			else
				l=mid+1;
		}
		printf("%d\n",r+1);
	}
	return 0;
}