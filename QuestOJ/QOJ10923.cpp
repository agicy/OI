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
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=1e3+5;
const int MAXM=2e3+5;

int n,m;
int ans,flag;
bitset<MAXN> M[MAXM];

inline void Gauss(void){
	for(reg int i=1;i<=n;++i){
		reg int Max=i;
		for(reg int j=i+1;j<=m;++j)
			if(M[j][i]>M[Max][i])
				Max=j;
		if(!M[Max][i]){
			flag=true;
			return;
		}
		if(Max>ans)
			ans=Max;
		swap(M[i],M[Max]);
		for(reg int j=1;j<=m;++j)
			if(i!=j&&M[j][i])
				M[j]^=M[i];
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static char s[MAXN];
		read(s+1);
		for(reg int j=1;j<=n;++j)
			M[i][j]=(s[j]=='1');
		M[i][n+1]=read();
	}
	Gauss();
	if(flag)
		puts("Cannot Determine");
	else{
		printf("%d\n",ans);
		for(reg int i=1;i<=n;++i)
			puts(M[i][n+1]?"?y7M#":"Earth");
	}
	return 0 ;
}