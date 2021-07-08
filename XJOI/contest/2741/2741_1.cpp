//stupid time limit
//ST^2+nT^3logn+qT^2
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,sse2,sse3,sse4,mmx")
#pragma GCC optimize("-fno-stack-protecter")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline uint64_t read_uint64(void){
	reg char ch=getchar();
	reg uint64_t res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline char* read(reg char* s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return s;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline void swap(reg int& a,reg int& b){
	a^=b,b=a^b,a^=b;
	return;
}

const int MAXN=6.5e4+5;
const int MAXS=2e6+5;
const int MAXQ=3e6+5;
const int mod=998244353;
const int SIGMA=7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

uint64_t tmp[SIGMA+1][SIGMA+1];

struct Matrix{
	int n,m,unit[SIGMA+1][SIGMA+1];
	inline Matrix(void){
		return;
	}
	inline Matrix(reg int n,reg int m):n(n),m(m){
		return;
	}
	inline Matrix(reg int n,reg int m,reg int x):n(n),m(m){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
	inline Matrix operator+(const Matrix& a)const{
		//assert(n==a.n),assert(m==a.m);
		Matrix res(n,m);
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<m;++j)
				res.unit[i][j]=add(unit[i][j],a.unit[i][j]);
		return res;
	}
	inline Matrix operator*(const Matrix& a)const{
		//assert(m==a.n);
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<a.m;++j)
				tmp[i][j]=0;
		for(reg int i=0;i<n;++i)
			for(reg int k=0;k<m;++k)
				for(reg int j=0;j<a.m;++j)
					tmp[i][j]+=1ull*unit[i][k]*a.unit[k][j];
		Matrix res(n,a.m);
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<a.m;++j)
				res.unit[i][j]=tmp[i][j]%mod;
		return res;
	}
};

namespace SAM{
	struct Node{
		int fa,len;
		int ch[SIGMA];
		int f[SIGMA];
		#define fa(x) unit[(x)].fa
		#define len(x) unit[(x)].len
		#define ch(x) unit[(x)].ch
		#define f(x) unit[(x)].f
	};
	int tot,las;
	Node unit[MAXS<<1];
	inline void init(void){
		memset(unit+1,0,sizeof(Node)*tot);
		tot=las=1;
		return;
	}
	inline void insert(reg int c){
		reg int np=++tot,p=las;
		len(np)=len(p)+1;
		while(p&&!ch(p)[c])
			ch(p)[c]=np,p=fa(p);
		if(!p)
			fa(np)=1;
		else{
			reg int q=ch(p)[c];
			if(len(q)==len(p)+1)
				fa(np)=q;
			else{
				reg int nq=++tot;
				unit[nq]=unit[q];
				len(nq)=len(p)+1;
				fa(np)=fa(q)=nq;
				while(p&&ch(p)[c]==q)
					ch(p)[c]=nq,p=fa(p);
			}
		}
		las=np;
		return;
	}
	int cnt[MAXS];
	int rnk[MAXS<<1];
	inline Matrix build(reg char s[],reg int len){
		init();
		for(reg int i=0;i<len;++i)
			insert(s[i]-'a');
		memset(cnt,0,sizeof(int)*(len+1));
		for(reg int i=1;i<=tot;++i) ++cnt[len(i)];
		for(reg int i=1;i<=len;++i) cnt[i]+=cnt[i-1];
		for(reg int i=1;i<=tot;++i) rnk[cnt[len(i)]--]=i;
		Matrix g(SIGMA+1,SIGMA+1,0);
		for(reg int c=0;c<SIGMA;++c)
			if(ch(1)[c])
				f(ch(1)[c])[c]=1;
			else
				g.unit[c][c]=1;
		g.unit[SIGMA][SIGMA]=1;
		for(reg int i=2;i<=tot;++i){
			reg int p=rnk[i];
			for(reg int v=0;v<SIGMA;++v)
				if(f(p)[v]){
					for(reg int c=0;c<SIGMA;++c)
						if(ch(p)[c])
							f(ch(p)[c])[v]=add(f(ch(p)[c])[v],f(p)[v]);
						else
							g.unit[v][c]=add(g.unit[v][c],f(p)[v]);
					g.unit[v][SIGMA]=add(g.unit[v][SIGMA],f(p)[v]);
				}
		}
		return g;
	}
	#undef fa
	#undef len
	#undef ch
}

