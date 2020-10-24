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

const int MAXT=1e6+5;

int n,T;
int nex[MAXT];

int main(void){
	n=read(),T=read();
	for(reg int i=1;i<=n;++i){
		static int l,r;
		l=read(),r=read();
		nex[l]=max(nex[l],r);
	}
	for(reg int i=1;i<=T;++i)
		nex[i]=max(nex[i],nex[i-1]);
	reg int ans=0,ptr=1;
	while(ptr<=T&&nex[ptr]>=ptr){
		++ans;
		ptr=nex[ptr]+1;
	}
	printf("%d\n",ptr<=T?-1:ans);
	return 0;
}