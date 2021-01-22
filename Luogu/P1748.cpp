#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e4+5;

int n;
int a=1,b=1,c=1,d=1;
ll w[MAXN];

int main(void){
	n=read();
	w[1]=1;
	for(reg int i=2;i<=n;++i){
		w[i]=w[a]*2;
		if(w[i]>w[b]*3)
			w[i]=w[b]*3;
		if(w[i]>w[c]*5)
			w[i]=w[c]*5;
		if(w[i]>w[d]*7)
			w[i]=w[d]*7;
		if(w[i]==w[a]*2)
			++a;
		if(w[i]==w[b]*3)
			++b;
		if(w[i]==w[c]*5)
			++c;
		if(w[i]==w[d]*7)
			++d;
	}
	printf("%lld\n",w[n]);
	return 0;
}