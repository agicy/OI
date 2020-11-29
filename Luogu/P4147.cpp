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

inline void cMax(reg int& a,reg int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e3+5;
const int MAXM=1e3+5;

int n,m;
char M[MAXN][MAXM];
int up[MAXM];
pair<int,int> S[MAXN];

inline int calc(void){
	int res=0;
	reg int top=0;
	for(reg int i=1;i<=m+1;++i)
		if(!top||up[i]>S[top].first)
			S[++top]=make_pair(up[i],1);
		else{
			reg int w=0;
			while(top&&S[top].first>up[i]){
				w+=S[top].second;
				cMax(res,w*S[top].first);
				--top;
			}
			S[++top]=make_pair(up[i],w+1);
		}
	return res;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			do
				M[i][j]=getchar();
			while(!isalpha(M[i][j]));
	int ans=0;
	for(reg int i=1;i<=n;++i){
		for(reg int j=1;j<=m;++j)
			if(M[i][j]=='F')
				++up[j];
			else
				up[j]=0;
		cMax(ans,calc());
	}
	printf("%d\n",ans*3);
	return 0;
}