#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;

namespace ST{
	int Lg[MAXN];
	int G[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg int a[]){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			Lg[i]=Lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			G[0][i]=a[i];
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				G[j][i]=gcd(G[j-1][i],G[j-1][i+(1<<(j-1))]);
		return;
	}
	inline int query(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		return gcd(G[k][l],G[k][r-(1<<k)+1]);
	}
}

int n;
int a[MAXN];

inline bool check(reg int i,reg int r){
	return ST::query(i,r)==1;
}

int main(void){
	n=read();
	reg int d=0,cnt1=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		d=gcd(a[i],d);
		if(a[i]==1)
			++cnt1;
	}
	if(cnt1)
		printf("%d\n",n-cnt1);
	else if(d!=1)
		puts("-1");
	else{
		ST::Init(n,a);
		int len=n;
		for(reg int i=1;i<=n;++i){
			reg int l=i,r=min(i+len-1,n),mid;
			if(!check(i,r))
				continue;
			while(l<r){
				mid=(l+r)>>1;
				if(!check(i,mid))
					l=mid+1;
				else
					r=mid;
			}
			len=min(len,l-i+1);
		}
		printf("%d\n",len-1+n-1);
	}
	return 0;
}