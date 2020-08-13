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

const int MAXN=2e6+5;
const int MAXC=2e6+5;
const int MAXM=2e6+5;

int n,c,m;
int x[MAXN];
int pos[MAXC],nex[MAXN];

struct querys{
	int l,r,id;
	inline querys(reg int l=0,reg int r=0,reg int id=0):l(l),r(r),id(id){
		return;
	}
	inline bool operator<(const querys& a)const{
		return l<a.l;
	}
};

namespace TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXN];
	inline void Init(reg int S){
		n=S;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void update(reg int id,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int query(reg int id){
		reg int res=0;
		for(reg int i=id;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
}

int T[MAXC];
int ans[MAXM];
querys Q[MAXM];

int main(void){
	n=read(),c=read(),m=read();
	for(reg int i=1;i<=n;++i)
		x[i]=read();
	for(reg int i=1;i<=m;++i){
		static int l,r;
		l=read(),r=read();
		Q[i]=querys(l,r,i);
	}
	sort(Q+1,Q+m+1);
	for(reg int i=n;i>=1;--i){
		nex[i]=pos[x[i]];
		pos[x[i]]=i;
	}
	TreeArray::Init(n);
	for(reg int i=1;i<=n;++i)
		if(++T[x[i]]==2)
			TreeArray::update(i,1);
	reg int ptr=1;
	for(reg int i=1;i<=m;++i){
		while(ptr<Q[i].l){
			if(nex[ptr])
				TreeArray::update(nex[ptr],-1);
			if(nex[nex[ptr]])
				TreeArray::update(nex[nex[ptr]],1);
			++ptr;
		}
		ans[Q[i].id]=TreeArray::query(Q[i].r)-TreeArray::query(Q[i].l-1);
	}
	for(reg int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}