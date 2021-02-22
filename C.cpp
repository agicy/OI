#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int mod=998244353;

int n;
int l[MAXN],r[MAXN],s[MAXN],t[MAXN];

namespace Subtask1{
	const int MAXN=15+5;
	int ans=0;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=mod?a-mod:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+mod:a;
	}
	inline int fpow(reg int x,reg int exp){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%mod;
			x=1ll*x*x%mod;
			exp>>=1;
		}
		return res;
	}
	inline int fac(reg int n){
		reg int res=1;
		for(reg int i=1;i<=n;++i)
			res=1ll*res*i%mod;
		return res;
	}
	namespace ScanningLine{
		struct Line{
			int x,y1,y2;
			int k;
			inline Line(reg int x=0,reg int y1=0,reg int y2=0,reg int k=0):x(x),y1(y1),y2(y2),k(k){
				return;
			}
			inline bool operator<(const Line& a)const{
				return x<a.x;
			}
		};
		int n;
		Line L[MAXN*2];
		vector<int> V;
		namespace SegmentTree{
			#define lson ( (k) << 1 )
			#define rson ( (k) << 1 | 1 )
			#define mid ( ( (l) + (r) ) >> 1 )
			struct Node{
				int cnt;
				int len;
				#define cnt(x) unit[(x)].cnt
				#define len(x) unit[(x)].len
			};
			Node unit[MAXN<<3];
			inline void pushup(reg int k,reg int l,reg int r){
				if(cnt(k))
					len(k)=sub(V[r+1],V[l]);
				else if(l!=r)
					len(k)=add(len(lson),len(rson));
				else
					len(k)=0;
				return;
			}
			inline void update(reg int k,reg int l,reg int r,reg int pl,reg int pr,reg int val){
				if(pl<=l&&r<=pr){
					cnt(k)=add(cnt(k),val);
					pushup(k,l,r);
					return;
				}
				if(pl<=mid)
					update(lson,l,mid,pl,pr,val);
				if(pr>mid)
					update(rson,mid+1,r,pl,pr,val);
				pushup(k,l,r);
				return;
			}
			#undef lson
			#undef rson
			#undef mid
		}
		inline int getId(int x){
			return lower_bound(V.begin(),V.end(),x)-V.begin();
		}
		inline int solve(reg int _n,reg int _l[],reg int _r[],reg int _s[],reg int _t[],reg int _p[]){
			n=_n;
			V.clear();
			reg int tot=0;
			for(reg int i=0;i<n;++i){
				static int x1,y1,x2,y2;
				x1=_l[i+1],x2=_r[i+1];
				y1=_s[_p[i+1]],y2=_t[_p[i+1]];
				L[tot++]=Line(x1,y1,y2,1);
				L[tot++]=Line(x2,y1,y2,-1);
				V.push_back(y1),V.push_back(y2);
			}
			sort(V.begin(),V.end());
			V.erase(unique(V.begin(),V.end()),V.end());
			reg int m=V.size()-2;
			sort(L,L+tot);
			reg double ans=0.0;
			for(reg int i=0;i<tot;++i){
				if(i>0)
					ans+=SegmentTree::unit[1].len*(L[i].x-L[i-1].x);
				SegmentTree::update(1,0,m,getId(L[i].y1),getId(L[i].y2)-1,L[i].k);
			}
			return ans;
		}
	}
	int p[MAXN];
	bool vis[MAXN];
	inline void dfs(reg int dep){
		if(dep==n+1){
			ans=add(ans,ScanningLine::solve(n,l,r,s,t,p));
			return;
		}
		for(reg int i=1;i<=n;++i)
			if(!vis[i]){
				vis[i]=true;
				p[dep]=i;
				dfs(dep+1);
				vis[i]=false;
			}
		return;
	}
	inline void Solve(void){
		dfs(1);
		ans=1ll*ans*fpow(fac(n),mod-2)%mod;
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		l[i]=read(),r[i]=read();
	for(reg int i=1;i<=n;++i)
		s[i]=read(),t[i]=read();
	if(n<=10){
		Subtask1::Solve();
	}
	return 0;
}