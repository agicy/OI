#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
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

const int MAXN=12+5;

int f[MAXN];

int main(void){
	f[1]=1;
	for(reg int i=2;i<=12;++i){
		f[i]=INF;
		for(reg int j=1;j<i;++j)
			f[i]=min(f[i],(f[j]<<1)+(1<<(i-j))-1);
	}
	for(reg int i=1;i<=12;++i)
		printf("%d\n",f[i]);
	return 0;
}