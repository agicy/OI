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
const int MAXM=11+5;

const int c[]={1,2,3,5,7,11,13,17,19,23,29,31,33};

int n;
int a[MAXN];
int ID[MAXM];
int color[MAXN];

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		reg int cnt=0;
		memset(ID,0,sizeof(ID));
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=11;++j){
				if(a[i]%c[j]==0){
					if(ID[j]==0)
						ID[j]=++cnt;
					color[i]=ID[j];
					break;
				}
			}
		printf("%d\n",cnt);
		for(reg int i=1;i<=n;++i)
			printf("%d%c",color[i],i==n?'\n':' ');
	}
	return 0;
}
