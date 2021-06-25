#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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
const int MAXBLK=448+5;
const int C=75;
const int mod=1e9+7;

int n,m;
ll a[MAXN];
int lef[MAXBLK],rig[MAXBLK],id[MAXN];
ll sum[MAXBLK];
ll q[C+1][C];

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int B=sqrt(n);
	reg int tot=(n+B-1)/B;
	for(reg int i=1;i<=tot;++i){
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
		for(reg int j=lef[i];j<=rig[i];++j)
			id[j]=i,sum[i]+=a[j];
	}
	while(m--){
		static int opt,x,y,z,l,r;
		opt=read();
		switch(opt){
			case 1:{
				x=read(),y=read(),z=read();
				if(x>C){
					for(reg int i=y;i<=n;i+=x)
						a[i]+=z,sum[id[i]]+=z;
				}
				else{
					y%=x;
					for(reg int i=y;i<x;++i)
						q[x][i]+=z;
				}
				break;
			}
			case 2:{
				l=read(),r=read();
				reg int idl=id[l],idr=id[r];
				reg ll ans=0;
				if(idl==idr)
					for(reg int i=l;i<=r;++i)
						ans+=a[i];
				else{
					for(reg int i=l;i<=rig[idl];++i)
						ans+=a[i];
					for(reg int i=lef[idr];i<=r;++i)
						ans+=a[i];
					for(reg int i=idl+1;i<idr;++i)
						ans+=sum[i];
				}
				for(reg int i=1;i<=C;++i)
					if(l/i==r/i)
						ans+=q[i][r%i]-((l%i)?q[i][l%i-1]:0);
					else
						ans+=q[i][i-1]*(r/i-l/i)-((l%i)?q[i][l%i-1]:0)+q[i][r%i];
				writeln(ans%mod);
				break;
			}
		}
	}
	flush();
	return 0;
}