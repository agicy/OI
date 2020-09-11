#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=2e5+5;
const int MAXR=1e6+5;

int n;
ll s[MAXN],k[MAXN];
int r[MAXN];
vector<int> G1[MAXN],G2[MAXN];
bool inque[MAXN];
ll dis[MAXN];
queue<int> Q;

inline ll spfa(void){
	for(int i=1;i<=n;++i)
		inque[i]=true,dis[i]=k[i],Q.push(i);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		reg ll sum=s[u];
		for(vector<int>::iterator it=G1[u].begin();it!=G1[u].end();++it)
			sum+=dis[*it];
		if(sum<dis[u]){
			dis[u]=sum;
			for(vector<int>::iterator it=G2[u].begin();it!=G2[u].end();++it)
				if(!inque[*it]){
					inque[*it]=true;
					Q.push(*it);
				}
		}
	}
	return dis[1];
}

int main(void){
	n=read();
	for(int i=1;i<=n;++i){
		s[i]=read(),k[i]=read(),r[i]=read();
		G1[i].resize(r[i]);
		for(reg int j=1;j<=r[i];++j){
			static int x;
			x=read();
			G1[i][j-1]=x;
			G2[x].push_back(i);
		}
	}
	printf("%lld\n",spfa());
	return 0;
}