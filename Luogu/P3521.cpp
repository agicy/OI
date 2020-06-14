#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=200000+5;

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1)
	const int MAXSIZE=MAXN*30;
	int tot,lson[MAXSIZE],rson[MAXSIZE];
	ll sum[MAXSIZE];
	int top,S[MAXSIZE];
	inline int New(void){
		if(top)
			return S[top--];
		else
			return ++tot;
	}
	inline void del(reg int k){
		S[++top]=k;
		lson[k]=rson[k]=sum[k]=0;
		return;
	}
	ll ans1,ans2;
	inline int merge(reg int u,reg int v){
		if(!u||!v)
			return u|v;
		reg int k=New();
		sum[k]=sum[u]+sum[v];
		ans1+=sum[rson[u]]*sum[lson[v]];
		ans2+=sum[lson[u]]*sum[rson[v]];
		lson[k]=merge(lson[u],lson[v]);
		rson[k]=merge(rson[u],rson[v]);
		del(u),del(v);
		return k;
	}
	inline void Update(reg int &k,reg int l,reg int r,reg int pos){
		if(!k)
			k=New();
		++sum[k];
		if(l!=r){
			if(pos<=mid)
				Update(lson[k],l,mid,pos);
			else
				Update(rson[k],mid+1,r,pos);
		}
		return;
	}
	#undef mid
}

using namespace SegmentTree;

int n;
ll ans;

inline void Solve(reg int &x){
	x=0;
	reg int val=read();
	if(!val){
		int lson,rson;
		Solve(lson),Solve(rson);
		ans1=ans2=0;
		x=merge(lson,rson);
		ans+=min(ans1,ans2);
	}
	else
		Update(x,1,n,val);
	return;
}

int main(void){
	n=read();
	int root=0;
	Solve(root);
	printf("%lld\n",ans);
	return 0;
}