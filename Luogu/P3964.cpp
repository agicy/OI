#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

int n;
ll x[MAXN],y[MAXN];
ll Rx[MAXN],Ry[MAXN];
ll sumx[MAXN],sumy[MAXN];

inline ll Calc(reg int u){
	reg ll ansx=0,ansy=0;
	reg int posx=lower_bound(x+1,x+1+n,Rx[u])-x;
	reg int posy=lower_bound(y+1,y+1+n,Ry[u])-y;
	ansx=posx*Rx[u]-sumx[posx]+sumx[n]-sumx[posx]-(n-posx)*Rx[u];
	ansy=posy*Ry[u]-sumy[posy]+sumy[n]-sumy[posy]-(n-posy)*Ry[u];
	return ansx+ansy;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static ll a,b;
		a=read(),b=read();
		x[i]=Rx[i]=a+b;
		y[i]=Ry[i]=a-b;
	}
	sort(x+1,x+n+1);
	sort(y+1,y+n+1);
	for(reg int i=1;i<=n;++i){
		sumx[i]=sumx[i-1]+x[i];
		sumy[i]=sumy[i-1]+y[i];
	}
	ll ans=INF;
	for(reg int i=1;i<=n;++i)
		ans=min(ans,Calc(i));
	printf("%llu\n",ans>>1);
	return 0;
}