int n,q;
char s[MAXS];
uint64_t k1,k2;
Matrix M[MAXN];

inline int getSum(const Matrix& M){
	reg uint64_t res=0;
	for(reg int i=0;i<=SIGMA;++i)
		res+=M.unit[i][SIGMA];
	return res%mod;
}

struct querys{
	int l,r;
};

int ans;
Matrix lsum[MAXN],lpre[MAXN],lsuf[MAXN],lpod[MAXN];
Matrix rsum[MAXN],rpre[MAXN],rsuf[MAXN],rpod[MAXN];
querys qu[MAXQ];
int id[MAXQ];
Matrix Vec;

inline void solve(reg int l,reg int r,reg int L,reg int R){
	if(l>r||L>R)
		return;
	if(l==r){
		if((R-L+1)&1)
			ans^=(Vec*M[l]).unit[0][SIGMA];
		return;
	}
	reg int mid=(l+r)>>1;
	reg int __l=mid+1,__r=mid;
	reg int tot=0,cntl=0,cntr=0;
	static int V[MAXQ],lef[MAXQ],rig[MAXQ];
	for(reg int i=L;i<=R;++i)
		if(qu[id[i]].l<=mid&&mid<qu[id[i]].r){
			__l=min(__l,qu[id[i]].l),__r=max(__r,qu[id[i]].r);
			V[++tot]=id[i];
		}
		else if(qu[id[i]].l<=mid)
			lef[++cntl]=id[i];
		else
			rig[++cntr]=id[i];
	if(__l<__r){
		lsum[mid]=lpre[mid]=lsuf[mid]=lpod[mid]=M[mid];
		for(reg int i=mid-1;i>=__l;--i){
			lsum[i]=M[i]+lsum[i+1]+M[i]*lsuf[i+1];
			lpre[i]=M[i]*lpod[i+1]+lpre[i+1];
			lsuf[i]=M[i]+M[i]*lsuf[i+1];
			lpod[i]=M[i]*lpod[i+1];
		}
		rsum[mid+1]=rpre[mid+1]=rsuf[mid+1]=rpod[mid+1]=M[mid+1];
		for(reg int i=mid+2;i<=__r;++i){
			rsum[i]=rsum[i-1]+M[i]+rpre[i-1]*M[i];
			rpre[i]=rpre[i-1]*M[i]+M[i];
			rsuf[i]=rsuf[i-1]+rpod[i-1]*M[i];
			rpod[i]=rpod[i-1]*M[i];
		}
		for(reg int i=1;i<=tot;++i)
			ans^=(Vec*(lsum[qu[V[i]].l]+rsum[qu[V[i]].r])+(Vec*lpre[qu[V[i]].l])*rsuf[qu[V[i]].r]).unit[0][SIGMA];
	}
	for(reg int i=1;i<=cntl;++i)
		id[L+i-1]=lef[i];
	for(reg int i=1;i<=cntr;++i)
		id[R-i+1]=rig[i];
	solve(l,mid,L,L+cntl-1),solve(mid+1,r,R-cntr+1,R);
	return;
}

inline uint64_t Rand(void){
	reg uint64_t k3=k1,k4=k2;
	k1=k4,k3^=k3<<23,k2=k3^k4^(k3>>17)^(k4>>26);
	return k2+k4;
}

bool ed;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		M[i]=SAM::build(s,read(s)-s);
	q=read(),k1=read_uint64(),k2=read_uint64();
	for(reg int i=1;i<=q;++i){
		static int l,r;
		l=Rand()%n+1,r=Rand()%n+1;
		if(l>r) swap(l,r);
		id[i]=i,qu[i].l=l,qu[i].r=r;
	}
	Vec.n=1,Vec.m=SIGMA+1;
	for(reg int i=0;i<=SIGMA;++i)
		Vec.unit[0][i]=1;
	solve(1,n,1,q);
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}