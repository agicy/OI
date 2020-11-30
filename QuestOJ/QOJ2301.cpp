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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;

int n,q;
int v[MAXN];
int d[MAXN],l[MAXN],r[MAXN];
int top,S[MAXN];

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		v[i]=read();
	for(reg int i=1;i<n;++i){
		d[i]=abs(v[i]-v[i+1]);
		l[i]=0,r[i]=n;
	}
	top=0;
	for(reg int i=1;i<n;++i){
		while(top&&d[i]>d[S[top]])
			r[S[top--]]=i;
		S[++top]=i;
	}
	top=0;
	for(reg int i=n-1;i>=1;--i){
		while(top&&d[i]>=d[S[top]])
			l[S[top--]]=i;
		S[++top]=i;
	}
	while(q--){
		static int L,R;
		L=read(),R=read();
		reg ll ans=0;
		for(reg int i=L;i<R;++i){
			reg int lef=max(l[i],L-1),rig=min(r[i],R);
			ans+=1ll*d[i]*(i-lef)*(rig-i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}