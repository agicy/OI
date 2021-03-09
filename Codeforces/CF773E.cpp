#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('\n');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int sgn(reg int x){
	if(!x)
		return 0;
	else
		return x<0?-1:1;
}

const int MAXN=5e5+5;
const int inf=0x3f3f3f3f;

int n;
pair<int,int> a[MAXN];
int pos[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		pair<int,int> Min;
		int tag;
		#define Min(x) unit[(x)].Min
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k){
		Min(k)=min(Min(lson),Min(rson));
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg pair<int,int> a[]){
		if(l==r){
			Min(k)=make_pair(a[l].first,(int)l);
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k);
		return;
	}
	inline void add(reg int k,reg int val){
		Min(k).first+=val;
		tag(k)+=val;
		return;
	}
	inline void pushdown(reg int k){
		if(tag(k)){
			add(lson,tag(k)),add(rson,tag(k));
			tag(k)=0;
		}
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int val){
		if(L<=l&&r<=R){
			add(k,val);
			return;
		}
		pushdown(k);
		if(L<=mid)
			update(lson,l,mid,L,R,val);
		if(R>mid)
			update(rson,mid+1,r,L,R,val);
		pushup(k);
		return;
	}
	inline pair<int,int> query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return Min(k);
		pushdown(k);
		if(L<=mid&&mid<R)
			return min(query(lson,l,mid,L,R),query(rson,mid+1,r,L,R));
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

int main(void){
	n=read();
	for(int i=0;i<n;++i)
		a[i]=make_pair(read(),i);
	sort(a,a+n);
	for(reg int i=0;i<n;++i)
		pos[a[i].second]=i;
	SegmentTree::build(1,0,n-1,a);
	set<int> Sn,S0,Sp;
	for(reg int id=0;id<n;++id){
		int i=pos[id];
		pair<int,int> p=SegmentTree::query(1,0,n-1,i,i);
		switch(sgn(p.first)){
			case 0:{
				S0.insert(i);
				break;
			}
			case 1:{
				Sp.insert(i);
				SegmentTree::update(1,0,n-1,i,n-1,-1);
				pair<int,int> q=SegmentTree::query(1,0,n-1,i,n-1);
				if(q.first==-1){
					int pos=q.second;
					Sp.erase(pos);
					SegmentTree::update(1,0,n-1,pos,n-1,1);
					S0.insert(pos);
				}
				break;
			}
			case -1:{
				Sn.insert(i);
				SegmentTree::update(1,0,n-1,i,n-1,1);
				int rigN=*(--Sn.end());
				if(a[rigN].first==1-(int)Sn.size()){
					Sn.erase(rigN),S0.insert(rigN);
					SegmentTree::update(1,0,n-1,rigN,n-1,-1);
				}
				else if(!S0.empty()){
					int lef0=*(S0.begin());
					S0.erase(lef0),Sp.insert(lef0);
					SegmentTree::update(1,0,n-1,lef0,n-1,-1);
				}
				break;
			}
		}
		printf("%ld\n",Sp.size()-Sn.size());
	}
	return 0;
}