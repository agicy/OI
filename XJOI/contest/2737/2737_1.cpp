#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline uint32_t read_uint32(void){
	reg char ch=getchar();
	reg uint32_t res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline uint64_t read_uint64(void){
	reg char ch=getchar();
	reg uint64_t res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=5e5;
const int MAXW=60;

uint32_t n,w;
uint64_t a[MAXN];
uint64_t tag[MAXN];

bool ed;

int main(void){
	reg uint32_t t=read_uint32();
	while(t--){
		n=read_uint32(),w=read_uint32();
		for(reg uint32_t i=0;i<n;++i)
			a[i]=read_uint64(),tag[i]=(1ull<<(w+1))-1;
		reg uint64_t ans=(1ull<<w)-1;
		for(reg int i=w-1;i>=0;--i){
			static uint32_t cnt[MAXW+1];
			static uint64_t tmp[MAXN];
			for(reg uint32_t j=0;j<n;++j)
				tmp[j]=tag[j]&(~(a[j]>>i)),++cnt[__builtin_ffsll(tmp[j])-1];
			reg uint32_t lim=0;
			for(reg int j=w;j>=0;--j)
				lim=(lim>>1)+cnt[j],cnt[j]=0;
			if(lim){
				ans^=1ull<<i;
				for(reg uint32_t j=0;j<n;++j)
					tag[j]=tmp[j];
			}
		}
		printf("%lu\n",ans);
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}