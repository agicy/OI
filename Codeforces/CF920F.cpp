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

const int MAXN=3e5+5;
const int MAXA=1e6+1;

int n,m;
int fa[MAXN];
ll a[MAXN];
ll d[MAXA];

namespace TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	ll unit[MAXN];
	inline void Init(reg int S){
		n=S;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg ll val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline ll query(reg int id){
		reg ll res=0;
		for(reg int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
}

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

int main(void){
	for(reg int i=1;i<MAXA;++i)
		for(reg int j=i;j<MAXA;j+=i)
			++d[j];
	n=read(),m=read();
	TreeArray::Init(n);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		TreeArray::update(i,a[i]);
		fa[i]=i;
	}
	fa[n+1]=n+1;
	while(m--){
		static int t,l,r;
		t=read(),l=read(),r=read();
		if(l>r)
			swap(l,r);
		switch(t){
			case 1:{
				for(reg int i=l;i<=r;){
					TreeArray::update(i,d[a[i]]-a[i]);
					a[i]=d[a[i]];
					if(a[i]<=2)
						fa[i]=i+1;
					if(i==find(i))
						++i;
					else
						i=fa[i];
				}
				break;
			}
			case 2:{
				printf("%lld\n",TreeArray::query(r)-TreeArray::query(l-1));
				break;
			}
		}
	}
	return 0;
}