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

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=3e5+5;
const int MAXM=1e6+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

struct Node{
	int id,l;
	inline Node(reg int id=0,reg int l=0):id(id),l(l){
		return;
	}
};

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
	#undef Max
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

vector<Node> q[MAXN];
int ans[MAXM];

namespace PAM{
	struct Node{
		int ch[26];
		int link;
		int fail,len;
		int s,d;
		#define ch(x) unit[(x)].ch
		#define link(x) unit[(x)].link
		#define fail(x) unit[(x)].fail
		#define len(x) unit[(x)].len
		#define s(x) unit[(x)].s
		#define d(x) unit[(x)].d
	};
	int n,tot,las;
	Node unit[MAXN];
	inline int New(reg int l){
		len(tot)=l;
		return tot++;
	}
	inline void Init(void){
		New(0),fail(0)=New(-1);
		s(0)=-1;
		return;
	}
	inline int getFail(reg int p){
		while(s(n-len(p)-1)!=s(n))
			p=fail(p);
		return p;
	}
	int mat[MAXN];
	inline void insert(reg char ch,reg int pos){
		reg int c=ch-'a';
		s(++n)=c;
		reg int u=getFail(las);
		if(!ch(u)[c]){
			reg int p=New(len(u)+2);
			fail(p)=ch(getFail(fail(u)))[c];
			ch(u)[c]=p;
			d(p)=len(p)-len(fail(p));
			link(p)=(d(fail(p))==d(p)?link(fail(p)):p);
		}
		las=ch(u)[c];
		mat[pos]=las;
		return;
	}
	int cnt,head[MAXN],to[MAXN],Next[MAXN];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void build(void){
		Add_Edge(1,0);
		for(reg int i=2;i<tot;++i)
			Add_Edge(fail(i),i);
		return;
	}
	int tim,lef[MAXN],rig[MAXN];
	inline void dfs(reg int u){
		lef[u]=++tim;
		for(reg int i=head[u];i;i=Next[i])
			dfs(to[i]);
		rig[u]=tim;
		return;
	}
	inline void solve(void){
		BIT::Init(n);
		for(reg int i=1;i<=n;++i){
			for(reg int j=mat[i];j;j=fail(link(j))){
				reg int l=max(1,SegmentTree::query(1,1,tot,lef[j],rig[j])-len(j)+2),r=i-len(link(j))+2;
				BIT::update(l,1),BIT::update(r,-1);
			}
			SegmentTree::update(1,1,tot,lef[mat[i]],i);
			for(reg int j=0,siz=q[i].size();j<siz;++j)
				ans[q[i][j].id]=BIT::query(q[i][j].l);
		}
		return;
	}
}

int n,m;
char str[MAXN];

int main(void){
	n=read(),m=read();
	read(str+1);
	PAM::Init();
	for(reg int i=1;i<=n;++i)
		PAM::insert(str[i],i);
	PAM::build(),PAM::dfs(1);
	for(reg int i=1,l,r;i<=m;++i){
		l=read(),r=read();
		q[r].push_back(Node(i,l));
	}
	PAM::solve();
	reg int Ans=0;
	for(reg int i=1;i<=m;++i)
		Ans=add(Ans,1ll*i*ans[i]%mod);
	printf("%d\n",Ans);
	return 0;
}