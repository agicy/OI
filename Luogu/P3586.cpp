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
const int MAXM=1e6+5;
const int MAXSIZE=MAXN+MAXM;

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n;
	ll unit[MAXSIZE];
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
		if(!id)
			return 0;
		reg ll res=0;
		for(reg int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
};

struct Node{
	char type;
	ll a,b;
	inline void Read(void){
		do
			type=getchar();
		while(type!='U'&&type!='Z');
		a=read(),b=read();
		return;
	}
};

int n,m;
ll a[MAXN];
Node Q[MAXM];
TreeArray T1,T2;
vector<ll> V;

int main(void){
	n=read(),m=read();
	V.push_back(0);
	for(reg int i=1;i<=m;++i){
		Q[i].Read();
		V.push_back(Q[i].b);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	reg int S=V.size();
	T1.Init(S),T2.Init(S);
	reg int id0=lower_bound(V.begin(),V.end(),0)-V.begin()+1;
	T2.update(id0,n);
	for(reg int i=1;i<=m;++i)
		switch(Q[i].type){
			case 'U':{
				reg int u=lower_bound(V.begin(),V.end(),a[Q[i].a])-V.begin()+1;
				reg int v=lower_bound(V.begin(),V.end(),Q[i].b)-V.begin()+1;
				T1.update(u,-a[Q[i].a]),T1.update(v,Q[i].b);
				T2.update(u,-1),T2.update(v,1);
				a[Q[i].a]=Q[i].b;
				break;
			}
			case 'Z':{
				reg int p=lower_bound(V.begin(),V.end(),Q[i].b)-V.begin()+1;
				reg ll sum=T1.query(p-1);
				reg ll cnt=n-T2.query(p-1);
				if((Q[i].a-cnt)*Q[i].b<=sum)
					puts("TAK");
				else
					puts("NIE");
				break;
			}
		}
	return 0;
}
