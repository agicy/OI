#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=50+5;

char str[MAXN];
int n,len;
ll T[MAXN];
ll C[MAXN][MAXN];

inline ll Calc(void){
	reg ll res=1;
	reg int m=n;
	for(reg int i=0;i<=9;++i)
		if(T[i]){
			res*=C[m][T[i]];
			m-=T[i];
		}
	return res;
}

int main(void){
	scanf("%s",str+1);
	n=len=strlen(str+1);
	C[0][0]=1;
	for(reg int i=1;i<=len;++i){
		C[i][0]=1;
		for(reg int j=1;j<=i;++j)
			C[i][j]=C[i-1][j-1]+C[i-1][j];
	}
	for(reg int i=1;i<=len;++i)
		++T[str[i]-'0'];
	reg ll ans=0;
	for(reg int i=1;i<=len;++i){
		--n;
		for(reg int j=0;j<str[i]-'0';++j)
			if(T[j]){
				--T[j];
				ans+=Calc();
				++T[j];
			}
		--T[str[i]-'0'];
	}
	printf("%lld\n",ans);
	return 0;
}
