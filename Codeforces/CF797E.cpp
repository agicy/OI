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

const int MAXN=1e5+5;
const int MAXQ=1e5+5;
const int MAXSQRTN=317+1;

int n,q;
int a[MAXN];
int B;
int ans[MAXSQRTN][MAXN];

inline void Init(void){
	for(reg int k=1;k<=B;++k)
		for(reg int p=n;p>=1;--p)
			if(p+a[p]+k>n)
				ans[k][p]=1;
			else
				ans[k][p]=ans[k][p+a[p]+k]+1;
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	B=sqrt(n);
	Init();
	q=read();
	while(q--){
		static int p,k;
		p=read(),k=read();
		if(k<=B)
			printf("%d\n",ans[k][p]);
		else{
			reg int cnt=0;
			while(p<=n){
				++cnt;
				p=p+a[p]+k;
			}
			printf("%d\n",cnt);
		}
	}
	return 0;
}