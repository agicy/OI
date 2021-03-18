#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
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

struct updates{
	int type,pos,color;
};

int n,m;
updates q[MAXM];
/*
namespace Subtask1{
	const int MAXN=1e3+5;
	int cnt[4];
	char M[MAXN][MAXN];
	inline void Solve(void){
		for(reg int i=1;i<=m;++i){
			switch(q[i].type){
				case 1:{
					for(reg int j=1;j<=n;++j)
						M[q[i].pos][j]|=1<<q[i].color;
					break;
				}
				case 2:{
					for(reg int j=1;j<=n;++j)
						M[j][q[i].pos]|=1<<q[i].color;
					break;
				}
				case 3:{
					for(reg int j=1;q[i].pos-j>=1&&j<=n;++j)
						if(q[i].pos-j<=n)
							M[j][q[i].pos-j]|=1<<q[i].color;
					break;
				}
			}
		}
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				++cnt[M[i][j]];
		printf("%d %d %d %d\n",cnt[0],cnt[1],cnt[2],cnt[3]);
		return;
	}
}

namespace Subtask2{
	char col[MAXN];
	int cnt[4];
	inline void Solve(void){
		for(reg int i=1;i<=m;++i)
			col[q[i].pos]|=1<<q[i].color;
		for(reg int i=1;i<=n;++i)
			++cnt[col[i]];
		printf("%lld %lld %lld %lld\n",1ll*n*cnt[0],1ll*n*cnt[1],1ll*n*cnt[2],1ll*n*cnt[3]);
		return;
	}
}

namespace Subtask3{
	char col[2][MAXN];
	int cnt[2][4];
	ll ans[4];
	inline void Solve(void){
		for(reg int i=1;i<=m;++i)
			col[q[i].type-1][q[i].pos]|=1<<q[i].color;
		for(reg int i=1;i<=n;++i)
			++cnt[0][col[0][i]],++cnt[1][col[1][i]];
		for(reg int i=0;i<4;++i)
			for(reg int j=0;j<4;++j)
				ans[i|j]+=1ll*cnt[0][i]*cnt[0][j];
		printf("%lld %lld %lld %lld\n",ans[0],ans[1],ans[2],ans[3]);
		return;
	}
}*/

namespace Poly{
	const int p=998244353;
	const int g=3;
	const int invg=332748118;
	inline int add(reg int a,reg int b){
		a+=b;
		return a>=p?a-p:a;
	}
	inline int sub(reg int a,reg int b){
		a-=b;
		return a<0?a+p:a;
	}
	inline int fpow(reg int x,reg int exp){
		reg int res=1;
		while(exp){
			if(exp&1)
				res=1ll*res*x%p;
			x=1ll*x*x%p;
			exp>>=1;
		}
		return res;
	}
	vector<int> rev;
	inline int getRev(reg int n){
		reg int limit=1,l=0;
		while(limit<n)
			limit<<=1,++l;
		rev.resize(limit);
		for(reg int i=0;i<limit;++i)
			rev[i]=(rev[i>>1]>>1)|((i&1)<<(l-1));
		return limit;
	}
	typedef vector<int> poly;
	inline void NTT(reg poly& a,reg int limit,reg int flag){
		for(reg int i=0;i<limit;++i)
			if(i<rev[i])
				swap(a[i],a[rev[i]]);
		for(reg int i=1;i<limit;i<<=1){
			reg int w=fpow(flag==1?g:invg,(p-1)/(i<<1));
			for(reg int j=0;j<limit;j+=(i<<1)){
				reg int e=1;
				for(reg int k=0;k<i;++k,e=1ll*e*w%p){
					reg int x=a[j+k],y=1ll*e*a[i+j+k]%p;
					a[j+k]=add(x,y),a[i+j+k]=sub(x,y);
				}
			}
		}
		if(flag==-1){
			reg int inv=fpow(limit,p-2);
			for(reg int i=0;i<limit;++i)
				a[i]=1ll*a[i]*inv%p;
		}
		return;
	}
	inline void print(const poly& a){
		for(reg int i=0,siz=a.size();i<siz;++i)
			printf("%d%c",a[i],i==siz-1?'\n':' ');
		return;
	}
	inline poly mul(poly a,poly b){
		reg int s=a.size()+b.size()-1;
		reg int limit=getRev(s);
		a.resize(limit),b.resize(limit);
		NTT(a,limit,1),NTT(b,limit,1);
		for(reg int i=0;i<limit;++i)
			a[i]=1ll*a[i]*b[i]%p;
		NTT(a,limit,-1);
		a.resize(s);
		return a;
	}
}
/*
namespace Subtask4{
	using namespace Poly;
	int col[MAXN<<1];
	inline void Solve(void){
		poly a,b;
		a.resize(n+1,1),b.resize(n+1,1);
		a[0]=0,b[0]=0;
		for(reg int i=1;i<=m;++i)
			switch(q[i].type){
				case 1:{
					a[q[i].pos]=0;
					break;
				}
				case 2:{
					b[q[i].pos]=0;
					break;
				}
				case 3:{
					col[q[i].pos]=1;
					break;
				}
			}
		poly res=mul(a,b);
		//printf("a:"),print(a);
		//printf("b:"),print(b);
		//printf("res:"),print(res);
		reg ll cnt0=0;
		for(reg int i=2;i<=(n<<1);++i)
			if(!col[i])
				cnt0+=res[i];
		printf("%lld %lld %lld %lld\n",cnt0,1ll*n*n-cnt0,0ll,0ll);
		return;
	}
}*/

