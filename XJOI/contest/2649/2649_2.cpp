#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s)) *s=getchar();
	while(isdigit(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

const int MAXN=300+5;
const int MAXQ=MAXN;

int n;
char r[MAXN][MAXN];
char b[MAXN][MAXN];
int q;
int k[MAXQ];

namespace Subtask1{
	const int MAXN=18;
	bool f[2][1<<MAXN][MAXN+1];
	vector<int> Gr[MAXN],Gb[MAXN];
	inline void Solve(void){
		for(reg int i=0;i<n;++i)
			for(int j=0;j<n;++j){
				if(r[i][j]=='1')
					Gr[i].push_back(j);
				if(b[i][j]=='1')
					Gb[i].push_back(j);
			}
		f[0][0][0]=1;
		for(reg int i=0;i<n;++i){
			for(reg int S=0;S<(1<<n);++S)
				for(reg int j=0;j<=i+1;++j)
					f[(i+1)&1][S][j]=0;
			for(reg int S=0;S<(1<<n);++S)
				for(reg int j=0;j<=i;++j)
					if(f[i&1][S][j]){
						for(int v:Gr[i])
							if(!((S>>v)&1))
								f[(i+1)&1][S|(1<<v)][j+1]^=f[i&1][S][j];
						for(int v:Gb[i])
							if(!((S>>v)&1))
								f[(i+1)&1][S|(1<<v)][j]^=f[i&1][S][j];
					}
		}
		for(reg int i=1;i<=q;++i)
			printf("%d\n",f[n&1][(1<<n)-1][k[i]]);
		return;
	}
}

namespace Subtask2check{
	inline bool Solve(void){
		for(reg int i=1;i<=q;++i)
			if(k[i]!=0&&k[i]!=n)
				return false;
		return true;
	}
}

inline bool Gauss(bitset<MAXN> G[MAXN]){
	reg bool res=1;
	for(reg int i=0;i<n;++i){
		reg int Max=-1;
		for(reg int j=i;j<n;++j)
			if(G[j][i])
				Max=j;
		if(Max==-1)
			return 0;
		swap(G[i],G[Max]);
		res=res&&G[i][i];
		for(reg int j=0;j<n;++j)
			if(i!=j&&G[j][i])
				G[j]^=G[i];
	}
	return res;
}

namespace Subtask2{
	bitset<MAXN> Gr[MAXN],Gb[MAXN];
	inline void Solve(void){
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j){
				Gr[i][j]=r[i][j]-'0';
				Gb[i][j]=b[i][j]-'0';
			}
		reg int ansr=Gauss(Gr),ansb=Gauss(Gb);
		for(reg int i=1;i<=q;++i){
			if(k[i]==0)
				printf("%d\n",ansb);
			else
				printf("%d\n",ansr);
		}
		return;
	}
}

namespace Subtask3check{
	inline bool Solve(void){
		reg int cnt=0;
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j)
				if(r[i][j]=='1')
					++cnt;
		return cnt<=10;
	}
}

namespace Subtask3{
	bitset<MAXN> Gb[MAXN];
	int tot;
	pair<int,int> pos[MAXN*MAXN];
	inline int binom(reg int n,reg int m){
		if(m<0||n<m)
			return 0;
		else
			return ((n&m)==m);
	}
	int val[MAXN];
	int ans[MAXN];
	bool del_l[MAXN],del_r[MAXN];
	inline void Solve(void){
		for(int i=0;i<n;++i)
			for(int j=0;j<n;++j)
				if(r[i][j]=='1')
					pos[tot++]=make_pair(i,j);
		for(reg int S=0;S<(1<<tot);++S){
			for(reg int i=0;i<tot;++i)
				if((S>>i)&1)
					del_l[pos[i].first]=del_r[pos[i].second]=true;
			for(reg int i=0;i<n;++i)
				for(reg int j=0;j<n;++j)
					if(!del_l[i]&&!del_r[j])
						Gb[i][j]=b[i][j]-'0';
					else
						Gb[i][j]=0;
			for(reg int i=0;i<tot;++i)
				if((S>>i)&1)
					Gb[pos[i].first][pos[i].second]=!Gb[pos[i].first][pos[i].second];
			for(reg int i=0;i<tot;++i)
				if((S>>i)&1)
					del_l[pos[i].first]=del_r[pos[i].second]=false;
			reg bool tmp=Gauss(Gb);
			val[__builtin_popcount(S)]^=tmp;
		}
		for(reg int i=0;i<=n;++i)
			for(reg int j=0;j<=i;++j)
				ans[i]^=val[j];
		for(reg int i=1;i<=q;++i)
			printf("%d\n",ans[k[i]]);
		return;
	}
}

bool ed;

int main(void){
	n=read();
	for(reg int i=0;i<n;++i)
		read(r[i]);
	for(reg int i=0;i<n;++i)
		read(b[i]);
	q=read();
	for(reg int i=1;i<=q;++i)
		k[i]=read();
	if(n<=18)
		Subtask1::Solve();
	else 
	if(Subtask2check::Solve())
		Subtask2::Solve();
	else 
	if(Subtask3check::Solve())
		Subtask3::Solve();
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}