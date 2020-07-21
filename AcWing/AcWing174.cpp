#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=20+5;

struct Node{
	int x,y,dir;
	inline Node(reg int x=0,reg int y=0,reg int dir=0):x(x),y(y),dir(dir){
		return;
	}
};

int n,m;
char G[MAXN][MAXN];
Node pre[MAXN][MAXN][4];
vector<int>path[MAXN][MAXN][4];
bool v[MAXN][MAXN][4];
pair<int,int> dis[MAXN][MAXN][4];

const int D1[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
const int D2[4][2]={{-1,0},{1,0},{0,-1},{0,1}};


inline bool check(reg int x,reg int y){
	return 0<=x&&x<n&&0<=y&&y<m&&G[x][y]!='#';
}

inline int BFS1(pair<int,int> S,pair<int,int> E,pair<int,int> B,vector<int>& V){
	static bool vis[MAXN][MAXN];
	static int from[MAXN][MAXN];
	memset(vis,false,sizeof(vis));
	memset(from,-1,sizeof(from));
	queue<pair<int,int> > Q;
	Q.push(S);
	vis[S.first][S.second]=true;
	vis[B.first][B.second]=true;
	while(!Q.empty()){
		static pair<int,int> u;
		u=Q.front();
		int x=u.first,y=u.second;
		Q.pop();
		if(u==E){
			V.clear();
			while(from[x][y]!=-1){
				int dir=from[x][y];
				V.push_back(dir);
				x+=D1[dir][0];
				y+=D1[dir][1];
			}
			return V.size();
		}
		for(reg int i=0;i<4;++i){
			int fx=x+D2[i][0],fy=y+D2[i][1];
			if(check(fx,fy)&&!vis[fx][fy]){
				vis[fx][fy]=true;
				from[fx][fy]=i;
				Q.push(make_pair(fx,fy));
			}
		}
	}
	return -1;
}

inline bool BFS2(pair<int,int> M,pair<int,int> B,Node &E){
	memset(v,false,sizeof(v));
	queue<Node> Q;
	reg int x=B.first,y=B.second;
	for(reg int i=0;i<4;++i){
		int fx=x+D1[i][0],fy=y+D1[i][1];
		int fxx=x-D1[i][0],fyy=y-D1[i][1];
		vector<int> V;
		if(check(fx,fy)&&check(fxx,fyy)&&BFS1(M,make_pair(fx,fy),B,V)!=-1){
			v[fxx][fyy][i]=true;
			Q.push(Node(fxx,fyy,i));
			dis[fxx][fyy][i]=make_pair(1,(int)V.size());
			path[fxx][fyy][i]=V;
			pre[fxx][fyy][i]=Node(x,y,-1);
		}
	}
	reg bool flag=false;
	pair<int,int> man_d={1e9,1e9};
	while(!Q.empty()){
		static Node u;
		u=Q.front();
		int x=u.x,y=u.y,dir=u.dir;
		Q.pop();
		if(G[x][y]=='T'){
			flag=true;
			if(dis[x][y][dir]<man_d){
				E=u;
				man_d=dis[x][y][dir];
			}
		}
		for(reg int i=0;i<4;++i){
			int fx=x+D1[i][0],fy=y+D1[i][1];
			int fxx=x-D1[i][0],fyy=y-D1[i][1];
			if(check(fx,fy)&&check(fxx,fyy)){
				pair<int,int> &p=dis[fxx][fyy][i];
				vector<int> V;
				int Dis=BFS1(make_pair(x+D1[dir][0],y+D1[dir][1]),make_pair(fx,fy),make_pair(x,y),V);
				if(Dis!=-1){
					pair<int,int> td=make_pair(dis[x][y][dir].first+1,dis[x][y][dir].second+Dis);
					if(!v[fxx][fyy][i]){
						v[fxx][fyy][i]=true;
						Q.push({fxx,fyy,i});
						path[fxx][fyy][i]=V;
						pre[fxx][fyy][i]=u;
						p=td;
					}
					else if(p>td){
						p=td;
						path[fxx][fyy][i]=V;
						pre[fxx][fyy][i]=u;
					}
				}
			}
		}
	}
	return flag;
}

int main(void){
	reg int T=0;
	while(scanf("%d%d",&n,&m)!=EOF&&(n||m)){
		for(reg int i=0;i<n;++i)
			scanf("%s",G[i]);
		printf("Maze #%d\n",++T);
		pair<int,int> M,B;
		for(int i=0;i<n;++i)
			for(int j=0;j<m;++j)
				switch(G[i][j]){
					case 'S':{
						M=make_pair(i,j);
						break;
					}
					case 'B':{
						B=make_pair(i,j);
						break;
					}
					default:break;
				}

		Node E;
		static char ops[]="NSWE";
		if(!BFS2(M,B,E))
			puts("Impossible.");
		else{
			string res="";
			reg int x=E.x,y=E.y,dir=E.dir;
			while(dir!=-1){
				res+=ops[dir];
				for(reg int i=0,size=path[x][y][dir].size();i<size;++i)
					res+=ops[path[x][y][dir][i]]+32;
				E=pre[x][y][dir];
				x=E.x,y=E.y,dir=E.dir;
			}
			reverse(res.begin(),res.end());
			cout<<res<<endl;
		}
		putchar('\n');
	}
	return 0;
}