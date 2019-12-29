#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=100+5;
const int MAXSIZE=1000000+5;

int n;
bitset<MAXSIZE> ans,temp;

int main(void){
	n=read();
	ans[0]=1;
	for(reg int i=1;i<=n;++i){
		static int l,r;
		l=read(),r=read();
		temp.reset();
		for(reg int j=l;j<=r;++j)
			temp|=ans<<(j*j);
		ans=temp;
	}
	printf("%ld\n",ans.count());
	return 0;
}
