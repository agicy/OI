#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100;

int n,m;
bool vis[MAXN];
vector<int> S[MAXN];

inline bool check(const vector<int>& V){
	for(reg int i=0,size=V.size();i<size;++i)
		if(vis[V[i]])
			return false;
	return true;
}

inline int A(void){
	static bool state[MAXN];
	memcpy(state,vis,sizeof(vis));
	reg int res=0;
	for(reg int i=0;i<m;++i)
		if(check(S[i])){
			++res;
			for(reg int j=0,size=S[i].size();j<size;++j)
				vis[S[i][j]]=true;
		}
	memcpy(vis,state,sizeof(state));
	return res;
}

inline bool DFS(reg int dep){
	if(A()>dep)
		return false;
	for(reg int i=0;i<m;++i)
		if(check(S[i])){
			for(reg int j=0,size=S[i].size();j<size;++j){
				vis[S[i][j]]=true;
				if(DFS(dep-1))
					return true;
				vis[S[i][j]]=false;
			}
			return false;
		}
	return true;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read();
		m=0;
		for(reg int i=1;i<=n;++i)
			for(reg int a=1;a+i-1<=n;++a)
				for(reg int b=1;b+i-1<=n;++b){
					S[m].clear();
					for(reg int j=0;j<i;++j){
						reg int d=2*n+1;
						S[m].push_back((a-1)*d+b+j);
						S[m].push_back((a-1+i)*d+b+j);
						S[m].push_back(n+1+(a-1)*d+b-1+j*d);
						S[m].push_back(n+1+(a-1)*d+b-1+j*d+i);
					}
					++m;
				}
		memset(vis,false,sizeof(vis));
		reg int K=read();
		while(K--)
			vis[read()]=true;
		reg int dep=0;
		while(!DFS(dep))
			++dep;
		printf("%d\n",dep);
	}
	return 0;
}