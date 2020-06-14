#include<bits/stdc++.h>
using namespace std;
#define reg register

const int MAXN=1000+5;

char M[MAXN][MAXN];
int up[MAXN][MAXN];

inline bool check(reg char ch,reg char x){
	if(ch=='z')
		return true;
	else if(ch=='w')
		return x=='a'||x=='b';
	else if(ch=='x')
		return x=='b'||x=='c';
	else if(ch=='y')
		return x=='a'||x=='c';
	else
		return ch==x;
}

int n,m,ans;
int S[MAXN],w[MAXN];

inline void Solve(reg char x){
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=m;++j){
			up[i][j]=check(M[i][j],x)?up[i-1][j]+1:0;
		}
		up[i][m+1]=-1;
	}
	reg int top=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m+1;++j){
			reg int W=0;
			while(top&&S[top]>=up[i][j]){
				W+=w[top];
				ans=max(ans,S[top--]*W);
			}
			++W;
			S[++top]=up[i][j];
			w[top]=W;
		}
	return;
}

int main(void){
	while(scanf("%d%d",&n,&m)!=EOF){
		ans=0;
		for(reg int i=1;i<=n;++i)
			scanf("%s",M[i]+1);
		for(reg int i='a';i<='c';++i)
			Solve(i);
		printf("%d\n",ans);
	}
	return 0;
}