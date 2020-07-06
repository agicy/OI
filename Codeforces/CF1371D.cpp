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

const int MAXN=300+5;

int n,k;
bool a[MAXN][MAXN];

int main(void){
	reg int T=read();
	while(T--){
		n=read(),k=read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				a[i][j]=true;
		reg int sum=n*n,cnt=0;
		printf("%d\n",(sum-k)%n?2:0);
		while(sum>k){
			if(sum-k>n){
				sum-=n;
				for(reg int i=1;i<=n;++i)
					a[i][(i+cnt)%n+1]=0;
			}
			else{
				for(reg int i=1;i<=sum-k;++i)
					a[i][(i+cnt)%n+1]=0;
				sum=k;
			}
			++cnt;
		}
		for(reg int i=1;i<=n;++i,putchar('\n'))
			for(reg int j=1;j<=n;++j)
				putchar(a[i][j]+'0');
	}
	return 0;
}