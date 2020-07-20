#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=1000000+5;

bool vis[MAXN];
int n;
int cnt,Prime[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	return;
}

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i)
		if(!vis[i]){
			Prime[++cnt]=i;
			for(reg int j=(i<<1);j<=n;j+=i)
				vis[j]=true;
		}
	return;
}

inline void Work(void){
	Init(n);
	for(reg int i=1;i<=cnt;++i){
		reg ll ans=0;
		for(reg ll j=Prime[i];j<=n;j*=Prime[i])
			ans+=n/j;
		printf("%d %lld\n",Prime[i],ans);
	}
	return;
}
