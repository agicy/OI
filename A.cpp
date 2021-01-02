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

const int MAXM=1e5+5;
const int MAXQ=1e5+5;

struct Node{
	int x,y;
	inline void Read(void){
		x=read(),y=read();
		return;
	}
	inline bool operator<(const Node& a)const{
		return x<a.x||(x==a.x&&y<a.y);
	}
};

int n,m,q;
Node p[MAXQ];
bool vis[MAXM];

int main(void){
	//freopen("iakioi.in","r",stdin);
	//freopen("iakioi.out","w",stdout);

	reg int t=read();
	while(t--){
		memset(vis,false,sizeof(vis));
		n=read(),m=read(),q=read();
		for(reg int i=1;i<=q;++i)
			p[i].Read();
		sort(p+1,p+q+1);
		reg int ans=0;
		p[q+1].x=-1;
		for(reg int i=1;i<=q;++i)
			if(!vis[p[i].y]){
				vis[p[i].y]=true;
				++ans;
				while(p[i+1].x==p[i].x)
					++i;
			}
		printf("%d\n",ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}