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

const int MAXNM=1.6e3+5;

int m,n,mn;
bitset<MAXNM> G[MAXNM];
bool ans[MAXNM];

inline void Gauss(void){
	for(reg int i=1;i<=mn;++i){
		reg int Max=i;
		while(Max<=mn&&!G[Max][i])
			++Max;
		if(Max>mn){
			G[i][mn+1]=true;
			for(reg int j=i+1;j<=mn;++j)
				G[i][j]=false;
			for(reg int j=i+1;j<=mn;++j)
				if(G[j][i])
					G[j].flip(mn+1);
			continue;
		}
		if(Max!=i)
			swap(G[i],G[Max]);
		for(reg int j=1;j<=mn;++j)
			if(i!=j&&G[j][i])
				G[j]^=G[i];
	}
	return;
}

int main(void){
	m=read(),n=read();
	mn=m*n;
	for(reg int i=1,id=0;i<=m;++i)
		for(reg int j=1;j<=n;++j){
			++id;
			G[id][id]=true;
			const int dx[]={-1,0,0,1};
			const int dy[]={0,-1,1,0};
			const int dId[]={-n,-1,1,n};
			for(reg int k=0;k<4;++k){
				reg int fx=i+dx[k],fy=j+dy[k];
				if(1<=fx&&fx<=m&&1<=fy&&fy<=n)
					G[id][id+dId[k]]=true;
			}
		}
	Gauss();
	for(reg int i=mn;i>=1;--i){
		ans[i]=G[i][mn+1];
		for(reg int j=i+1;j<=mn;++j)
			if(G[i][j])
				ans[i]^=ans[j];
	}
	for(reg int i=1,id=0;i<=m;++i)
		for(reg int j=1;j<=n;++j)
			printf("%d%c",ans[++id],j==n?'\n':' ');
	return 0;
}