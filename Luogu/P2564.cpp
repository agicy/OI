#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=1e6+5;
const int MAXK=60+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Node{
	int col,pos;
	inline Node(reg int col=0,reg int pos=0):col(col),pos(pos){
		return;
	}
	inline bool operator<(const Node& a)const{
		return pos<a.pos;
	}
};

int n,k;
Node a[MAXN];
int cnt;
int T[MAXK];

inline void add(reg int x){
	if(!T[a[x].col])
		++cnt;
	++T[a[x].col];
	return;
}

inline void del(reg int x){
	--T[a[x].col];
	if(!T[a[x].col])
		--cnt;
	return;
}

int main(void){
	n=read(),k=read();
	reg int tot=0;
	for(reg int i=1;i<=k;++i){
		static int l;
		l=read();
		while(l--)
			a[++tot]=Node(i,read());
	}
	sort(a+1,a+tot+1);
	reg ll ans=inf;
	for(reg int l=1,r=0;l<=n;++l){
		while(r<n&&cnt<k)
			add(++r);
		if(r==n&&cnt<k)
			break;
		if(cnt==k)
			ans=min(ans,0ll+a[r].pos-a[l].pos);
		del(l);
	}
	printf("%lld\n",ans);
	return 0;
}