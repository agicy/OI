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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=400+5;
const int MAXM=1e5+5;

int n,m;
int a[MAXM],b[MAXM];
bool del[MAXN];
bitset<MAXN> G[MAXN];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i)
		a[i]=read(),b[i]=read();
	for(reg int i=1;i<=n;++i){
		G[i][i]=true;
		for(reg int j=m;j>=1;--j){
			if(G[i][a[j]]&&G[i][b[j]]){
				del[i]=true;
				break;
			}
			if(G[i][a[j]])
				G[i][b[j]]=true;
			else if(G[i][b[j]])
				G[i][a[j]]=true;
		}
	}
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j)
			if(!del[i]&&!del[j]&&!((G[i]&G[j]).count()))
				++ans;
	printf("%d\n",ans);
	return 0;
}