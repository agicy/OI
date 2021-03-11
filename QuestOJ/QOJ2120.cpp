#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=5e3+5;

struct Vector{
	int x,y;
	inline Vector(reg int x=0,reg int y=0):x(x),y(y){
		return;
	}
	inline Vector operator+(const Vector& a)const{
		return Vector(x+a.x,y+a.y);
	}
	inline Vector operator-(const Vector& a)const{
		return Vector(x-a.x,y-a.y);
	}
};

inline ll cross(const Vector& a,const Vector& b){
	return 1ll*a.x*b.y-1ll*a.y*b.x;
}

typedef Vector Point;

int n;
Point a[MAXN];
char str[MAXN];
bool vis[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i].x=read(),a[i].y=read();
	read(str+1);
	reg int pos=0;
	for(reg int i=1;i<=n;++i)
		if(!pos||(a[i].x<a[pos].x||(a[i].x==a[pos].x&&a[i].y<a[pos].y)))
			pos=i;
	vis[pos]=true,write(pos),putchar(n==1?'\n':' ');
	for(reg int i=2;i<=n;++i){
		reg int nex=0;
		for(reg int j=1;j<=n;++j)
			if(!vis[j]){
				if(!nex||(str[i-1]=='L'&&(cross(a[j]-a[pos],a[nex]-a[pos])>0))||(str[i-1]=='R'&&(cross(a[j]-a[pos],a[nex]-a[pos])<0)))
					nex=j;
			}
		vis[nex]=true,write(nex),putchar(i==n?'\n':' ');
		pos=nex;
	}
	flush();
	return 0;
}