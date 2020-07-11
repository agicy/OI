#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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
bool vis[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		memset(vis,false,sizeof(vis));
		n=read();
		reg int x=0;
		for(reg int i=1;i<=n;++i){
			reg bool flag=true;
			reg int k=read();
			for(reg int j=1;j<=k;++j){
				reg int g=read();
				if(!vis[g]&&flag){
					vis[g]=true;
					flag=false;
				}
			}
			if(flag)
				x=i;
		}
		if(!x)
			puts("OPTIMAL");
		else
			for(reg int i=1;i<=n;++i)
				if(!vis[i]){
					printf("IMPROVE\n%d %d\n",x,i);
					break;
				}
	}
	return 0;
}
