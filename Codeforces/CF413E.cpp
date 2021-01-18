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

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int dis[2][2];
	};
	Node unit[MAXN<<2];
	inline Node operator+(const Node& a,const Node& b){
		Node res;
		memset(&res,-1,sizeof(res));
		reg int r;
		for(reg int i=0;i<2;++i)
			for(reg int k=0;k<2;++k)
				if(~(r=a.dis[i][k]))
					for(reg int j=0;j<2;++j)
						if(~b.dis[k][j])
							if(res.dis[i][j]==-1||((~res.dis[i][j])&&res.dis[i][j]>r+b.dis[k][j]+1))
								res.dis[i][j]=r+b.dis[k][j]+1;
		return res;
	}
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg char s[][2]){
		if(l==r){
			unit[k].dis[0][0]=unit[k].dis[1][1]=-1;
			unit[k].dis[0][1]=unit[k].dis[1][0]=-1;
			if(s[l][0]=='.')
				unit[k].dis[0][0]=0;
			if(s[l][1]=='.')
				unit[k].dis[1][1]=0;
			if(s[l][0]=='.'&&s[l][1]=='.')
				unit[k].dis[0][1]=unit[k].dis[1][0]=1;
			return;
		}
		build(lson,l,mid,s),build(rson,mid+1,r,s);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m;
char s[MAXN][2];

inline int getId(reg int x){
	if(x>n)
		return x-n;
	else
		return x;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		do
			s[i][0]=getchar();
		while(s[i][0]!='.'&&s[i][0]!='X');
	for(reg int i=1;i<=n;++i)
		do
			s[i][1]=getchar();
		while(s[i][1]!='.'&&s[i][1]!='X');
	SegmentTree::build(1,1,n,s);
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		if(getId(u)>getId(v))
			swap(u,v);
		SegmentTree::Node res=SegmentTree::query(1,1,n,getId(u),getId(v));
		printf("%d\n",res.dis[u>n][v>n]);
	}
	return 0;
}