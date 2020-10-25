#include<cstdio>
#include<algorithm>
using std::unique;
#include<iostream>
using std::cin;
#include<vector>
using std::vector;
#define reg register

int n;
vector<char> V;

int main(void){
	reg int i;
	scanf("%d",&n);
	for(i=1;i<=n;++i){
		static char ch;
		cin>>ch;
		V.push_back(ch);
	}
	V.erase(unique(V.begin(),V.end()),V.end());
	printf("%d\n",(int)V.size());
	return 0;
}
