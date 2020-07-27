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

const int MAXN=1.2e6+5;
const int p=19940105;

int n;
int fa[MAXN],num[MAXN],size[MAXN];

int main(void){
	n=read();
	for(reg int T=1;T<=10;++T){
		for(reg int i=2;i<=n;++i)
			if(T==1)
				fa[i]=read();
			else
				fa[i]=(fa[i]+p)%(i-1)+1;
		for(reg int i=1;i<=n;++i)
			size[i]=1,num[i]=0;
		for(reg int i=n;i>1;--i)
			size[fa[i]]+=size[i];
		for(reg int i=1;i<=n;++i)
			++num[size[i]];
		printf("Case #%d:\n1\n",T);
		for(reg int i=2;i<=n;++i)
			if(n%i==0){
				reg int t=0;
				for(int j=1;i*j<=n;++j)
					t+=num[i*j];
				if(t*i>=n)
					printf("%d\n",i);
			}
	}
	return 0;
}