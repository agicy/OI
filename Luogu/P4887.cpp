#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

inline int abs(reg int x){
	return x<0?-x:x;
}

inline int sgn(reg int x){
	if(x<0)
		return -1;
	else
		return x?1:0;
}

const int MAXN=1e5+5;
const int MAXM=1e5+5;

int n,m,k;
int a[MAXN];
int blk[MAXN];

struct querys{
	int id,l,r;
	ll ans;
	inline bool operator<(const querys& a)const{
		return blk[l]==blk[a.l]?r<a.r:l<a.l;
	}
};

struct Event{
	int id,l,r;
	inline Event(reg int id=0,reg int l=0,reg int r=0):id(id),l(l),r(r){
		return;
	}
};

querys q[MAXM];
ll ans[MAXM];
int T[16384];
ll pre1[MAXN],pre2[MAXN];
vector<Event> V[MAXM];

int main(void){
	n=read(),m=read(),k=read();
	if(k>14){
		for(reg int i=1;i<=m;++i)
			writeln(0);
	}
	else{
		vector<int> S;
		for(int i=0;i<(1<<14);++i)
			if(__builtin_popcount(i)==k)
				S.push_back(i);
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		reg int B=max(100,int(n/sqrt(m))),tot=(n+B-1)/B;
		for(reg int i=1;i<=tot;++i){
			reg int lef=(i-1)*B+1,rig=min(i*B,n);
			for(reg int j=lef;j<=rig;++j)
				blk[j]=i;
		}
		for(reg int i=1;i<=m;++i)
			q[i].id=i,q[i].l=read(),q[i].r=read();
		sort(q+1,q+m+1);
		for(reg int i=1;i<=n;++i){
			pre1[i]=pre1[i-1]+T[a[i]];
			for(int x:S)
				++T[a[i]^x];
			pre2[i]=pre2[i-1]+T[a[i]];
		}
		reg int l=1,r=0;
		for(reg int i=1;i<=m;++i){
			if(r<q[i].r){
				V[l-1].push_back(Event(-i,r+1,q[i].r));
				q[i].ans+=pre1[q[i].r]-pre1[r],r=q[i].r;
			}
			if(r>q[i].r){
				V[l-1].push_back(Event(i,q[i].r+1,r));
				q[i].ans-=pre1[r]-pre1[q[i].r],r=q[i].r;
			}
			if(l<q[i].l){
				V[r].push_back(Event(-i,l,q[i].l-1));
				q[i].ans+=pre2[q[i].l-1]-pre2[l-1],l=q[i].l;
			}
			if(l>q[i].l){
				V[r].push_back(Event(i,q[i].l,l-1));
				q[i].ans-=pre2[l-1]-pre2[q[i].l-1],l=q[i].l;
			}
		}
		fill(T,T+16384,0);
		for(reg int i=1;i<=n;++i){
			for(int x:S)
				++T[a[i]^x];
			for(Event e:V[i]){
				reg ll sum=0;
				for(reg int j=e.l;j<=e.r;++j)
					sum+=T[a[j]];
				q[abs(e.id)].ans+=sgn(e.id)*sum;
			}
		}
		for(reg int i=1;i<=m;++i)
			q[i].ans+=q[i-1].ans;
		for(reg int i=1;i<=m;++i)
			ans[q[i].id]=q[i].ans;
		for(reg int i=1;i<=m;++i)
			writeln(ans[i]);
	}
	flush();
	return 0;
}