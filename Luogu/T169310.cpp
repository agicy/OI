#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=2e5+5;
const int MAXM=1e6+5;

int mat[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	const int MAXE=5e6+5;
	int cnt,head[MAXM<<2],id[MAXE],Next[MAXE];
	inline void Add_Id(reg int x,reg int Id){
		Next[++cnt]=head[x];
		id[cnt]=Id;
		head[x]=cnt;
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int L,reg int R,reg int id){
		if(L<=l&&r<=R){
			Add_Id(k,id);
			return;
		}
		if(L<=mid)
			update(lson,l,mid,L,R,id);
		if(R>mid)
			update(rson,mid+1,r,L,R,id);
		return;
	}
	inline int query(reg int k,reg int l,reg int r,reg int pos,reg int Id){
		reg int res=0;
		for(reg int i=head[k];i;i=Next[i]){
			reg int v=id[i];
			if(!mat[v]){
				++res;
				mat[v]=Id;
			}
		}
		head[k]=0;
		if(l==r)
			return res;
		if(pos<=mid)
			res+=query(lson,l,mid,pos,Id);
		else
			res+=query(rson,mid+1,r,pos,Id);
		return res;
	}
	#undef lson
	#undef rson
	#undef mid
}

int n,m,q;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i){
		static int l,r;
		l=read(),r=read();
		SegmentTree::update(1,1,m,l,r,i);
	}
	reg int lastcnt=0;
	reg int q=read();
	for(reg int i=1;i<=q;++i){
		static int x;
		x=(read()+lastcnt)%m+1;
		write(lastcnt=SegmentTree::query(1,1,m,x,i)),putchar(i==q?'\n':' ');
	}
	for(reg int i=1;i<=n;++i)
		write(mat[i]),putchar(i==n?'\n':' ');
	flush();
	return 0;
}