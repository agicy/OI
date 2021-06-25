#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
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

inline int ins(reg int n,reg int k,const vector<int>& x,const vector<int>& y){
	reg int res=0;
	for(reg int i=0;i<n;++i){
		reg int tmp1=y[i],tmp2=1;
		for(int j=0;j<n;++j)
			if(i!=j)
				tmp1=1ll*tmp1*sub(k,x[j])%mod,tmp2=1ll*tmp2*sub(x[i],x[j])%mod;
		res=add(res,1ll*tmp1*fpow(tmp2,mod-2)%mod);
	}
	return res;
}

char s[MAXN];
int n,k;
int a[MAXK];
int f[MAXK][MAXK][2];
int binom[MAXK][MAXK];
int basep[MAXK];

int main(void){
	read(s),n=strlen(s);
	k=read();
	for(reg int i=0;i<k;++i)
		a[i]=read();
	binom[0][0]=1;
	for(reg int i=1;i<=k;++i){
		binom[i][0]=1;
		for(reg int j=1;j<=i;++j)
			binom[i][j]=add(binom[i-1][j-1],binom[i-1][j]);
	}
	f[0][0][0]=1;
	for(reg int i=1,bas=1;i<=k;++i,bas=add(bas,bas)){
		basep[0]=1;
		for(reg int j=1;j<k;++j)
			basep[j]=1ll*basep[j-1]*bas%mod;
		for(reg int j=0;j<k;++j){
			static int tmp[2];
			tmp[0]=tmp[1]=0;
			for(reg int k=0;k<=j;++k)
				tmp[0]=add(tmp[0],1ll*f[i-1][k][1]*basep[j-k]%mod*binom[j][k]%mod),tmp[1]=add(tmp[1],1ll*f[i-1][k][0]*basep[j-k]%mod*binom[j][k]%mod);
			f[i][j][0]=add(f[i-1][j][0],tmp[0]),f[i][j][1]=add(f[i-1][j][1],tmp[1]);
		}
	}
	reg int ans=0;
	for(reg int i=n-1,bas=0,ptr=0;i>=0;--i)
		if(s[n-i-1]=='1'){
			if(i>k)
				bas=add(bas,fpow(2,i));
			else{
				basep[0]=1;
				for(reg int j=1;j<k;++j)
					basep[j]=1ll*basep[j-1]*bas%mod;
				for(reg int j=0;j<k;++j){
					reg int sum=0;
					for(reg int k=0;k<=j;++k)
						sum=add(sum,1ll*f[i][k][!ptr]*binom[j][k]%mod*basep[j-k]%mod);
					ans=add(ans,1ll*sum*a[j]%mod);
				}
				bas=add(bas,fpow(2,i));
			}
			ptr=!ptr;
		}
	reg int bas=0;
	for(reg int i=n-1;i>k;--i)
		if(s[n-i-1]=='1')
			bas=add(bas,fpow(2,i));
	vector<int> x,y;
	for(int i=0,sum=0;i<=k;++i){
		x.push_back(i),y.push_back(sum);
		reg int tmp=0;
		for(reg int j=k-1;j>=0;--j)
			tmp=add(1ll*tmp*i%mod,a[j]);
		sum=add(sum,tmp);
	}
	reg int inv2=fpow(2,mod-2);
	printf("%d\n",add(ans,1ll*inv2*ins(x.size(),bas,x,y)%mod));
	return 0;
}