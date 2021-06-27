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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

int n,a[MAXN];
ll ans;
set<int> S;

struct BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	ll unit[MAXN];
	inline void init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
	inline ll query(reg int l,reg int r){
		return query(r)-query(l-1);
	}
};

BIT B[2];

inline void calc(set<int>::iterator l,set<int>::iterator r,reg int opt){
	set<int>::iterator i,j;
	ll sum=*l&&a[*l+1]>a[*l]&&!((*l^*--(j=l))&1)&&!((*l^*++(j=l))&1)?a[*l]:0;
	for(i=l++;i!=r;i=l++)
		if(a[*l]>a[*i])
			sum+=B[*l&1].query(*i+1,*l);
		else
			sum+=B[*i&1].query(*i+1,*l-((*l^*++(j=l))&1));
	ans+=sum*opt;
	return;
}

inline void check(reg int x){
	if((a[x]>a[x-1])!=(a[x+1]>a[x]))
		S.insert(x);
	else
		S.erase(x);
	return;
}

inline void update(reg int x){
	reg int y=read();
	set<int>::iterator i=S.lower_bound(x);
	set<int>::iterator l=i,r=i;
	--l;
	if(l!=S.begin())
		--l;
	++r;
	if(r==S.end()||(*i==x&&++r==S.end()))
		--r;
	calc(l,r,-1);
	B[x&1].update(x,y-a[x]);
	a[x]=y;
	check(x);
	if(x>1) check(x-1);
	if(x<n) check(x+1);
	calc(l,r,1);
	return;
}

bool ed;

int main(void){
	n=read();
	S.insert(0),S.insert(n+1);
	B[0].init(n),B[1].init(n);
	for(reg int i=1;i<=n;++i)
		update(i);
	reg int q=read();
	while(q--){
		update(read());
		writeln(ans);
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}