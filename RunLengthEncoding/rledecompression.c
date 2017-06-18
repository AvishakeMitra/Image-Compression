#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1000000
int main()
{ 
	int i,n,index,h,v,t3;
	unsigned int *cp=calloc(MAX,sizeof(char));
	unsigned int count;
	char kt[50];
	FILE *fp=NULL;
	FILE *ft=NULL;
	
	x : printf("ENTER THE FILE NAME WHICH YOU WANT TO DECOMPRESS USING RLE DECOMPRESSION : ");
	scanf("%s",kt);
	puts("\n");
	fp=fopen(kt,"r"); 
	if(fp==NULL)
	{
	  puts("CHECK THE FILE NAME AND TRY AGAIN\n");
	  goto x;
	}
	else
	{   index=0;
		printf("ENTER THE FILE NAME TO SAVE THE DECOMPRESSED IMAGE : ");
		scanf("%s",kt);
		t3=strlen(kt);
		kt[t3]='.';
		kt[t3+1]='p';
		kt[t3+2]='g';
		kt[t3+3]='m';
		kt[t3+4]='\0';
		ft=fopen(kt,"w");
		fscanf(fp,"%d %d ",&h,&v);	
	    fprintf(ft,"P2\n# Created by\n%d %d\n255\n",h,v);
		while(!feof(fp))
		{
			fscanf(fp, "%d ", &cp[index++]);
     
		}
		count=0;
		for(i=0;cp[i]!=0 && cp[i+1]!=0;i=i+2)
		{
			count=cp[i];
			while(count>0)
			{    
		
				fprintf(ft,"%d ",cp[i+1]);
				count--;
			}
			
		}				
		
	}
    return 0;
}