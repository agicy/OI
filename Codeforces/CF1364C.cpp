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

int n;
bool vis[MAXN];
int a[MAXN],b[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	memset(b,-1,sizeof(b));
	for(reg int i=1;i<=n;++i)
		if(a[i]!=a[i-1]){
			b[i]=a[i-1];
			vis[b[i]]=true;
		}
	vis[a[n]]=1;
	reg int ptr=0;
	for(reg int i=1;i<=n;++i){
		while(vis[ptr])
			++ptr;
		if(b[i]==-1){
			b[i]=ptr;
			vis[ptr]=true;
		}
		printf("%d%c",b[i],i==n?'\n':' ');
	}
	return 0;
}