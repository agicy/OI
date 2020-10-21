#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline void cMax(int &a,int b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

struct Node{
	int id,pos,dis;
	inline Node(int id=0,int pos=0,int dis=0):id(id),pos(pos),dis(dis){
		return;
	}
	inline bool operator<(const Node& a)const{
		return dis<a.dis;
	}
	inline bool operator>(const Node& a)const{
		return dis>a.dis;
	}
};

int n,m;
vector<pair<int,int>/**/> V[MAXN],tmp;
int id[MAXN],f[2*MAXN];
priority_queue<Node,vector<Node>,greater<Node>/**/> Q;

inline void solve(const Node& p,int pos){
	int siz=V[pos].size();
	int r=V[p.pos][p.id-id[p.pos]].second;
	int i=lower_bound(V[pos].begin(),V[pos].end(),make_pair(p.dis+1,0))-V[pos].begin()-1;
	if(V[pos][i].second>=p.dis+1)
		if(f[id[pos]+i]>p.dis+1){
			f[id[pos]+i]=p.dis+1;
			Q.push(Node(id[pos]+i,pos,p.dis+1));
		}
	for(++i;i<siz&&V[pos][i].first<=r+1;++i)
		if(f[id[pos]+i]>V[pos][i].first){
			f[id[pos]+i]=V[pos][i].first;
			Q.push(Node(id[pos]+i,pos,V[pos][i].first));
		}
	return;
}

int main(){
	n=read(),m=read();
	for(int i=1,a,b,c;i<=m;++i){
		a=read(),b=read(),c=read();
		V[a].push_back(make_pair(b,c));
	}
	id[1]=1;
	for(int i=1;i<=n;++i){
		sort(V[i].begin(),V[i].end());
		tmp.clear();
		int r=-1;
		for(auto p:V[i]){
			if(p.first>r+1)
				tmp.push_back(make_pair(r+1,p.first-1));
			cMax(r,p.second);
		}
		tmp.push_back(make_pair(r+1,inf));
		V[i]=tmp;
		id[i+1]=id[i]+V[i].size();
	}
	V[0].push_back(make_pair(0,inf));
	V[n+1].push_back(make_pair(0,inf));
	memset(f,0x3f,sizeof(f));
	f[0]=0;
	Q.push(Node(0,0,0));
	while(!Q.empty()){
		static Node s;
		s=Q.top();
		Q.pop();
		if(s.dis>f[s.id])
			continue;
		if(s.pos>0)
			solve(s,s.pos-1);
		if(s.pos<n+1)
			solve(s,s.pos+1);
	}
	printf("%d\n",f[id[n+1]]);
	return 0;
}