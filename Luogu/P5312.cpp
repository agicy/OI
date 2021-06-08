#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
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

const int MAXN=1e5+5;
const int MAXM=1e5+5;
const int MAXLOG2A=30;

int n;
int tXor;
int a[MAXN+MAXM];
int sum[MAXN+MAXM][MAXLOG2A];
int lim,tag[MAXLOG2A];

namespace Trie{
	const int MAXSIZE=(MAXN+MAXM)*15;
	struct Node{
		int ch[2];
		int siz;
		int sum[MAXLOG2A];
		#define ch(x) unit[(x)].ch
		#define siz(x) unit[(x)].siz
		#define sum(x) unit[(x)].sum
	};
	const int rt=0;
	int tot;
	Node unit[MAXSIZE];
	inline void insert(reg int x){
		reg int p=rt;
		for(reg int i=MAXLOG2A-1;i>=0;--i){
			reg int c=(x>>i)&1;
			if(!ch(p)[c])
				ch(p)[c]=++tot;
			p=ch(p)[c];
			++siz(p);
			for(reg int j=0;j<MAXLOG2A;++j)
				sum(p)[j]+=(x>>j)&1;
		}
		return;
	}
	inline ll query(reg int k){
		if(!k)
			return 0;
		reg int p=rt,val=0;
		reg ll res=0;
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if(k<=siz(ch(p)[tag[i]]))
				p=ch(p)[tag[i]],val|=tag[i]<<i;
			else{
				reg int x=siz(ch(p)[tag[i]]);
				k-=x;
				for(reg int j=0;j<MAXLOG2A;++j){
					reg int cnt=sum(ch(p)[tag[i]])[j];
					if((tXor>>j)&1)
						res+=(1ll*(x-cnt))<<j;
					else
						res+=(1ll*cnt)<<j;
				}
				p=ch(p)[tag[i]^1],val|=(tag[i]^1)<<i;
			}
		return res+1ll*(val^tXor)*k;
	}
	#undef ch
	#undef siz
	#undef sum
}

inline ll getSum(reg int l,reg int r){
	reg int len=r-l+1;
	reg ll res=0;
	for(reg int i=0;i<MAXLOG2A;++i){
		reg int cnt=sum[r][i]-sum[l-1][i];
		if((tXor>>i)&1)
			res+=(1ll*(len-cnt))<<i;
		else
			res+=(1ll*cnt)<<i;
	}
	return res;
}

inline void sort(void){
	for(reg int i=0;i<MAXLOG2A;++i)
		tag[i]=(tXor>>i)&1;
	return;
}

inline ll query(reg int l,reg int r){
	if(r<=lim)
		return Trie::query(r)-Trie::query(l-1);
	else if(l>lim)
		return getSum(l,r);
	else
		return Trie::query(lim)-Trie::query(l-1)+getSum(lim+1,r);
}

bool ed;

int main(void){
	n=read();
	lim=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		for(reg int j=0;j<MAXLOG2A;++j)
			sum[i][j]=sum[i-1][j]+((a[i]>>j)&1);
	}
	reg int m=read();
	while(m--){
		static int opt,l,r;
		opt=read();
		switch(opt){
			case 1:{
				a[++n]=read()^tXor;
				for(reg int j=0;j<MAXLOG2A;++j)
					sum[n][j]=sum[n-1][j]+((a[n]>>j)&1);
				break;
			}
			case 2:{
				l=read(),r=read();
				writeln(query(l,r));
				break;
			}
			case 3:{
				tXor^=read();
				break;
			}
			case 4:{
				for(reg int i=lim+1;i<=n;++i)
					Trie::insert(a[i]);
				lim=n;
				sort();
				fill(sum[n],sum[n]+MAXLOG2A,0);
				break;
			}
		}
	}
	flush();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}