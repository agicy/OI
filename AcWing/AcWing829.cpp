#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

int m;
queue<int> Q;

int main(void){
	cin>>m;
	while(m--){
		static string str;
		static int x;
		cin>>str;
		if(str=="push"){
			cin>>x;
			Q.push(x);
		}
		else if(str=="pop")
			Q.pop();
		else if(str=="empty")
			cout<<(Q.empty()?"YES":"NO")<<endl;
		else if(str=="query")
			cout<<Q.front()<<endl;
	}
	return 0;
}