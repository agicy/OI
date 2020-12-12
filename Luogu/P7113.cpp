#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0.;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXD=5;
const int MAXE=MAXN*MAXD;

int n,m;
int indeg[MAXN],outdeg[MAXN];
int cnt,head[MAXN],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

struct BigNumber{
	__int128 x;
	inline BigNumber(reg __int128 x=0):x(x){
		return;
	}
	inline BigNumber operator+(const BigNumber& a)const{
		return x+a.x;
	}
	inline BigNumber operator-(const BigNumber& a)const{
		return x-a.x;
	}
	inline BigNumber operator*(const BigNumber& a)const{
		return x*a.x;
	}
	inline BigNumber operator/(const BigNumber& a)const{
		return x/a.x;
	}
	inline BigNumber operator%(const BigNumber& a)const{
		return x%a.x;
	}
	inline bool operator==(const BigNumber& a)const{
		return x==a.x;
	}
	inline void print(void){
		static char buf[32];
		reg int p=-1;
		if(x==0)
			putchar('0');
		else
			for(;x;x/=10)
				buf[++p]=x%10+48;
		while(~p)
			putchar(buf[p--]);
		return;
	}
};

inline BigNumber gcd(const BigNumber& a,const BigNumber& b){
	return (b==0)?a:gcd(b,a%b);
}

inline BigNumber lcm(const BigNumber& a,const BigNumber& b){
	return a/gcd(a,b)*b;
}

struct Node{
	BigNumber a,b;
	inline Node(const BigNumber& a=0,const BigNumber& b=0):a(a),b(b){
		return;
	}
	inline Node operator+(const Node& x)const{
		BigNumber Lcm=lcm(b,x.b);
		BigNumber tagA=Lcm/b,tagB=Lcm/x.b;
		BigNumber na=tagA*a+tagB*x.a;
		BigNumber Gcd=gcd(na,Lcm);
		return Node(na/Gcd,Lcm/Gcd);
	}
	inline void print(void){
		a.print(),putchar(' '),b.print(),putchar('\n');
		return;
	}
};

inline Node Div(const Node& a,const BigNumber& x){
	BigNumber nb=a.b*x;
	BigNumber Gcd=gcd(a.a,nb);
	return Node(a.a/Gcd,nb/Gcd);
}

Node f[MAXN];
queue<int> Q;

inline void topo(void){
	for(int i=1;i<=n;++i)
		if(i<=m){
			f[i]=Node(1,1);
			Q.push(i);
		}
		else
			f[i]=Node(0,1);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		Node tag=Div(f[u],outdeg[u]);
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			f[v]=f[v]+tag;
			--indeg[v];
			if(!indeg[v])
				Q.push(v);
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		outdeg[i]=read();
		for(reg int j=1;j<=outdeg[i];++j){
			static int a;
			a=read();
			++indeg[a];
			Add_Edge(i,a);
		}
	}
	topo();
	for(reg int i=1;i<=n;++i)
		if(!outdeg[i])
			f[i].print();
	return 0;
}