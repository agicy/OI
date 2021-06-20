#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int main(void){
	ll a,b,c,d;
	cin>>a>>b>>c>>d;
	cout<<max(abs(a-c),abs(b-d))<<endl;
	return 0;
}