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

const int MAXN=1e3+5;
const int MAXA=31;
const int dx[]={-1,0,0,1};
const int dy[]={0,-1,1,0};
const char dc[]="LDUR";

int n;
pair<int,int> p[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		p[i].first=read(),p[i].second=read();
	for(reg int i=1;i<n;++i)
		if((p[i].first+p[i].second+p[i+1].first+p[i+1].second)&1){
			puts("-1");
			return 0;
		}
	if(((p[1].first+p[1].second)&1)^1){
		printf("%d\n",MAXA+1);
		printf("1");
		for(reg int i=MAXA-1;i>=0;--i)
			printf(" %d",1<<i);
		putchar('\n');
	}
	else{
		printf("%d\n",MAXA);
		for(reg int i=MAXA-1;i>=0;--i)
			printf("%d%c",1<<i,i?' ':'\n');
	}
	for(reg int i=1;i<=n;++i){
		reg ll x=p[i].first,y=p[i].second;
		if(((x+y)&1)^1)
			putchar('U'),--y;
		for(reg int j=MAXA-1;j>=0;--j)
			for(reg int k=0;k<4;++k){
				reg ll fx=x+dx[k]*(1ll<<j),fy=y+dy[k]*(1ll<<j);
				if(0ll+abs(fx)+abs(fy)<(1ll<<j)){
					x=fx,y=fy;
					putchar(dc[3-k]);
					break;
				}
			}
		putchar('\n');
	}
	return 0;
}