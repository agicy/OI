#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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
	while(isspace(*s))*s=getchar();
	while(!isspace(*s))*(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=50+5;

int n,A,B;
int Max[MAXN][MAXN],Min[MAXN][MAXN];

int main(void){
	n=read(),A=read(),B=read();
	for(reg int i=1;i<=n;++i){
		static char M[MAXN];
		read(M+1);
		for(reg int j=1;j<=n;++j)
			switch(M[j]){
				case '+':{
					Max[i][j]=2,Min[i][j]=1;
					break;
				}
				case '-':{
					Max[i][j]=-1,Min[i][j]=-2;
					break;
				}
				case '=':{
					Max[i][j]=Min[i][j]=0;
					break;
				}
				case '?':{
					if(i==j)
						Max[i][j]=Min[i][j]=0;
					else
						Max[i][j]=2,Min[i][j]=-2;
					break;
				}
			}
	}
	for(reg int k=1;k<=n;++k)
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j)
				if(k!=i&&k!=j&&i!=j){
					Max[i][j]=min(Max[i][j],Max[i][k]+Max[k][j]);
					Min[i][j]=max(Min[i][j],Min[i][k]+Min[k][j]);
				}
	reg int ans1=0,ans2=0,ans3=0;
	for(reg int i=1;i<=n;++i)
		if(i!=A&&i!=B)
			for(reg int j=1;j<i;++j)
				if(j!=A&&j!=B){
					if(Min[A][i]>Max[j][B]||Min[B][i]>Max[j][A])
						++ans1;
					if((Min[A][i]==Max[A][i]&&Min[j][B]==Max[j][B]&&Min[A][i]==Min[j][B])||(Min[A][j]==Max[A][j]&&Min[i][B]==Max[i][B]&&Min[A][j]==Min[i][B]))
						++ans2;
					if(Min[i][A]>Max[B][j]||Min[i][B]>Max[A][j])
						++ans3;
				}
	printf("%d %d %d\n",ans1,ans2,ans3);
	return 0;
}