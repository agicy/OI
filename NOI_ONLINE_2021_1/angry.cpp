#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s)) *s=getchar();
	while(isdigit(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=5e5+5;
const int MAXK=500+5;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

char n[MAXN];
int k;
int a[MAXK];
int binom[MAXK][MAXK];

inline int f(reg int x){
	reg int res=0;
	for(reg int i=k-1;i>=0;--i)
		res=add(1ll*res*x%mod,a[i]);
	return res;
}

int tag[MAXN];
int suma[MAXK],sumb[MAXK];
int delta[MAXK];

int main(void){
	freopen("angry.in","r",stdin);
	freopen("angry.out","w",stdout);
	read(n);
	reg int len=strlen(n);
	k=read();
	for(reg int i=0;i<k;++i)
		a[i]=read();
	binom[0][0]=1;
	for(reg int i=1;i<=k;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=i;++j)
			binom[i][j]=add(binom[i-1][j-1],binom[i-1][j]);
	}
	reg int flag=1;
	for(reg int i=0;i<len;++i){
		if(n[i]=='1'){
			tag[i]=flag?1:-1;
			flag^=1;
		}
	}
	reg int bas=1;
	suma[0]=1,sumb[0]=0;
	reg int ans=0;
	for(reg int i=0,tmp=0;i<len;++i){
		delta[i]=tmp;
		if(n[i]=='1')
			tmp=add(tmp,fpow(2,len-i-1));
	}
	for(reg int i=0;i<len;++i){
		switch(tag[len-i-1]){
			case 1:{
				reg int sum=0;
				for(reg int j=0;j<k;++j){
					reg int tmp=0;
					for(reg int l=0;l<=j;++l)
						tmp=add(tmp,1ll*binom[j][l]*sumb[l]%mod*fpow(delta[len-i-1],j-l)%mod);
					sum=add(sum,1ll*tmp*a[j]%mod);
				}
				ans=add(ans,sum);
				break;
			}
			case -1:{
				reg int sum=0;
				for(reg int j=0;j<k;++j){
					reg int tmp=0;
					for(reg int l=0;l<=j;++l)
						tmp=add(tmp,1ll*binom[j][l]*suma[l]%mod*fpow(delta[len-i-1],j-l)%mod);
					sum=add(sum,1ll*tmp*a[j]%mod);
				}
				ans=add(ans,sum);
				break;
			}
			default:{
				break;
			}
		}
		static int tmpa[MAXK],tmpb[MAXK];
		for(reg int j=0;j<k;++j)
			tmpa[j]=suma[j],tmpb[j]=sumb[j];
		for(reg int j=0;j<k;++j){
			for(reg int l=0;l<=j;++l)
				sumb[j]=add(sumb[j],1ll*binom[j][l]*tmpa[l]%mod*fpow(bas,j-l)%mod);
			for(reg int l=0;l<=j;++l)
				suma[j]=add(suma[j],1ll*binom[j][l]*tmpb[l]%mod*fpow(bas,j-l)%mod);
		}
		bas=add(bas,bas);
	}
	printf("%d\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}