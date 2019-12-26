#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F

const int MAXN=1000+5;
const int MAXM=1000+5;

int n,m;
bool M[MAXN][MAXM];

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			static char ch;
			cin>>ch;
			M[i][j]=(ch=='F');
		}
	return;
}

int sum[MAXN][MAXM];
int S[MAXM],w[MAXM];

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(M[i][j])
				sum[i][j]=sum[i-1][j]+1;
			else
				sum[i][j]=0;
	for(reg int i=1;i<=n;++i)
		sum[i][m+1]=0;
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		reg int top=0,Max=0;
		for(reg int j=1;j<=m+1;++j)
			if(S[top]<sum[i][j])
				S[++top]=sum[i][j],w[top]=1;
			else{
				reg int width=0;
				while(top&&S[top]>sum[i][j]){
					width+=w[top];
					Max=max((int)Max,width*S[top]);
					--top;
				}
				S[++top]=sum[i][j],w[top]=width+1;
			}
		ans=max((int)ans,(int)Max);
	}
	printf("%d\n",ans*3);
	return;
}
