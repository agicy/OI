#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f

const int N=400+5;
const int mod=998244353;

inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c>='0' && c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}

int n;
int a[N],tot=0;
struct node{
	int to,last;
}tree[N*2];
int s=0,head[N];
inline void add(int from,int to)
{
	tree[++s].to=to;
	tree[s].last=head[from];
	head[from]=s;
}

int high[N],len[N];
inline int dfs1(int l,int r,int h)
{
	if(l>r) return 0;
	int now=(++tot),minn=inf;
	for(int i=l;i<=r;i++) minn=min(minn,a[i]);
	high[now]=minn-h; len[now]=r-l+1;
	int last=l-1;
	for(int i=l;i<=r;i++)
		if(a[i]==minn)
		{
			int son=dfs1(last+1,i-1,minn);
			if(son) add(now,son);
			last=i;
		}
	int son=dfs1(last+1,r,minn);
	if(son) add(now,son);
	return now;
}
inline int power(int x,int y)
{
	int ans=1;
	for(;y;y>>=1)
	{
		if(y&1) ans=ans*x%mod;
		x=x*x%mod;
	}
	return ans;
}

int pre[N],ni[N];
inline void prework()
{
	pre[0]=ni[0]=1;
	for(int i=1;i<=n;i++) pre[i]=pre[i-1]*i%mod;
	ni[n]=power(pre[n],mod-2);
	for(int i=n-1;i>=1;i--) ni[i]=ni[i+1]*(i+1)%mod;
}
inline int C(int n,int m)
{
	if(n<m) return 0;
	return pre[n]*ni[m]%mod*ni[n-m]%mod;
}

int f[N][N][2],siz[N],tmp[N][2];
inline void Add(int &x,int y)
{
	x=(x+y)%mod;
}
inline int ask(int n,int opt)
{
	int c;
	if(n&1) c=mod-1; 
	else c=1;
	if(!opt) return c;
	if(!n) return 0;
	return (mod-c)%mod;
}
inline void dfs2(int from,int to)
{
	f[to][0][0]=1;
	for(int i=head[to];i;i=tree[i].last)
	{
		int k=tree[i].to;
		if(k==from) continue;
		dfs2(to,k);
		memset(tmp,0,sizeof(tmp));
		for(int k1=0;k1<=siz[to];k1++)
			for(int k2=0;k2<=len[k];k2++)
				for(int p1=0;p1<=1;p1++)
					for(int p2=0;p2<=1;p2++)
						Add(tmp[k1+k2][p1|p2],f[to][k1][p1]*f[k][k2][p2]%mod);
		memcpy(f[to],tmp,sizeof(tmp));
		siz[to]+=len[k];
	}
	int res=len[to]-siz[to];
	memset(tmp,0,sizeof(tmp));
	for(int k1=0;k1<=siz[to];k1++)
		for(int k2=0;k2<=res;k2++)
			for(int p1=0;p1<=1;p1++)
				for(int p2=0;p2<=1;p2++)
				{
					int cnt=C(res,k2)*ask(k2,p2);
					int val=(power(2,len[to]-(k1+k2))-(p1|p2)+mod)%mod;
					val=power(val,high[to]);
					Add(tmp[k1+k2][p1|p2],f[to][k1][p1]%mod*val%mod*cnt%mod);
				}
	memcpy(f[to],tmp,sizeof(tmp));
}

int root;
signed main()
{
	n=read(); prework();
	for(int i=1;i<=n;i++) a[i]=read();
	root=dfs1(1,n,0); dfs2(0,root);
	int Ans=0;
	for(int i=0;i<=n;i++)
		for(int p=0;p<=1;p++)
			Ans=(Ans+f[1][i][p])%mod;
	printf("%lld\n",Ans);
	return 0;
}
