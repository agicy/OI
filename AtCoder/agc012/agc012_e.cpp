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
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void writeln(const char* s){
	while(*s) putchar(*(s++));
	putchar('\n');
	return;
}

const int MAXN=2e5+5;
const int MAXLOG2V=18;

int n,V;
int a[MAXN];
int cnt=-1,tot[MAXLOG2V+1],r[MAXLOG2V+1][MAXN];
int rig[1<<MAXLOG2V],lef[1<<MAXLOG2V];

int main(void){
	n=read(),V=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int x=V<<1;
	while(x){
		x>>=1,++cnt;
		for(reg int i=1;i<n;++i)
			if(a[i+1]-a[i]>x)
				r[cnt][++tot[cnt]]=i;
		r[cnt][++tot[cnt]]=n;
	}
	if(tot[0]>cnt+1)
		for(reg int i=1;i<=n;++i)
			writeln("Impossible");
	else{
		for(reg int S=0;S<(1<<cnt);++S)
			lef[S]=n+1;
		for(reg int S=0;S<(1<<cnt);++S)
			for(reg int i=1;i<=cnt;++i)
				if(!((S>>(i-1))&1)){
					lef[S|(1<<(i-1))]=min(lef[S|(1<<(i-1))],*(lower_bound(r[i]+1,r[i]+tot[i]+1,lef[S]-1)-1)+1);
					rig[S|(1<<(i-1))]=max(rig[S|(1<<(i-1))],*upper_bound(r[i]+1,r[i]+tot[i]+1,rig[S]));
				}
		for(reg int i=1;i<=tot[0];++i){
			reg bool flag=false;
			for(reg int S=0;S<(1<<cnt);++S)
				if(r[0][i-1]<=rig[S]&&lef[((1<<cnt)-1)^S]<=r[0][i]+1){
					flag=true;
					break;
				}
			for(reg int j=r[0][i-1]+1;j<=r[0][i];++j)
				writeln(flag?"Possible":"Impossible");
		}
	}
	flush();
	return 0;
}