#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const ll f[]={1,1,2,3,5,8,13,21,34,55,89,144,233,377,610,987,1597,2584,4181,6765,10946,17711,28657,46368,75025,121393,196418,317811,514229,832040,1346269,2178309,3524578,5702887,9227465,14930352,24157817,39088169,63245986,102334155,165580141,267914296,433494437,701408733,1134903170,1836311903,2971215073,4807526976,7778742049,12586269025,20365011074,32951280099,53316291173,86267571272,139583862445,225851433717,365435296162,591286729879,956722026041,1548008755920,2504730781961,4052739537881,6557470319842,10610209857723,17167680177565,27777890035288,44945570212853,72723460248141,117669030460994,190392490709135,308061521170129,498454011879264,806515533049393,1304969544928657,2111485077978050,3416454622906707,5527939700884757,8944394323791464,14472334024676221,23416728348467685,37889062373143906,61305790721611591,99194853094755497,160500643816367088,259695496911122585,420196140727489673,679891637638612258,1100087778366101931,1779979416004714189,2880067194370816120};
const int n=sizeof(f)/sizeof(ll);
vector<pair<ll,ll>/**/> g[n-2];

inline int getMax(reg ll a,reg ll b){
	reg int l=1,r=n-2,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(f[mid+1]<=a&&f[mid+2]<=b)
			l=mid+1;
		else
			r=mid;
	}
	return l;
}

inline int getCnt(const pair<ll,ll>& p,reg ll a,reg ll b){
	reg int res=0;
	if(p.second<=a&&p.first+p.second<=b)
		res=add(res,((b-p.first)/p.second)%mod);
	if(p.second<=b&&p.first+p.second<=a)
		res=add(res,((a-p.first)/p.second)%mod);
	return res;
}

int main(void){
	g[0].push_back(make_pair(0,1)),g[0].push_back(make_pair(0,2));
	for(reg int i=0;i<n-3;++i)
		for(pair<ll,ll> p:g[i]){
			ll x=p.first+p.second,y=p.second;
			while(x<=f[i+3]+f[i]){
				if(x>y)
					g[i+1].push_back(make_pair(y,x));
				x+=y;
			}
		}
	reg int q=read();
	while(q--){
		static ll a,b;
		a=readll(),b=readll();
		if(a>b)
			swap(a,b);
		reg int ans1=getMax(a,b),ans2=0;
		if(ans1==1)
			ans2=1ll*a*b%mod;
		else
			for(pair<ll,ll> p:g[ans1-1])
				ans2=add(ans2,getCnt(p,b,a));
		write(ans1),putchar(' '),write(ans2),putchar('\n');
	}
	flush();
	return 0;
}