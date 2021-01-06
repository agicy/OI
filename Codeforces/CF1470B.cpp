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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=3e5+5;
const int MAXA=1e6+5;

int n;
bool vis[MAXA];
int tot,prime[MAXA];
int cnt,pr2[MAXA];
vector<int> V;
unordered_map<int,int> M;

inline void Init(reg int n){
	for(reg int i=2;i<=n;++i){
		if(!vis[i])
			prime[++tot]=i;
		for(reg int j=1;j<=tot&&i*prime[j]<=n;++j){
			vis[i*prime[j]]=true;
			if(i%prime[j]==0)
				break;
		}
	}
	for(reg int i=1;i<=tot;++i)
		if(1ll*prime[i]*prime[i]<=n)
			pr2[++cnt]=prime[i]*prime[i];
		else
			break;
	return;
}

int main(void){
	Init(1e6);
	reg int t=read();
	while(t--){
		M.clear();
		n=read();
		V.resize(n);
		int ans0=0,ans1=0;
		for(reg int i=1,a;i<=n;++i){
			a=read();
			for(reg int j=1;j<=cnt&&pr2[j]<=a;++j)
				while(a%pr2[j]==0)
					a/=pr2[j];
			V[i-1]=a;
			++M[a];
			ans0=max(ans0,M[a]);
		}
		for(vector<int>::iterator it=V.begin();it!=V.end();++it)
			if(*it==1||!(M[*it]&1))
				++ans1;
		reg int q=read();
		while(q--){
			static ll w;
			w=readll();
			printf("%d\n",!w?ans0:max(ans0,ans1));
		}
	}
	return 0;
}