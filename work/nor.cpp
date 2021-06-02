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

inline ll gcd(reg ll a,reg ll b){
	return b?gcd(b,a%b):a;
}

struct Node{
	ll a,b;
	inline Node(reg ll a=0,reg ll b=0):a(a),b(b){
		return;
	}
	inline bool operator<(const Node& x)const{
		return a*x.b-b*x.a<0;
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

namespace Subtask1{
	int val[MAXN];
	vector<Node> V;
	inline void Solve(void){
		for(reg int i=0;i<n;++i)
			val[i]=a[i+1];
		V.resize((1<<n)-1);
		for(reg int S=1;S<(1<<n);++S){
			reg ll sum=0;
			for(reg int i=0;i<n;++i)
				if((S>>i)&1)
					sum+=val[i];
			V[S-1]=Node(sum,__builtin_popcount(S));
		}
		sort(V.begin(),V.end());
		for(reg int i=0;i<k;++i)
			V[i].print();
		return;
	}
}

namespace Subtask2{
	inline double binom(reg int n,reg int m){
		if(m<0||n<m)
			return 0;
		reg double res=1;
		for(reg int i=1;i<=m;++i)
			res=res*(n-i+1)/i;
		return res;
	}
	const int LIM=5;
	int cnt[LIM+1];
	struct Data{
		int T[LIM+1];
		inline int getSum(void)const{
			reg int res=0;
			for(reg int i=1;i<=LIM;++i)
				res+=T[i]*i;
			return res;
		}
		inline int getCnt(void)const{
			reg int res=0;
			for(reg int i=1;i<=LIM;++i)
				res+=T[i];
			return res;
		}
		inline double getFA(void)const{
			reg double res=1;
			for(reg int i=1;i<=LIM;++i)
				res*=binom(cnt[i],T[i]);
			return res;
		}
		inline bool operator<(const Data& a)const{
			return Node(getSum(),getCnt())<Node(a.getSum(),a.getCnt());
		}
	};
	priority_queue<Data,vector<Data>,less<Data> > Q;
	double sum=0;
	inline void Solve(void){
		for(reg int i=1;i<=n;++i)
			++cnt[a[i]];
		for(reg int i=1;i<=LIM;++i){
			vector<Data> V;
			V.reserve(Q.size());
			while(!Q.empty())
				V.push_back(Q.top()),Q.pop();
			sum=0;
			for(reg int j=1;j<=cnt[i];++j){
				Data tmp;
				fill(tmp.T,tmp.T+LIM+1,0);
				tmp.T[i]=j;
				if(sum>=k&&Q.top()<tmp)
					break;
				else{
					Q.push(tmp);
					sum+=tmp.getFA();
					while(sum>k&&sum-Q.top().getFA()>k)
						sum-=Q.top().getFA(),Q.pop();
				}
			}
			for(Data x:V)
				for(reg int j=0;j<=cnt[i];++j){
					Data tmp=x;
					tmp.T[i]=j;
					if(sum>=k&&Q.top()<tmp)
						break;
					else{
						Q.push(tmp);
						sum+=tmp.getFA();
						while(sum>k&&sum-Q.top().getFA()>k)
							sum-=Q.top().getFA(),Q.pop();
					}
				}
		}
		vector<Data> V;
		V.reserve(Q.size());
		while(!Q.empty())
			V.push_back(Q.top()),Q.pop();
		reverse(V.begin(),V.end());
		reg int cnt=0;
		for(reg int i=0,siz=V.size();i<siz;++i){
			reg double lim=V[i].getFA();
			for(reg int j=1;j<=lim;++j){
				if(++cnt<=k)
					Node(V[i].getSum(),V[i].getCnt()).print();
				else
					break;
			}
			if(cnt>=k)
				break;
		}
		return;
	}
}

namespace Subtask3{
	priority_queue<Node,vector<Node>,less<Node> > Q;
	inline void Solve(void){
		sort(a+1,a+n+1);
		for(reg int i=1;i<=n;++i){
			vector<Node> V;
			V.reserve(Q.size());
			while(!Q.empty()){
				V.push_back(Q.top());
				Q.pop();
			}
			Q.push(Node(a[i],1));
			for(reg int j=0,siz=V.size();j<siz;++j){
				Q.push(V[j]);
				Q.push(Node(V[j].a+a[i],V[j].b+1));
				while((int)Q.size()>k)
					Q.pop();
			}
		}
		vector<Node> V;
		V.reserve(k);
		reg int tmp=k;
		while(tmp--){
			V.push_back(Q.top());
			Q.pop();
		}
		for(reg int i=k-1;i>=0;--i)
			V[i].print();
		return;
	}
}

bool ed;

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	if(*max_element(a+1,a+n+1)<=5)
		//puts("S2"),
		Subtask2::Solve();
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}