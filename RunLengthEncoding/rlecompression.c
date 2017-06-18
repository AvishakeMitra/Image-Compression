#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 1000000

int main()
{	
	unsigned int *s=calloc(MAX,sizeof(char));
	unsigned int count;
	char ipname[50],opname[50];
	float percentage=0.0; 
	unsigned char t1,t2;
	int i,h,v,t3,index,sizeo,sizei;

	x:printf("\nIMAGE NAME WHICH YOU WANT TO COMPRESS USING RLE COMPRESSION(don't include any extension) : ");
	scanf("%s",ipname);
	puts("\n");
	t3=strlen(ipname);
	ipname[t3]='.';
	ipname[t3+1]='p';
	ipname[t3+2]='g';
	ipname[t3+3]='m';
	ipname[t3+4]='\0';
  
	FILE *fp=NULL;
	fp=fopen(ipname,"r"); 
	FILE *fq; 
	int ik=0;
	if(fp==NULL)
	{
		puts("CHECK THE FILE NAME AND TRY AGAIN");
		goto x;
	}
	else
	{	index=0;
		fscanf(fp,"%c%c\n%d%d\n%d\n",&t1,&t2,&h,&v,&t3);
		
		while(!feof(fp))
		{
			fscanf(fp, "%d ", &s[index++]);
     
		}
	unsigned int *frle=calloc(MAX,sizeof(char));	
	printf("Enter the filename to save the Compressed File : ");
	scanf("%s",opname);
	fq=fopen(opname , "w" );
	fprintf(fq,"%d %d ",h,v);
	for(i=0;i<index;i++)//RLE compression
	{
		count=0;
		while(s[i]==s[i+1])
		{
			
				i++;
				count++;
			
			
		}
  	fprintf(fq,"%d %d ",count+1,s[i]);
	}
	fclose(fp);
	fclose(fq);
    puts("-------COMPRESSION COMPLETE SUCESSFULLY-------");	
	FILE *fr=fopen(ipname,"r"); 
	FILE *fs=fopen(opname , "r" );
	fseek(fr, 0, SEEK_END);    
	sizei=ftell(fr);  
	sizei=(sizei/1024)+1;
	fseek(fs, 0,SEEK_END);    
	sizeo = ftell(fs);  
	sizeo=(sizeo/1024)+1;
	percentage=(sizei-sizeo);
	printf("\nOrginal Size of the given image is : %dKB\n", sizei);    
	printf("\nCompressed size of the given image is : %dKB\n", sizeo); 
	puts("--------------------------------------------");
	printf("COMPRESSION PERCENTAGE IS : %.2f%% \n",(percentage/sizei)*100);
	fclose(fr);
	fclose(fs);	
  }
}  
		