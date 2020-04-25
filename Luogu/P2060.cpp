#include<cstdio>
#include<algorithm>
using std::swap;
#define reg register
#define abs(x) ( (x) > 0 ? (x) : ( - (x) ) )
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

int sx,sy,tx,ty;
int T[5][5]={0,3,2,3,2,3,2,1,2,3,2,1,4,3,2,3,2,3,2,3,2,3,2,3,4};

int main(void){
	reg int ans=0;
	sx=read(),sy=read(),tx=read(),ty=read();
	int x=abs(sx-tx),y=abs(sy-ty);
	while(x>4||y>4){
		if(x<0)
			x=-x;
		if(y<0)
			y=-y;
		if(x<y)
			swap(x,y);
		x-=2;
		y-=1;
		++ans;
	}
	printf("%d\n",ans+T[x][y]);
	return 0;
}
