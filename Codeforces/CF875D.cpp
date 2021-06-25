#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXLOG2A=30;

int n;
int a[MAXN];
int top,S[MAXN];
int las[MAXLOG2A];
int lef[MAXN],rig[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),lef[i]=0,rig[i]=n+1;
	a[0]=0x7fffffff;
	S[top=1]=0;
	for(reg int i=0;i<MAXLOG2A;++i)
		las[i]=0;
	for(reg int i=1;i<=n;++i){
		while(top&&a[S[top]]<a[i])
			--top;
		lef[i]=S[top];
		S[++top]=i;
		for(reg int j=0;j<MAXLOG2A;++j)
			if((a[i]>>j)&1)
				las[j]=i;
			else
				lef[i]=max(lef[i],las[j]);
	}
	a[n+1]=0x7fffffff;
	S[top=1]=n+1;
	for(reg int i=0;i<MAXLOG2A;++i)
		las[i]=n+1;
	for(reg int i=n;i>=1;--i){
		while(top&&a[S[top]]<=a[i])
			--top;
		rig[i]=S[top];
		S[++top]=i;
		for(reg int j=0;j<MAXLOG2A;++j)
			if((a[i]>>j)&1)
				las[j]=i;
			else
				rig[i]=min(rig[i],las[j]);
	}
	reg ll ans=(1ll*n*(n+1))>>1;
	for(reg int i=1;i<=n;++i)
		ans-=1ll*(i-lef[i])*(rig[i]-i);
	printf("%lld\n",ans);
	return 0;
}