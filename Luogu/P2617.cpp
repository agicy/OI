#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 2147483647
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
const int MAXSIZE=5*MAXM;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int a[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	return;
}

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXN];
	inline void Init(reg int size){
		n=size;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int ID,reg int val){
		for(reg int i=ID;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int Query(reg int ID){
		reg int res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
};

struct Opt{
	int type,i,j,k,id;
	inline Opt(reg int type=0,reg int i=0,reg int j=0,reg int k=0,reg int id=0):type(type),i(i),j(j),k(k),id(id){
		return;
	}
};

TreeArray T;
Opt O[MAXSIZE];
int ans[MAXM];

inline void Solve(reg int l,reg int r,reg int L,reg int R){
	if(L>R)
		return;
	if(r-l==1){
		for(reg int i=L;i<=R;++i)
			if(O[i].type==1)
				ans[O[i].id]=l;
		return;
	}
	reg int mid=(l+r)>>1;
	reg int cnt1=0,cnt2=0;
	static Opt O1[MAXSIZE],O2[MAXSIZE];
	static Opt temp;
	for(reg int i=L;i<=R;++i){
		temp=O[i];
		if(temp.type==0){
			if(temp.k<mid){
				T.Update(temp.i,temp.j);
				O1[++cnt1]=temp;
			}
			else
				O2[++cnt2]=temp;
		}
		else{
			int kth=T.Query(temp.j)-T.Query(temp.i-1);
			if(kth>=temp.k)
				O1[++cnt1]=temp;
			else{
				temp.k-=kth;
				O2[++cnt2]=temp;
			}
		}
	}
	for(reg int i=L,j=1;j<=cnt1;++i,++j)
		O[i]=O1[j];
	for(reg int i=L+cnt1,j=1;j<=cnt2;++i,++j)
		O[i]=O2[j];
	for(reg int j=1;j<=cnt1;++j)
		if(O1[j].type==0)
			T.Update(O1[j].i,-O1[j].j);
	Solve(l,mid,L,L+cnt1-1);
	Solve(mid,r,L+cnt1,R);
	return;
}

inline void Work(void){
	reg int tot=0;
	for(reg int i=1;i<=n;++i)
		O[++tot]=Opt(0,i,1,a[i],0);
	for(reg int i=0;i<m;++i){
		static char ch;
		do
			ch=getchar();
		while(ch!='C'&&ch!='Q');
		if(ch=='C'){
			static int x,y;
			x=read(),y=read();
			O[++tot]=Opt(0,x,-1,a[x],0);
			a[x]=y;
			O[++tot]=Opt(0,x,1,y,0);
		}
		else if(ch=='Q'){
			static int l,r,k;
			l=read(),r=read(),k=read();
			O[++tot]=Opt(1,l,r,k,i);
		}
	}
	for(reg int i=0;i<m;++i)
		ans[i]=-1;
	T.Init(n);
	Solve(0,1e9,1,tot);
	for(reg int i=0;i<m;++i)
		if(ans[i]!=-1)
			printf("%d\n",ans[i]);
	return;
}
