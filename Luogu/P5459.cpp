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

int n;
ll L,R;
int a[MAXN];
ll sum[MAXN];
vector<ll> V;

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXN*3];
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

TreeArray T;

int main(void){
	n=read(),L=read(),R=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+a[i];
	for(reg int i=1;i<=n;++i){
		V.push_back(sum[i]);
		V.push_back(sum[i]-L);
		V.push_back(sum[i]-R);
	}
	V.push_back(0);
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	T.Init(V.size());
	T.Update(lower_bound(V.begin(),V.end(),0)-V.begin()+1,1);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		reg int l=lower_bound(V.begin(),V.end(),sum[i]-R)-V.begin()+1;
		reg int r=lower_bound(V.begin(),V.end(),sum[i]-L)-V.begin()+1;
		ans+=T.Query(r)-T.Query(l-1);
		reg int ID=lower_bound(V.begin(),V.end(),sum[i])-V.begin()+1;
		T.Update(ID,1);
	}
	printf("%lld\n",ans);
	return 0;
}
