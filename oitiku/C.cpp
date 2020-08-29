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
const int MAXM=1e6+5;

int n,m;
int l[MAXM],r[MAXM];
int B;
int ans;

inline void query(reg int l,reg int r){
	if((l-1)/B==(r-1)/B)
		ans+=(r-l+1);
	else
		ans+=((r-1)/B-(l-1)/B)*(1-B)+r-l+B;
	return;
}

int main(void){
	freopen("block.in","r",stdin);
	freopen("block.out","w",stdout);
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		l[i]=read(),r[i]=read();
	for(reg int i=1;i<=n;++i){
		B=i,ans=0;
		for(reg int j=1;j<=m;++j)
			query(l[j],r[j]);
		printf("%d%c",ans,i==n?'\n':' ');
	}
	return 0;
}