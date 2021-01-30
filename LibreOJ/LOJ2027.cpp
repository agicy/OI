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

const int MAXN=17;
const int MAXM=MAXN*(MAXN-1)/2;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
}

int n;
int m[MAXN];
int u[MAXN][MAXM],v[MAXN][MAXM];

inline int lowbit(reg int x){
	return x&(-x);
}

inline int getCnt(reg int x){
	reg int res=0;
	while(x){
		++res;
		x^=lowbit(x);
	}
	return res;
}

int G[MAXN][MAXN];

inline int Gauss(void){
	reg int res=1,sgn=0;
	for(reg int i=0;i<n-1;++i){
		reg int Max=i;
		for(reg int j=i+1;j<n-1;++j)
			if(abs(G[j][i])>abs(G[Max][i]))
				Max=j;
		if(i!=Max){
			sgn^=1;
			for(reg int k=0;k<=n-1;++k)
				swap(G[i][k],G[Max][k]);
		}
		if(!G[i][i])
			return 0;
		for(reg int j=i+1;j<n-1;++j)
			while(G[j][i]){
				reg int d=G[j][i]/G[i][i];
				for(reg int k=i;k<n-1;++k)
					G[j][k]=sub(G[j][k],1ll*d*G[i][k]%p);
				if(!G[j][i])
					break;
				sgn^=1;
				swap(G[i],G[j]);
			}
		res=1ll*res*G[i][i]%p;
	}
	return sgn?p-res:res;
}

int main(void){
	n=read();
	for(reg int i=0;i<n-1;++i){
		m[i]=read();
		for(reg int j=0;j<m[i];++j)
			u[i][j]=read()-1,v[i][j]=read()-1;
	}
	reg int ans=0;
	for(reg int S=1;S<(1<<(n-1));++S){
		memset(G,0,sizeof(G));
		for(reg int i=0;i<n-1;++i)
			if((S>>i)&1)
				for(reg int j=0;j<m[i];++j){
					reg int x=u[i][j],y=v[i][j];
					G[x][x]=add(G[x][x],1);
					G[y][y]=add(G[y][y],1);
					G[x][y]=sub(G[x][y],1);
					G[y][x]=sub(G[y][x],1);
				}
		reg int sum=Gauss();
		if((n-getCnt(S))&1)
			ans=add(ans,sum);
		else
			ans=sub(ans,sum);
	}
	printf("%d\n",ans);
	return 0;
}