#pragma GCC optimize("Ofast")
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

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline ll gcd(reg ll a,reg ll b){
	return b?gcd(b,a%b):a;
}

struct Node{
	int id;
	ll a,b;
	inline Node(reg int id=0,reg ll a=0,reg ll b=0):id(id),a(a),b(b){
		return;
	}
	inline bool operator<(const Node& x)const{
		return a*x.b-b*x.a<0;
	}
	inline bool operator>(const Node& x)const{
		return a*x.b-b*x.a>0;
	}
	inline void print(void)const{
		reg ll d=gcd(a,b);
		write(a/d),putchar('/'),write(b/d),putchar('\n');
		return;
	}
};

const int MAXN=2e5+5;

int n,k;
int a[MAXN];
priority_queue<Node,vector<Node>,greater<Node> > Q;

bool ed;

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	sort(a+1,a+n+1);
	Q.push(Node(1,a[1],1));
	while(k--){
		static Node s;
		s=Q.top();
		Q.pop();
		s.print();
		if(s.id<n){
			Q.push(Node(s.id+1,s.a-a[s.id]+a[s.id+1],s.b));
			Q.push(Node(s.id+1,s.a+a[s.id+1],s.b+1));
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}