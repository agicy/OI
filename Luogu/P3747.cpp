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

const int MAXN=50000+5;
const int MAXM=50000+5;
const int MAXP=100000000+5;
const int MAXLOGP=50+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,p,c;
int a[MAXN];

inline void Read(void){
	n=read(),m=read(),p=read(),c=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline int Calcphi(reg int x){
	reg int res=x;
	for(reg int i=2;i*i<=x;++i)
		if(x%i==0){
			res=res/i*(i-1);
			while(x%i==0)
				x/=i;
		}
	if(x!=1)
		res=res/x*(x-1);
	return res;
}

int cnt,phi[MAXLOGP];

const int MAXBASE=10000;

ll pow1[MAXBASE+1][MAXLOGP],pow2[MAXBASE+1][MAXLOGP];
bool b1[MAXBASE+1][MAXLOGP],b2[MAXBASE+1][MAXLOGP];

bool flag;

inline int Calc(reg int v,reg int id){
	flag=false;
	reg int v1=v%MAXBASE,v2=v/MAXBASE;
	reg ll res=pow1[v1][id]*pow2[v2][id];
	if(res>=phi[id]){
		res%=phi[id];
		flag=true;
	}
	flag|=(b1[v1][id]||b2[v2][id]);
	return res;
}

inline int DFS(reg int v,reg int dep,reg int lim){
	flag=false;
	if(dep==lim){
		if(v>=phi[dep]){
			flag=true;
			v%=phi[dep];
		}
		return v;
	}
	reg int c=DFS(v,dep+1,lim);
	return Calc(c+(flag?phi[dep+1]:0),dep);
}

inline void Init(void){
	for(reg int i=p;i!=1;i=Calcphi(i))
		phi[cnt++]=i;
	phi[cnt]=1;
	phi[++cnt]=1;
	for(reg int i=0;i<=cnt;++i){
		pow1[0][i]=1;
		for(reg int j=1;j<=MAXBASE;++j){
			pow1[j][i]=pow1[j-1][i]*c;
			if(pow1[j][i]>=phi[i]){
				pow1[j][i]%=phi[i];
				b1[j][i]=true;
			}
			b1[j][i]|=b1[j-1][i];
		}
	}
	for(reg int i=0;i<=cnt;++i){
		pow2[0][i]=1;
		b2[1][i]=b1[MAXBASE][i];
		for(reg int j=1;j<=MAXBASE;++j){
			pow2[j][i]=pow2[j-1][i]*pow1[MAXBASE][i];
			if(pow2[j][i]>=phi[i]){
				pow2[j][i]%=phi[i];
				b2[j][i]=true;
			}
			b2[j][i]|=b2[j-1][i];
		}
	}
	return;
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	int val[MAXN<<2];
	int tim[MAXN<<2];
	inline void pushup(reg int k){
		val[k]=val[lson]+val[rson];
		if(val[k]>=p)
			val[k]-=p;
		tim[k]=min(tim[lson],tim[rson]);
		return;
	}
	inline void Build(reg int k,reg int l,reg int r){
		if(l==r){
			val[k]=a[l];
			return;
		}
		Build(lson,l,mid);
		Build(rson,mid+1,r);
		pushup(k);
		return;
	}
	inline void Update(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(tim[k]>=cnt)
			return;
		if(l==r){
			++tim[k];
			val[k]=DFS(a[l],0,tim[k]);
			return;
		}
		if(L<=mid)
			Update(lson,l,mid,L,R);
		if(R>mid)
			Update(rson,mid+1,r,L,R);
		pushup(k);
		return;
	}
	inline int Query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return val[k];
		reg int res=0;
		if(L<=mid)
			res+=Query(lson,l,mid,L,R);
		if(R>mid)
			res+=Query(rson,mid+1,r,L,R);
		return res>=p?res-p:res;
	}
	#undef lson
	#undef rson
	#undef mid
}

inline void Work(void){
	Init();
	SegmentTree::Build(1,1,n);
	while(m--){
		static int opt,l,r;
		opt=read(),l=read(),r=read();
		switch(opt){
			case 0:{
				SegmentTree::Update(1,1,n,l,r);
				break;
			}
			case 1:{
				reg int ans=SegmentTree::Query(1,1,n,l,r);
				printf("%d\n",ans);
				break;
			}
			default:break;
		}
	}
	return;
}