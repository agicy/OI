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

const int t=461*773*2803;

const int MAXN=1e5+5;
const int MAXM=1e4+5;
const int MAXSIZE=3e3+5;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=t?sum-t:sum;
}

int n,m;
int a[MAXN];
int fac[MAXN];

inline void Init(reg int n){
	fac[0]=1;
	for(reg int i=1;i<=n;++i)
		fac[i]=1ll*fac[i-1]*i%t;
	return;
}

int f[MAXN];
int sum[MAXN];

struct querys{
	int k,id;
	inline querys(reg int k=0,reg int id=0):k(k),id(id){
		return;
	}
	inline bool operator<(const querys& a)const{
		return k<a.k;
	}
};

vector<int> V;
querys q[MAXM];
int ans[MAXM];

int main(void){
	Init(3e3);
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(int i=1;i<=n;++i){
		a[i]=fac[a[i]];
		f[1]=max(f[1],a[i]);
		sum[i]=add(sum[i-1],a[i]);
		if(a[i])
			V.push_back(i);
	}
	for(reg int i=0,size=V.size();i<size;++i)
		for(reg int j=i+1;j<size;++j)
			f[V[j]-V[i]+1]=max(f[V[j]-V[i]+1],add(sum[V[j]],t-sum[V[i]-1]));
	for(reg int i=1;i<=m;++i){
		static int k;
		k=read();
		q[i]=querys(k,i);
	}
	sort(q+1,q+m+1);
	reg int j=1;
	for(reg int i=1;i<=n;++i)
		while(j<=m&&q[j].k<=f[i]){
			ans[q[j].id]=i;
			++j;
		}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]?ans[i]:-1);
	return 0;
}