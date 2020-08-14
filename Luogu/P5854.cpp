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

const int MAXN=1e7+5;

int n;
int p[MAXN];

namespace Tree{
	int ch[MAXN][2];
	inline void build(reg int n,reg int p[]){
		static int S[MAXN];
		reg int top=0;
		for(reg int i=1;i<=n;++i){
			reg int cur=top;
			while(cur&&p[S[cur]]>p[i])
				--cur;
			if(cur)
				ch[S[cur]][1]=i;
			if(cur<top)
				ch[i][0]=S[cur+1];
			S[++cur]=i;
			top=cur;
		}
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i]=read();
	Tree::build(n,p);
	reg ll ans1=0,ans2=0;
	for(reg int i=1;i<=n;++i){
		ans1^=1ll*i*(Tree::ch[i][0]+1);
		ans2^=1ll*i*(Tree::ch[i][1]+1);
	}
	printf("%lld %lld\n",ans1,ans2);
	return 0;
}