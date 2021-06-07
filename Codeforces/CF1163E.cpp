#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=2e5+5;
const int MAXLOG2S=19;

namespace Basis{
	int unit[MAXLOG2S];
	vector<int> V;
	inline void insert(reg int x){
		int tmp=x;
		for(reg int i=MAXLOG2S-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					unit[i]=x,V.push_back(tmp);
					break;
				}
				else
					x^=unit[i];
			}
		return;
	}
}

int n;
int s[MAXN];
vector<int> ans;

inline void dfs(reg int dep){
	if(dep==-1)
		return;
	dfs(dep-1);
	ans.push_back(Basis::V[dep]);
	dfs(dep-1);
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		s[i]=read();
	sort(s+1,s+n+1);
	reg int x=0;
	for(reg int i=1,ptr=1;i<MAXLOG2S;++i){
		while(ptr<=n&&s[ptr]<(1<<i))
			Basis::insert(s[ptr++]);
		if((int)Basis::V.size()==i)
			x=i;
	}
	Basis::V.push_back(0);
	ans.reserve(1<<(x+1));
	ans.push_back(0);
	dfs(x);
	write(x),putchar('\n');
	for(reg int i=1;i<(1<<x);++i)
		ans[i]^=ans[i-1];
	for(reg int i=0;i<(1<<x);++i)
		write(ans[i]),putchar(i==(1<<x)-1?'\n':' ');
	flush();
	return 0;
}