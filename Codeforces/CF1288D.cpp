#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=300000+5;
const int MAXM=8+5;

int n,m,a[MAXN][MAXM];
pair<int,int> ans;

inline bool check(reg int mid){
	static int f[MAXN],rank[1<<MAXM];
	memset(rank,0,sizeof(rank));
	reg int p=(1<<m)-1;
	for(reg int i=1;i<=n;++i){
		f[i]=0;
		for(reg int j=1;j<=m;++j)
			if(a[i][j]>=mid)
				f[i]+=1<<(j-1);
		rank[f[i]]=i;
	}
	for(reg int i=1;i<=n;++i)
		for(reg int j=0;j<(1<<m);++j)
			if(rank[j]&&(f[i]|j)==p){
				ans=make_pair(i,rank[j]);
				return true;
			}
	return false;
}

int main(void){
	n=read(),m=read();
	int Max=-INF,Min=INF;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			a[i][j]=read();
			Max=max(Max,a[i][j]);
			Min=min(Min,a[i][j]);
		}
	reg int l=Min,r=Max,mid;
	while(l<=r){
		mid=(l+r)>>1;
		if(check(mid))
			l=mid+1;
		else
			r=mid-1;
	}
	printf("%d %d\n",ans.first,ans.second);
	return 0;
}
