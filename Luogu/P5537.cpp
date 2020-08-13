#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> hash_t;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;

int n,m,q,a[MAXN];
vector<int> G[MAXN];

inline int add(reg int a,reg int b,reg int mod){
	reg int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline int mul(reg int a,reg int b,reg int mod){
	return 1ll*a*b%mod;
}

const hash_t p=hash_t(71,853);
const hash_t mod=hash_t(int(1e9+7),int(1e9+9));

hash_t basep[MAXN];

inline hash_t operator+(const hash_t& a,const hash_t& b){
	return hash_t(add(a.first,b.first,mod.first),add(a.second,b.second,mod.second));
}

inline hash_t operator*(const hash_t& a,const hash_t& b){
	return hash_t(mul(a.first,b.first,mod.first),mul(a.second,b.second,mod.second));
}

inline void init(void){
	basep[0]=hash_t(1,1);
	for(reg int i=1;i<MAXN;++i)
		basep[i]=basep[i-1]*p;
	return;
}

hash_t h[MAXN];

namespace HashTable{
	const int P=1e6-17,seed=24601;
	struct edge{
		hash_t to;
		int w,next;
	};
	edge e[MAXN];
	int head[P],ecnt;
	inline void Add_Edge(reg int a,const hash_t& b,reg int c){
		e[ecnt]=(edge){b,c,head[a]},head[a]=ecnt++;
		return;
	}
	inline void init(void){
		ecnt=0;
		memset(head,-1,sizeof(head));
		return;
	}
	inline void insert(const hash_t& a,reg int b){
		reg int tmp=((ll)a.first*seed+a.second)%P;
		Add_Edge(tmp,a,b);
		return;
	}
	inline int query(const hash_t& a){
		reg int tmp=((ll)a.first*seed+a.second)%P;
		for(reg int i=head[tmp];~i;i=e[i].next)
			if(e[i].to==a)
				return e[i].w;
		return -1;
	}
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l)+(r) ) >> 1 )
	struct Node{
		hash_t h;
		#define h(x) unit[(x)].h
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k,reg int l,reg int r){
		h(k)=h(lson)*basep[r-mid]+h(rson);
		return;
	}
	inline void build(reg int k,reg int l,reg int r,reg int a[]){
		if(l==r){
			h(k)=hash_t(a[l],a[l]);
			return;
		}
		build(lson,l,mid,a),build(rson,mid+1,r,a);
		pushup(k,l,r);
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,int val){
		if(l==r){
			h(k)=hash_t(val,val);
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val);
		else
			update(rson,mid+1,r,pos,val);
		pushup(k,l,r);
		return;
	}
	inline hash_t query(reg int k,reg int l,int r,reg int L,int R){
		if(L<=l&&r<=R)
			return h(k);
		if(R<=mid)
			return query(lson,l,mid,L,R);
		else if(L>mid)
			return query(rson,mid+1,r,L,R);
		else
			return query(lson,l,mid,L,R)*basep[min(R,r)-mid]+query(rson,mid+1,r,L,R);
	}
	inline int query(reg int k,int l,reg int r,int L,reg int R,const hash_t& H){
		if(l==r)
			return HashTable::query(H*p+h(k));
		if (R<=mid)
			return query(lson,l,mid,L,R,H);
		else if (L>mid)
			return query(rson,mid+1,r,L,R,H);
		else{
			int w;
			hash_t hh=H*basep[mid-max(L,l)+1]+(L<=l?h(lson):query(1,1,m,L,mid));
			if((w=HashTable::query(hh))!=-1){
				reg int tmp=query(rson,mid+1,r,L,R,hh);
				if(tmp==-1)
					return w;
				else
					return tmp;
			}
			else
				return query(lson,l,mid,L,R,H);
		}
	}
}

inline void dfs(reg int u){
	int cnt=0;
	for(reg int i=0,size=G[u].size();i<size;++i){
		reg int v=G[u][i];
		++cnt;
		h[v]=h[u]*p+hash_t(cnt,cnt);
		dfs(v);
	}
	return;
}

int main(void){
	using namespace SegmentTree;
	init();
	HashTable::init();
	n=read(),m=read(),q=read();
	reg int root=0;
	for(int i=1;i<=n;++i){
		static int f;
		f=read();
		if(!f)
			root=i;
		else
			G[f].push_back(i);
	}
	for(reg int i=1;i<=n;++i)
		sort(G[i].begin(),G[i].end());
	h[root]=hash_t(0,0);
	dfs(root);
	for(reg int i=1;i<=n;++i)
		HashTable::insert(h[i],i);
	for(reg int i=1;i<=m;++i)
		a[i]=read();
	build(1,1,m,a);
	while(q--){
		int opt=read();
		if(opt==1){
			int x,l,r,ans;
			x=read(),l=read(),r=read();
			ans=query(1,1,m,l,r,h[x]);
			printf("%d\n",ans==-1?x:ans);
		}
		else{
			int t,k;
			t=read(),k=read();
			update(1,1,m,t,k);
		}
	}
	return 0;
}