#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e6+5;

namespace SA{
	const int MAXS=1e6+5;
	int sa[MAXN],rk[MAXN<<1],oldrk[MAXN<<1],px[MAXN],id[MAXN];
	int cnt[MAXS];
	int ht[MAXN];
	inline bool cmp(reg int x,reg int y,reg int w){
		return oldrk[x]==oldrk[y]&&oldrk[x+w]==oldrk[y+w];
	}
	inline void build(reg int n,reg char s[]){
		reg int m=max(n,300);
		for(reg int i=1;i<=n;++i)
			++cnt[rk[i]=s[i]];
		for(reg int i=1;i<=m;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=n;i>=1;--i)
			sa[cnt[rk[i]]--]=i;
		for(reg int w=1;w<n;w<<=1){
			reg int p=0;
			for(reg int i=n;i>n-w;--i)
				id[++p]=i;
			for(reg int i=1;i<=n;++i)
				if(sa[i]>w)
					id[++p]=sa[i]-w;
			memset(cnt,0,sizeof(cnt));
			for(reg int i=1;i<=n;++i)
				++cnt[px[i]=rk[id[i]]];
			for(reg int i=1;i<=m;++i)
				cnt[i]+=cnt[i-1];
			for(reg int i=n;i>=1;--i)
				sa[cnt[px[i]]--]=id[i];
			memcpy(oldrk,rk,sizeof(rk));
			p=0;
			for(reg int i=1;i<=n;++i)
				rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
		}
		for(reg int i=1,k=0;i<=n;++i){
			if(k)
				--k;
			while(s[i+k]==s[sa[rk[i]-1]+k])
				++k;
			ht[rk[i]]=k;
		}
		return;
	}
}

namespace ST{
	const int MAXLOG2N=18+1;
	int Lg[MAXN];
	int Min[MAXLOG2N][MAXN];
	inline void build(reg int n,reg int a[]){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			Lg[i]=Lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Min[0][i]=a[i];
		for(reg int i=1;i<MAXLOG2N;++i)
			for(reg int j=1;j+(1<<i)-1<=n;++j)
				Min[i][j]=min(Min[i-1][j],Min[i-1][j+(1<<(i-1))]);
		return;
	}
	inline int queryMin(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
}

inline int query(reg int l,reg int r){
	if(l==r)
		return n-SA::sa[l]+1;
	else
		return ST::queryMin(l+1,r);
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*30;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot,root[MAXN];
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int l,reg int r,reg int val){
		reg int k=++tot;
		unit[k]=unit[pre];
		++sum(k);
		if(val<=mid)
			lson(k)=update(lson(pre),l,mid,val);
		else
			rson(k)=update(rson(pre),mid+1,r,val);
		return k;
	}
	inline int query(reg int k,reg int pre,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return sum(k)-sum(pre);
		if(L<=mid&&mid<R)
			return query(lson(k),lson(pre),l,mid,L,R)+query(rson(k),rson(pre),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(k),lson(pre),l,mid,L,R);
		else
			return query(rson(k),rson(pre),mid+1,r,L,R);
	}
	inline int query(reg int k,reg int pre,reg int l,reg int r,reg int val){
		if(l==r)
			return l;
		reg int sum=sum(lson(k))-sum(lson(pre));
		if(val<=sum)
			return query(lson(k),lson(pre),l,mid,val);
		else
			return query(rson(k),rson(pre),mid+1,r,val-sum);
	}
	#undef mid
}

int n,m;
char s[MAXN];

int main(void){
	scanf("%s%d",s+1,&m);
	n=strlen(s+1);
	SA::build(n,s);
	ST::build(n,SA::ht);
	using SegmentTree::root;
	for(reg int i=1;i<=n;++i)
		root[i]=SegmentTree::update(root[i-1],1,n,SA::rk[i]);
	while(m--){
		int i, l, r, sum, L, R, Ls, Rs, mid, ans;
		scanf("%d%d%d",&i,&l,&r);
		i=SA::rk[i];
		/*
		reg int sum=SegmentTree::query(root[r],root[l-1],1,n,1,i-1);
		if(sum<SegmentTree::unit[root[r]].sum-SegmentTree::unit[root[l-1]].sum){
			R=SegmentTree::query(root[r],root[l-1],1,n,sum+1);
			Rs=query(i,R);
		}
		else{

		}
		if(sum<seg[rt[r]].sum - seg[rt[l - 1]].sum )
			(R = query(sum + 1, rt[l - 1], rt[r], 1, n), Rs sum ? = (L query(i, R)) = query(sum, rt [l:(Rs = --1), 1], rt[r], 1, n), Ls = query(L, i))
			: (Ls = -1);
		if (Ls >= Rs)
		{
			printf("%d ", Ls), L = 1, R = i - 1, ans = i;
			while (L <= R)
				mid = L + R >> 1, query(mid, i) >= Ls ? (R = mid - 1, ans = mid) : (L = mid + 1);
			printf("%d\n", sa[query(query(1, ans - 1, rt[l - 1], rt[r], 1, n) + 1, rt[l - 1], rt[r], 1, n)]);
		}
		else
			printf("%d %d\n", Rs, sa[R]);*/
	}
	return 0;
}