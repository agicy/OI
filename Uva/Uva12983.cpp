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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e3+5;
const int MAXM=1e3+5;
const int p=1e9+7;
const int inf=0x3f3f3f3f;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

int n,m;
int a[MAXN];

namespace BIT{
	int n,Id;
	int unit[MAXN],tag[MAXN];
	inline int lowbit(reg int x){
		return x&(-x);
	}
	inline void Init(reg int s){
		n=s,++Id;
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i)){
			if(tag[i]!=Id)
				tag[i]=Id,unit[i]=0;
			unit[i]=add(unit[i],val);
		}
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			if(tag[i]==Id)
				res=add(res,unit[i]);
		return res;
	}
}

int f[MAXM][MAXN];
vector<int> V;

int main(void){
	reg int t=read();
	reg int Case=0;
	while(t--){
		n=read(),m=read();
		V.resize(n+1);
		V[0]=a[0]=-inf;
		for(reg int i=1;i<=n;++i){
			a[i]=read();
			V[i]=a[i];
		}
		sort(V.begin(),V.end());
		V.erase(unique(V.begin(),V.end()),V.end());
		for(reg int i=0;i<=n;++i)
			a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
		f[0][0]=1;
		for(reg int i=1;i<=m;++i){
			BIT::Init(n+1);
			BIT::update(a[0],f[i-1][0]);
			for(reg int j=1;j<=n;++j){
				f[i][j]=BIT::query(a[j]-1);
				BIT::update(a[j],f[i-1][j]);
			}
		}
		reg int ans=0;
		for(reg int i=1;i<=n;++i)
			ans=add(ans,f[m][i]);
		printf("Case #%d: %d\n",++Case,ans);
	}
	return 0;
}