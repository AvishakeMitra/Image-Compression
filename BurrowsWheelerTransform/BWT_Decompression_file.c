#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 100000
int main()
{
 
  int i,j,n,len,count,lenfrle,index,ik,h,v,t3;
  unsigned char key,*p,*q;
  unsigned char *brle=calloc(MAX,sizeof(char));
  unsigned char *dbwt=calloc(MAX,sizeof(char));
  unsigned char *op2=calloc(MAX,sizeof(char));
  unsigned char *frlet=calloc(MAX,sizeof(char));
  char  *cp=calloc(MAX,sizeof(char));
  char kt[50];
  unsigned int sx;
  FILE *fp=NULL; /*input compression file pointer*/
  FILE *ft=NULL;/*output uncompress file pointer*/
  
 
  
 
 /*--------------------RLE DECOMPRESSION------------------------------*/
  x : printf("ENTER THE FILE NAME WHICH YOU WANT TO DECOMPRESS USING BWT DECOMPRESSION : ");
  scanf("%s",kt);
  puts("\n");
  ik=0;
  fp=fopen(kt,"r"); 
  if(fp==NULL)
  {
	  puts("CHECK THE FILE NAME AND TRY AGAIN\n");
	  goto x;
  }
	  
  else{
  fscanf(fp,"%d %d ",&h,&v);
  puts("DECOMPRESSING.....");
  while((cp[ik++]=fgetc(fp))!=EOF);      /*Reading compressed file for Decompression*/
  cp[--ik]='\0';
 /* puts("--Compress File Content--");*/
 /* puts("-----------------------------"); */
  /*puts(cp);*/
  strcpy(frlet,cp);

  lenfrle=strlen(frlet);
  int indx=0;
  count=0;
  for(i=0;i<lenfrle;i=i+2)
  {
  	count=frlet[i]-'0';//atoi conversion;
  	while(count>0)
  		{
  			brle[indx++]=frlet[i+1];
  			count--;
  		}
  }
  strcpy(dbwt,brle);
  /*puts("--RLE DECOMPRESS STRING(BWT CODE)--");
    puts("--------------------------------------"); */
  /*puts(dbwt);*/
  /*----------------------SORTING BWT CODE----------------------------*/
  len=strlen(brle);
  for(i=0;i<len;i++)//selection sort
  {
      for(j=i+1;j<len;j++)
   		{
			if(brle[i]>brle[j])
			{
	  			key=brle[j];
	  			brle[j] = brle[i];
	  			brle[i]=key;
	        }
   		}
  }	
   
   /*puts("----Sorted BWT code----"); 
   puts("-----------------------------");  
   puts(brle);*/
   /*---------------------- BWT DECOMPRESSION CODE---------------------*/
   len=strlen(brle)-1;
   op2[len]=dbwt[0];
   n=0;
  for(i=1;i<strlen(brle);i++)
  {
   	count=0;j=0;
   	p=&dbwt[n];
   	key=dbwt[n];
   	q=&dbwt[0];
    while(p!=q)
   		{
   			if(key==dbwt[j])
   				count++;
   			j++;	
   			q++;
   		}
   n=0;
   while(count>=0)
   		{
   			if(brle[n]==key)
   	  			count--;
   			n++;  
   		}
   		n--;
   		op2[--len]=dbwt[n];
 
 
  } 
  /*puts("--DECOMPRESS ORIGINAL STRING--");
  puts("---------------------------------");
  puts(op2+3);*/
  puts("DECOMPRESSION DONE!!!!!!");
  printf("ENTER THE FILE NAME TO SAVE THE DECOMPRESSED IMAGE : ");
  scanf("%s",kt);
  t3=strlen(kt);
  kt[t3]='.';
  kt[t3+1]='p';
  kt[t3+2]='g';
  kt[t3+3]='m';
  kt[t3+4]='\0';
  ft=fopen(kt,"w");	
 /* puts("--DECOMPRESS ORIGINAL STRING in Decimal ASCII format--");
  puts("-------------------------------------------------------");	*/
  fprintf(ft,"P2\n# Created by Abhishek\n%d %d\n255\n",h,v);
  for(i=0;i<=strlen(op2)-4;i++)
	{
       		 /*printf("%d ",op2[i+3]);*/
		 fprintf(ft,"%d ",op2[i+3]);
	}	
  
  

	
  }  
}