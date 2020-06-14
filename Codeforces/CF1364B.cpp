#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;

int n,p[MAXN];
vector<int> V;

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			p[i]=read();
		V.clear();
		V.push_back(p[1]);
		for(reg int i=2;i<n;++i)
			if((p[i-1]<p[i])!=(p[i]<p[i+1]))
				V.push_back(p[i]);
		V.push_back(p[n]);
		printf("%lu\n",V.size());
		for(reg int i=0,size=V.size();i<size;++i)
			printf("%d%c",V[i],i==size-1?'\n':' ');
	}
	return 0;
}