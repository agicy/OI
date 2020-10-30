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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100+5;
const int MAXM=1e5+5;

int n,m;
int a[MAXN],c[MAXN];
bool f[MAXM];
int used[MAXM];

int main(void){
	while(n=read(),m=read(),n||m){
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=1;i<=n;++i)
			c[i]=read();
		memset(f,false,sizeof(f));
		f[0]=true;
		for(reg int i=1;i<=n;++i){
			fill(used,used+m+1,0);
			for(reg int j=a[i];j<=m;++j)
				if(!f[j]&&f[j-a[i]]&&used[j-a[i]]<c[i])
					f[j]=true,used[j]=used[j-a[i]]+1;
		}
		reg int ans=0;
		for(reg int i=1;i<=m;++i)
			ans+=f[i];
		printf("%d\n",ans);
	}
	return 0;
}