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

const int MAXN=1e6+5;
const int MAXM=1e6+5;

int n,m;
int a[MAXN];
int opt[MAXM],x[MAXM],y[MAXM];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=i;
	for(reg int i=1;i<=m;++i){
		opt[i]=read();
		if(opt[i]==3)
			x[i]=read(),y[i]=read();
	}
	reg int las=m;
	while(las){
		if(opt[las]==1||opt[las]==2)
			break;
		--las;
	}
	reg bool rev=(opt[las]==2)?true:false;
	for(reg int i=las+1;i<=m;++i)
		if(opt[i]==3)
			if(!rev)
				swap(a[x[i]],a[y[i]]);
			else
				swap(a[n-x[i]+1],a[n-y[i]+1]);
		else
			rev^=1;
	if(rev)
		reverse(a+1,a+n+1);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i],i==n?'\n':' ');
	return 0;
}