#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
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

const int MAXN=2e5+5;
const int MAXA=2e5+5;
const int mod=1e9+7;

bool vis[MAXA];
int tot,prime[MAXA],rnk[MAXA];
int from[MAXA];

inline void Init(reg int n){
	from[1]=1;
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			rnk[i]=tot-1;
			from[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			from[i*prime[j]]=prime[j];
			if(!(i%prime[j]))
				break;
		}
	}
	return;
}

int n,q;
map<int,int> cnt[MAXN];
vector<int> pcnt[MAXA];
int ans=1;

inline void add(int pos,int val){
	while(from[val]!=1){
		reg int p=from[val];
		while(from[val]==p){
			val/=p;
			int id=rnk[p],tmp=cnt[pos][id]++;
			if(pcnt[id].size()<=tmp)
				pcnt[id].push_back(0);
			if(++pcnt[id][tmp]==n)
				ans=1ll*ans*p%mod;
		}
	}
	return;
}

int main(void){
	Init(2e5);
	n=read(),q=read();
	for(reg int i=1;i<=n;++i)
		add(i,read());
	while(q--){
		static int i,x;
		i=read(),x=read();
		add(i,x);
		writeln(ans);
	}
	flush();
	return 0;
}