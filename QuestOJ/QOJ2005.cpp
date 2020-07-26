#include<cstdio>
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

int n;
ll a[MAXN];
int cnt;
ll Prime[MAXN];

inline ll gcd(reg ll,reg ll);
inline void Read(void);
inline void Work(void);
inline void Divide(reg ll);

int main(void){
	Read();
	Divide(a[1]);
	Work();
	return 0;
}

inline ll gcd(reg ll a,reg ll b){
	return b==0?a:gcd(b,a%b);
}

inline void Read(void){
	reg int i;
	n=read();
	for(i=1;i<=n;++i)
		a[i]=read();
	return;
}

inline void Work(void){
	reg bool flag;
	reg int i,j;
	reg ll w;
	for(i=1;i<=n;++i){
		flag=false;
		w=gcd(a[1],a[i]);
		for(j=1;j<=cnt;++j)
			if(w%Prime[j]==0){
				flag=true;
				w/=Prime[j];
				break;
			}
			else if(w<Prime[j])
				break;
		printf("%lld%c",flag?w:-1,i==n?'\n':' ');
	}
	return;
}

inline void Divide(reg ll n){
	reg ll i;
	for(i=2;i*i<=n;++i)
		if(n%i==0){
			Prime[++cnt]=i;
			while(n%i==0)
				n/=i;
		}
	if(n>1)
		Prime[++cnt]=n;
	return;
}
