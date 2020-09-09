#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

struct Node{
	string from;
	char ch;
	inline Node(string from="",reg char ch='\0'):from(from),ch(ch){
		return;
	}
};

queue<string> Q;
unordered_map<string,Node> M;

const int MAXSIZE=1e5+5;

char str[MAXSIZE];

inline void bfs(const string& s){
	Q.push(s);
	while(!Q.empty()){
		static string x,now;
		now=x=Q.front();
		Q.pop();
		if(x=="12345678x"){
			reg int cnt=0;
			while(x!=s){
				str[++cnt]=M[x].ch;
				x=M[x].from;
			}
			for(reg int i=cnt;i>=1;--i)
				putchar(str[i]);
			putchar('\n');
			return;
		}
		reg int pos=x.find('x');
		reg int px=pos/3,py=pos%3;
		const int dx[]={-1,0,0,1};
		const int dy[]={0,-1,1,0};
		const char ch[]="ulrd";
		for(reg int i=0;i<4;++i){
			reg int fx=px+dx[i],fy=py+dy[i];
			if(0<=fx&&fx<3&&0<=fy&&fy<3){
				reg int tmp=fx*3+fy;
				swap(x[pos],x[tmp]);
				if(!M.count(x)){
					M[x]=Node(now,ch[i]);
					Q.push(x);
				}
				swap(x[pos],x[tmp]);
			}
		}
	}
	puts("unsolvable");
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