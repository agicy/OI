#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXH=1.5e3+5;
const int MAXW=1.5e3+5;

int h,w,n,m;
int X[MAXH][MAXW],Y[MAXW][MAXH];

int main(void){
	h=read(),w=read(),n=read(),m=read();
	for(reg int i=1,x,y;i<=n;++i){
		y=read(),x=read();
		X[y][x]=Y[x][y]=1;
	}
	for(reg int i=1,x,y;i<=m;++i){
		y=read(),x=read();
		X[y][x]=Y[x][y]=-1;
	}
	for(reg int y=1;y<=h;++y){
		reg char c=0;
		for(reg int x=1;x<=w;++x){
			reg char a=X[y][x];
			if(a==1)
				c=X[y][x]=1;
			else if(a==-1)
				c=0;
			else
				X[y][x]=c;
		}
		for(reg int x=w;x>=1;--x){
			reg char a=X[y][x];
			if(a==1)
				c=1;
			else if(a==-1)
				c=0;
			X[y][x]=c;
		}
	}
	for(reg int x=1;x<=w;++x){
		reg char c=0;
		for(reg int y=1;y<=h;++y){
			reg char a=Y[x][y];
			if(a==1)
				c=Y[x][y]=1;
			else if(a==-1)
				c=0;
			else
				Y[x][y]=c;
		}
		for(reg int y=h;y>=1;--y){
			reg char a=Y[x][y];
			if(a==1)
				c=1;
			else if(a==-1)
				c=0;
			Y[x][y]=c;
		}
	}
	reg int ans=0;
	for(reg int x=1;x<=w;++x)
		for(reg int y=1;y<=h;++y)
			ans+=(X[y][x]|Y[x][y]);
	printf("%d\n",ans);
	return 0;
}