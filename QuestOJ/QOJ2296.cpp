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

const int MAXN=2e6+5;

int n;
int a[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	n=unique(a+1,a+n+1)-(a+1);
	reg int ans=0;
	for(reg int i=n;i>=1;--i){
		if(ans>=a[i])
			break;
		reg int l=i,r,mid;
		for(reg int j=a[i]*2;j<=a[n]+a[i];j+=a[i]){
			reg int val=j-1;
			if(val<=i)
				continue;
			r=n;
			while(l<r){
				mid=(l+r)>>1;
				if(a[mid+1]<=val)
					l=mid+1;
				else
					r=mid;
			}
			if(a[l]%a[i]>ans)
				ans=a[l]%a[i];
		}
	}
	printf("%d\n",ans);
	return 0;
}