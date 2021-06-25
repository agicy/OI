#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e4+5;
const int base=1331;
const int S=1e4;

int n;
int a[MAXN];
uint basep[MAXN];

namespace BIT1{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	uint unit[MAXN];
	inline void Init(reg int s){
		n=s;
		fill(unit+1,unit+n+1,0);
		return;
	}
	inline void update(reg int id){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=basep[i-id];
		return;
	}
	inline uint query(reg int id){
		reg uint res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i]*basep[id-i];
		return res;
	}
	inline uint query(reg int l,reg int r){
		return query(r)-query(l-1)*basep[r-l+1];
	}
}

namespace BIT2{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	uint unit[MAXN];
	inline void Init(reg int s){
		n=s;
		fill(unit+1,unit+n+1,0);
		return;
	}
	inline void update(reg int id){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=basep[i-id];
		return;
	}
	inline uint query(reg int id){
		reg uint res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i]*basep[id-i];
		return res;
	}
	inline uint query(reg int l,reg int r){
		return query(r)-query(l-1)*basep[r-l+1];
	}
}

int main(void){
	basep[0]=1;
	for(reg int i=1;i<=S;++i)
		basep[i]=basep[i-1]*base;
	reg int T=read();
	while(T--){
		n=read();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		BIT1::Init(n),BIT2::Init(n);
		reg bool flag=false;
		for(reg int i=1;i<=n;++i){
			reg int len=min(a[i],n-a[i]+1);
			if(BIT1::query(a[i]-len+1,a[i])!=BIT2::query(n-a[i]-len+2,n-a[i]+1)){
				flag=true;
				break;
			}
			BIT1::update(a[i]),BIT2::update(n-a[i]+1);
		}
		putchar(flag?'Y':'N'),putchar('\n');
	}
	return 0;
}