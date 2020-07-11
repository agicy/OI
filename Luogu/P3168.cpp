#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;
const int MAXM=100000+5;
const int MAXT=100000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

struct Event{
	int t,p,val;
	inline Event(reg int t=0,reg int p=0,reg int val=0):t(t),p(p),val(val){
		return;
	}
	inline bool operator<(const Event& a)const{
		return t<a.t;
	}
};

int m,n;
int cnt;
Event E[MAXM<<1];
vector<int> V;

inline void Read(void){
	m=read(),n=read();
	for(reg int i=1;i<=m;++i){
		static int s,e,p;
		s=read(),e=read(),p=read();
		E[++cnt]=Event(s,p,1);
		E[++cnt]=Event(e+1,p,-1);
		V.push_back(p);
	}
	return;
}

const int MAXSIZE=MAXN*40;

struct SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot;
	int root[MAXN<<1];
	int lson[MAXSIZE],rson[MAXSIZE];
	int cnt[MAXSIZE],sum[MAXSIZE];
	inline void pushup(reg int k){
		cnt[k]=cnt[lson[k]]+cnt[rson[k]];
		sum[k]=sum[lson[k]]+sum[rson[k]];
		return;
	}
	inline int Build(reg int l,reg int r){
		reg int dir=++tot;
		if(l==r)
			cnt[dir]=sum[dir]=0;
		else{
			lson[dir]=Build(l,mid);
			rson[dir]=Build(mid+1,r);
			pushup(dir);
		}
		return dir;
	}
	inline int Update(reg int pre,reg int l,reg int r,reg int pos,reg int val){
		reg int dir=++tot;
		lson[dir]=lson[pre];
		rson[dir]=rson[pre];
		cnt[dir]=cnt[pre];
		sum[dir]=sum[pre];
		if(l==r&&pos==l){
			cnt[dir]+=val;
			sum[dir]+=val*V[pos-1];
		}
		else{
			if(pos<=mid)
				lson[dir]=Update(lson[pre],l,mid,pos,val);
			if(pos>mid)
				rson[dir]=Update(rson[pre],mid+1,r,pos,val);
			pushup(dir);
		}
		return dir;
	}
	inline int Query(reg int now,reg int l,reg int r,int K){
		if(l==r)
			return min(K,cnt[now])*V[l-1];
		reg int res=0;
		if(cnt[lson[now]]>=K){
			res+=Query(lson[now],l,mid,K);
		}
		if(cnt[lson[now]]<K){
			res+=sum[lson[now]];
			res+=Query(rson[now],mid+1,r,K-cnt[lson[now]]);
		}
		return res;
	}
	#undef mid
};

SegmentTree T;

inline void Work(void){
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=cnt;++i)
		E[i].p=lower_bound(V.begin(),V.end(),E[i].p)-V.begin()+1;
	sort(E+1,E+cnt+1);
	T.root[0]=T.Build(1,V.size());
	reg int MaxT=E[cnt].t;
	for(reg int i=1,ptr=1;i<=MaxT&&ptr<=cnt;++i){
		T.root[i]=T.root[i-1];
		while(E[ptr].t==i){
			T.root[i]=T.Update(T.root[i],1,V.size(),E[ptr].p,E[ptr].val);
			++ptr;
		}
	}
	reg int pre=1;
	while(n--){
		static int x,a,b,c;
		x=read(),a=read(),b=read(),c=read();
		reg int k=1+((ll)a*pre%c+b)%c;
		reg int ans=T.Query(T.root[x],1,V.size(),k);
		printf("%d\n",ans);
		pre=ans;
	}
	return;
}
