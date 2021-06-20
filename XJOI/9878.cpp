#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int main(void){
	ll a,b[5];
	cin>>a>>b[0]>>b[1]>>b[2]>>b[3]>>b[4];
	cout<<*max_element(b,b+5)+1-a<<endl;
	return 0;
}