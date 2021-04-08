#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline char* read(reg char *s){
	*s=getchar();
	while(!isalnum(*s))*s=getchar();
	while(isalnum(*s))*(++s)=getchar();
	*s='\0';
	return s;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e6+5;

namespace SA{
	int sa[MAXN],rk[MAXN<<1],oldrk[MAXN<<1],px[MAXN],id[MAXN];
	int cnt[MAXN];
	inline bool cmp(reg int x,reg int y,reg int w){
		return oldrk[x]==oldrk[y]&&oldrk[x+w]==oldrk[y+w];
	}
	inline void build(reg char s[],reg int n){
		reg int m=max(n,300);
		for(reg int i=1;i<=n;++i)
			++cnt[rk[i]=s[i]];
		for(reg int i=1;i<=m;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=n;i>=1;--i)
			sa[cnt[rk[i]]--]=i;
		for(reg int w=1;w<n;w<<=1){
			reg int p=0;
			for(reg int i=n;i>n-w;--i)
				id[++p]=i;
			for(reg int i=1;i<=n;++i)
				if(sa[i]>w)
					id[++p]=sa[i]-w;
			memset(cnt,0,sizeof(cnt));
			for(reg int i=1;i<=n;++i)
				++cnt[px[i]=rk[id[i]]];
			for(reg int i=1;i<=m;++i)
				cnt[i]+=cnt[i-1];
			for(reg int i=n;i>=1;--i)
				sa[cnt[px[i]]--]=id[i];
			memcpy(oldrk,rk,sizeof(rk));
			p=0;
			for(reg int i=1;i<=n;++i)
				rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
		}
		return;
	}
}

char s[MAXN];

int main(void){
	reg int n=read(s+1)-(s+1);
	SA::build(s,n);
	for (reg int i=1;i<=n;++i)
		write(SA::sa[i]),putchar(i==n?'\n':' ');
	flush();
	return 0;
}