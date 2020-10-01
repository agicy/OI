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

const int MAXN=1e6+5;

int n,m;
int a[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	while(m--){
		static int x;
		x=read();
		reg int l=1,r=n,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(x<=a[mid])
				r=mid;
			else
				l=mid+1;
		}
		printf("%d%c",a[l]==x?l:-1,m?' ':'\n');
	}
	return 0;
}