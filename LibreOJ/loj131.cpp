#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=1e6+5;

namespace BIT{
	int n;
	ll unit[MAXN];
	inline void init(reg int s){
		n=s;
		return;
	}
	inline void __update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll __query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline void update(reg int l,reg int r,reg ll val){
		__update(l,val),__update(r+1,-val);
		return;
	}
	inline ll query(reg int id){
		return __query(id);
	}
}

int n,q;

bool ed;

int main(void){
	n=read(),q=read();
	BIT::init(n);
	for(reg int i=1;i<=n;++i)
		BIT::update(i,i,read());
	while(q--){
		switch(read()){
			case 1:{
				static int l,r,x;
				l=read(),r=read(),x=read();
				BIT::update(l,r,x);
				break;
			}
			case 2:{
				writeln(BIT::query(read()));
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3f MiB\n",(&ed-&st)/1048576.0);
	return 0;
}