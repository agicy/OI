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
int a[MAXN],b[MAXN];
priority_queue<int> Q;

int main(void){
	n=read();
	Q.push(b[1]=read()-1);
	a[1]=Q.top();
	for(reg int i=2;i<=n;++i){
		int x=read()-i;
		Q.push(b[i]=x);
		if(Q.top()>x){
			Q.pop();
			Q.push(x);
		}
		a[i]=Q.top();
	}
	for(reg int i=n-1;i>=1;--i)
		a[i]=min(a[i],a[i+1]);
	reg ll sum=0;
	for(reg int i=1;i<=n;++i)
		sum+=abs(a[i]-b[i]);
	printf("%lld\n",sum);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i]+i,i==n?'\n':' ');
	return 0;
}