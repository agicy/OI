#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e5+50;
const int MAXSQRTN=512;

int n,m;
int BLOCK_SIZE,Lg;
int bel[MAXN],S[MAXSQRTN][MAXSQRTN],top[MAXSQRTN],pos[MAXSQRTN];
ll a[MAXN];
ll h[MAXN],add[MAXSQRTN],del[MAXSQRTN];

#define Top S[x][top[x]]
#define sTop S[x][top[x]-1]
#define Max(x) S[x][pos[x]]

inline void remove(reg int x){
	for(reg int i=((x-1)<<Lg)|1;i<=(x<<Lg);++i)
		a[i]+=add[x]*i-del[x];
	add[x]=del[x]=pos[x]=top[x]=0;
	return;
}

inline void build(reg int x){
	memset(S[x],0,sizeof(S[x]));
	for(reg int i=((x-1)<<Lg)+1;i<=(x<<Lg);++i){
		while(top[x]>1&&(a[i]-a[Top])*(Top-sTop)>=(a[Top]-a[sTop])*(i-Top))
			--top[x];
		S[x][++top[x]]=i;
	}
	pos[x]=1;
	while(pos[x]<=top[x]&&a[S[x][pos[x]+1]]>=a[S[x][pos[x]]])
		++pos[x];
	return;
}

inline void update(reg int x){
	while(pos[x]<=top[x]){
		if(a[S[x][pos[x]+1]]+add[x]*S[x][pos[x]+1]<a[S[x][pos[x]]]+add[x]*S[x][pos[x]])
			break;
		++pos[x];
	}
	return;
}

inline void Init(void){
	if(1<=BLOCK_SIZE&&BLOCK_SIZE<2)
		BLOCK_SIZE=1,Lg=0;
	else if(2<=BLOCK_SIZE&&BLOCK_SIZE<4)
		BLOCK_SIZE=2,Lg=1;
	else if(4<=BLOCK_SIZE&&BLOCK_SIZE<8)
		BLOCK_SIZE=4,Lg=2;
	else if(8<=BLOCK_SIZE&&BLOCK_SIZE<16)
		BLOCK_SIZE=8,Lg=3;
	else if(16<=BLOCK_SIZE&&BLOCK_SIZE<32)
		BLOCK_SIZE=16,Lg=4;
	else if(32<=BLOCK_SIZE&&BLOCK_SIZE<64)
		BLOCK_SIZE=32,Lg=5;
	else if(64<=BLOCK_SIZE&&BLOCK_SIZE<128)
		BLOCK_SIZE=64,Lg=6;
	else if(128<=BLOCK_SIZE&&BLOCK_SIZE<256)
		BLOCK_SIZE=128,Lg=7;
	else if(256<=BLOCK_SIZE&&BLOCK_SIZE<512)
		BLOCK_SIZE=256,Lg=8;
	else if(512<=BLOCK_SIZE&&BLOCK_SIZE<1024)
		BLOCK_SIZE=512,Lg=9;
	return;
}

int main(void){
	n=read(),m=read();
	BLOCK_SIZE=sqrt(n);
	Init();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=n;++i)
		bel[i]=((i-1)>>Lg)+1;
	for(reg int i=1;i<=bel[n];++i)
		build(i);
	while(m--){
		static int type,l,r,t;
		type=read(),l=read(),r=read();
		switch(type){
			case 1:{
				reg ll begin=a[1]+add[1]-del[1];
				ll Max=begin;
				for(;bel[l]==bel[l-1]&&l<=r;l++)
					Max=max(Max,a[l]+add[bel[l]]*l-del[bel[l]]);
				for(;l+BLOCK_SIZE<=r;l+=BLOCK_SIZE)
					Max=max(Max,a[Max(bel[l])]+add[bel[l]]*Max(bel[l])-del[bel[l]]);
				for(;l<=r;++l)
					Max=max(Max,a[l]+add[bel[l]]*l-del[bel[l]]);
				printf("%lld\n",Max-begin);
				break;
			}
			case 2:{
				remove(bel[l]),remove(bel[r]);
				swap(a[l],a[r]);
				build(bel[l]),build(bel[r]);
				break;
			}
			case 3:{
				t=read();
				reg int tmp=l;
				for(;bel[l]==bel[l-1]&&l<=r;l++) a[l]+=(l-tmp+1)*t;
				remove(bel[l-1]),build(bel[l-1]);
				for(;l+BLOCK_SIZE<=r;l+=BLOCK_SIZE)
					add[bel[l]]+=t,del[bel[l]]+=(tmp-1)*t,update(bel[l]);
				for(;l<=r;++l)
					a[l]+=(l-tmp+1)*t;
				remove(bel[r]),build(bel[r]);
				break;
			}
		}
	}
	return 0;
}