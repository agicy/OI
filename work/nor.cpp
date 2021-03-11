#include<bits/stdc++.h>
using namespace std;
#define int long long

const int N=20;
const int M=1e6+5;

inline int read()
{
	int x=0,f=1;
	char c=getchar();
	while(c<'0' || c>'9')
	{
	    if(c=='-')
	        f=-1;
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
int f[(1<<18)+5][N];
int a[N][N];
char c[M];

signed main()
{
	n=read();
	scanf("%s",c+1);
	int ans=0;
	for(int i=n;i>=1;i--)
	{
		if(c[i]=='0') continue;
		int place=i-1;
		while(place && c[place]=='1') place--;
		if(place==i-1) ans++;
		else 
		{
			c[place]='1';
			i=place+1;		
			ans++;
		} 
	}
	if(c[0]=='1') ans++;
	cout<<ans<<endl;
	/*n=read(); 
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			a[i][j]=read();
	f[0][0]=1;
	for(int i=0;i<n;i++) f[(1<<i)][i]=1;
	for(int i=1;i<(1<<n);i++)
		for(int j=0;j<n;j++)
			if(((i>>j)&1) && !f[i][j])
			{
				for(int k=0;k<n;k++)
					if(k!=j && ((i>>k)&1))
						f[i][j]=(f[i][j]+f[i^(1<<j)][k]);
			}
	int ans=0;
	for(int i=0;i<n;i++) ans=(ans+f[(1<<n)-1])%mod;*/
	return 0;
}