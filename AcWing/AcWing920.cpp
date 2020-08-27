#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXSIZE=1048576;
const int MAXN=500+5;

int m,n;
int f[MAXN][MAXN];

int main(void){
	scanf("%d%d\n",&m,&n);
	memset(f,0x3f,sizeof(f));
	for(reg int i=1;i<=n;++i)
		f[i][i]=0;
	for(reg int i=1;i<=m;++i){
		static char s[MAXSIZE];
		cin.getline(s,MAXSIZE,'\n');
		reg int len=strlen(s);
		reg int tmp=0,tot=0;
		static int S[MAXN];
		for(reg int j=0;j<=len;++j)
			if('0'<=s[j]&&s[j]<='9')
				tmp=10*tmp+s[j]-'0';
			else{
				S[++tot]=tmp;
				tmp=0;
			}
		for(reg int j=1;j<=tot;++j)
			for(reg int k=j+1;k<=tot;++k)
				f[S[j]][S[k]]=1;
	}
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				f[i][j]=min(f[i][j],f[i][k]+f[k][j]);
	if(f[1][n]==0x3f3f3f3f)
		puts("NO");
	else
		printf("%d\n",f[1][n]-1);
	return 0;
}