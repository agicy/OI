#include<cstdio>
#include<cstring>
#define reg register
typedef long long ll;
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

const int MAXN=200+5;
const int MAXV=5000+5;
const int MAXK=50+5;

int K,V,n;
int w[MAXN],p[MAXN];
ll dp[MAXV][MAXK];
ll temp[MAXK];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	reg int i;
	K=read(),V=read(),n=read();
	for(i=1;i<=n;++i)
		w[i]=read(),p[i]=read();
	return;
}

inline void Work(void){
	reg int i,j,k,L1,L2,cnt;
	reg ll sum=0;
	memset(dp,-0X3F,sizeof(dp));
	dp[0][1]=0;
	for(i=1;i<=n;++i)
		for(j=V;j>=w[i];--j){
			L1=L2=1,cnt=0;
			while(cnt<=K)
				if(dp[j][L1]>dp[j-w[i]][L2]+p[i])
					temp[++cnt]=dp[j][L1++];
				else
					temp[++cnt]=dp[j-w[i]][L2++]+p[i];
			for(k=1;k<=K;++k)
				dp[j][k]=temp[k];
		}
	for(i=1;i<=K;++i)
		sum+=dp[V][i];
	printf("%lld\n",sum);
	return;
}
