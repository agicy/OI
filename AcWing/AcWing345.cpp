#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXT=100+5;
const int MAXSIZE=200;
const int inf=0x3f3f3f3f;

struct Matrix{
	int unit[MAXSIZE][MAXSIZE];
	inline Matrix(void){
		memset(unit,0x3f,sizeof(unit));
		return;
	}
	inline Matrix operator*(const Matrix& a){
		Matrix res;
		for(reg int i=0;i<MAXSIZE;++i)
			for(reg int k=0;k<MAXSIZE;++k)
				if(unit[i][k]!=inf){
					reg int r=unit[i][k];
					for(reg int j=0;j<MAXSIZE;++j)
						if(a.unit[k][j]!=inf)
							res.unit[i][j]=min(res.unit[i][j],r+a.unit[k][j]);
				}
		return res;
	}
	inline int* operator[](reg int i){
		return unit[i];
	}
};

int n,t,s,e;
int w[MAXT],u[MAXT],v[MAXT];
vector<int> V;
Matrix G;

int main(void){
	scanf("%d%d%d%d",&n,&t,&s,&e);
	V.push_back(s),V.push_back(e);
	for(reg int i=1;i<=t;++i){
		scanf("%d%d%d",&w[i],&u[i],&v[i]);
		V.push_back(u[i]),V.push_back(v[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	s=lower_bound(V.begin(),V.end(),s)-V.begin();
	e=lower_bound(V.begin(),V.end(),e)-V.begin();
	for(reg int i=1;i<=t;++i){
		u[i]=lower_bound(V.begin(),V.end(),u[i])-V.begin();
		v[i]=lower_bound(V.begin(),V.end(),v[i])-V.begin();
		G[u[i]][v[i]]=G[v[i]][u[i]]=min(G[u[i]][v[i]],w[i]);
	}
	Matrix base=G,x=G;
	--n;
	while(n){
		if(n&1)
			base=base*x;
		x=x*x;
		n>>=1;
	}
	printf("%d\n",base[s][e]);
	return 0;
}