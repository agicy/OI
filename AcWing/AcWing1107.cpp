#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

struct Node{
	string from;
	char ch;
	int dep;
	inline Node(string from="",reg char ch='\0',reg int dep=0):from(from),ch(ch),dep(dep){
		return;
	}
};

string s;
queue<string> Q;
unordered_map<string,Node> M;

inline void opa(string& a){
	for(reg int i=0;i<4;++i)
		swap(a[i],a[i+4]);
	return;
}

inline void opb(string& a){
	for(reg int i=2;i>=0;--i){
		swap(a[i],a[i+1]);
		swap(a[i+4],a[i+5]);
	}
	return;
}

inline void opc(string& a){
	swap(a[1],a[2]);
	swap(a[5],a[1]);
	swap(a[6],a[5]);
	return;
}

inline void print(const string& x){
	if(x=="12348765")
		return;
	print(M[x].from);
	putchar(M[x].ch);
	return;
}

inline void bfs(void){
	M["12348765"]=Node("",'\0',0);
	Q.push("12348765");
	while(!Q.empty()){
		static string x,now;
		now=Q.front();
		Q.pop();
		if(now==s){
			printf("%d\n",M[now].dep);
			print(now);
			putchar('\n');
			return;
		}
		reg int d=M[now].dep;
		x=now,opa(x);
		if(!M.count(x)){
			M[x]=Node(now,'A',d+1);
			Q.push(x);
		}
		x=now,opb(x);
		if(!M.count(x)){
			M[x]=Node(now,'B',d+1);
			Q.push(x);
		}
		x=now,opc(x);
		if(!M.count(x)){
			M[x]=Node(now,'C',d+1);
			Q.push(x);
		}
	}
	return;
}

int main(void){
	s.resize(8);
	for(reg int i=0;i<4;++i)
		cin>>s[i];
	for(reg int i=0;i<4;++i)
		cin>>s[7-i];
	cout<<s;
	if(s=="12348765")
		puts("0");
	else
		bfs();
	return 0;
}