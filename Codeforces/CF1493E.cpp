#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int n;
string l,r;

inline string inc(string s){
	reg int i=s.size()-1;
	while(s[i]=='1')
		s[i--]='0';
	s[i]='1';
	return s;
}

int main(void){
	cin>>n>>l>>r;
	if(l==r)
		cout<<r<<endl;
	else if(l[0]=='0'&&r[0]=='1')
		cout<<string(n,'1')<<endl;
	else if(r[n-1]=='1')
		cout<<r<<endl;
	else if(inc(l)==r)
		cout<<r<<endl;
	else
		cout<<inc(r)<<endl;
	return 0;
}