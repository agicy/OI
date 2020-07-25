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

const int MAXN=1e6+5;
const int MAXK=MAXN;
const int pr1=200019,pr2=200011;
const int mod1=1e9+7,mod2=1e9+9;

struct Node{
	int id,h1,h2;
	inline Node(reg int id=0,reg int h1=0,reg int h2=0):id(id),h1(h1),h2(h2){
		return;
	}
	inline bool operator<(const Node& a)const{
		if(h1!=a.h1)
			return h1<a.h1;
		else if(h2!=a.h2)
			return h2<a.h2;
		else
			return id<a.id;
	}
};

int n,K;
int a[MAXN];
int las[MAXK];
int T[MAXK];
int base1[MAXN],base2[MAXN];
Node H[MAXN];

inline void Init(reg int n){
	base1[0]=base2[0]=1;
	for(reg int i=1;i<=n;++i){
		base1[i]=1ll*base1[i-1]*pr1%mod1;
		base2[i]=1ll*base2[i-1]*pr2%mod2;
	}
	return;
}

int main(void){
	Init(1e6);
	n=read(),K=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=n;i>=1;--i)
		if(!las[a[i]])
			las[a[i]]=i;
	reg int h1=0,h2=0;
	for(reg int i=1;i<=n;++i){
		++T[a[i]];
		h1=(h1+base1[a[i]-1])%mod1;
		h2=(h2+base2[a[i]-1])%mod2;
		if(i==las[a[i]]){
			h1=(h1-1ll*T[a[i]]*base1[a[i]-1]%mod1+mod1)%mod1;
			h2=(h2-1ll*T[a[i]]*base2[a[i]-1]%mod2+mod2)%mod2;
		}
		H[i]=Node(i,h1,h2);
	}
	sort(H+1,H+n+1);
	reg int mid=(1+n)>>1;
	int ans=n;
	reg ll cnt=0;
	for(reg int i=1;i<=n;){
		reg int nxt=i;
		while(nxt<=n&&H[nxt].h1==H[i].h1&&H[nxt].h2==H[i].h2)
			++nxt;
		cnt+=(1ll*(nxt-i)*(nxt-i-1))>>1;
		for(reg int l=i,r=i;r<nxt;++r){
			while(l<r&&H[r].id-H[l].id>=mid)
				++l;
			if(l>i)
				ans=min(ans,abs(n-2*(H[r].id-H[l-1].id)));
			ans=min(ans,abs(n-2*(H[r].id-H[l].id)));
		}
		i=nxt;
	}
	printf("%lld %d\n",cnt,ans);
	return 0;
}
