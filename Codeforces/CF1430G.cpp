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

const int MAXN=18;

int n,m;
int in[MAXN],W[1<<MAXN];
int f[1<<MAXN],from[1<<MAXN];
int ans[MAXN];

int main(void){
	n=read(),m=read();
	reg int sum=0;
	for(reg int i=1;i<=m;++i){
		static int x,y,w;
		x=read()-1,y=read()-1,w=read();
		in[y]|=(1<<x);
		W[(1<<x)|(1<<y)]=w;
		sum+=w;
	}
	reg int U=(1<<n)-1;
	for(reg int i=0;i<n;++i)
		for(reg int S=0;S<=U;++S)
			if((S>>i)&1)
				W[S]+=W[S^(1<<i)];
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	for(reg int S=0;S<=U;++S){
		f[S]+=sum-(W[S]+W[U^S]);
		reg int Sub=0;
		for(reg int i=0;i<n;++i)
			if(!((S>>i)&1)&&(in[i]&S)==in[i])
				Sub|=(1<<i);
		for(reg int sub=Sub;sub;sub=(sub-1)&Sub)
			if(f[S|sub]>f[S])
				f[S|sub]=f[S],from[S|sub]=sub;
	}
	for(reg int S=U;S;S^=from[S])
		for(reg int i=0;i<n;++i)
			if((S>>i)&1)
				++ans[i];
	for(reg int i=0;i<n;++i)
		printf("%d%c",ans[i],i==n-1?'\n':' ');
	return 0;
}