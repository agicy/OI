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
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int MAXQ=1e5+5;

struct querys{
	int l,r,c,d;
};

int n,q;
int a[MAXN],b[MAXN];
querys Q[MAXQ];

namespace Subtask1{
	inline void Solve(void){
		for(reg int i=1;i<=q;++i){
			reg int cnt=0;
			for(reg int j=Q[i].l;j<=Q[i].r;++j)
				if((a[j]^Q[i].c)<=min(b[j],Q[i].d))
					++cnt;
			writeln(cnt);
		}
		flush();
		return;
	}
}

namespace Subtask{
	const int MAXLOG2A=25;
	const int inf=1<<24;
	namespace Trie{
		const int MAXSIZE=MAXN*60;
		struct Node{
			int ch[2];
			int siz,Max,Min;
			#define ch(x) unit[(x)].ch
			#define siz(x) unit[(x)].siz
			#define Max(x) unit[(x)].Max
			#define Min(x) unit[(x)].Min
		};
		int tot;
		Node unit[MAXSIZE];
		inline void Init(void){
			tot=0;
			unit[0].ch[0]=0;
			unit[0].ch[1]=0;
			unit[0].siz=0;
			unit[0].Max=0,unit[0].Min=inf;
			return;
		}
		inline int insert(reg int pre,reg int dep,reg int a,reg int b){
			reg int p=++tot;
			unit[p]=unit[pre];
			++siz(p),Max(p)=max(Max(p),b),Min(p)=min(Min(p),b);
			if(dep!=-1){
				reg int c=(a>>dep)&1;
				ch(p)[c]=insert(ch(pre)[c],dep-1,a,b);
			}
			return p;
		}
		inline int query(reg int p,reg int dep,reg int c,reg int d,reg int val){
			if(!p)
				return 0;
			if(val>min(Max(p),d))
				return 0;
			if((val|((1<<(dep+1))-1))<=min(Min(p),d))
				return siz(p);
			if(dep==-1)
				return (val<=min(Max(p),d))*siz(p);
			else{
				reg int tag=(c>>dep)&1;
				reg int lef=query(ch(p)[0],dep-1,c,d,val|((tag^0)<<dep));
				reg int rig=query(ch(p)[1],dep-1,c,d,val|((tag^1)<<dep));
				return lef+rig;
			}
		}
	}
	int id[MAXQ];
	int ans[MAXQ];
	int rt[MAXN];
	inline void solve(reg int l,reg int r,reg int L,reg int R){
		if(l>r||L>R)
			return;
		if(l==r){
			for(reg int i=L;i<=R;++i)
				ans[id[i]]=((a[l]^Q[id[i]].c)<=min(b[l],Q[id[i]].d));
			return;
		}
		reg int mid=(l+r)>>1;

		Trie::Init();
		rt[mid]=Trie::insert(rt[0],MAXLOG2A-1,a[mid],b[mid]);
		for(reg int i=mid-1;i>=l;--i)
			rt[i]=Trie::insert(rt[i+1],MAXLOG2A-1,a[i],b[i]);
		rt[mid+1]=Trie::insert(rt[0],MAXLOG2A-1,a[mid+1],b[mid+1]);
		for(reg int i=mid+2;i<=r;++i)
			rt[i]=Trie::insert(rt[i-1],MAXLOG2A-1,a[i],b[i]);

		reg int cntl=0,cntr=0;
		static int idl[MAXQ],idr[MAXQ];
		for(reg int i=L;i<=R;++i){
			if(Q[id[i]].l<=mid&&mid<Q[id[i]].r){
				reg int lef=Trie::query(rt[Q[id[i]].l],MAXLOG2A-1,Q[id[i]].c,Q[id[i]].d,0);
				reg int rig=Trie::query(rt[Q[id[i]].r],MAXLOG2A-1,Q[id[i]].c,Q[id[i]].d,0);
				ans[id[i]]=lef+rig;
			}
			else if(Q[id[i]].l<=mid)
				idl[++cntl]=id[i];
			else
				idr[++cntr]=id[i];
		}
		for(reg int i=1;i<=cntl;++i)
			id[L+i-1]=idl[i];
		for(reg int i=1;i<=cntr;++i)
			id[R-i+1]=idr[i];
		solve(l,mid,L,L+cntl-1),solve(mid+1,r,R-cntr+1,R);
		return;
	}
	inline bool cmp(reg int a,reg int b){
		return Q[a].l<Q[b].l;
	}
	inline void Solve(void){
		for(reg int i=1;i<=q;++i)
			id[i]=i;
		solve(1,n,1,q);
		for(reg int i=1;i<=q;++i)
			writeln(ans[i]);
		flush();
		return;
	}
}

int main(void){
	freopen("island.in","r",stdin);
	freopen("island.out","w",stdout);
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),b[i]=read();
	for(reg int i=1;i<=q;++i)
		Q[i].l=read(),Q[i].r=read(),Q[i].c=read(),Q[i].d=read();
	if(n<=1e4&&q<=1e4)
		//puts("S1"),
		Subtask1::Solve();
	else
		//puts("S:"),
		Subtask::Solve();

	fclose(stdin);
	fclose(stdout);
	return 0;
}