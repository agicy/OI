#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;

const int MAXN=10000+5;
const int MAXM=75+5;

int n,m;
bool flag[MAXM];
char s[MAXN][MAXM];
int Next[MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=n;++i){
		scanf("%s",s[i]);
		for(reg int j=1;j<m;++j){
			for(reg int k=j;k<m;k+=j){
				for(reg int l=0;l<j&&l+k<m;++l){
					if(s[i][l]!=s[i][l+k])
						flag[j]=true;
				}
			}
		}
	}
	reg int width=0;
	for(reg int i=1;i<=m;++i)
		if(!flag[i]){
			width=i;
			break;
		}
	for(reg int i=1;i<=n;++i)
		s[i][width]='\0';
	for(reg int i=2,j=0;i<=n;++i){
		while(j&&strcmp(s[i],s[j+1]))
			j=Next[j];
		if(!strcmp(s[i],s[j+1]))
			++j;
		Next[i]=j;
	}
	printf("%d\n",width*(n-Next[n]));
	return 0;
}
