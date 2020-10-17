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

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXLOG2A=31;

int n;
int f[MAXLOG2A],g[MAXLOG2A];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		memcpy(g,f,sizeof(f));
		reg int a=read();
		for(reg int j=0;j<MAXLOG2A;++j)
			if((a>>j)&1)
				for(reg int k=0;k<MAXLOG2A;++k)
					if((a>>k)&1)
						cMax(f[j],g[k]+1);
	}
	int ans=1;
	for(reg int i=0;i<MAXLOG2A;++i)
		cMax(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}