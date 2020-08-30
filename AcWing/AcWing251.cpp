#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e4+5;
const int MAXM=5e4+5;

int B;

struct querys{
	int id,l,r;
	inline void Read(int i){
		id=i;
		l=read(),r=read();
		return;
	}
	inline bool operator<(const querys& a)const{
		return l/B==a.l/B?r<a.r:l<a.l;
	}
};

int n,m;
int c[MAXN];
querys Q[MAXM];

struct Node{
	int x,y;
	inline Node(int x=0,int y=0):x(x),y(y){
		return;
	}
	inline int gcd(int a,int b){
		return b==0?a:gcd(b,a%b);
	}
	inline void update(void){
		int d=gcd(x,y);
		x/=d,y/=d;
		return;
	}
	inline void print(void){
		printf("%d/%d\n",x,y);
		return;
	}
};

Node ans[MAXM];

int x,y,len;
int T[MAXN];

inline void add(int c){
	x+=(T[c]++);
	y+=(len++);
	return;
}

inline void del(int c){
	x-=(--T[c]);
	y-=(--len);
	return;
}

int main(void){
	n=read(),m=read();
	B=n/sqrt(m);
	for(int i=1;i<=n;++i)
		c[i]=read();
	for(int i=1;i<=m;++i)
		Q[i].Read(i);
	sort(Q+1,Q+m+1);
	int l=1,r=0;
	for(int i=1;i<=m;++i)
		if(Q[i].l==Q[i].r)
			ans[Q[i].id]=Node(0,1);
		else{
			while(Q[i].l<l)
				add(c[--l]);
			while(l<Q[i].l)
				del(c[l++]);
			while(r<Q[i].r)
				add(c[++r]);
			while(Q[i].r<r)
				del(c[r--]);
			ans[Q[i].id]=Node(x,y);
			ans[Q[i].id].update();
		}
	for(int i=1;i<=m;++i)
		ans[i].print();
	return 0;
}