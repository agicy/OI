#pragma GCC optimize("Ofast")
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

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=400+5;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Node{
	int id,val;
	inline Node(reg int id=0,reg int val=0):id(id),val(val){
		return;
	}
	inline bool operator<(const Node& a)const{
		return val<a.val;
	}
};

int n;
int a[MAXN];
ll val[MAXN][MAXN];
ll dis1[MAXN][MAXN],disn[MAXN][MAXN];
ll f[MAXN][MAXN];
ll lef[MAXN][MAXN],rig[MAXN][MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=i;j<=n;++j)
			val[i][j]=val[j][i]=1ll*(a[j]-a[i])*((int)sqrt(a[j]-a[i]));
	memset(dis1,0x3f,sizeof(dis1));
	dis1[0][1]=0;
	for(reg int t=0;t<n-1;++t)
		for(reg int i=1;i<=n;++i)
			if(dis1[t][i]<inf)
				for(reg int j=i;j<=n;++j)
					dis1[t+1][j]=min(dis1[t+1][j],dis1[t][i]+val[i][j]);
	memset(disn,0x3f,sizeof(disn));
	disn[0][n]=0;
	for(reg int t=0;t<n-1;++t)
		for(reg int i=n;i>=1;--i)
			if(disn[t][i]<inf)
				for(reg int j=i;j>=1;--j)
					disn[t+1][j]=min(disn[t+1][j],disn[t][i]+val[i][j]);
	memset(f,0x3f,sizeof(f));
	for(reg int i=1;i<=n;++i){
		static Node tmp[MAXN];
		for(reg int j=1;j<=n;++j)
			tmp[j]=Node(j,abs(a[j]-a[i]));
		sort(tmp+1,tmp+n+1);
		reg int ptrl=i,ptrr=i;
		for(reg int j=1;j<=n;++j){
			reg int id=tmp[j].id,dis=tmp[j].val;
			while(ptrl-1>=1&&a[i]-a[ptrl-1]<=dis)
				--ptrl;
			while(ptrr+1<=n&&a[ptrr+1]-a[i]<=dis)
				++ptrr;
			for(reg int k=1;k<n;++k)
				if(dis1[k-1][ptrl]<inf&&disn[k-1][ptrr]<inf)
					f[k][i]=min(f[k][i],dis1[k-1][ptrl]+disn[k-1][ptrr]+val[i][id]);
		}
	}
	memset(lef,0x3f,sizeof(lef));
	for(reg int j=1;j<n;++j)
		for(reg int i=1;i<=n;++i){
			lef[j][i]=f[j][i];
			for(reg int k=1;k<=i;++k)
				if(lef[j-1][k]<inf)
					lef[j][i]=min(lef[j][i],lef[j-1][k]+val[i][k]);
		}
	memset(rig,0x3f,sizeof(rig));
	for(reg int j=1;j<n;++j)
		for(reg int i=n;i>=1;--i){
			rig[j][i]=f[j][i];
			for(reg int k=i;k<=n;++k)
				if(rig[j-1][k]<inf)
					rig[j][i]=min(rig[j][i],rig[j-1][k]+val[i][k]);
		}
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<n;++j)
			write(min(f[j][i],min(lef[j][i],rig[j][i]))),putchar(j==n-1?'\n':' ');
	flush();
	return 0;
}