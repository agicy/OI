#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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
const int MAXM=300+5;
const int MAXC=100+5;

struct BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,m;
	int unit[MAXN][MAXM];
	inline void Init(reg int N,reg int M){
		n=N,m=M;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int x,reg int y,reg int val){
		for(reg int i=x;i<=n;i+=lowbit(i))
			for(reg int j=y;j<=m;j+=lowbit(j))
				unit[i][j]+=val;
		return;
	}
	inline int query(reg int x,reg int y){
		if(!x||!y)
			return 0;
		reg int res=0;
		for(reg int i=x;i;i-=lowbit(i))
			for(reg int j=y;j;j-=lowbit(j))
				res+=unit[i][j];
		return res;
	}
};

int n,m,q;
int c[MAXN][MAXM];
BIT T[MAXC];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=100;++i)
		T[i].Init(n,m);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			c[i][j]=read();
			T[c[i][j]].update(i,j,1);
		}
	q=read();
	while(q--){
		static int opt,x1,y1,x2,y2,C;
		opt=read();
		switch(opt){
			case 1:{
				x1=read(),y1=read(),C=read();
				T[c[x1][y1]].update(x1,y1,-1);
				c[x1][y1]=C;
				T[c[x1][y1]].update(x1,y1,1);
				break;
			}
			case 2:{
				x1=read(),x2=read(),y1=read(),y2=read(),C=read();
				reg int ans=T[C].query(x2,y2)+T[C].query(x1-1,y1-1)-(T[C].query(x2,y1-1)+T[C].query(x1-1,y2));
				printf("%d\n",ans);
				break;
			}
		}
	}
	return 0;
}