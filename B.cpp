#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5+5;

int n,p,q,r;
int a[MAXN],b[MAXN],c[MAXN];

inline ll solve(reg int x1,reg int y1,reg int x2,reg int y2,reg int x3,reg int y3){
	const int X[3][3]={{x1,(x1+y1)>>1,y1},{x2,(x2+y2)>>1,y2},{x3,(x3+y3)>>1,y3}};
	int cnt[2][3][3][3];
	memset(cnt,0,sizeof(cnt));
	for(reg int i=1;i<=n;++i){
		for(reg int j=0;j<2;++j)
			for(reg int x=0;x<3;++x)
				for(reg int y=0;y<3;++y)
					for(reg int z=0;z<3;++z){
						reg int flag=(a[i]<X[0][x]+j*(x==1))+(b[i]<X[1][y]+j*(y==1))+(c[i]<X[2][z]+j*(z==1));
						cnt[j][x][y][z]+=(flag>=2);
					}
	}
	if(cnt[0][2][2][2]<n)
		return 0;
	else if(cnt[0][0][0][0]==n)
		return 1ll*(y1-x1+1)*(y2-x2+1)*(y3-x3+1);
	else{
		bool vis[2][2][2];
		memset(vis,false,sizeof(vis));
		reg ll res=0;
		for(reg int x=0;x<2;++x)
			for(reg int y=0;y<2;++y)
				for(reg int z=0;z<2;++z)
					if(cnt[1][x][y][z]==n){
						vis[x][y][z]=true;
						res+=1ll*(X[0][x+1]-(X[0][x]+x)+1)*(X[1][y+1]-(X[1][y]+y)+1)*(X[2][z+1]-(X[2][z]+z)+1);
					}
		for(reg int x=1;x<3;++x)
			for(reg int y=1;y<3;++y)
				for(reg int z=1;z<3;++z)
					if(cnt[0][x][y][z]<n)
						vis[x-1][y-1][z-1]=true;
		for(reg int x=0;x<2;++x)
			for(reg int y=0;y<2;++y)
				for(reg int z=0;z<2;++z)
					if(!vis[x][y][z])
						res+=solve(X[0][x]+x,X[0][x+1],X[1][y]+y,X[1][y+1],X[2][z]+z,X[2][z+1]);
		return res;
	}
}

int main(void){
	n=read(),p=read(),q=read(),r=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),b[i]=read(),c[i]=read();
	printf("%lld\n",solve(1,p,1,q,1,r));
	return 0;
}