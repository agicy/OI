#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

int T;
ll n,a,b;

pair<ll,ll> Solve(reg ll,reg ll);

int main(void){
	T=read();
	while(T--){
		n=read(),a=read(),b=read();
		pair<ll,ll> A=Solve(n,a-1);
		pair<ll,ll> B=Solve(n,b-1);
		ll dx=A.first-B.first;
		ll dy=A.second-B.second;
		printf("%.0f\n",sqrt(dx*dx+dy*dy)*10);
	}
	return 0;
}

pair<ll,ll> Solve(reg ll n,reg ll a){
	if(n==0)
		return make_pair(0,0);
	ll cnt=1ll<<(2*n-2),len=1ll<<(n-1);
	pair<ll,ll> pos=Solve(n-1,a%cnt);
	ll x=pos.first,y=pos.second;
	ll z=a/cnt;
	if(z==0)
		return make_pair(y,x);
	else if(z==1)
		return make_pair(x,y+len);
	else if(z==2)
		return make_pair(x+len,y+len);
	else
		return make_pair(2*len-y-1,len-x-1);
}