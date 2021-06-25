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
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x<0) x=-x,putchar('-');
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=2e6+5;
const int base=1331;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,k,m;
char s[MAXN];
bool a[MAXN],b[MAXN];
int basep[MAXN];
bool tag[MAXN];
int tmp[MAXN];
int sum[3][MAXN],ans[MAXN];

inline bool check(reg int l,reg int r){
	reg int Hash=sub(sum[1][r],sum[0][l]);
	if(!a[l])
		return !Hash;
	else
		return !(add(Hash,basep[l%k])&&sub(Hash,basep[l%k]));
}

int main(void){
	n=read(),k=read(),m=read(),read(s+1);
	for(reg int i=1;i<=n;++i)
		a[i]=s[i]^'0',b[i]=a[i]^a[i-1];
	basep[0]=1;
	for(reg int i=1;i<=k;++i)
		basep[i]=1ll*basep[i-1]*base%mod;
	for(reg int i=1;i<=n;++i){
		if(b[i]){
			reg int p=i%k;
			tag[p]=!tag[p];
			if(tag[p])
				sum[0][i]=add(sum[0][i-1],basep[p]);
			else
				sum[0][i]=sub(sum[0][i-1],basep[p]);
		}
		else
			sum[0][i]=sum[0][i-1];
		if(a[i]){
			reg int p=(i+1)%k;
			if(!tag[p])
				sum[1][i]=add(sum[0][i],basep[p]);
			else
				sum[1][i]=sub(sum[0][i],basep[p]);
		}
		else
			sum[1][i]=sum[0][i];
	}
	for(reg int i=1;i<=n;++i){
		if(b[i]){
			sum[2][i]=sum[2][i-1]-2*tmp[i%k]+i/k;
			tmp[i%k]=-tmp[i%k]+i/k;
		}
		else
			sum[2][i]=sum[2][i-1];
		if(a[i])
			ans[i]=sum[2][i]-2*tmp[(i+1)%k]+(i+1)/k;
		else
			ans[i]=sum[2][i];
	}
	for(reg int i=1;i<=m;++i){
		static int l,r;
		l=read(),r=read();
		if(!check(l,r))
			writeln(-1);
		else
			writeln(ans[r]-ans[l-1]);
	}
	flush();
	return 0;
}