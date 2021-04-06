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

const int prime[]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149};
const int tot=sizeof(prime)/sizeof(int);

int n;
int T[tot];

int main(void){
	n=read();
	if(n==1){
		if(read())
			puts("0");
		else
			puts("1");
	}
	else{
		for(reg int i=1;i<=n-2;++i){
			reg int tmp=i;
			if(tmp>1)
				for(reg int j=0;j<tot;++j)
					while(!(tmp%prime[j]))
						++T[j],tmp/=prime[j];
		}
		reg int sumd=0;
		for(reg int i=1;i<=n;++i){
			reg int x=read()-1;
			if(!(x+1)){
				puts("0");
				return 0;
			}
			sumd+=x+1;
			for(reg int k=2;k<=x;++k){
				reg int tmp=k;
				for(reg int j=0;j<tot;++j)
					while(!(tmp%prime[j]))
						--T[j],tmp/=prime[j];
			}
		}
		reg ll ans=1;
		for(reg int i=0;i<tot;++i)
			if(T[i]<0)
				ans=0;
			else{
				reg ll res=1,x=prime[i];
				while(T[i]){
					if(T[i]&1)
						res*=x;
					x*=x;
					T[i]>>=1;
				}
				ans*=res;
			}
		if(sumd==(n-1)<<1)
			printf("%lld\n",ans);
		else
			puts("0");
	}
	return 0;
}