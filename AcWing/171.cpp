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

const int MAXN=46+5;
const int MAXSIZE=(1<<23)+5;

int n,mid;
ll w;
int cnt;
ll g[MAXN];
ll s[MAXSIZE];
ll ans;

inline void Read(void);
inline void Work(void);


int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	w=read(),n=read();
	for(reg int i=1;i<=n;++i)
		g[i]=read();
	return;
}

inline void DFS1(reg int dep,reg ll sum){
	if(dep==mid+1){
		s[++cnt]=sum;
		return;
	}
	DFS1(dep+1,sum);
	if(sum+g[dep]<=w)
		DFS1(dep+1,sum+g[dep]);
	return;
}

inline void DFS2(reg int dep,reg ll sum){
	if(dep==n+1){
		reg int l=1,r=cnt,mid;
		while(l<r){
			mid=(l+r+1)>>1;
			if(s[mid]<=w-sum)
				l=mid;
			else
				r=mid-1;
		}
		ans=max(ans,sum+s[l]);
		return;
	}
	DFS2(dep+1,sum);
	if(sum+g[dep]<=w)
		DFS2(dep+1,sum+g[dep]);
	return;
}

inline void Work(void){
	mid=(n>>1);
	DFS1(1,0);
	sort(s+1,s+cnt+1);
	cnt=unique(s+1,s+cnt+1)-s-1;
	DFS2(mid+1,0);
	printf("%lld\n",ans);
	return;
}
