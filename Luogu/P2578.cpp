#include<bits/stdc++.h>
#include<unordered_map>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

string s;

inline void Print(const string& s){
	for(reg int i=0;i<3;++i)
		for(reg int j=0;j<3;++j)
			printf("%c%c",s[i*3+j],j==3-1?'\n':' ');
	putchar('\n');
	return;
}

queue<string> Q;
unordered_map<string,bool> vis;
unordered_map<string,int> dep;
unordered_map<string,string> last;

const string ed="012345678";

/*
012
345
678
*/

inline void change1(string& s){
	char temp=s[0];
	s[0]=s[3],s[3]=s[6],s[6]=s[7],s[7]=s[8],s[8]=s[5],s[5]=s[2],s[2]=s[1],s[1]=temp;
	return;
}

inline void change2(string& s){
	char temp=s[3];
	s[3]=s[5];
	s[5]=s[4];
	s[4]=temp;
	return;
}

clock_t st;

inline void BFS(const string& s){
	string now,temp;
	clock_t x;
	while(!Q.empty())
		Q.pop();
	vis[s]=true,dep[s]=0;
	Q.push(s);
	while(!Q.empty()){
		now=Q.front();
		Q.pop();
		x=clock();
		if((double)(x-st)/CLOCKS_PER_SEC>=0.87){
			puts("UNSOLVABLE");
			exit(0);
		}
		temp=now;
		change1(temp);
		if(!vis[temp]){
			vis[temp]=true;
			dep[temp]=dep[now]+1;
			last[temp]=now;
			if(vis[ed])
				return;
			Q.push(temp);
		}
		temp=now;
		change2(temp);
		if(!vis[temp]){
			vis[temp]=true;
			dep[temp]=dep[now]+1;
			last[temp]=now;
			if(vis[ed])
				return;
			Q.push(temp);
		}
	}
	return;
}

int cnt;
string X[100];

int main(void){
	s.resize(9);
	for(reg int i=0;i<9;++i){
		static int x;
		scanf("%d",&x);
		s[i]=(x+'0');
	}
	st=clock();
	BFS(s);
	printf("%d\n",dep[ed]);
	string now=ed;
	while(now!=s){
		X[++cnt]=now;
		now=last[now];
	}
	Print(s);
	for(reg int i=cnt;i>=1;--i)
		Print(X[i]);
	return 0;
}
