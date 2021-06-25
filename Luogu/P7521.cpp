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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=2e5+5;

int n,a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	reg int ans=0;
	for(reg int k=n;k>=1;--k){
		if(k<n&&a[k]==a[k+1])
			continue;
		if(a[k]<=ans+1)
			break;
		reg int tot=0;
		static int b[MAXN];
		for(reg int i=1;i<=n;++i)
			if(i!=k)
				b[++tot]=a[i]%a[k];
		sort(b+1,b+tot+1);
		reg int l=1,r=tot;
		while(l<=tot&&r>=1){
			while(r>=1&&b[l]+b[r]>=a[k])
				--r;
			if(l==r)
				--r;
			if(!r)
				break;
			ans=max(ans,b[l]+b[r]);
			++l;
		}
		ans=max(ans,(b[tot-1]+b[tot])%a[k]);
	}
	printf("%d\n",ans);
	return 0;
}