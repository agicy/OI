#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n;
string str;
char ch;

int main(void){
	cin>>n>>str>>ch;
	if(str.find(ch)==string::npos)
		puts("-1");
	else
		printf("%ld\n",str.find(ch));
	return 0;
}