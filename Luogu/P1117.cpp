#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s))*s=getchar();
	while(isalpha(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXS=3e4+5;
const int MAXLOG2S=15+1;

namespace SAs{
	const int MAXN=MAXS;
	int sa[MAXN],rk[MAXN],oldrk[MAXN<<1],id[MAXN],px[MAXN],cnt[MAXN];
	int ht[MAXN];
	inline bool cmp(reg int a,reg int b,reg int w){
		return oldrk[a]==oldrk[b]&&oldrk[a+w]==oldrk[b+w];
	}
	inline void buildsa(reg char s[],reg int n){
		memset(cnt,0,sizeof(cnt));
		memset(rk,0,sizeof(rk));
		int m=300;
		for(reg int i=1;i<=n;++i)
			++cnt[rk[i]=s[i]];
		for(reg int i=1;i<=m;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=n;i>=1;--i)
			sa[cnt[rk[i]]--]=i;
		for(reg int w=1,p,i;w<n;w<<=1,m=p){
			for(p=0,i=n;i>n-w;--i)
				id[++p]=i;
			for(i=1;i<=n;++i)
				if(sa[i]>w)
					id[++p]=sa[i]-w;
			memset(cnt,0,sizeof(cnt));
			for(i=1;i<=n;++i)
				++cnt[px[i]=rk[id[i]]];
			for(i=1;i<=m;++i)
				cnt[i]+=cnt[i-1];
			for(i=n;i>=1;--i)
				sa[cnt[px[i]]--]=id[i];
			memcpy(oldrk,rk,sizeof(rk));
			for(p=0,i=1;i<=n;++i)
				rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
		}
		for(reg int i=1,k=0;i<=n;++i){
			if(k)
				--k;
			while(s[i+k]==s[sa[rk[i]-1]+k])
				++k;
			ht[rk[i]]=k;
		}
		return;
	}
	int Lg[MAXN];
	int Min[MAXLOG2S][MAXN];
	inline void buildst(reg int a[],reg int n){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			Lg[i]=Lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Min[0][i]=a[i];
		for(reg int j=1;j<MAXLOG2S;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				Min[j][i]=min(Min[j-1][i],Min[j-1][i+(1<<(j-1))]);
		return;
	}
	inline int query(int l,int r){
		l=rk[l],r=rk[r];
		if(l>r)
			swap(l,r);
		++l;
		reg int k=Lg[r-l+1];
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
}

namespace SAt{
	const int MAXN=MAXS;
	int sa[MAXN],rk[MAXN],oldrk[MAXN<<1],id[MAXN],px[MAXN],cnt[MAXN];
	int ht[MAXN];
	inline bool cmp(reg int a,reg int b,reg int w){
		return oldrk[a]==oldrk[b]&&oldrk[a+w]==oldrk[b+w];
	}
	inline void buildsa(reg char s[],reg int n){
		memset(cnt,0,sizeof(cnt));
		memset(rk,0,sizeof(rk));
		int m=300;
		for(reg int i=1;i<=n;++i)
			++cnt[rk[i]=s[i]];
		for(reg int i=1;i<=m;++i)
			cnt[i]+=cnt[i-1];
		for(reg int i=n;i>=1;--i)
			sa[cnt[rk[i]]--]=i;
		for(reg int w=1,p,i;w<n;w<<=1,m=p){
			for(p=0,i=n;i>n-w;--i)
				id[++p]=i;
			for(i=1;i<=n;++i)
				if(sa[i]>w)
					id[++p]=sa[i]-w;
			memset(cnt,0,sizeof(cnt));
			for(i=1;i<=n;++i)
				++cnt[px[i]=rk[id[i]]];
			for(i=1;i<=m;++i)
				cnt[i]+=cnt[i-1];
			for(i=n;i>=1;--i)
				sa[cnt[px[i]]--]=id[i];
			memcpy(oldrk,rk,sizeof(rk));
			for(p=0,i=1;i<=n;++i)
				rk[sa[i]]=cmp(sa[i],sa[i-1],w)?p:++p;
		}
		for(reg int i=1,k=0;i<=n;++i){
			if(k)
				--k;
			while(s[i+k]==s[sa[rk[i]-1]+k])
				++k;
			ht[rk[i]]=k;
		}
		return;
	}
	int Lg[MAXN];
	int Min[MAXLOG2S][MAXN];
	inline void buildst(reg int a[],reg int n){
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i)
			Lg[i]=Lg[i>>1]+1;
		for(reg int i=1;i<=n;++i)
			Min[0][i]=a[i];
		for(reg int j=1;j<MAXLOG2S;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				Min[j][i]=min(Min[j-1][i],Min[j-1][i+(1<<(j-1))]);
		return;
	}
	inline int query(int l,int r){
		l=rk[l],r=rk[r];
		if(l>r)
			swap(l,r);
		++l;
		reg int k=Lg[r-l+1];
		return min(Min[k][l],Min[k][r-(1<<k)+1]);
	}
}

int n;
char s[MAXS],t[MAXS];
int a[MAXS],b[MAXS];

int main(void){
	reg int T=read();
	while(T--){
		memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
		read(s+1);
		reg int n=strlen(s+1);
		for(reg int i=1;i<=n;++i)
			t[i]=s[n-i+1];
		SAs::buildsa(s,n),SAs::buildst(SAs::ht,n);
		SAt::buildsa(t,n),SAt::buildst(SAt::ht,n);
		for(reg int len=1;(len<<1)<=n;++len){
			for(reg int i=len;i+len<=n+1;i+=len){
				reg int l=i,r=i+len,L=n-(r-1)+1,R=n-(l-1)+1;
				reg int lcp=SAs::query(l,r);
				lcp=min(lcp,len);
				reg int lcs=SAt::query(L,R);
				lcs=min(lcs,len-1);
				if(lcp+lcs>=len){
					++b[i-lcs],--b[i-lcs+(lcp+lcs-len+1)];
					++a[r+lcp-(lcp+lcs-len+1)],--a[r+lcp];
				}
			}
		}
		for(reg int i=1;i<=n;++i)
			a[i]+=a[i-1],b[i]+=b[i-1];
		reg ll ans=0;
		for(reg int i=1;i<n;++i)
			ans+=1ll*a[i]*b[i+1];
		printf("%lld\n",ans);
	}
	return 0;
}