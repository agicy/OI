#include<bits/stdc++.h>
using namespace std;
#define reg register

string a,b;

inline string Solve(string &s,int &_s){
	++_s;
	vector<string> V;
	while(s[_s]=='0')
		V.push_back(Solve(s,_s));
	++_s;
	sort(V.begin(),V.end());
	string res="0";
	for(reg int i=0;i<(int)V.size();++i)
		res+=V[i];
	res+='1';
	return res;
}

int main(void){
	int T;
	scanf("%d",&T);
	while(T--){
		cin>>a>>b;
		a='0'+a+'1',b='0'+b+'1';
		int _a=0,_b=0;
		puts(Solve(a,_a)==Solve(b,_b)?"same":"different");
	}
	return 0;
}
