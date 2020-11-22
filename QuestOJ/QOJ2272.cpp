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

const int MAXN=10+1;
const int MAXM=10+1;
const int MAXK=10+1;
const int p=998244353;

int n,m,k;
int a[MAXN][MAXM];
int T[MAXK];
int f[MAXN][MAXM];
int Lg[1<<MAXK];

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline int dfs(reg int x,reg int y){
	if(y==m+1)
		++x,y=1;
	if(x==n+1)
		return 1;
	reg int res=0,C=f[x-1][y]|f[x][y-1];
	reg int sum=0;
	for(reg int i=C;i;i^=lowbit(i))
		++sum;
	if(m+n-x-y+1>k-sum)
		return 0;
	reg int S=(~C)&((1<<k)-1);
	for(reg int i=S,tag=-1;i;i^=lowbit(i)){
		reg int id=Lg[lowbit(i)]+1;
		if(a[x][y]==0||a[x][y]==id){
			f[x][y]=C|(1<<(id-1));
			++T[id];
			if(T[id]==1){
				if(tag==-1)
					tag=dfs(x,y+1);
				res=add(res,tag);
			}
			else if(T[id])
				res=add(res,dfs(x,y+1));
			--T[id];
		}
	}
	return res;
}

int main(void){
	n=read(),m=read(),k=read();
	Lg[0]=-1;
	for(reg int i=1,U=(1<<k)-1;i<=U;++i)
		Lg[i]=Lg[i>>1]+1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			a[i][j]=read();
			if(a[i][j])
				++T[a[i][j]];
		}
	if(n+m-1>k)
		puts("0");
	else
		printf("%d\n",dfs(1,1));
	return 0;
}