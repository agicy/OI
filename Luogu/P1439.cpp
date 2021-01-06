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

const int MAXN=1e5+5;

int n;
int pos[MAXN];
int a[MAXN];
int b[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		pos[read()]=i;
	for(reg int i=1;i<=n;++i)
		a[i]=pos[read()];
	memset(b,0x3f,sizeof(b));
	for(reg int i=1;i<=n;++i)
		*lower_bound(b+1,b+n+1,a[i])=a[i];
	printf("%ld\n",lower_bound(b+1,b+n+1,b[0])-(b+1));
	return 0;
}