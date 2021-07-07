#include<bits/stdc++.h>
#include <numeric>
using namespace std;
#define reg register
typedef long long ll;
#define int ll

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(!x) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e5+5;
const int mod=1e9+7;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct Interval{
	int l,r;
	inline bool operator<(const Interval& a)const{
		return r<a.r;
	}
	inline bool contain(reg int x)const{
		return l<=x&&x<=r;
	}
};

struct Skill{
	Interval inv;
	int w;
	inline bool operator<(const Skill& a)const{
		return inv<a.inv;
	}
};

int n,q;
set<Skill> S;

bool ed;

signed main(void){
	n=read(),q=read();
	reg int lastans=0;
	while(q--){
		switch(read()){
			case 1:{
				Skill tmp;
				tmp.inv.l=read()^lastans,tmp.inv.r=read()^lastans,tmp.w=read();
				S.insert(tmp);
				break;
			}
			case 2:{
				static int k,s[MAXN];
				k=read();
				for(reg int i=1;i<=k;++i)
					s[i]=read()^lastans;
				sort(s+1,s+k+1);
				static ll f[MAXN];
				fill(f+1,f+k+1,inf);
				f[0]=0;
				for(reg int i=1;i<=k;++i)
					for(set<Skill>::iterator it=S.begin();it!=S.end();++it)
						if((it->inv).contain(s[i])){
							reg int pos=lower_bound(s+1,s+k+1,(it->inv).l)-s-1;
							f[i]=min(f[i],f[pos]+(it->w));
						}
				printf("%lld\n",f[k]==inf?0:f[k]);
				lastans=(f[k]==inf?0:f[k])%mod;
			}
		}
	}
	return 0;
}