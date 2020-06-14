#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2000+5;
const int MAXM=2000+5;

int n,m;
int top,S[MAXN];
int l[MAXM],r[MAXM],h[MAXM];

inline ll Solve(void){
	for(reg int i=m;i>=1;--i){
		while(top!=0&&h[i]<=h[S[top]])
			l[S[top--]]=i;
		S[++top]=i;
	}
	while(top)
		l[S[top--]]=0;
	for(reg int i=1;i<=m;++i){
		while(top!=0&&h[i]<h[S[top]])
			r[S[top--]]=i;
		S[++top]=i;
	}
	while(top)
		r[S[top--]]=m+1;
	reg ll sum=0;
	for(reg int i=1;i<=m;++i)
		sum+=(ll)(i-l[i])*(r[i]-i)*h[i];
	return sum;
}

char M[MAXN][MAXM];

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		scanf("%s",M[i]+1);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=m;++j){
				++h[j];
				if(M[i][j]=='*')
					h[j]=0;
			}
		ans+=Solve();
	}
	printf("%lld\n",ans);
	return 0;
}