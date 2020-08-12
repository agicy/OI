#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXSQRTN=317+5;
const int MAXQ=1e5+5;

int n,q;
int a[MAXN];
int pos[MAXN];
int L[MAXSQRTN],R[MAXSQRTN];

struct querys{
	int l,r,id;
	inline querys(reg int l=0,reg int r=0,reg int id=0):l(l),r(r),id(id){
		return;
	}
	inline bool operator<(const querys& a)const{
		if(pos[l]!=pos[a.l])
			return l<a.l;
		return r<a.r;
	}
};

querys Q[MAXQ];

inline void build(void){
	reg int size=sqrt(n);
	reg int tot=n/size;
	for(reg int i=1;i<=tot;++i){
		L[i]=(i-1)*size+1;
		R[i]=i*size;
	}
	if(R[tot]<n){
		++tot;
		R[tot]=n;
		L[tot]=R[tot-1]+1;
	}
	for(reg int i=1;i<=tot;++i)
		for(reg int j=L[i];j<=R[i];++j)
			pos[j]=i;
	return;
}

vector<int> V;
int __cnt[MAXN];
int T[MAXN];
ll ans[MAXQ];

inline void add(reg int x,reg ll &ans){
	++T[x];
	ans=max(ans,1ll*V[x-1]*T[x]);
	return;
}

inline void del(reg int x){
	--T[x];
	return;
}

int main(void){
	n=read(),q=read();
	build();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	for(reg int i=1;i<=q;++i){
		static int l,r;
		l=read(),r=read();
		Q[i]=querys(l,r,i);
	}
	sort(Q+1,Q+q+1);
	reg int l=1,r=0;
	ll Ans=0,tmp;
	int LastB=0;
	for(reg int i=1;i<=q;++i){
		if(pos[Q[i].l]==pos[Q[i].r]){
			ll Ans=0;
			for(reg int j=Q[i].l;j<=Q[i].r;++j){
				++__cnt[a[j]];
				Ans=max(Ans,1ll*V[a[j]-1]*__cnt[a[j]]);
			}
			for(reg int j=Q[i].l;j<=Q[i].r;++j)
				--__cnt[a[j]];
			ans[Q[i].id]=Ans;
			continue;
		}
		if(pos[Q[i].l]!=LastB){
			while(r>R[pos[Q[i].l]])
				del(a[r--]);
			while(l<R[pos[Q[i].l]]+1)
				del(a[l++]);
			Ans=0;
			LastB=pos[Q[i].l];
		}
		while(r<Q[i].r)
			add(a[++r],Ans);
		reg int __l=l;
		tmp=Ans;
		while(__l>Q[i].l)
			add(a[--__l],tmp);
		ans[Q[i].id]=tmp;
		while(__l<l)
			del(a[__l++]);
	}
	for(reg int i=1;i<=q;++i)
		printf("%lld\n",ans[i]);
	return 0;
}