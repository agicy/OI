#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=4096+5;
const int MAXM=4096+5;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,m;
	ll unit[MAXN][MAXM];
	inline void Init(reg int s1,reg int s2){
		n=s1,m=s2;
		return;
	}
	inline void update(reg int x,reg int y,reg int val){
		for(reg int i=x;i<=n;i+=lowbit(i))
			for(reg int j=y;j<=m;j+=lowbit(j))
				unit[i][j]+=val;
		return;
	}
	inline ll query(reg int x,reg int y){
		reg ll res=0;
		for(reg int i=x;i;i^=lowbit(i))
			for(reg int j=y;j;j^=lowbit(j))
				res+=unit[i][j];
		return res;
	}
}

int n,m;

int main(void){
	n=read(),m=read();
	BIT::Init(n,m);
	static int opt;
	while(scanf("%d",&opt)!=EOF){
		static int a,b,c,d,k,x,y;
		switch(opt){
			case 1:{
				a=read(),b=read(),c=read(),d=read(),k=read();
				BIT::update(a,b,k),BIT::update(c+1,d+1,k);
				BIT::update(a,d+1,-k),BIT::update(c+1,b,-k);
				break;
			}
			case 2:{
				x=read(),y=read();
				writeln(BIT::query(x,y));
				break;
			}
		}
	}
	flush();
	return 0;
}