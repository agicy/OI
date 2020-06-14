#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const int MAXM=200000+5;

int n,m,k;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int pos[MAXN];
vector<int> S,C,color[2];

inline bool DFS(int ID){
	pos[ID]=S.size();
	color[pos[ID]&1].push_back(ID);
	S.push_back(ID);
	int low=-1;
	for(reg int i=head[ID];i;i=Next[i])
		if(pos[to[i]]!=-1&&pos[ID]-pos[to[i]]>1)
			low=max(low,pos[to[i]]);
	if(low!=-1){
		for(reg int i=low;i<=pos[ID];++i)
			C.push_back(S[i]);
		return true;
	}
	for(reg int i=head[ID];i;i=Next[i])
		if(pos[to[i]]==-1)
			if(DFS(to[i]))
				return true;
	S.pop_back();
	return 0;
}

int main(void){
	n=read(),m=read(),k=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	memset(pos,-1,sizeof(pos));
	DFS(1);
	if(C.empty()){
		if(color[0].size()<color[1].size())
			swap(color[0],color[1]);
		puts("1");
		for(reg int i=0,size=((k+1)>>1);i<size;++i)
			printf("%d%c",color[0][i],i==size-1?'\n':' ');
	}
	else{
		if((int)C.size()<=k){
			puts("2");
			printf("%lu\n",C.size());
			for(reg int i=0,size=C.size();i<size;++i)
				printf("%d%c",C[i],i==size-1?'\n':' ');
		}
		else{
			puts("1");
			for(reg int i=0,size=((k+1)>>1);i<size;++i)
				printf("%d%c",C[2*i],i==size-1?'\n':' ');
		}
	}
	return 0;
}