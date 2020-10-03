#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int inf=0x3f3f3f3f;
const int MAXSIZE=25;

int n;

struct Node{
	int S,x,y;
	bool f;
	inline Node(reg int S=0,reg int x=0,reg int y=0,reg bool f=false):S(S),x(x),y(y),f(f){
		return;
	}
};

unordered_map<int,int> M[2][MAXSIZE];

inline int get(const Node& x){
	if(M[x.f][x.x*5+x.y].count(x.S))
		return M[x.f][x.x*5+x.y][x.S];
	else
		return inf;
}

inline void Set(const Node& x,reg int val){
	M[x.f][x.x*5+x.y][x.S]=val;
	return;
}

inline int bfs(const Node& s){
	queue<Node> Q;
	Node t=Node(0x863df,2,2,true);
	Set(s,0),Set(t,0);
	Q.push(s),Q.push(t);
	while(!Q.empty()){
		static Node u,tmp;
		u=Q.front();
		Q.pop();
		reg bool f=u.f;
		reg int x=u.x,y=u.y,S=u.S;
		tmp=Node(S,x,y,!f);
		if(get(u)+get(tmp)<=15)
			return get(u)+get(tmp);
		if(get(u)>=8)
			break;
		const int dx[]={-2,-2,-1,-1,1,1,2,2};
		const int dy[]={-1,1,-2,2,-2,2,-1,1};
		for(reg int i=0;i<8;++i){
			reg int fx=u.x+dx[i],fy=u.y+dy[i];
			if(0<=fx&&fx<5&&0<=fy&&fy<5){
				reg int p1=5*fx+fy,p2=5*x+y;
				reg int v1=((S>>p1)&1),v2=((S>>p2)&1);
				reg int s=(S&(~(1<<p1))&(~(1<<p2)))|(v2<<p1)|(v1<<p2);
				tmp=Node(s,fx,fy,f);
				if(get(u)+1<get(tmp)){
					M[tmp.f][tmp.x*5+tmp.y][tmp.S]=get(u)+1;
					Q.push(tmp);
				}
			}
		}
	}
	return -1;
}

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		for(reg int i=0;i<2;++i)
			for(reg int j=0;j<MAXSIZE;++j)
				M[i][j].clear();
		reg int sum=0,x=-1,y=-1;
		for(reg int i=0;i<5;++i){
			static char str[6];
			scanf("%s",str);
			for(reg int j=0;j<5;++j)
				switch(str[j]){
					case '*':{
						x=i,y=j;
						break;
					}
					default:{
						if(str[j]=='1')
							sum|=(1<<(5*i+j));
						break;
					}
				}
		}
		printf("%d\n",bfs(Node(sum,x,y,false)));
	}
	return 0;
}