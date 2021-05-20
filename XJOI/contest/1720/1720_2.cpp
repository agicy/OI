#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll getSum1(reg int i){
	return 1ll*i*(i+1)/2;
}

struct Interval{
	int l,r;
	inline Interval(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
	inline int len(void)const{
		return r-l+1;
	}
};

const int MAXN=3e6;

int n;
int l[MAXN];
Interval a[MAXN];
ll f[MAXN];

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		l[i]=read()-1;
	reg int top=0;
	static int S[MAXN];
	for(reg int i=0;i<n;++i){
		while(top&&l[S[top-1]]>=l[i])
			--top;
		S[top++]=i;
	}
	reg int tot=0;
	for(reg int i=0;i<top;++i)
		a[tot++]=Interval(l[S[i]],S[i]);
	top=0;
	for(reg int i=0;i<tot;++i){
		for(reg int j=(i?a[i-1].r+1:0);j<=a[i].r;++j){
			reg int len=j-a[i].l+1;
			while(top&&a[S[top-1]].len()<=len)
				--top;
			if(!top)
				f[j]=getSum1(len)+1ll*len*a[i].l;
			else{
				reg int k=S[top-1];
				f[j]=getSum1(len)+1ll*(j-a[k].r-1)*len+f[a[k].r]-getSum1(j-a[i].l);
			}
		}
		S[top++]=i;
	}
	reg ll ans=0;
	const int __BLK=4;
	reg int __tot=n/__BLK,__res=n%__BLK,__ptr=0;
	while(__tot--){
		ans+=f[__ptr];
		ans+=f[__ptr+1];
		ans+=f[__ptr+2];
		ans+=f[__ptr+3];
		__ptr+=4;
	}
	switch(__res){
		case 3:ans+=f[__ptr+2];
		case 2:ans+=f[__ptr+1];
		case 1:ans+=f[__ptr];
		case 0:;
	}
	printf("%lld\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	return 0;
}