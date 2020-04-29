#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=100000+5;

int n;
int a[MAXN],b[MAXN];

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=1;i<=n;++i)
			b[i]=read();
		int Minp1=INF,Minn1=INF;
		for(int i=1;i<=n;++i){
			if(a[i]==1)
				Minp1=min(Minp1,i);
			if(a[i]==-1)
				Minn1=min(Minn1,i);
		}
		reg bool flag=true;
		for(reg int i=n;i>=1;--i){
			if(a[i]!=b[i]){
				if(a[i]>b[i]){
					if(Minn1>=i){
						flag=false;
						break;
					}
				}
				else{
					if(Minp1>=i){
						flag=false;
						break;
					}
				}
			}
		}
		puts(flag?"YES":"NO");
	}
	return 0;
}
