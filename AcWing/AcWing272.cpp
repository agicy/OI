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

const int MAXN=3000+5;

int n;
int a[MAXN],b[MAXN];
int f[MAXN];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		b[i]=read();
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i){
		reg int Max=0;
		for(reg int j=1;j<=n;++j){
			if(b[j]<a[i]&&Max<f[j])
				Max=f[j];
			if(b[j]==a[i])
				f[j]=Max+1;
		}
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		ans=max((int)ans,f[i]);
	printf("%d\n",ans);
	return;
}
