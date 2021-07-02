#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXL=102;
const int LIMIT=2550+1;

int n,lim;
bitset<LIMIT> b[MAXL+1];

bool ed;

int main(void){
	n=read(),lim=read();
	bitset<LIMIT> f;
	f[0]=true;
	for(reg int i=1;i<=n;++i){
		static int p,l;
		p=read(),l=read();
		for(reg int j=0;j<=l;++j)
			b[j].reset();
		b[0][0]=true;
		for(reg int j=1;j<=p;++j){
			static int e,c;
			e=read(),c=read();
			if(j>=l){
				static bitset<LIMIT> tmp;
				tmp=b[l]<<e;
				for(reg int S=c-1;S;S^=lowbit(S))
					tmp|=tmp<<(e*lowbit(S));
				b[l]|=tmp;
			}
			for(reg int pos=min(j,l);pos>=1;--pos){
				static bitset<LIMIT> tmp;
				tmp=b[pos-1]<<e;
				for(reg int S=c-1;S;S^=lowbit(S))
					tmp|=tmp<<(e*lowbit(S));
				b[pos]|=tmp;
			}
		}
		static bitset<LIMIT> tmp;
		tmp.reset();
		for(reg int j=b[l]._Find_first();j!=(int)b[l].size()&&j<=lim;j=b[l]._Find_next(j))
			tmp|=f<<j;
		f=tmp;
	}
	reg int ans=0;
	for(reg int i=0;i<=lim;++i)
		ans+=f[i];
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}