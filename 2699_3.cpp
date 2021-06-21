#include<bits/stdc++.h>
using namespace std;
#define int long long
#define inf 0x3f3f3f3f

const int mod=1e9+9;
const int N=5e5+5;

inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9')
	{
		if(c=='-')
		    f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}

int n,m,a[N];
struct node{
	int l,r;
}re[N];
inline bool cmp(node x,node y)
{
	return x.r<y.r;
}
inline void Add(int &x,int y)
{
	x=(x+y)%mod;
}

int f[N],tmp[N],p[N];
signed main()
{
	n=read(); m=read();
	for(int i=1;i<=n;i++) re[i].l=read(),re[i].r=read();
	for(int i=1;i<=m;i++) a[i]=read();
	sort(a+1,a+m+1); sort(re+1,re+n+1,cmp);
	for(int i=1;i<=n;i++) 
	{
		p[i]=upper_bound(a+1,a+m+1,re[i].r)-a;
		assert(p[i]!=0);
		if(p[i]==m+1) p[i]=0;
	}
	if(a[m]>re[n].r)
	{
		printf("0\n");
		return 0;
	}
	f[0]=1; a[0]=inf;
	for(int i=0;i<n;i++)
	{
		memset(tmp,0,sizeof(tmp));
		for(int j=0;j<=m && a[j]<=re[i].r;j++)
			if(f[j])
			{
				if(!j)
				{
					if(re[i+1].l<=a[p[i]]) Add(tmp[0],f[j]);
					else Add(tmp[p[i]],f[j]);
					Add(tmp[p[i]],f[j]);
				}
				else
				{
					if(re[i+1].l<=a[j]) Add(tmp[0],f[j]);
					else Add(tmp[j],f[j]);
					Add(tmp[j],f[j]);
				}
			}
		for(int j=0;j<=m && a[j]<=re[i].r;j++)
			f[j]=tmp[j];
	}
	printf("%lld\n",f[0]);
	return 0;
}