#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

string str;

int main(void){
	cin>>str;
	string tmp=str;
	reverse(tmp.begin(),tmp.end());
	puts(str==tmp?"yes":"no");
	return 0;
}