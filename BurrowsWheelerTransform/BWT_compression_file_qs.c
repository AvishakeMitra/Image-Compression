#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>

#define MAX 100000

int cmp(const void *p1, const void *p2)
{
	return strcmp(*(char * const *)p1, *(char * const *)p2);
}
int main()
{
  unsigned char *s=calloc(MAX,sizeof(char)); //source
  unsigned char **s2;//Destination
  unsigned char key,*p,*q,t1,t2;
  char ipname[50];
  char opname[50];
  clock_t t;
  double time_taken;
  int i,j,n,len,count,lenfrle,index,h,v,t3,sizei,sizeo;
  float percentage=0.0;
  x:printf("\nIMAGE NAME WHICH YOU WANT TO COMPRESS USING BWT COMPRESSION(don't include any extension) : ");
  scanf("%s",ipname);
  puts("\n");
  t3=strlen(ipname);
  ipname[t3]='.';
  ipname[t3+1]='p';
  ipname[t3+2]='g';
  ipname[t3+3]='m';
  ipname[t3+4]='\0';
  
  FILE *fp=NULL;
  fp=fopen(ipname,"r"); /*input orginal file pointer*/
  FILE *fq; /*output compress file pointer*/
  int ik=0;
  if(fp==NULL)
  {
	  puts("CHECK THE FILE NAME AND TRY AGAIN");
	  goto x;
  }
  else
  {	
   	t = clock();	 
	puts("Compressing 25%......");
/*-------------------------File Input-----------------------*/     
	fscanf(fp,"%c%c\n%d%d\n%d",&t1,&t2,&h,&v,&t3);
	index=3;
	while(!feof(fp))
	       	fscanf(fp, "%d ", &s[index++]);
     	
	s[index]='\0';
	s[0]=' ';
	s[1]='$';
	s[2]=' '; 
	len=strlen(s);
	/* puts(s);*/
	fclose(fp);
	puts("Compressing 40%......");
/*------------------------STRING ROTATION------------------------*/
	s2=calloc(len+5,sizeof(char *));
	for(i=0;i<=len-1;i++)//rotation of the string
	{
		key=s[len-1];
		j=len-1;
		while(j>=1)
  		{
  			s[j]=s[j-1];
  			j--;
  		}
		s[0]=key;
		s2[i]=calloc(len+5,sizeof(char));
		memcpy(s2[i],s,len+1);
	}
	s2[i]=calloc(len+5,sizeof(char));
	free(s);
       /*puts("The String after Rotation is : \n");
       puts("----------------------------------------");*/
       /*for(i=0;i<=len;i++)
		puts(s2[i]);*/
	puts("Compressing 60%......");
/*------------------------BLOCK SORTING---------------------------*/  
  
	qsort(s2,len+1, sizeof(char *), cmp);
  
	puts("Compressing 75%......");
/*---------------------BWT CODE GENERATION-------------------------*/
        /*puts("The Sorted String after Rotation is : \n");
        puts("--------------------------------------------");*/
	unsigned char *op1=calloc(len+5,sizeof(char));
	for(i=0;i<=len;i++)//bwt code generation 
	{
		/* puts(s2[i]);*/
		op1[i]=s2[i][len-1];
	}   
 
	/* puts("--BWT CODE--");
	puts("---------------"); */
	/* puts(op1+1);*/
	free(s2);
/*-------------------------RLE COMPRESSION OF BWT CODE-----------------*/
	unsigned char *frle=calloc(MAX,sizeof(char));
	int k=0;
	for(i=1;i<=len;i++)//RLE compression
	{
		count=0;
		while(op1[i]==op1[i+1])
		{
			if(count<127)
			{
				i++;
				count++;
			}
			else break;
		}
  	/*printf("%d%c ",count+1,op1[i]);*/
		frle[k]='0'+count+1;//converting itoa
		frle[++k]=op1[i];
		k++;
	}
	frle[k]='\0';
	/*puts("--RLE COMPRESSION STRING--");
	puts("-----------------------------"); */
	/*puts(frle);*/
	puts("Compressing 100%......");
	puts(".....Compression Complete Sucessfully....\n");
	t = clock() - t;
	time_taken = ((double)t)/CLOCKS_PER_SEC;
	printf("Enter the filename to save the Compressed File : ");
	scanf("%s",opname);
	fq=fopen(opname , "w" );
	fprintf(fq,"%d %d ",h,v);
	fwrite(frle , 1 , strlen(frle)+1 , fq );
	fclose(fq);
	free(frle);
  
/*--------------Calculatting the Compression Percentage-----------------*/
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
	puts("\n--------------------------------------------|");
	printf("COMPRESSION PERCENTAGE IS : %.2f%% \n",(percentage/sizei)*100);
	puts("--------------------------------------------|\n");
	fclose(fr);
	fclose(fs);
	printf("%.2f seconds is the execution time \n", time_taken);
  }
}
