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
int Deg[MAXN];
vector<int> V[MAXN];
int ans[MAXN];

int main(void){
	n=read();
	for(int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		++Deg[u];
		++Deg[v];
		V[u].push_back(i);
		V[v].push_back(i);
	}
	reg bool flag=false;
	reg int pos=-1;
	for(reg int i=1;i<=n;++i){
		if(Deg[i]>=3){
			flag=true;
			pos=i;
			break;
		}
	}
	if(flag){
		ans[V[pos][0]]=1;
		ans[V[pos][1]]=2;
		ans[V[pos][2]]=3;
		reg int cnt=3;
		for(reg int i=1;i<n;++i)
			if(ans[i])
				printf("%d\n",ans[i]-1);
			else
				printf("%d\n",++cnt-1);
	}
	else{
		reg int cnt=0;
		for(reg int i=1;i<n;++i)
			printf("%d\n",++cnt-1);
	}
	return 0;
}
