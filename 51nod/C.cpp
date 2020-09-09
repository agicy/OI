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

const int MAXN=1e5+5;
const int MAXV=1e5+5;
const int inf=0x3f3f3f3f;

int n;
int a[MAXN],b[MAXN];
int Ta[MAXV],Tb[MAXV];

int main(void){
	n=read();
	int aMax=-inf,aMin=inf;
	int bMax=-inf,bMin=inf;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		++Ta[a[i]];
		aMax=max(aMax,a[i]),aMin=min(aMin,a[i]);
	}
	for(reg int i=1;i<=n;++i){
		b[i]=read();
		++Tb[b[i]];
		bMax=max(bMax,b[i]),bMin=min(bMin,b[i]);
	}
	if(aMax<=5000&&bMax<=5000){
		int ans=0;
		for(reg int x=aMin+bMin;x<=aMax+bMax;++x){
			int sum=0;
			for(reg int i=aMin;i<=aMax;++i)
				if(bMin<=x-i&&x-i<=bMax)
					sum+=min(Ta[i],Tb[x-i]);
			ans=max(ans,sum);
		}
		printf("%d\n",ans);
	}
	else{
		clock_t st=clock();
		int l=aMin+bMax,r=aMax+bMin;
		if(l>r)
			swap(l,r);
		const int delta=30;
		l=max(l-delta,aMin+bMin),r=min(r+delta,aMax+bMax);
		int ans=0;
		for(reg int x=l;x<=r;++x){
			int sum=0;
			for(reg int i=aMin;i<=aMax;++i)
				if(bMin<=x-i&&x-i<=bMax)
					sum+=min(Ta[i],Tb[x-i]);
			ans=max(ans,sum);
			clock_t a=clock();
			if((a-st)/(1.0*CLOCKS_PER_SEC)>1.2)
				break;
		}
		printf("%d\n",ans);
	}
	return 0;
}