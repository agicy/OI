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
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e5+5;

namespace SegmentTree{
	const int MAXSIZE=MAXN*50;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int sum;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
	};
	int tot;
	Node unit[MAXSIZE];
	inline int update(reg int pre,reg int l,reg int r,reg int pos,reg int val){
		reg int p=++tot;
		unit[p]=unit[pre];
		++sum(p);
		if(l!=r){
			if(pos<=mid)
				lson(p)=update(lson(pre),l,mid,pos,val);
			else
				rson(p)=update(rson(pre),mid+1,r,pos,val);
		}
		return p;
	}
	inline int query(reg int p,reg int pre,reg int l,reg int r,reg int val){
		if(l==r)
			return l;
		reg int lef=sum(lson(p))-sum(lson(pre)),rig=sum(rson(p))-sum(rson(pre));
		reg int res;
		if(lef>val){
			res=query(lson(p),lson(pre),l,mid,val);
			if(res!=-1)
				return res;
		}
		if(rig>val){
			res=query(rson(p),rson(pre),mid+1,r,val);
			if(res!=-1)
				return res;
		}
		return -1;
	}
	#undef mid
}

int n,q;
int a[MAXN];
int rt[MAXN];
vector<int> V;

int main(void){
	n=read(),q=read();
	V.resize(n);
	for(reg int i=1;i<=n;++i)
		V[i-1]=a[i]=read();
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	reg int m=V.size();
	for(reg int i=1;i<=n;++i){
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		rt[i]=SegmentTree::update(rt[i-1],1,m,a[i],1);
	}
	while(q--){
		static int l,r,k;
		l=read(),r=read(),k=read();
		reg int val=(r-l+1)/k;
		reg int res=SegmentTree::query(rt[r],rt[l-1],1,m,val);
		if(res==-1)
			writeln(-1);
		else
			writeln(V[res-1]);
	}
	flush();
	return 0;
}