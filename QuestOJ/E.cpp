#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define MOD 998244353
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=400000+5;
const int MAXM=400000+5;

int n,m,k;
int a[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline int gcd(reg int a,reg int b){
	return b==0?a:gcd(b,a%b);
}

int ans[MAXM];
int b[MAXN],gcdb[MAXN];

inline void DFS(reg int dep,reg int notsame){
	if(notsame<k)
		return;
	if(dep==n+1){
		if(notsame>=k){
			//for(reg int i=1;i<=n;++i)
			//	printf("%d%c",b[i],i==n?'\n':' ');
			//for(reg int i=1;i<=n;++i)
			//	printf("%d%c",gcdb[i],i==n?'\n':' ');
			//putchar('\n');
			++ans[gcdb[n]];
			ans[gcdb[n]]%=MOD;
		}
		return;
	}
	for(reg int i=1;i<=m;++i){
		b[dep]=i;
		gcdb[dep]=gcd(b[dep],gcdb[dep-1]);
		if(a[dep]==b[dep])
			DFS(dep+1,notsame-1);
		else
			DFS(dep+1,notsame);
	}
	return;
}

inline void Work(void){
	DFS(1,n);
	for(reg int i=1;i<=m;++i)
		printf("%d%c",ans[i],i==m?'\n':' ');
	return;
}
