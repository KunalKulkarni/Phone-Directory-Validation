#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct{
	char first[100];
	char last[100];
	char ph_number[50];
}Directory;

Directory d[200];
Directory q[200];
int size=0;
int SamePos=0;
void create (char filename[20]);
int found=0;
int pos=0;
void create(char filename[20]){
	FILE *fptr = fopen( filename, "r");
	char c;
	size=1;
	for (c = getc(fptr); c!= EOF ; c=getc(fptr)){
		if (c == '\n') size += 1; 
	}
	fclose(fptr);
	char buff[100];
	char *token;
	char str[200] ={}; 
	int i=0;
	FILE *fptr1 = fopen( filename, "r");
	while(fgets (buff, sizeof(buff), fptr1) != NULL){
		token = strtok(buff," ");
		strcpy(d[i].first, token);
		token = strtok(NULL, ",");
		strcpy(d[i].last, token);
		token = strtok(NULL, "\n");
		strcpy(d[i].ph_number, token);
		i++;
	}
}

void merge(Directory d[], Directory left[], int l, Directory right[], int r){
	int i=0, j=0, k=0;
	while(i<l && j<r){
		if(strcasecmp(left[i].last,right[j].last)==0){
			if(strcasecmp(left[i].first,right[j].first)<0){
				d[k] = left[i++];
			} else {
				d[k] = right[j++];
			}
		}
		else if(strcasecmp(left[i].last,right[j].last)<0){
			d[k] = left[i++];
		} else {
			d[k] = right[j++];
		}
		k++;
	}
	while(i<l){
		d[k++] = left[i++];
	}
	while(j<r){
		d[k++] = right[j++];
	}
}

void sortDirectory(Directory d[], int size){
	int m, i;
	if(size<2) return;
	m = size/2;
	Directory left[m], right[size-m];
	for(i=0; i<m; i++) left[i] = d[i];
	for(i=m; i<size; i++) right[i-m] = d[i];
	sortDirectory(left, m);
	sortDirectory(right,size-m);
	merge(d,left,m,right,size-m);
}
int partition(Directory dir[],int p,int r);

void quickSort(Directory dir[],int p,int q,int length){
	int j;
	if(p<q){
		j=partition(dir,p,q);
		quickSort(dir,p,j-1,length);
		quickSort(dir,j+1,q,length);
	}
}
 
int partition(Directory dir[],int p,int r){
	int pivotI=p+rand()%(r-p+1);
	char pivot[50];
	int i=p-1;
	int j;
	strcpy(pivot,dir[pivotI].ph_number);
	char temp[50];
	strcpy(temp,dir[pivotI].ph_number);
	strcpy(dir[pivotI].ph_number,dir[r].ph_number);
	strcpy(dir[r].ph_number,temp);
	for(j=p;j<r;j++){
		if(strcmp(dir[j].ph_number,pivot)<0){
			i++;
			char temp1[50];
			strcpy(temp1,dir[i].ph_number);
			strcpy(dir[i].ph_number,dir[j].ph_number);
			strcpy(dir[j].ph_number,temp1);
		}
	}
	strcpy(temp,dir[i+1].ph_number);
	strcpy(dir[i+1].ph_number,dir[r].ph_number);
	strcpy(dir[r].ph_number,temp);
	return i+1;
}

void randQsort(){
	int i=0;int j=1;int k=0; Directory collect[100];
	sortDirectory(d,size);
	int fin=0;int fin1=0;
	while(i<size){
		 fin=i;
		 while((strcasecmp(d[i].first, d[j].first)==0) 
				 && (strcasecmp(d[i].last, d[j].last)==0)){
					 if(i==(j-1)){
						collect[k]=d[i];
						k=k+1;
					}
					collect[k]=d[j];
					fin1=j;
					j=j+1;
					k=k+1;
		}	
		srand(time(NULL));
		int x=0;
		quickSort(collect,0,k-1,k);
		k=0;
		i=j;	
		j=j+1;
		int g=0;
		for(int i=fin;i<=fin1;i++){
			strcpy(d[i].ph_number,collect[g].ph_number);
			g++;
		}
	}	
}

