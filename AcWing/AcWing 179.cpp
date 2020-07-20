#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const char ch[]="udlr";
const int dx[]={-1,1,0,0},dy[]={0,0,-1,1};

queue<string> Q;
unordered_map<string,char> ans;
unordered_map<string,string> last;

inline bool BFS(const string& s){
	ans[s]=0;
	Q.push(s);
	static string now;
	while(!Q.empty()){
		now=Q.front();
		Q.pop();
		if(now=="12345678x")
			return true;
		reg int pos=now.find('x');
		reg int x=pos/3,y=pos%3;
		string Temp=now;
		for(reg int i=0;i<4;++i){
			reg int fx=x+dx[i],fy=y+dy[i];
			if(0<=fx&&fx<=2&&0<=fy&&fy<=2){
				reg int temp=fx*3+fy;
				swap(now[pos],now[temp]);
				if(!ans.count(now)){
					ans[now]=ch[i],last[now]=Temp;
					Q.push(now);
				}
				swap(now[temp],now[pos]);
			}
		}
	}
	return false;
}

string str;
stack<char> S;

int main(void){
	for(reg int i=0;i<9;++i){
		static char ch;
		cin>>ch;
		str+=ch;
	}
	if(BFS(str)){
		string temp="12345678x";
		while(temp!=str){
			S.push(ans[temp]);
			temp=last[temp];
		}
		while(!S.empty()){
			putchar(S.top());
			S.pop();
		}
		putchar('\n');
	}
	else
		puts("unsolvable");
	return 0;
}
