#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

struct options{
	int opt,lef,rig,col;
};

struct updates{
	int t,pos,pre,val;
	inline updates(reg int t=0,reg int pos=0,reg int pre=0,reg int val=0):t(t),pos(pos),pre(pre),val(val){
		return;
	}
	inline bool operator<(const updates& a)const{
		return pre<a.pre;
	}
};

struct querys{
	int t,l,r,ans;
	inline querys(reg int t=0,reg int l=0,reg int r=0,reg int ans=0):t(t),l(l),r(r),ans(ans){
		return;
	}
	inline bool operator<(const querys& a)const{
		return l<a.l;
	}
};

int n,m;
int a[MAXN],pre[MAXN],las[MAXN+MAXM];
int npre[MAXN];
options opt[MAXM];
int totU,totQ,tim;
updates U[3*(MAXN+MAXM)];
querys Q[MAXM];

struct Data{
	int l,r,x;
	inline Data(reg int l=0,reg int r=0,reg int x=0):l(l),r(r),x(x){
		return;
	}
	inline bool operator<(const Data& a)const{
		return r<a.r;
	}
};

struct Node{
	int l,r;
	inline Node(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
	inline bool operator<(const Node& a)const{
		return r<a.r;
	}
};

set<Data> S;
set<Node> c[MAXN+MAXM];
set<int> tmp;

inline void split(reg int mid){
	set<Data>::iterator it=S.lower_bound(Data(0,mid,0));
	reg int l=it->l,r=it->r,x=it->x;
	if(mid!=r){
		S.erase(it);
		S.insert(Data(l,mid,x)),S.insert(Data(mid+1,r,x));
		c[x].erase(Node(l,r));
		c[x].insert(Node(l,mid)),c[x].insert(Node(mid+1,r));
	}
	return;
}

inline void del(const set<Data>::iterator& it){
	tmp.insert(it->l);
	set<Node>::iterator it1,it2;
	it1=it2=c[it->x].find(Node(it->l,it->r));
	++it2;
	if(it2!=c[it->x].end())
		tmp.insert(it2->l);
	c[it->x].erase(it1);
	S.erase(it);
	return;
}

inline void insert(const Data& p){
	S.insert(p);
	set<Node>::iterator it=c[p.x].insert(Node(p.l,p.r)).first;
	++it;
	if(it!=c[p.x].end())
		tmp.insert(it->l);
	return;
}

inline void getUpdates(reg int pos,reg int col){
	if(npre[pos]!=col){
		U[++totU]=updates(++tim,pos,npre[pos],-1);
		npre[pos]=col;
		U[++totU]=updates(++tim,pos,npre[pos],1);
	}
	return;
}

inline void cover(reg int l,reg int r,reg int x){
	if(l!=1)
		split(l-1);
	split(r);
	set<Data>::iterator it;
	for(reg int p=l;p!=r+1;p=it->r+1,del(it))
		it=S.lower_bound(Data(0,p,0));
	insert(Data(l,r,x));
	for(auto it=tmp.begin();it!=tmp.end();++it){
		set<Data>::iterator it1=S.lower_bound(Data(0,*it,0));
		if(*it!=it1->l)
			getUpdates(*it,*it-1);
		else{
			set<Node>::iterator it2=c[it1->x].lower_bound(Node(0,*it));
			if(it2!=c[it1->x].begin())
				--it2,getUpdates(*it,it2->r);
			else
				getUpdates(*it,0);
		}
	}
	tmp.clear();
	return;
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,tim;
	int t[MAXN],unit[MAXN];
	inline void Init(reg int s){
		n=s,++tim;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			unit[i]+=val;
		}
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i)){
			if(t[i]!=tim)
				t[i]=tim,unit[i]=0;
			res+=unit[i];
		}
		return res;
	}
}

int pos[MAXN];

inline bool cmpt(const querys &a,const querys &b){
	return a.t<b.t;
}

inline bool cmpl(reg int a,reg int b){
	return pre[a]<pre[b];
}

inline void solve(reg int l1,reg int r1,reg int l2,reg int r2,reg int L,reg int R){
	if(l1==r1||l2==r2)
		return;
	reg int mid=(L+R)>>1;
	reg int mid1=l1;
	while(mid1<r1&&U[mid1+1].t<=mid)
		++mid1;
	reg int mid2=l2;
	while(mid2<r2&&Q[mid2+1].t<=mid)
		++mid2;
	solve(l1,mid1,l2,mid2,L,mid),solve(mid1,r1,mid2,r2,mid,R);
	if(l1!=mid1&&mid2!=r2){
		sort(U+l1+1,U+mid1+1),sort(Q+mid2+1,Q+r2+1);
		BIT::Init(n);
		for(reg int i=mid2+1,ptr=l1+1;i<=r2;++i){
			while(ptr<=mid1&&U[ptr].pre<Q[i].l){
				BIT::update(U[ptr].pos,U[ptr].val);
				++ptr;
			}
			Q[i].ans+=BIT::query(Q[i].r)-BIT::query(Q[i].l-1);
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	vector<int> V;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	for(reg int i=1;i<=m;++i){
		opt[i].opt=read(),opt[i].lef=read(),opt[i].rig=read();
		if(opt[i].opt==1){
			opt[i].col=read();
			V.push_back(opt[i].col);
		}
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	for(reg int i=1;i<=m;++i)
		if(opt[i].opt==1)
			opt[i].col=lower_bound(V.begin(),V.end(),opt[i].col)-V.begin()+1;
	for(reg int i=1;i<=n;++i)
		pre[i]=las[a[i]],las[a[i]]=i;
	for(reg int i=1;i<=n;++i)
		npre[i]=pre[i];
	reg int col=a[1],cnt=1;
	for(reg int i=2;i<=n;++i)
		if(col!=a[i]){
			S.insert(Data(i-cnt,i-1,col)),c[col].insert(Node(i-cnt,i-1));
			col=a[i],cnt=1;
		}
		else
			++cnt;
	S.insert(Data(n-cnt+1,n,a[n])),c[a[n]].insert(Node(n-cnt+1,n));
	for(reg int i=1;i<=m;++i)
		if(opt[i].opt==1)
			cover(opt[i].lef,opt[i].rig,opt[i].col);
		else
			Q[++totQ]=querys(++tim,opt[i].lef,opt[i].rig,0);
	sort(Q+1,Q+totQ+1);
	for(reg int i=1;i<=n;++i)
		pos[i]=i;
	sort(pos+1,pos+n+1,cmpl);
	BIT::Init(n);
	for(reg int i=1,ptr=1;i<=totQ;++i){
		while(ptr<=n&&pre[pos[ptr]]<Q[i].l)
			BIT::update(pos[ptr++],1);
		Q[i].ans+=BIT::query(Q[i].r)-BIT::query(Q[i].l-1);
	}
	sort(Q+1,Q+totQ+1,cmpt);
	solve(0,totU,0,totQ,0,tim);
	sort(Q+1,Q+totQ+1,cmpt);
	for(reg int i=1;i<=totQ;++i)
		writeln(Q[i].ans);
	flush();
	return 0;
}