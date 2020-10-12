#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e6+5;

int n,q;
int d[MAXN];
int f[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		d[i]=read();
	q=read();
	while(q--){
		reg int k=read();
		deque<int> Q;
		Q.push_back(1);
		for(reg int i=2;i<=n;++i){
			while(!Q.empty()&&i-Q.front()>k)
				Q.pop_front();
			if(d[Q.front()]>d[i])
				f[i]=f[Q.front()];
			else
				f[i]=f[Q.front()]+1;
			while(!Q.empty()&&(f[Q.back()]>f[i]||(f[Q.back()]==f[i]&&d[Q.back()]<=d[i])))
				Q.pop_back();
			Q.push_back(i);
		}
		printf("%d\n",f[n]);
	}
	return 0;
}