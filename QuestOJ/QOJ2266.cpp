#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXS=26;

int n,m;
char s[MAXN];
ull sum[MAXN][MAXS];
ull basep[MAXN];

int main(void){
	n=read(),m=read();
	scanf("%s",s+1);
	for(reg int i=1;i<=n;++i){
		for(reg int j=0;j<MAXS;++j)
			sum[i][j]=(sum[i-1][j]*3);
		++sum[i][s[i]-'a'];
	}
	basep[0]=1;
	for(reg int i=1;i<=n;++i)
		basep[i]=basep[i-1]*3;
	while(m--){
		static int x,y,z;
		x=read(),y=read(),z=read();
		static int S1[MAXS],S2[MAXS];
		for(reg int i=0;i<MAXS;++i)
			S1[i]=sum[x+z-1][i]-sum[x-1][i]*basep[z];
		for(reg int i=0;i<MAXS;++i)
			S2[i]=sum[y+z-1][i]-sum[y-1][i]*basep[z];
		sort(S1,S1+MAXS),sort(S2,S2+MAXS);
		reg bool flag=true;
		for(reg int i=0;i<MAXS;++i)
			if(S1[i]!=S2[i]){
				flag=false;
				break;
			}
		puts(flag?"YES":"NO");
	}
	return 0;
}