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

inline void cMax(reg ll &a,reg ll b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=18;

int n;
ll w;
int c[MAXN];
int f[1<<MAXN];
ll g[1<<MAXN];

int main(void){
	n=read(),w=read();
	for(reg int i=0;i<n;++i)
		c[i]=read();
	reg int U=(1<<n)-1;
	memset(f,0x3f,sizeof(f));
	f[0]=1,g[0]=w;
	for(reg int S=0;S<=U;++S)
		for(reg int i=0;i<n;++i)
			if(!((S>>i)&1)){
				reg int x=S^(1<<i);
				if(g[S]>=c[i]&&f[x]>=f[S]){
					f[x]=f[S];
					cMax(g[x],g[S]-c[i]);
				}
				else if(g[S]<c[i]&&f[x]>=f[S]+1){
					f[x]=f[S]+1;
					cMax(g[x],w-c[i]);
				}
			}
	printf("%d\n",f[U]);
	return 0;
}