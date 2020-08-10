#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<string>
using std::string;
bool cmp(string a,string b){
	return a+b>b+a;
}
int main(void){
	int n;
	scanf("%d",&n);
	string num[n];
	for(int i=0;i<n;i++)
		std::cin>>num[i];
	std::sort(num,num+n,cmp);
	for(int i=0;i<n;i++)
		std::cout<<num[i];
	return 0;
}