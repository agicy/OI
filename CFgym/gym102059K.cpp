#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=3e5+5;

int n;
int c[MAXN],d[MAXN];
vector<int> row[MAXN];

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i;i^=lowbit(i))
			unit[i]=max(unit[i],val);
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i<=n;i+=lowbit(i))
			res=max(res,unit[i]);
		return res;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		c[i]=read();
	for(reg int i=1;i<=n;++i)
		d[i]=read();
	for(int i=1;i<=n;++i)
		if(i>=c[i]&&c[i]!=1)
			row[i-c[i]+1].push_back(i);
	BIT::Init(n);
	for(reg int i=1;i<=n;++i){
		for(reg int j=row[i].size()-1;j>=0;--j){
			reg int v=row[i][j];
			BIT::update(v-1,BIT::query(v)+d[v]);
		}
		write(BIT::query(i)+(c[i]==1)*d[i]),putchar(i==n?'\n':' ');
		if(i+c[i]-1<=n)
			BIT::update(i+c[i]-1,BIT::query(i+c[i]-1)+d[i]);
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/1048576.0);
	return 0;
}