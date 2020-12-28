#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline ll readll(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

static char wbuf[1<<21];
int wp1;
const int wp2=1<<21;

inline void flush(void){
	fwrite(wbuf,1,wp1,stdout);
	wp1=0;
	return;
}

#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putchar('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putchar(buf[p--]);
	putchar('\n');
	return;
}

const int p=998244353;
const int inv2=499122177;

int n,m,x,y;
ll k;

namespace SubtaskMineq1{
	inline int Solve(void){
		reg int pos=max(x,y),len=max(n,m);
		reg int dis=min(pos,len-pos+1);
		if(k<=len-dis+1)
			return 1ll*(k+1)*k%p*inv2%p;
		else if(k>=len+max(0,dis-2))
			return (k%p*len%p-1ll*len*(len-1)%p*inv2%p+p)%p;
		else{
			reg ll v=((k-max(dis,len-dis+1)+1)/2+max(dis,len-dis+1))%p;
			return (v*(k%p)%p-v*(v-1)%p*inv2%p+p)%p;
		}
	}
}

namespace SubtaskMinneq1{
	inline int Solve(void){
		if(k<=1ll*n*m)
			return 1ll*(k+1)*k%p*inv2%p;
		else
			return (1ll*(1ll*n*m%p+1)*(1ll*n*m%p)%p*inv2%p+(k%p-1ll*n*m%p+p)%p*(1ll*n*m%p)%p)%p;
	}
}

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read(),x=read(),y=read(),k=readll();
		reg int ans;
		if(min(n,m)==1)
			ans=SubtaskMineq1::Solve();
		else
			ans=SubtaskMinneq1::Solve();
		writeln(ans);
	}
	flush();
	return 0;
}