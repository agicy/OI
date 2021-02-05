#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXA=5e5+5;

int n,q;
int a[MAXN];

bool vis[MAXA];
int tot,prime[MAXA];
int from[MAXA];

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i]){
			prime[++tot]=i;
			from[i]=i;
		}
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			from[i*prime[j]]=prime[j];
			if(i%prime[j]==0)
				break;
		}
	}
	return;
}

bool in[MAXN];
int fac[MAXA];
int f[MAXA];

int main(void){
	freopen("pair.in","r",stdin);
	freopen("pair.out","w",stdout);

	Init(5e5);
	n=read(),q=read();
	int Maxa=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		Maxa=max(Maxa,a[i]);
	}
	reg int ans=0,siz=0;
	while(q--){
		static int x;
		x=read();
		reg int tmp=a[x];
		if(tmp==1){
			if(in[x])
				ans-=siz-1,--siz,--f[a[x]];
			else
				ans+=siz,++siz,++f[a[x]];
			in[x]^=1;
		}
		else{
			tot=0;
			while(tmp>1){
				reg int t=from[tmp],cnt=0;
				while(tmp%t==0)
					++cnt,tmp/=t;
				fac[tot++]=t;
			}
			reg int U=(1<<tot)-1;
			reg int res=0;
			for(reg int i=0;i<=U;++i){
				reg int cnt=0,pod=1;
				for(reg int j=0;j<tot;++j)
					if((i>>j)&1){
						++cnt;
						pod*=fac[j];
					}
				if(cnt&1)
					res-=f[pod];
				else
					res+=f[pod];
			}
			if(in[x]){
				ans-=res,--siz;
				for(reg int i=1;i*i<=a[x];++i)
					if(a[x]%i==0){
						--f[i];
						if(i*i!=a[x])
							--f[a[x]/i];
					}
			}
			else{
				ans+=res,++siz;
				for(reg int i=1;i*i<=a[x];++i)
					if(a[x]%i==0){
						++f[i];
						if(i*i!=a[x])
							++f[a[x]/i];
					}
			}
			in[x]^=1;
		}
		printf("%d\n",ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}