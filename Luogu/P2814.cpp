#include<cstdio>
#include<iostream>
using std::cin;
using std::cout;
#include<string>
using std::string;
#include<map>
using std::map;

char ch;
string str,last;
map<string,string> ID;

string find(string x);

int main(void){
	while(cin>>ch,ch!='$')
		if(cin>>str,ch=='#')
			last=str,(ID[str]=="")&&(ID[str]=str,true);
		else if(ch=='+')
			ID[str]=last;
		else
			cout<<str<<' '<<find(str)<<'\n';
	return 0;
}

string find(string x){
	if(x==ID[x])
		return ID[x];
	else
		return ID[x]=find(ID[x]);
}
