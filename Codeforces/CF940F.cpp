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

const int MAXN=2e5+5;
const int MAXQ=1e5+5;

int n,q;
int a[MAXN];
int pos[MAXN];
int ans[MAXQ];
int cnt[MAXN],T[MAXN];

struct querys{
	int l,r,tim,id;
	inline querys(reg int l=0,reg int r=0,reg int tim=0,reg int id=0):l(l),r(r),tim(tim),id(id){
		return;
	}
	inline bool operator<(const querys& a)const{
		if(pos[l]!=pos[a.l])
			return l<a.l;
		if(pos[r]!=pos[a.r])
			return r<a.r;
		return tim<a.tim;
	}
};

struct updates{
	int pos,val;
	inline updates(reg int pos=0,reg int val=0):pos(pos),val(val){
		return;
	}
};

updates U[MAXN];
querys Q[MAXQ];

inline void change(reg int x,reg int y){
	if(Q[y].l<=U[x].pos&&U[x].pos<=Q[y].r){
		--T[cnt[U[x].val]];
		++T[++cnt[U[x].val]];
		--T[cnt[a[U[x].pos]]];
		++T[--cnt[a[U[x].pos]]];
	}
	swap(a[U[x].pos],U[x].val);
	return;
}

inline void add(reg int x){
	--T[cnt[a[x]]];
	++T[++cnt[a[x]]];
	return;
}

inline void sub(reg int x){
	--T[cnt[a[x]]];
	++T[--cnt[a[x]]];
	return;
}

int op[MAXQ],x[MAXQ],y[MAXQ];
vector<int> V;

int main(void){
	n=read(),q=read();
	reg int B=pow(n,0.66666667);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
		pos[i]=i/B;
	}
	for(reg int i=1;i<=q;++i){
		op[i]=read(),x[i]=read(),y[i]=read();
		if(op[i]==2)
			V.push_back(y[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	reg int cntQ=0,cntU=0;
	for(reg int i=1;i<=q;++i)
		switch(op[i]){
			case 1:{
				++cntQ;
				Q[cntQ]=querys(x[i],y[i],cntU,cntQ);
				break;
			}
			case 2:{
				y[i]=lower_bound(V.begin(),V.end(),y[i])-V.begin()+1;
				U[++cntU]=updates(x[i],y[i]);
				break;
			}
		}
	sort(Q+1,Q+cntQ+1);
	reg int l=1,r=0,tim=0;
	for(reg int i=1;i<=cntQ;++i){
		while(l>Q[i].l)
			add(--l);
		while(r<Q[i].r)
			add(++r);
		while(l<Q[i].l)
			sub(l++);
		while(r>Q[i].r)
			sub(r--);
		while(Q[i].tim>tim)
			change(++tim,i);
		while(Q[i].tim<tim)
			change(tim--,i);
		ans[Q[i].id]=1;
		while(T[ans[Q[i].id]])
			++ans[Q[i].id];
	}
	for(reg int i=1;i<=cntQ;++i)
		printf("%d\n",ans[i]);
	return 0;
}