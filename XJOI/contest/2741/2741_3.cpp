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

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;

int n;
set<int> S1,S2;

namespace UnionFind{
	struct Node{
		int fa,siz;
		set<int> S;
		#define fa(x) unit[(x)].fa
		#define siz(x) unit[(x)].siz
		#define S(x) unit[(x)].S
	};
	Node unit[MAXN<<1];
	inline int find(reg int x){
		if(x==fa(x))
			return x;
		else
			return fa(x)=find(fa(x));
	}
	inline void merge1(reg int a,reg int b){
		a=find(a),b=find(b);
		if(S(a).size()<S(b).size())
			swap(S(a),S(b));
		for(set<int>::iterator it=S(b).begin();it!=S(b).end();++it)
			S(a).insert(*it);
		fa(b)=a;
		siz(a)+=siz(b);
		return;
	}
	inline void merge2(reg int a,reg int b){
		a=find(a),b=find(b);
		if(!S(a).empty()){
			S1.erase(*S(a).begin());
			if(siz(a)>1)
				S2.erase(*S(a).begin());
		}
		if(!S(b).empty()){
			S1.erase(*S(b).begin());
			if(siz(b)>1)
				S2.erase(*S(b).begin());
		}
		S(a).erase(*S(a).begin());
		if(S(a).size()<S(b).size())
			swap(S(a),S(b));
		for(set<int>::iterator it=S(b).begin();it!=S(b).end();++it)
			S(a).insert(*it);
		S(b).clear();
		fa(b)=a;
		siz(a)+=siz(b)-2;
		if(!S(a).empty()){
			S1.insert(*S(a).begin());
			if(siz(a)>1)
				S2.insert(*S(a).begin());
		}
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
	inline void init(reg int n){
		for(reg int i=1;i<=(n<<1);++i)
			fa(i)=i,siz(i)=1;
		for(int i=n+1;i<=(n<<1);++i)
			S(i).insert(i);
		return;
	}
	#undef fa
	#undef siz
	#undef S
}

int ans[MAXN];

bool ed;

int main(void){
	n=read();
	UnionFind::init(n);
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		UnionFind::merge1(x,y);
	}
	for(reg int i=1;i<=(n<<1);++i)
		if(i==UnionFind::find(i)&&!UnionFind::unit[i].S.empty()){
			S1.insert(*UnionFind::unit[i].S.begin());
			if(UnionFind::unit[i].siz>1)
				S2.insert(*UnionFind::unit[i].S.begin());
		}
	for(reg int i=n;i>=1;--i){
		if(UnionFind::unit[UnionFind::find(i)].siz==1&&i!=1){
			int tmp=*S2.begin();
			if(!UnionFind::search(tmp,i))
				ans[i]=tmp;
			else{
				S2.erase(tmp);
				ans[i]=*S2.begin();
				S2.erase(S2.begin());
				S2.insert(tmp);
			}
		}
		else{
			int tmp=*S1.begin();
			if(!UnionFind::search(tmp,i))
				ans[i]=tmp;
			else{
				S1.erase(tmp);
				ans[i]=*S1.begin();
				S1.erase(S1.begin());
				S1.insert(tmp);
			}
		}
		UnionFind::merge2(ans[i],i);
	}
	for(reg int i=1;i<=n;++i)
		writeln(i);
	for(reg int i=n;i>=1;--i)
		writeln(ans[i]);
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}