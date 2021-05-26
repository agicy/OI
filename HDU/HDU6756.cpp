#include<cstdio>
#include<cctype>
#include<cmath>
#include<vector>
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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
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

const int MAXN=1e5+5;
const int MAXM=1e5+5;

struct BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	vector<int> unit;
	inline void Init(reg int s){
		n=s;
		unit.clear(),unit.resize(n+1);
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
};

int n,m;
unsigned a[MAXN];
bool tag[MAXN];
vector<int> G[MAXN],Big[MAXN];
BIT bit[MAXN];
vector<int> T[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read();
		for(reg int i=1;i<=n;++i)
			G[i].clear(),Big[i].clear();
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		for(reg int i=1;i<=m;++i){
			static int u,v;
			u=read(),v=read();
			G[u].push_back(v),G[v].push_back(u);
		}
		reg int B=max(10,int(sqrt(n)));
		for(reg int i=1;i<=n;++i)
			if(G[i].size()>(unsigned)B){
				tag[i]=true;
				bit[i].Init(G[i].size()+1);
				T[i].clear(),T[i].resize(G[i].size());
			}
			else
				tag[i]=false;
		for(reg int i=1;i<=n;++i)
			for(int v:G[i])
				if(tag[v])
					Big[i].push_back(v);
		for(reg int i=1;i<=n;++i)
			for(int v:Big[i])
				if(a[i]<T[v].size()){
					++T[v][a[i]];
					if(T[v][a[i]]==1)
						bit[v].update(a[i]+1,1);
				}
		reg int q=read();
		while(q--){
			static int opt,u,x;
			opt=read();
			switch(opt){
				case 1:{
					u=read(),x=read();
					for(int v:Big[u]){
						if(a[u]<T[v].size()){
							if(T[v][a[u]]==1)
								bit[v].update(a[u]+1,-1);
							--T[v][a[u]];
						}
					}
					a[u]=x;
					for(int v:Big[u]){
						if(a[u]<T[v].size()){
							++T[v][a[u]];
							if(T[v][a[u]]==1)
								bit[v].update(a[u]+1,1);
						}
					}
					break;
				}
				case 2:{
					u=read();
					if(tag[u]){
						reg int _l=0,_r=G[u].size(),_mid;
						while(_l<_r){
							_mid=(_l+_r)>>1;
							if(bit[u].query(_mid+1)==_mid+1)
								_l=_mid+1;
							else
								_r=_mid;
						}
						writeln(_l);
					}
					else{
						vector<bool> V;
						V.resize(G[u].size()+1);
						for(int v:G[u]){
							if(a[v]<V.size())
								V[a[v]]=true;
						}
						reg int ptr=0;
						while(V[ptr])
							++ptr;
						writeln(ptr);
					}
					break;
				}
			}
		}
	}
	flush();
	return 0;
}