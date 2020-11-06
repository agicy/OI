#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

struct querys{
	int id,len,cnt;
	inline querys(reg int id=0,reg int len=0,reg int cnt=0):id(id),len(len),cnt(cnt){
		return;
	}
	inline bool operator<(const querys& a)const{
		return len<a.len;
	}
};

const int MAXN=2e5+5;
const int MAXQ=2e5+5;

int n,Q;
char str[MAXN];
int sum[MAXN];
querys q[MAXQ];
int ans[MAXQ];
int T[MAXN];

inline void solve(reg int len){
	for(reg int i=1;i+len-1<=n;++i)
		++T[sum[i+len-1]-sum[i-1]];
	return;
}

int main(void){
	freopen("similar.in","r",stdin);
	freopen("similar.out","w",stdout);

	scanf("%s",str+1);
	n=strlen(str+1);
	for(reg int i=1;i<=n;++i)
		sum[i]=sum[i-1]+(str[i]^'0');
	Q=read();
	for(reg int i=1;i<=Q;++i){
		static char t[MAXN];
		scanf("%s",t+1);
		reg int l=strlen(t+1);
		reg int s=0;
		for(reg int j=1;j<=l;++j)
			s+=(t[j]^'0');
		q[i]=querys(i,l,s);
	}
	sort(q+1,q+Q+1);
	for(reg int l=1,r;l<=Q;l=r+1){
		r=l;
		while(r<=n&&q[r+1].len==q[l].len)
			++r;
		solve(q[l].len);
		for(reg int i=l;i<=r;++i)
			ans[q[i].id]=T[q[i].cnt];
		for(reg int i=0;i<=q[l].len;++i)
			T[i]=0;
	}
	for(reg int i=1;i<=Q;++i)
		printf("%d\n",ans[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}