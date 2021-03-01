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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=5e3+5;
const int inf=0x7f7f7f7f;

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,tim,t[MAXN];
	ll unit[MAXN];
	inline void Init(reg int s){
		n=s;
		++tim;
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			unit[i]+=val;
		}
		return;
	}
	inline void update(reg int l,reg int r,reg ll val){
		update(l,val),update(r+1,-val);
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			res+=unit[i];
		}
		return res;
	}
}

int n;
int S[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=1;i<=n;++i)
			S[i]=read();
		BIT::Init(n);
		reg ll ans=0;
		for(reg int i=1;i<=n;++i){
			reg ll tmp=BIT::query(i);
			if(tmp<S[i]-1){
				ans+=S[i]-1-tmp;
				tmp=S[i]-1;
			}
			BIT::update(i+1,i+1,tmp-S[i]+1);
			if(i+2<=n)
				BIT::update(i+2,min(n,i+S[i]),1);
		}
		writeln(ans);
	}
	flush();
	return 0;
}