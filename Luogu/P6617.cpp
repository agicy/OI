#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;
const int MAXW=5e5+5;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max;
		#define Max(x) unit[(x)].Max
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Max(k)=max(Max(lson),Max(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			Max(k)=0;
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
		if(l==r){
			Max(k)=val;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Max(k);
		if(L<=mid&&mid<R)
			return max(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m,w;
int a[MAXN];
set<int> S[MAXW];
vector<int> V;

inline int getPre(int i){
	static set<int>::iterator it1,it2;
	it1=S[a[i]].lower_bound(i),it2=S[w-a[i]].lower_bound(i);
	if(it2==S[w-a[i]].begin())
		return 0;
	else if(it1==S[a[i]].begin())
		return *--it2;
	else if(*--it1>*--it2)
		return 0;
	else
		return *it2;
}

int main(void){
	n=read(),m=read(),w=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=n;++i){
		SegmentTree::update(1,1,n,i,getPre(i));
		S[a[i]].insert(i);
	}
	reg int cnt=0;
	while(m--){
		static int opt,x,y;
		static set<int>::iterator it;
		opt=read(),x=read(),y=read();
		switch(opt){
			case 1:{
				V.clear();
				it=S[a[x]].upper_bound(x);
				if(it!=S[a[x]].end())
					V.push_back(*it);
				it=S[w-a[x]].upper_bound(x);
				if(it!=S[w-a[x]].end())
					V.push_back(*it);

				S[a[x]].erase(x),a[x]=y,S[a[x]].insert(x);
				V.push_back(x);

				it=S[a[x]].upper_bound(x);
				if(it!=S[a[x]].end())
					V.push_back(*it);
				it=S[w-a[x]].upper_bound(x);
				if(it!=S[w-a[x]].end())
					V.push_back(*it);

				for(reg int i=0,siz=V.size();i<siz;++i)
					SegmentTree::update(1,1,n,V[i],getPre(V[i]));
				break;
			}
			case 2:{
				x^=cnt,y^=cnt;
				reg bool ans=SegmentTree::query(1,1,n,x,y)>=x;
				cnt+=ans;
				puts(ans?"Yes":"No");
				break;
			}
		}
	}
	return 0;
}