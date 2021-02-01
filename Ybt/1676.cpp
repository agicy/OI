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

const int MAXN=5e4+5;
const int inf=0x3f3f3f3f;

int n,k;
int a[MAXN];

inline bool check(reg int mid){
	static int tmp[MAXN];
	for(reg int i=1;i<=n;++i)
		tmp[i]=a[i];
	reg int sum=k;
	for(reg int i=n;i>=1&&sum>=0;--i)
		while(tmp[i]>=0&&sum>=0){
			for(reg int j=i;j>=1&&(i-j)*(i-j)<mid;--j)
				tmp[j]-=mid-(i-j)*(i-j);
			--sum;
		}
	return sum>=0;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int l=1,r=inf,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}