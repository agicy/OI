#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const ull base=1331;

int n,q;
char s[MAXN];
int sum[MAXN];
ull basep[MAXN];
ull Hash[MAXN],H[MAXN];

inline ull getHash(reg int l,reg int r){
	return Hash[r]-Hash[l-1]*basep[r-l+1];
}

inline ull getH(reg int l,reg int r){
	return H[r]-H[l-1]*basep[r-l+1];
}

int main(void){
	scanf("%s%d",s+1,&q);
	n=strlen(s+1);
	basep[0]=1;
	for(reg int i=1;i<=n;++i){
		basep[i]=basep[i-1]*base;
		Hash[i]=Hash[i-1]*base+(s[i]-'0'+1);
	}
	while(q--){
		static char t[MAXN];
		static int L,R;
		scanf("%s%d%d",t+1,&L,&R);
		reg int len=strlen(t+1);
		for(reg int i=1;i<=len;++i){
			sum[i]=sum[i-1]+(t[i]-'0');
			H[i]=H[i-1]*base+(t[i]-'0'+1);
		}
		reg int ans=0;
		for(reg int i=1,l,r,mid,st,ed;i<=len;++i){
			if(t[i]-'0'>R)
				continue;
			if(sum[len]-sum[i-1]<L)
				continue;
			l=i,r=len;
			while(l<r){
				mid=(l+r)>>1;
				if(sum[mid]-sum[i-1]>=L)
					r=mid;
				else
					l=mid+1;
			}
			st=l;
			l=i,r=len;
			while(l<r){
				mid=(l+r)>>1;
				if(sum[mid+1]-sum[i-1]>R)
					r=mid;
				else
					l=mid+1;
			}
			ed=l;
			for(reg int j=st;j<=ed;++j){
				reg int len=j-i+1;
				reg bool f=false;
				for(reg int k=1;k+len-1<=n;++k)
					if(getHash(k,k+len-1)==getH(i,j)){
						f=true;
						break;
					}
				if(f)
					++ans;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}