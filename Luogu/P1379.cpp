#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};
queue<string> Q;
unordered_map<string,int> ans;

inline void BFS(const string& s){
	ans[s]=0;
	Q.push(s);
	static string now;
	while(!Q.empty()){
		now=Q.front();
		Q.pop();
		if(now=="123804765"){
			printf("%d\n",ans[now]);
			return;
		}
		reg int pos=now.find('0');
		reg int x=pos/3,y=pos%3;
		string Temp=now;
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(0<=fx&&fx<=2&&0<=fy&&fy<=2){
				reg int temp=fx*3+fy;
				swap(now[pos],now[temp]);
				if(!ans.count(now)){
					ans[now]=ans[Temp]+1;
					Q.push(now);
				}
				swap(now[temp],now[pos]);
			}
		}
	}
	return;
}

string str;

int main(void){
	cin>>str;
	BFS(str);
	return 0;
}