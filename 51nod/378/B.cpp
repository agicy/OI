#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXSIZE=20+5;
const int inf=0x3f3f3f3f;

int n;
int len[MAXN];
char str[MAXN][MAXSIZE];
int f[MAXN],sum[MAXN];

inline int F(reg int x,reg int y){
	for(reg int ans=min(len[x],len[y]);ans>=0;--ans){
		reg bool flag=true;
		for(reg int i=1;i<=ans;++i)
			if(str[x][i+len[x]-ans]!=str[y][i]){
				flag=false;
				break;
			}
		if(flag)
			return len[y]-ans;
	}
	return len[y];
}

namespace Subtask3{
	const int MAXN=2e5+5;
	const int MAXSIZE=20*MAXN;
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int Min;
			#define Min(x) unit[(x)].Min
		};
		Node unit[MAXN<<2];
		inline void pushup(reg int k){
			Min(k)=min(Min(lson),Min(rson));
			return;
		}
		inline void build(reg int k,reg int l,reg int r){
			if(!k)
				exit(0);
			if(l==r){
				Min(k)=inf;
				return;
			}
			build(lson,l,mid),build(rson,mid+1,r);
			pushup(k);
			return;
		}
		inline void update(reg int k,reg int l,reg int r,reg int pos,int val){
			if(l==r){
				Min(k)=min(Min(k),val);
				return;
			}
			if(pos<=mid)
				update(lson,l,mid,pos,val);
			else
				update(rson,mid+1,r,pos,val);
			pushup(k);
			return;
		}
		int res;
		inline void query(reg int k,reg int l,reg int r,reg int L,reg int R,reg int p){
			if(l==r){
				res=min(res,Min(k)+F(l-1,p));
				return;
			}
			reg int tmp1=res-Min(lson),tmp2=res-Min(rson);
			if(tmp1>tmp2){
				if(tmp1>0)
					query(lson,l,mid,L,R,p);
				if(Min(rson)<res)
					query(rson,mid+1,r,L,R,p);
			}
			else{
				if(tmp2>0)
					query(rson,mid+1,r,L,R,p);
				if(Min(lson)<res)
					query(lson,l,mid,L,R,p);
			}
			return;
		}
	}
	int g[MAXN];
	inline void Solve(void){
		SegmentTree::build(1,1,n);
		memset(g,0x3f,sizeof(g));
		int ans=inf;
		g[1]=len[1];
		ans=min(ans,g[1]+sum[n]-sum[1]);
		SegmentTree::update(1,1,n,1,g[1]-sum[1]);
		for(reg int i=2;i<=n;++i){
			SegmentTree::res=inf;
			SegmentTree::query(1,1,n,1,i-1,i);
			g[i]=SegmentTree::res+sum[i-1];
			SegmentTree::update(1,1,n,i,g[i]-sum[i]);
			ans=min(ans,g[i]+sum[n]-sum[i]);
		}
		printf("%d\n",ans);
		return;
	}
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		scanf("%s",str[i]+1);
		len[i]=strlen(str[i]+1);
		f[i]=F(i-1,i);
		sum[i]=sum[i-1]+f[i];
	}
	Subtask3::Solve();
	return 0;
}