void searchDirectory(char *name){
	char firstN[100];
	char lastN[100];
	char buff[100];
	strcpy(buff,name);
	char *token;
	token = strtok(buff," ");
	strcpy(firstN, token);
	token = strtok (NULL,"\0");
	strcpy(lastN, token);
	int l=0,r=0,m=0;
	r = size-1;
	m = (l+r)/2;
	int posfirst=0;
	randQsort();
	Directory result[20];
	while(l<=r){
		if(strcasecmp(d[m].last, lastN)<0){
			l= m+1;
		
		} else if (strcasecmp(d[m].last, lastN)==0) {
			if (strcasecmp(d[m].first, firstN) == 0) {
				printf("%s %s %s \n", d[m].first, d[m].last, d[m].ph_number);
				
				pos=m;
				SamePos=m;
				posfirst=m;
				found=1;
				break;
			} else if (strcasecmp(d[m].first, firstN) < 0) {
				l = m+1;
			} else {
				r = m-1;
			}
		} else {
			r = m-1;
		}
		m = (l+r)/2;
	}
	
	for(int i=posfirst+1;i<size;i++){
		if(strcasecmp(d[i].last, lastN)==0){
			if(strcasecmp(d[i].first, firstN) == 0){
		printf("%s %s %s \n", d[i].first, d[i].last, d[i].ph_number);
				
				SamePos=i;

			}
		}
	}
	for(int i=posfirst-1;i>=0;i--){
		if(strcasecmp(d[i].last, lastN)==0){
			if(strcasecmp(d[i].first, firstN) == 0){
			
				printf("%s %s %s \n", d[i].first, d[i].last, d[i].ph_number);
			}
		}
	}


	if (l>r) printf("Name not found\n");
}
 void insert(char* name,char* number){ 
	char firstN[100];
	char lastN[100];
	char num[100]; char num1[100];
	char buff[100];
	strcpy(buff,name);
	char *token;
	char numtoken[50];
	char tokenIn[50];
	token = strtok(buff," ");
	strcpy(firstN, token);
	token = strtok (NULL,"\0");
	strcpy(lastN, token);
	strcpy(num,number);
	char phonenum[100];
	
	int c=0;
	for(int i=0;i<size;i++){
		if(strcmp(d[i].first,firstN)==0){
			if((strcmp(d[i].last,lastN)==0)){
				strcpy(phonenum,d[i].ph_number);
			}
		}
	}
	//printf("%s",num);
	for(int i=0;i<strlen(phonenum);i++){
		if(phonenum[i]!=' ')
			numtoken[i]=phonenum[i];
	}
	for(int i=0;i<strlen(num);i++){
		if(num[i]!=' ')
			tokenIn[i]=num[i];
	}
	for(int i=0;i<strlen(numtoken)-1;i++){
		if(tokenIn[i]==numtoken[i] || tokenIn[i]==' ' || numtoken[i]==' '){
			c=1;
		} else {		
			c=0;
			break;
		}
	}
	
	if(c==1){
		printf("\nExists\n");
		exit(0);
	}
	strcpy(d[size].first,firstN);
	strcpy(d[size].last,lastN);
	strcpy(d[size].ph_number,num);
	size=size+1;
}

 void deleteEntry(char *name){
	searchDirectory(name);
	int i;
	if(found==1){
	
	for(i=SamePos;i<size;i++){
		d[i]=d[i+1];
	}
		found=0;	
		size=size-1;
	}
	
 }

int main(int argc,char *argv[]){
	
	create(argv[1]);
	char choice;
	while(1){
		printf("\n-------------------------------------------------\n");
		printf("Please provide options:\n");
		printf("Insert		(press 1)\n");
		printf("Search		(press 2)\n");
		printf("Delete		(press 3)\n");
		printf("Show Directory	(press 4)\n");
		printf("Exit		(press 5)");
		printf("\n-------------------------------------------------\n");
		printf("Choice :-");
		scanf(" %c",&choice);
		
		switch(choice){
			case '1':
			{
				char name[100];
				char number[100];
				char s;
				printf("Enter Name :");
				char tem; int i=0;
				while((s=getchar())!=EOF && s!='\n');
				fgets(name,100,stdin);
				for(int i=0;i<strlen(name);i++)
				{
					if(name[i]=='\n')
						name[i]='\0';
				}

				printf("Enter Number :");
				scanf("%s",number);
				printf("%s",name);
				printf("%s",number);
				insert(name,number);
				break;
			}
			case '2':{
			char name[100]; char s;
			printf("Enter Name :");
				while((s=getchar())!=EOF && s!='\n');
				fgets(name,100,stdin);
				for(int i=0;i<strlen(name);i++)
				{
					if(name[i]=='\n')
						name[i]='\0';
				}
				searchDirectory(name);
			found=0;
			pos=0;
			break;
			}
			case '3':{
			char name[100]; char s;
			printf("Enter Name :");
				while((s=getchar())!=EOF && s!='\n');
				fgets(name,100,stdin);
				for(int i=0;i<strlen(name);i++)
				{
					if(name[i]=='\n')
						name[i]='\0';
				}
				deleteEntry(name);
				break;
			}
			case '4':
			randQsort();
			for(int i=0; i<size; i++){
		printf("%s %s %s\n", d[i].first, d[i].last, d[i].ph_number);
			}
			break;
			case '5':exit(0);
		}
	}
	return 0;
}






































