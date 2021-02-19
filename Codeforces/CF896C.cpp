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

const int MAXN=1e5+7;

inline int add(reg int a,reg int b,reg int mod){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int fpow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

namespace ChthollyTree{
	struct Node{
		int l,r;
		mutable ll v;
		inline Node(reg int l=0,reg int r=-1,reg ll v=0):l(l),r(r),v(v){
			return;
		}
		inline bool operator<(const Node& a)const{
			return l<a.l;
		}
	};
	set<Node> s;
	inline set<Node>::iterator split(reg int pos){
		set<Node>::iterator it=s.lower_bound(Node(pos));
		if(it!=s.end()&&it->l==pos)
			return it;
		else{
			--it;
			reg int l=it->l,r=it->r;
			reg ll v=it->v;
			s.erase(it);
			s.insert(Node(l,pos-1,v));
			return s.insert(Node(pos,r,v)).first;
		}
	}
	inline void add(reg int l,reg int r,reg ll val){
		set<Node>::iterator itl=split(l),itr=split(r+1);
		while(itl!=itr)
			(itl++)->v+=val;
		return;
	}
	inline void assign(reg int l,reg int r,reg ll val){
		set<Node>::iterator itl=split(l),itr=split(r+1);
		s.erase(itl,itr);
		s.insert(Node(l,r,val));
		return;
	}
	vector<pair<ll,int>/**/> V;
	inline ll rnk(reg int l,reg int r,reg int k){
		set<Node>::iterator itl=split(l),itr=split(r+1);
		V.clear();
		while(itl!=itr){
			V.push_back(make_pair(itl->v,itl->r-itl->l+1));
			++itl;
		}
		sort(V.begin(),V.end());
		for(vector<pair<ll,int>/**/>::iterator it=V.begin();it!=V.end();++it){
			k-=it->second;
			if(k<=0)
				return it->first;
		}
		return -1;
	}
	inline int sum(reg int l,reg int r,reg int exp,reg int mod){
		set<Node>::iterator itl=split(l),itr=split(r+1);
		reg int res=0;
		while(itl!=itr){
			res=::add(res,1ll*(itl->r-itl->l+1)*fpow(itl->v%mod,exp,mod)%mod,mod);
			++itl;
		}
		return res;
	}
	inline void insert(reg int i,reg ll val){
		s.insert(Node(i,i,val));
		return;
	}
}

int n,m;
ll seed,vmax;

inline int rnd(void){
	reg int res=seed;
	seed=(7ll*seed+13)%(1000000007);
	return res;
}

ll a[MAXN];

int main(void){
	scanf("%d%d%lld%lld",&n,&m,&seed,&vmax);
	for(reg int i=1;i<=n;++i){
		a[i]=(rnd()%vmax)+1;
		ChthollyTree::insert(i,a[i]);
	}
	ChthollyTree::insert(n+1,0);
	for(reg int i=1;i<=m;++i){
		static int op,l,r,x,y;
		op=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1;
		if(l>r) swap(l,r);
		switch(op){
			case 1:{
				x=rnd()%vmax+1;
				ChthollyTree::add(l,r,x);
				break;
			}
			case 2:{
				x=rnd()%vmax+1;
				ChthollyTree::assign(l,r,x);
				break;
			}
			case 3:{
				x=rnd()%(r-l+1)+1;
				printf("%lld\n",ChthollyTree::rnk(l,r,x));
				break;
			}
			case 4:{
				x=rnd()%vmax+1,y=rnd()%vmax+1;
				printf("%d\n",ChthollyTree::sum(l,r,x,y));
				break;
			}
		}
	}
	return 0;
}