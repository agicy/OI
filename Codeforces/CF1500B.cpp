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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;
const int MAXV=2*MAXN;

int n,m;
ll k;
int A[MAXN],B[MAXM];
int d;
int val[MAXV];
int pos[MAXV];

inline int gcd(reg int a,reg int b){
	return b?gcd(b,a%b):a;
}

int main(void){
	n=read(),m=read(),k=readll()-1;
	for(reg int i=0;i<n;++i)
		A[i]=read();
	for(reg int i=0;i<m;++i)
		B[i]=read();
	if(n>m)
		swap(n,m),swap(A,B);
	d=gcd(n,m);
	reg ll lcm=1ll*n*m/d;
	memset(pos,-1,sizeof(pos));
	for(reg int i=0;i<n;++i)
		pos[A[i]]=i;
	for(reg int i=0;i<m;++i){
		if(pos[B[i]]==-1)
			continue;
		reg int p=i-pos[B[i]];
		if(p<0)
			p+=m;
		--val[p];
	}
	for(reg int i=0;i<m;++i)
		val[i]+=n;
	reg ll sum=0;
	for(reg int i=0;i<m/d;++i)
		sum+=val[1ll*i*n%m];
	reg ll ans=lcm*(k/sum);
	k%=sum;
	for(reg int i=0;i<m;++i){
		reg int pos=1ll*i*n%m;
		if(val[pos]<=k){
			k-=val[pos];
			ans+=n;
		}
		else
			break;
	}
	while(true){
		if(A[ans%n]!=B[ans%m]){
			if(!k){
				printf("%lld\n",ans+1);
				break;
			}
			--k;
		}
		++ans;
	}
	return 0;
}