#include<bits/stdc++.h>
using namespace std;
#define reg register
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

string T;

int main(void){
	reg int t=read();
	while(t--){
		cin>>T;
		reg int len=T.length();
		reg int cnt=0;
		for(reg int i=1;i<len;++i)
			if(T[i]==T[i-1])
				++cnt;
		if(cnt==len-1)
			cout<<T<<endl;
		else{
			string S;
			for(reg int i=0;i<len;++i){
                S+=T[i];
                if(T[i+1]==T[i])
					S+=T[i]^1;
			}
			if(S.length()&1)
				S+=S[S.length()-1]^1;
			cout<<S<<endl;
		}
	}
	return 0;
}
