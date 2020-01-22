#include<stdio.h>
#include<string.h>
struct Node{
	char name[32];
	Node *l,*r;
	Node(void){
		memset(name,0,sizeof(name)),l=r=NULL;
		return;
	}
}tree[128];
Node* Create(char *zx,char *hx){
	if(strlen(zx)==0)
		return NULL;
	int index=0,len=strlen(hx);
	for(int i=0;i<len;i++)
		if(zx[i]==hx[len-1]){
			index=i;
			break;
		}
	printf("%c",hx[len-1]);
	//strcpy(tree[hx[len-1]].name,hx+len-1);
	//tree[hx[len-1]].name[0]=hx[len-1];
	hx[len-1]='\0';
	char temp=hx[index];
	hx[index]=zx[index]='\0';
	tree[hx[len-1]].l=Create(zx,hx);
	hx[index]=temp;
	tree[hx[len-1]].r=Create(zx+index+1,hx+index);

	return NULL;
}
int main(void){
	char zx[32],hx[32];
	scanf("%s%s",zx,hx);
	Create(zx,hx);
	///for(int i=0;i<128;i++)
	//	printf("%d %s\n",i,tree[i].name);
	return 0;
}
