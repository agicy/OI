#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

string s;

int main(void){
	cin>>s;
	for(char &i:s)
		if('0'<=i&&i<='9')
			i='*';
	cout<<s<<endl;
	return 0;
}