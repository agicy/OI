#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int m;
stack<int> S;

int main(void){
	cin>>m;
	while(m--){
		static string str;
		static int x;
		cin>>str;
		if(str=="push"){
			cin>>x;
			S.push(x);
		}
		else if(str=="pop")
			S.pop();
		else if(str=="empty")
			cout<<(S.empty()?"YES":"NO")<<endl;
		else if(str=="query")
			cout<<S.top()<<endl;
	}
	return 0;
}