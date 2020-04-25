#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000+5;
const int MAXP=500+5;

int n,p;
int a[MAXN];
vector<int> V[MAXP];

int main(void){
	n=read(),p=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1,greater<int>());
	reg int ptr=1;
	while(ptr<=n){
		for(reg int i=1;i<=p&&ptr<=n;++i)
			V[i].push_back(a[ptr++]);
		for(reg int i=p;i>=1&&ptr<=n;--i)
			V[i].push_back(a[ptr++]);
	}
	for(reg int i=1;i<=p;++i)
		for(reg int j=0,size=V[i].size();j<size;++j)
			printf("%d%c",V[i][j],j==size-1?'\n':' ');
	return 0;
}
