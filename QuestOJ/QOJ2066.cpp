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

inline int max(reg int a,reg int b){
	return a<b?b:a;
}

const int MAXN=1e5+5;
const int MAXK=1e5+5;

int n,k;
int rt[MAXN];
int S,ans;

struct Point{
	int x,y,c;
	inline bool operator<(const Point& a)const{
		return x<a.x||(x==a.x&&y<a.y);
	}
};

Point p[MAXN];

inline bool cmpy(const Point& a,const Point& b){
	return a.y<b.y||(a.y==b.y&&a.x<b.x);
}

vector<Point> V[MAXN];
vector<int> Vx,Vy;

namespace SegmentTree{
	const int MAXSIZE=MAXN*30;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson,sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int l,reg int r,reg int pos){
		reg int k=++tot;
		unit[k]=unit[pre];
		++sum(k);
		if(l==r)
			return k;
		if(pos<=mid)
			lson(k)=update(lson(pre),l,mid,pos);
		else
			rson(k)=update(rson(pre),mid+1,r,pos);
		return k;
	}
	inline int query(reg int k,reg int pre,reg int l,reg int r,reg int L,reg int R){
		if(L>R)
			return 0;
		if(L<=l&&r<=R)
			return sum(k)-sum(pre);
		if(L<=mid&&mid<R)
			return query(lson(k),lson(pre),l,mid,L,R)+query(rson(k),rson(pre),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(k),lson(pre),l,mid,L,R);
		else
			return query(rson(k),rson(pre),mid+1,r,L,R);
	}
	inline void Init(void){
		tot=0;
		for(reg int l=1,r=0,las=0;l<=n;l=r+1){
			r=l;
			rt[p[l].x]=update(las,1,S,p[l].y);
			las=rt[p[l].x];
			while(r+1<=n&&p[r+1].x==p[l].x){
				++r;
				rt[p[l].x]=update(las,1,S,p[r].y);
				las=rt[p[l].x];
			}
		}
		return;
	}
}

multiset<Point> M;
multiset<Point>::iterator it;

inline void getAns(reg int col){
	using namespace SegmentTree;
	if(V[col].empty()){
		ans=n;
		return;
	}
	reg int siz=V[col].size();
	sort(V[col].begin(),V[col].end());
	ans=max(ans,max(query(rt[V[col].front().x-1],0,1,S,1,S),query(rt[Vx.size()],rt[V[col].back().x],1,S,1,S)));
	for(reg int i=1;i<siz;++i)
		ans=max(ans,query(rt[V[col][i].x-1],rt[V[col][i-1].x],1,S,1,S));
	sort(V[col].begin(),V[col].end(),cmpy);
	M.clear();
	for(reg int i=siz-1,l,r,y;i>=0;--i){
		it=M.insert(V[col][i]);
		y=V[col][i].y+1;
		if(it!=M.begin())
			--it,l=it->x,++it;
		else
			l=0;
		++it;
		if(it!=M.end())
			r=it->x-1;
		else
			r=Vx.size();
		--it;
		ans=max(ans,query(rt[r],rt[l],1,S,y,S));
	}
	M.clear();
	for(reg int i=0,l,r,y;i<siz;++i){
		it=M.insert(V[col][i]);
		y=V[col][i].y-1;
		if(it!=M.begin())
			--it,l=it->x,++it;
		else
			l=0;
		++it;
		if(it!=M.end())
			r=it->x-1;
		else
			r=Vx.size();
		--it;
		ans=max(ans,query(rt[r],rt[l],1,S,1,y));
	}
	return;
}

int cnt[MAXK];

int main(void){
	reg int T=read();
	while(T--){
		n=read(),k=read();
		Vx.resize(n),Vy.resize(n);
		for(reg int i=1;i<=n;++i){
			Vx[i-1]=p[i].x=read(),Vy[i-1]=p[i].y=read(),p[i].c=read();
			++cnt[p[i].c];
		}
		sort(Vx.begin(),Vx.end()),Vx.erase(unique(Vx.begin(),Vx.end()),Vx.end());
		sort(Vy.begin(),Vy.end()),Vy.erase(unique(Vy.begin(),Vy.end()),Vy.end());
		S=Vy.size();
		for(reg int i=1;i<=k;++i)
			V[i].resize(cnt[i]),cnt[i]=0;
		for(reg int i=1;i<=n;++i){
			p[i].x=lower_bound(Vx.begin(),Vx.end(),p[i].x)-Vx.begin()+1;
			p[i].y=lower_bound(Vy.begin(),Vy.end(),p[i].y)-Vy.begin()+1;
			V[p[i].c][cnt[p[i].c]++]=p[i];
		}
		for(reg int i=1;i<=k;++i)
			cnt[i]=0;
		sort(p+1,p+n+1);
		ans=0;
		SegmentTree::Init();
		for(reg int i=1;i<=k;++i){
			getAns(i);
			if(ans==n)
				break;
		}
		printf("%d\n",ans);
	}
	return 0;
}