#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=100+5;
const int MAXLOG2A=30;
const int A=14;
const int B=MAXLOG2A-A;
const int U=(1<<A)-1;

int n;
int a[MAXN];
map<vector<int>,int> M;

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	vector<int> V;
	V.resize(n-1);
	for(reg int i=0;i<(1<<A);++i){
		reg int tmp=__builtin_popcount((a[0]&U)^i);
		for(reg int j=1;j<n;++j)
			V[j-1]=tmp-__builtin_popcount((a[j]&U)^i);
		M[V]=i;
	}
	for(reg int i=0;i<(1<<B);++i){
		reg int tmp=__builtin_popcount((a[0]>>A)^i);
		for(reg int j=1;j<n;++j)
			V[j-1]=__builtin_popcount((a[j]>>A)^i)-tmp;
		if(M.count(V)){
			printf("%d\n",(i<<A)|M[V]);
			exit(0);
		}
	}
	puts("-1");
	return 0;
}