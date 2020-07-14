#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXQ=15000+5;
const int MAXC=15000+5;
const int MAXLOG2Q=16+1;

int q,maxc;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	bool vis[MAXQ<<2];
	int dp[MAXLOG2Q][MAXC];
	vector<pair<int,int>/**/> val[MAXQ<<2];
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R,const pair<int,int> &P){
		if(L<=l&&r<=R){
			val[k].push_back(P);
			return;
		}
		if(L<=mid)
			Update(lson,l,mid,L,R,P);
		if(R>mid)
			Update(rson,mid+1,r,L,R,P);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int pos,reg int Val,reg int dep){
		if(!vis[k]){
			memcpy(dp[dep],dp[dep-1],sizeof(dp[dep]));
			for(reg int i=0,size=val[k].size();i<size;++i)
				for(reg int j=maxc;j>=val[k][i].first;--j)
					dp[dep][j]=max(dp[dep][j],dp[dep][j-val[k][i].first]+val[k][i].second);
			vis[k]=true;
		}
		if(l==r)
			return dp[dep][Val];
		if(pos<=mid)
			return Query(lson,l,mid,pos,Val,dep+1);
		else
			return Query(rson,mid+1,r,pos,Val,dep+1);
	}
	#undef lson
	#undef rson
	#undef mid
}

using namespace SegmentTree;

int main(void){
	q=read(),maxc=read();
	for(reg int i=1;i<=q;++i){
		static int opt,c,v,e;
		opt=read(),c=read();
		switch(opt){
			case 1:{
				v=read(),e=read();
				Update(1,1,q,i,e,make_pair(c,v));
				break;
			}
			case 2:{
				reg int ans=Query(1,1,q,i,c,1);
				printf("%d\n",ans);
				break;
			}
			default:break;
		}
	}
	return 0;
}