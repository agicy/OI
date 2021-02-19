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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e3+5;

int n;
int x[MAXN],y[MAXN];
int cnt[2][2];
int ans[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read(),y[i]=read();
	while(true){
		memset(cnt,0,sizeof(cnt));
		for(reg int i=1;i<=n;++i)
			++cnt[x[i]&1][y[i]&1];
		if(cnt[0][0]+cnt[1][1]>0&&cnt[0][1]+cnt[0][1]>0){
			reg int tot=0;
			for(reg int i=1;i<=n;++i)
				if(!((x[i]+y[i])&1))
					ans[++tot]=i;
			printf("%d\n",tot);
			for(reg int i=1;i<=tot;++i)
				printf("%d%c",ans[i],i==tot?'\n':' ');
			break;
		}
		if(cnt[0][0]+cnt[0][1]>0&&cnt[1][0]+cnt[1][1]>0){
			reg int tot=0;
			for(reg int i=1;i<=n;++i)
				if(x[i]&1)
					ans[++tot]=i;
			printf("%d\n",tot);
			for(reg int i=1;i<=tot;++i)
				printf("%d%c",ans[i],i==tot?'\n':' ');
			break;
		}
		for(reg int i=1;i<=n;++i)
			x[i]>>=1,y[i]>>=1;
	}
	return 0;
}