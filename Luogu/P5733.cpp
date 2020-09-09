#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

string str;

int main(void){
	cin>>str;
	for(reg int i=0,siz=str.length();i<siz;++i)
		if('a'<=str[i]&&str[i]<='z')
			str[i]-=' ';
	cout<<str<<endl;
	return 0;
}