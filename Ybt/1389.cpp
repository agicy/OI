#include<cstdio>
#include<iostream>
using std::cin;

const int MAXN=100000+5;
const int MAXM=200000+5;

char ch;
int n,m;
int ID[MAXN],size[MAXN];

void connect(int,int);
bool search(int,int);
int find(int);

int main(void){
	register int i;
	scanf("%d%d",&n,&m);
	for(i=1;i<=n;++i)
		ID[i]=i,size[i]=1;
	for(i=1;i<=m;++i){
		cin>>ch;
		if(ch=='M'){
			static int a,b;
			scanf("%d%d",&a,&b);
			if(!search(a,b)){
				size[find(a)]+=size[find(b)];
				connect(a,b);
			}
		}
		if(ch=='Q'){
			static int a;
			scanf("%d",&a);
			printf("%d\n",size[find(a)]);
		}
	}
	return 0;
}

void connect(int a,int b){
	register int ra=find(a),rb=find(b);
	if(ra!=rb)
		ID[rb]=ra;
	return;
}

bool search(int a,int b){
	return find(a)==find(b);
}

int find(int x){
	if(x==ID[x])
		return x;
	else
		return ID[x]=find(ID[x]);
}
