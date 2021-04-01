#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXQ=5e5+5;

struct Node{
	int a,b;
	inline Node(reg int a=0,reg int b=0):a(a),b(b){
		return;
	}
};

int n;
int tot;
Node a[MAXQ];

inline void solve(reg int l,reg int r){
	if(l==r)
		return;
	reg int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	for(reg int i=l;i<=mid;++i)
		a[++tot]=Node(i,i-l+mid+1);
	return;
}

int main(void){
	scanf("%d",&n);
	reg int tmp=1;
	while((tmp<<1)<n)
		tmp<<=1;
	solve(1,tmp),solve(n-tmp+1,n);
	write(tot),putchar('\n');
	for(reg int i=1;i<=tot;++i)
		write(a[i].a),putchar(' '),write(a[i].b),putchar('\n');
	flush();
	return 0;
}