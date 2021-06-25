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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const ll inf=0x3f3f3f3f3f3f3f3f;

int n;
vector<pair<ll,char> > V;

int main(void){
	n=read();
	V.resize(n<<1);
	reg int r=0,g=0,b=0;
	for(reg int i=0;i<(n<<1);++i){
		V[i].first=readll();
		do
			V[i].second=getchar();
		while(!isalpha(V[i].second));
		switch(V[i].second){
			case 'R':++r;break;
			case 'G':++g;break;
			case 'B':++b;break;
		}
	}
	if((r&1)||(g&1)||(b&1)){
		sort(V.begin(),V.end());
		reg ll Minrg=inf,Mingb=inf,Minbr=inf;
		for(reg int i=0,siz=V.size();i<siz-1;++i){
			reg char nxt=V[i+1].second,now=V[i].second;
			reg ll dif=V[i+1].first-V[i].first;
			if((now=='R'&&nxt=='G')||(now=='G'&&nxt=='R'))
				Minrg=min(Minrg,dif);
			else if((now=='G'&&nxt=='B')||(now=='B'&&nxt=='G'))
				Mingb=min(Mingb,dif);
			else if((now=='B'&&nxt=='R')||(now=='R'&&nxt=='B'))
				Minbr=min(Minbr,dif);
		}
		reg ll ans;
		if((r&1)&&(g&1))
			ans=min(Minrg,Mingb+Minbr);
		else if((g&1)&&(b&1))
			ans=min(Mingb,Minbr+Minrg);
		else
			ans=min(Minbr,Minrg+Mingb);
		printf("%lld\n",ans);
	}
	else
		puts("0");
}