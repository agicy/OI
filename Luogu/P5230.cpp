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

const int MAXN=1e3+5;
const int p=1e4+7;

int n;
char M[MAXN][MAXN];
int u[MAXN][MAXN],d[MAXN][MAXN];
ll dir[5][MAXN][MAXN];
int top,S[MAXN],wid[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		read(M[i]+1);
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			u[i][j]=(M[i][j]=='B')?u[i-1][j]+1:0;
	for(reg int i=n;i>=1;--i)
		for(reg int j=1;j<=n;++j)
			d[i][j]=(M[i][j]=='B')?d[i+1][j]+1:0;
	for(reg int i=1;i<=n;++i){
		reg int top=0;
		for(reg int j=n;j>=1;--j){
			if(u[i][j]>S[top]){
				S[++top]=u[i][j],wid[top]=1;
				dir[1][i][j]=dir[1][i][j+1]+u[i][j];
			}
			else{
				reg ll width=0,now=dir[1][i][j+1]+u[i][j];
				while(S[top]>u[i][j]){
					width+=wid[top];
					now-=wid[top]*(S[top]-u[i][j]);
					--top;
				}
				S[++top]=u[i][j],wid[top]=width+1;
				dir[1][i][j]=now;
			}
		}
	}
	for(reg int i=1;i<=n;++i){
		reg int top=0;
		for(reg int j=1;j<=n;++j){
			reg ll cnt=1,ans=dir[2][i][j-1]+u[i][j];
			while(top&&S[top]>u[i][j]){
				ans-=wid[top]*(S[top]-u[i][j]);
				cnt+=wid[top];
				--top;
			}
			if(!top||S[top]!=u[i][j])
				S[++top]=u[i][j],wid[top]=cnt;
			else
				wid[top]+=cnt;
			dir[2][i][j]=ans;
		}
	}
	for(reg int i=n;i>=1;--i){
		reg int top=0;
		for(reg int j=1;j<=n;++j){
			reg ll cnt=1,ans=dir[3][i][j-1]+d[i][j];
			while(top&&S[top]>d[i][j]){
				ans-=wid[top]*(S[top]-d[i][j]);
				cnt+=wid[top];
				--top;
			}
			if(!top||S[top]!=d[i][j])
				S[++top]=d[i][j],wid[top]=cnt;
			else
				wid[top]+=cnt;
			dir[3][i][j]=ans;
		}
	}
	for(reg int i=n;i>=1;--i){
		reg int top=0;
		for(reg int j=n;j>=1;--j){
			reg ll cnt=1,ans=dir[4][i][j+1]+d[i][j];
			while(top&&S[top]>d[i][j]){
				ans-=wid[top]*(S[top]-d[i][j]);
				cnt+=wid[top];
				--top;
			}
			if(!top||S[top]!=d[i][j])
				S[++top]=d[i][j],wid[top]=cnt;
			else
				wid[top]+=cnt;
			dir[4][i][j]=ans;
		}
	}
	for(reg int i=n;i>=1;--i)
		for(reg int j=n;j>=1;--j)
			if(dir[4][i][j]>0)
				dir[4][i][j]=dir[4][i][j]-1ll+dir[4][i+1][j]+dir[4][i][j+1]-dir[4][i+1][j+1];
			else
				dir[4][i][j]=(dir[4][i+1][j]+dir[4][i][j+1]-dir[4][i+1][j+1]);
	for(reg int i=n;i>=1;--i)
		for(reg int j=1;j<=n;++j)
			if(dir[3][i][j]>0)
				dir[3][i][j]=dir[3][i][j]-1ll+dir[3][i+1][j]+dir[3][i][j-1]-dir[3][i+1][j-1];
			else
				dir[3][i][j]=(dir[3][i+1][j]+dir[3][i][j-1]-dir[3][i+1][j-1]);
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(dir[2][i][j]>0)
				ans=(ans+1ll*(dir[2][i][j]-1ll)*(dir[4][1][j+1]+dir[4][i+1][1]-dir[4][i+1][j+1])%p)%p;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=n;++j)
			if(dir[1][i][j]>0)
				ans=(ans-1ll*(dir[1][i][j]-1ll)*(dir[3][i+1][j-1])%p+p)%p;
	printf("%d\n",ans);
	return 0;
}