//excellent time limit
//compile time limit exceeded
//ST+nT^2logn+qT+nT^3
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
#include<bitset>
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

template<const int N,const int M> struct Matrix{
	int unit[N][M];
	inline Matrix<N,M>(void){
		return;
	}
	inline Matrix<N,M>(reg int x){
		for(reg int i=0;i<N;++i)
			for(reg int j=0;j<M;++j)
				unit[i][j]=(i==j)?x:0;
		return;
	}
};

template<const int N,const int M> inline Matrix<N,M> operator+(const Matrix<N,M> & a,const Matrix<N,M>& b){
	Matrix<N,M> res;
	for(reg int i=0;i<N;++i)
		for(reg int j=0;j<M;++j)
			res.unit[i][j]=add(a.unit[i][j],b.unit[i][j]);
	return res;
}

template<const int N,const int M,const int K> inline Matrix<N,K> operator*(const Matrix<N,M> & a,const Matrix<M,K>& b){
	static uint64_t tmp[N][K];
	for(reg int i=0;i<N;++i)
		for(reg int j=0;j<K;++j)
			tmp[i][j]=0;
	for(reg int i=0;i<N;++i)
		for(reg int k=0;k<M;++k)
			for(reg int j=0;j<K;++j)
				tmp[i][j]+=1ull*a.unit[i][k]*b.unit[k][j];
	Matrix<N,K> res;
	for(reg int i=0;i<N;++i)
		for(reg int j=0;j<K;++j)
			res.unit[i][j]=tmp[i][j]%mod;
	return res;
}

namespace SAM{
	struct Node{
		int fa,len;
		int ch[SIGMA];
		int f[SIGMA+1];
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
	namespace Graph{
		int cnt,head[MAXS<<1],to[MAXS<<1],nxt[MAXS<<1];
		inline void init(reg int tot){
			cnt=0,memset(head+1,0,sizeof(int)*tot);
			return;
		}
		inline void Add_Edge(reg int u,reg int v){
			nxt[++cnt]=head[u];
			to[cnt]=v;
			head[u]=cnt;
			return;
		}
	}
	int inDeg[MAXS<<1];
	inline Matrix<SIGMA+1,SIGMA+1> build(reg char s[],reg int len){
		init();
		for(reg int i=0;i<len;++i)
			insert(s[i]-'a');
		Graph::init(tot);
		for(reg int i=1;i<=tot;++i)
			for(reg int j=0;j<SIGMA;++j)
				if(ch(i)[j])
					++inDeg[i],Graph::Add_Edge(ch(i)[j],i);
		reg int _head=0,_tail=0;
		static int Q[MAXS<<1];
		for(reg int i=1;i<=tot;++i)
			if(!inDeg[i])
				Q[_tail++]=i;
		while(_head<_tail){
			reg int p=Q[_head++];
			for(reg int c=0;c<SIGMA;++c)
				if(!ch(p)[c])
					f(p)[c]=add(f(p)[c],1);
			f(p)[SIGMA]=add(f(p)[SIGMA],1);
			for(reg int i=Graph::head[p];i;i=Graph::nxt[i]){
				reg int v=Graph::to[i];
				--inDeg[v];
				if(!inDeg[v])
					Q[_tail++]=v;
				for(reg int c=0;c<SIGMA+1;++c)
					f(v)[c]=add(f(v)[c],f(p)[c]);
			}
		}
		Matrix<SIGMA+1,SIGMA+1> g(0);
		for(reg int i=0;i<SIGMA;++i)
			for(reg int c=0;c<SIGMA+1;++c)
				g.unit[i][c]=f(ch(1)[i])[c];
		for(reg int i=0;i<SIGMA;++i)
			if(!ch(1)[i])
				g.unit[i][i]=1;
		g.unit[SIGMA][SIGMA]=1;
		return g;
	}
	#undef fa
	#undef len
	#undef ch
}

int n,q;
char s[MAXS];
uint64_t k1,k2;
Matrix<SIGMA+1,SIGMA+1> M[MAXN];

struct querys{
	int l,r;
};

int ans;
Matrix<1,1> lsum[MAXN],rsum[MAXN];
Matrix<1,SIGMA+1> suf[MAXN];
Matrix<SIGMA+1,1> pre[MAXN];
querys qu[MAXQ];
Matrix<1,SIGMA+1> B;
Matrix<SIGMA+1,1> D;
int id[MAXQ];

struct Node{
	Matrix<SIGMA+1,SIGMA+1> pod;
	Matrix<SIGMA+1,1> Sl;
	Matrix<1,SIGMA+1> Sr;
	inline Node(const Matrix<SIGMA+1,SIGMA+1>& pod,const Matrix<SIGMA+1,1>& Sl,const Matrix<1,SIGMA+1>& Sr):pod(pod),Sl(Sl),Sr(Sr){
		return;
	}
};

inline Node solve(reg int l,reg int r,reg int L,reg int R){
	if(l==r){
		if((R-L+1)&1)
			ans^=(B*M[l]*D).unit[0][0];
		lsum[l]=rsum[l]=B*M[l]*D;
		pre[l]=M[l]*D,suf[l]=B*M[l];
		return Node(M[l],M[l]*D,B*M[l]);
	}
	reg int mid=(l+r)>>1;
	reg int tot=0,cntl=0,cntr=0;
	static int V[MAXQ],lef[MAXQ],rig[MAXQ];
	for(reg int i=L;i<=R;++i)
		if(qu[id[i]].l<=mid&&mid<qu[id[i]].r)
			V[++tot]=id[i];
		else if(qu[id[i]].l<=mid)
			lef[++cntl]=id[i];
		else
			rig[++cntr]=id[i];
	for(reg int i=1;i<=cntl;++i)
		id[L+i-1]=lef[i];
	for(reg int i=1;i<=cntr;++i)
		id[R-i+1]=rig[i];
	reg int beg=L+cntl,end=R-cntr;
	for(reg int i=1;i<=tot;++i)
		id[L+cntl+i-1]=V[i];
	Node __l=solve(l,mid,L,L+cntl-1),__r=solve(mid+1,r,R-cntr+1,R);
	for(reg int i=beg;i<=end;++i)
		ans^=(rsum[qu[id[i]].l]+lsum[qu[id[i]].r]+suf[qu[id[i]].l]*pre[qu[id[i]].r]).unit[0][0];
	for(reg int i=l;i<=mid;++i){
		rsum[i]=suf[i]*__r.Sl+rsum[i]+rsum[mid+1];
		suf[i]=suf[i]*__r.pod+suf[mid+1];
	}
	for(reg int i=mid+1;i<=r;++i){
		lsum[i]=__l.Sr*pre[i]+lsum[i]+lsum[mid];
		pre[i]=pre[mid]+__l.pod*pre[i];
	}
	return Node(__l.pod*__r.pod,__l.Sl+__l.pod*__r.Sl,__l.Sr*__r.pod+__r.Sr);
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
		qu[i].l=l,qu[i].r=r;
	}
	for(reg int i=0;i<=SIGMA;++i)
		B.unit[0][i]=1;
	D.unit[SIGMA][0]=1;
	for(reg int i=1;i<=q;++i)
		id[i]=i;
	solve(1,n,1,q);
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}