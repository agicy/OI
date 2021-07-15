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
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=4e5+5;
const int MAXM=4e5+5;
const int inf=0x3f3f3f3f;

struct Node{
	int x,y,z;
	inline Node(reg int x=0,reg int y=0,reg int z=0):x(x),y(y),z(z){
		return;
	}
	inline bool operator<(const Node& a)const{
		return x<a.x;
	}
};

struct querys{
	int id,x,y,tmp[2];
	inline bool operator<(const querys& a)const{
		return y<a.y;
	}
};


int n,m;
int a[MAXN];
int f[MAXN],g[MAXN];
int top,S[MAXN];
bool tag[MAXN];
int cnt[MAXN];
Node pre[MAXN],suf[MAXN];
querys q[MAXN];
int ans[MAXM];

namespace BIT{
	int n,unit[MAXN];
	inline void init(reg int s){
		n=s;
		memset(unit+1,0,sizeof(int)*n);
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]=max(unit[i],val);
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res=max(res,unit[i]);
		return res;
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=m;++i)
		q[i].id=i,q[i].x=read(),q[i].y=read();
	sort(q+1,q+m+1);
	S[top=0]=-inf;
	for(reg int i=1;i<=n;++i){
		if(a[i]>S[top]){
			S[++top]=a[i];
			f[i]=top;
		}
		else{
			f[i]=lower_bound(S+1,S+top+1,a[i],less<int>())-S;
			S[f[i]]=a[i];
		}
		pre[i]=Node(a[i],i,f[i]);
	}
	S[top=0]=inf;
	for(reg int i=n;i>=1;--i){
		if(a[i]<S[top]){
			S[++top]=a[i];
			g[i]=top;
		}
		else{
			g[i]=lower_bound(S+1,S+top+1,a[i],greater<int>())-S;
			S[g[i]]=a[i];
		}
		suf[i]=Node(a[i],n-i+1,g[i]);
	}
	sort(pre+1,pre+n+1),sort(suf+1,suf+n+1);
	BIT::init(n);
	for(reg int i=1;i<=n;++i)
		if(f[i]+g[i]==top+1)
			++cnt[f[i]],tag[i]=true;
	for(reg int i=1,ptr=1;i<=m;++i){
		while(ptr<=n&&pre[ptr].x<q[i].y){
			BIT::update(pre[ptr].y,pre[ptr].z);
			++ptr;
		}
		q[i].tmp[0]=BIT::query(q[i].x-1);
	}
	BIT::init(n);
	for(reg int i=m,ptr=n;i>=1;--i){
		while(ptr>=1&&suf[ptr].x>q[i].y){
			BIT::update(suf[ptr].y,suf[ptr].z);
			--ptr;
		}
		q[i].tmp[1]=BIT::query(n-q[i].x);
	}
	for(reg int i=1;i<=m;++i)
		ans[q[i].id]=max(top-(tag[q[i].x]&&(cnt[f[q[i].x]]==1)),q[i].tmp[0]+q[i].tmp[1]+1);
	for(reg int i=1;i<=m;++i)
		writeln(ans[i]);
	flush();
	return 0;
}