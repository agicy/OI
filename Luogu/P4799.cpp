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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=40;

int n;
ll m;
ll a[MAXN];
int cnt1,cnt2;
ll T1[1<<(MAXN/2)],T2[1<<(MAXN/2)];

int main(void){
	n=read(),m=readll();
	for(reg int i=0;i<n;++i)
		a[i]=readll();
	reg int p=n/2,q=n-p;
	reg int U1=(1<<p)-1,U2=(1<<q)-1;
	for(reg int S=0;S<=U1;++S){
		reg ll sum=0;
		for(reg int i=0;i<p;++i)
			if((S>>i)&1)
				sum+=a[i];
		T1[cnt1++]=sum;
	}
	for(reg int S=0;S<=U2;++S){
		reg ll sum=0;
		for(reg int i=0;i<q;++i)
			if((S>>i)&1)
				sum+=a[i+p];
		T2[cnt2++]=sum;
	}
	sort(T1,T1+cnt1),sort(T2,T2+cnt2);
	reg ll ans=0;
	for(reg int l=0,r=cnt2-1;l<cnt1;++l){
		while(r>=0&&T1[l]+T2[r]>m)
			--r;
		if(r>=0)
			ans+=r+1;
	}
	printf("%lld\n",ans);
	return 0;
}