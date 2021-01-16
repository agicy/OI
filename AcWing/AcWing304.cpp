#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef long double ld;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c)(wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(*s<33)*s=getchar();
	while(*s>=33)*(++s)=getchar();
	*s='\0';
	return;
}

inline void write(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

inline void write(const char *s){
	while(*s)
		putchar(*s++);
	return;
}

const int MAXN=1e5+5;
const int MAXS=30+5;

int n,l,p;
char s[MAXN][MAXS];
int a[MAXN];
int from[MAXN];
ld f[MAXN];
int k[MAXN];

inline ld fpow(reg ld x,reg int exp){
	reg ld res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x;
		exp>>=1;
	}
	return res;
}

inline ld calc(reg int i,reg int j){
	return f[j]+fpow(abs(a[i]-a[j]-l),p);
}

inline int bound(reg int x,reg int y){
	reg int l=x,r=n+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(calc(mid,x)>=calc(mid,y))
			r=mid;
		else
			l=mid+1;
	}
	return l;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),l=read()+1,p=read();
		for(reg int i=1;i<=n;++i){
			read(s[i]);
			a[i]=a[i-1]+strlen(s[i])+1;
		}
		reg int head=1,tail=1;
		static int Q[MAXN];
		Q[1]=0;
		for(reg int i=1;i<=n;++i){
			while(head<tail&&k[head]<=i)
				++head;
			f[i]=calc(i,Q[head]);
			from[i]=Q[head];
			while(head<tail&&k[tail-1]>=bound(Q[tail],i))
				--tail;
			k[tail]=bound(Q[tail],i);
			Q[++tail]=i;
		}
		if(f[n]>1e18)
			write("Too hard to arrange"),putchar('\n');
		else{
			write(f[n]),putchar('\n');
			reg int top=0;
			static int S[MAXN];
			S[0]=n;
			for(reg int i=n;i>=1;i=from[i])
				S[++top]=from[i];
			while(top){
				for(reg int i=S[top]+1;i<=S[top-1];++i)
					write(s[i]),putchar(i==S[top-1]?'\n':' ');
				--top;
			}
		}
		for(reg int i=0;i<20;++i)
			putchar('-');
		putchar('\n');
	}
	flush();
	return 0;
}