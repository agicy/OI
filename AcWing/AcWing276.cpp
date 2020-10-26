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

const int MAXN=15+1;

struct Node{
	int i,j,l,r,x,y;
	inline Node(reg int i=0,reg int j=0,reg int l=0,reg int r=0,reg int x=0,reg int y=0):i(i),j(j),l(l),r(r),x(x),y(y){
		return;
	}
};

int n,m,k;
int a[MAXN][MAXN];
int f[MAXN][MAXN*MAXN][MAXN][MAXN][2][2];
Node pre[MAXN][MAXN*MAXN][MAXN][MAXN][2][2];

inline int getVal(reg int i,reg int l,reg int r){
	return a[i][r]-a[i][l-1];
}

inline void print(const Node& x){
	if(!x.j)
		return;
	print(pre[x.i][x.j][x.l][x.r][x.x][x.y]);
	for(reg int i=x.l;i<=x.r;++i)
		printf("%d %d\n",x.i,i);
	return;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			a[i][j]=read()+a[i][j-1];
	memset(f,0xcf,sizeof(f));
	for(reg int r=0;r<=n;++r)
		for(reg int i=1;i<=m;++i)
			for(reg int j=i;j<=m;++j)
				f[r][0][i][j][0][0]=0;
	reg int ans=0;
	Node t;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=k;++j)
			for(reg int l=1;l<=m;++l)
				for(reg int r=l;r<=m;++r){
					if(j<r-l+1)
						continue;
					for(reg int l1=l;l1<=r;++l1)
						for(reg int r1=l1;r1<=r;++r1){
							reg int &v=f[i][j][l][r][0][0];
							reg int val=f[i-1][j-(r-l+1)][l1][r1][0][0]+getVal(i,l,r);
							if(v<val)
								v=val,pre[i][j][l][r][0][0]=Node(i-1,j-(r-l+1),l1,r1,0,0);
						}
					for(reg int l1=l;l1<=r;++l1)
						for(reg int r1=r;r1<=m;++r1)
							for(reg int y1=0;y1<2;++y1){
								reg int &v=f[i][j][l][r][0][1];
								reg int val=f[i-1][j-(r-l+1)][l1][r1][0][y1]+getVal(i,l,r);
								if(v<val)
									v=val,pre[i][j][l][r][0][1]=Node(i-1,j-(r-l+1),l1,r1,0,y1);
							}
					for(reg int l1=1;l1<=l;++l1)
						for(reg int r1=l;r1<=r;++r1)
							for(reg int x1=0;x1<2;++x1){
								reg int &v=f[i][j][l][r][1][0];
								reg int val=f[i-1][j-(r-l+1)][l1][r1][x1][0]+getVal(i,l,r);
								if(v<val)
									v=val,pre[i][j][l][r][1][0]=Node(i-1,j-(r-l+1),l1,r1,x1,0);
							}
					for(reg int l1=1;l1<=l;++l1)
						for(reg int r1=r;r1<=m;++r1)
							for(reg int x1=0;x1<2;++x1)
								for(reg int y1=0;y1<2;++y1){
									reg int &v=f[i][j][l][r][1][1];
									reg int val=f[i-1][j-(r-l+1)][l1][r1][x1][y1]+getVal(i,l,r);
									if(v<val)
										v=val,pre[i][j][l][r][1][1]=Node(i-1,j-(r-l+1),l1,r1,x1,y1);
								}
					if(j==k){
						for(reg int x=0;x<2;++x)
							for(reg int y=0;y<2;++y)
								if(ans<f[i][j][l][r][x][y])
									ans=f[i][j][l][r][x][y],t=Node(i,j,l,r,x,y);
					}
				}
	printf("Oil : %d\n",ans);
	print(t);
	return 0;
}