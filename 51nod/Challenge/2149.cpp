#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

string s,t;

int main(void){
	cin>>s>>t;
	if(s.find(t)==string::npos)
		puts("-1");
	else
		printf("%ld\n",s.find(t));
	return 0;
}