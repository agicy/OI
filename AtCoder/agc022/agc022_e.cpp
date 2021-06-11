#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int f[2][9];

int main(void){
	reg int ptr=0;
	f[ptr][0]=1;
	reg char opt;
	while(true){
		opt=getchar();
		if(opt!='0'&&opt!='1'&&opt!='?')
			break;
		memset(f[ptr^1],0,sizeof(f[ptr^1]));
		if(opt!='0'){
			f[ptr^1][0]=add(f[ptr^1][0],f[ptr][1]);
			f[ptr^1][1]=add(f[ptr^1][1],f[ptr][2]);
			f[ptr^1][3]=add(f[ptr^1][3],add(f[ptr][0],f[ptr][4]));
			f[ptr^1][4]=add(f[ptr^1][4],f[ptr][5]);
			f[ptr^1][6]=add(f[ptr^1][6],add(f[ptr][3],add(f[ptr][6],f[ptr][7])));
			f[ptr^1][7]=add(f[ptr^1][7],f[ptr][8]);
		}
		if(opt!='1'){
			f[ptr^1][1]=add(f[ptr^1][1],add(f[ptr][0],f[ptr][2]));
			f[ptr^1][2]=add(f[ptr^1][2],f[ptr][1]);
			f[ptr^1][4]=add(f[ptr^1][4],add(f[ptr][3],f[ptr][5]));
			f[ptr^1][5]=add(f[ptr^1][5],f[ptr][4]);
			f[ptr^1][7]=add(f[ptr^1][7],add(f[ptr][6],f[ptr][8]));
			f[ptr^1][8]=add(f[ptr^1][8],f[ptr][7]);
		}
		ptr^=1;
	}
	reg int ans=add(add(f[ptr][0],add(f[ptr][3],f[ptr][4])),add(f[ptr][6],add(f[ptr][7],f[ptr][8])));
	printf("%d\n",ans);
	return 0;
}