namespace Subtask5{
	using namespace Poly;
	int cola[MAXN],colb[MAXN];
	int col[MAXN<<1];
	inline ll getWhite(void){
		poly a,b;
		a.resize(n+1),b.resize(n+1);
		for(reg int i=1;i<=n;++i){
			a[i]=(cola[i]==0);
			b[i]=(colb[i]==0);
		}
		poly tmp=mul(a,b);
		reg ll res=0;
		for(reg int i=2;i<=(n<<1);++i)
			if(col[i]==0)
				res+=tmp[i];
		return res;
	}
	inline ll getCol(reg int c){
		poly a,b;
		a.resize(n+1),b.resize(n+1);
		for(reg int i=1;i<=n;++i){
			a[i]=((cola[i]&(1<<c))!=(1<<c));
			b[i]=((colb[i]&(1<<c))!=(1<<c));
		}
		poly tmp=mul(a,b);
		reg ll res=0;
		for(reg int i=2;i<=(n<<1);++i)
			if((col[i]&(1<<c))!=(1<<c))
				res+=tmp[i];
		return 1ll*n*n-res;
	}
	inline void Solve(void){
		for(reg int i=1;i<=m;++i)
			switch(q[i].type){
				case 1:{
					cola[q[i].pos]|=1<<q[i].color;
					break;
				}
				case 2:{
					colb[q[i].pos]|=1<<q[i].color;
					break;
				}
				case 3:{
					col[q[i].pos]|=1<<q[i].color;
					break;
				}
			}
		reg ll ans0=getWhite();
		reg ll tmp1=getCol(0),tmp2=getCol(1);
		reg ll ans3=(tmp1+tmp2)-(1ll*n*n-ans0);
		reg ll ans1=tmp1-ans3,ans2=tmp2-ans3;
		printf("%lld %lld %lld %lld\n",ans0,ans1,ans2,ans3);
		return;
	}
}

int main(void){
	n=read(),m=read();/*
	reg bool subtask2flag=true;
	reg bool subtask3flag=true;
	reg bool subtask4flag=true;*/
	for(reg int i=1;i<=m;++i){
		q[i].type=read(),q[i].pos=read(),q[i].color=read();/*
		if(q[i].type>1)
			subtask2flag=false;
		if(q[i].type>2)
			subtask3flag=false;
		if(q[i].color)
			subtask4flag=false;*/
	}/*
	if(n<=1e3)
		puts("S1"),
		Subtask1::Solve();
	//else 
	if(subtask2flag)
		puts("S2"),
		Subtask2::Solve();
	//else 
	if(subtask3flag)
		puts("S3"),
		Subtask3::Solve();
	//else 
	if(subtask4flag)
		puts("S4"),
		Subtask4::Solve();
	else
		puts("S5"),*/
		Subtask5::Solve();
	return 0;
}