#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define INF 0X3F3F3F3F3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=180+5;
const int MAXM=40000+5;
const int MAXSIZE=180;

struct Matrix{
	bitset<MAXSIZE> unit[MAXSIZE];
	inline Matrix(reg int x=0){
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				unit[i][j]=((i==j)?x:0);
		return;
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int k=0;k<MAXSIZE;++k)
				if(unit[i][k])
					res.unit[i]|=a.unit[k];
		return res;
	}
};

struct Edge{
	int u,v,lv;
	inline void Read(void){
		u=read()-1,v=read()-1,lv=read();
		return;
	}
	inline bool operator<(const Edge& a)const{
		return lv<a.lv;
	}
};

int n,m;
Edge E[MAXM];
queue<int> Q;

inline bitset<MAXSIZE> mul(bitset<MAXSIZE> a,Matrix b){
	bitset<MAXSIZE> res;
	for(reg int i=0;i<MAXSIZE;++i)
		res[i]=(a&b.unit[i]).any();
	return res;
}

inline void pow(Matrix x,reg int exp,bitset<MAXSIZE>& res){
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=x*x;
		exp>>=1;
	}
	return;
}

ll dis[MAXN];
Matrix a;
bitset<MAXSIZE> v;

inline void BFS(void){
	while(!Q.empty())Q.pop();
	for(int i=0;i<n;++i)
		if(v[i]){
			dis[i]=0;
			Q.push(i);
		}
		else
			dis[i]=INF;
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(int i=0;i<n;++i)
			if(a.unit[i][ID]&&dis[i]==INF){
				dis[i]=dis[ID]+1;
				Q.push(i);
			}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<m;++i)
		E[i].Read();
	sort(E,E+m);
	ll ans=INF;
	v[0]=true;
	for(reg int i=0,t=0;i<m;++i){
		pow(a,E[i].lv-t,v);
		a.unit[E[i].v][E[i].u]=true;
		t=E[i].lv;
		BFS();
		ans=min(ans,t+dis[n-1]);
	}
	if(ans!=INF)
		printf("%lld\n",ans);
	else
		puts("Impossible");
	return 0;
}