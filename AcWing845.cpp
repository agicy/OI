#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

queue<string> Q;
unordered_map<string,int> ans;

const int dx[]={-1,0,0,1};
const int dy[]={0,-1,1,0};

inline void bfs(const string& s){
	ans[s]=0;
	Q.push(s);
	while(!Q.empty()){
		static string x,now;
		now=x=Q.front();
		Q.pop();
		if(x=="12345678x"){
			printf("%d\n",ans[x]);
			return;
		}
		reg int pos=x.find('x');
		reg int px=pos/3,py=pos%3;
		for(reg int i=0;i<4;++i){
			reg int fx=px+dx[i],fy=py+dy[i];
			if(0<=fx&&fx<3&&0<=fy&&fy<3){
				reg int tmp=fx*3+fy;
				swap(x[pos],x[tmp]);
				if(!ans.count(x)){
					ans[x]=ans[now]+1;
					Q.push(x);
				}
				swap(x[pos],x[tmp]);
			}
		}
	}
	puts("-1");
	return;
}

int main(void){
	string s;
	s.resize(9);
	for(reg int i=0;i<9;++i)
		cin>>s[i];
	bfs(s);
	return 0;
}