#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=1e5+5;
const int MAXLOG2X=20+1;

struct Node{
	int op;
	ll a,b;
	inline Node(reg int op=0,reg ll a=0,reg ll b=0):op(op),a(a),b(b){
		return;
	}
};

int tot;
Node ans[MAXN];
bool vis[64];

inline void solve(reg int x){
	if(x==1)
		return;
	reg int l;
	for(reg int i=MAXLOG2X-1;i>=0;--i)
		if((x>>i)&1){
			l=i;
			break;
		}
	reg ll tmp=x;
	for(reg int i=0;i<l;++i){
		ans[++tot]=Node(0,tmp,tmp);
		tmp<<=1;
	}
	if(!vis[l+1]){
		ans[++tot]=Node(1,tmp,x);
		ans[++tot]=Node(0,tmp^x,tmp);
		ans[++tot]=Node(1,(tmp^x)+tmp,x);
		ans[++tot]=Node(0,tmp,tmp);
		ans[++tot]=Node(1,tmp<<1,((tmp^x)+tmp)^x);
		vis[l+1]=true;
	}
	for(reg int i=l+1;(1ll<<i)<=tmp;++i){
		if(!vis[i]){
			ans[++tot]=Node(0,1ll<<(i-1),1ll<<(i-1));
			vis[i]=true;
		}
		if((tmp>>i)&1){
			ans[++tot]=Node(1,tmp,1ll<<i);
			tmp^=(1ll<<i);
		}
	}
	vis[l]=true;
	ans[++tot]=Node(1,x,1ll<<l);
	solve(x^(1ll<<l));
	return;
}

int main(void){
	reg int x=read();
	solve(x);
	write(tot),putchar('\n');
	for(reg int i=1;i<=tot;++i)
		if(ans[i].op==0)
			write(ans[i].a),putchar(' '),putchar('+'),putchar(' '),write(ans[i].b),putchar('\n');
		else
			write(ans[i].a),putchar(' '),putchar('^'),putchar(' '),write(ans[i].b),putchar('\n');
	flush();
	return 0;
}