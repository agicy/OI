#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=26;
const int MAXM=2e3+5;

int m,n;
char s[MAXM];
int cost[MAXN][2];
int f[MAXM][MAXM];

int main(void){
	n=read(),m=read(),read(s+1);
	for(reg int i=1;i<=n;++i){
		static char ch;
		static int a,b;
		do
			ch=getchar();
		while(!isalpha(ch));
		a=read(),b=read();
		cost[ch-'a'][0]=a,cost[ch-'a'][1]=b;
	}
	memset(f,0x3f,sizeof(f));
	for(reg int i=1;i<=m;++i)
		f[i][i]=0;
	for(reg int len=2;len<=m;++len)
		for(reg int l=1;l+len-1<=m;++l){
			reg int r=l+len-1;
			f[l][r]=min(f[l+1][r]+min(cost[s[l]-'a'][0],cost[s[l]-'a'][1]),f[l][r-1]+min(cost[s[r]-'a'][0],cost[s[r]-'a'][1]));
			if(s[l]==s[r]){
				if(r-l==1)
					f[l][r]=0;
				else
					f[l][r]=min(f[l][r],f[l+1][r-1]);
			}
		}
	printf("%d\n",f[1][m]);
	return 0;
}