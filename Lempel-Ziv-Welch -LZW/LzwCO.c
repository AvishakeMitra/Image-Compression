#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 100000
int main()
{
 char *c[65536];
 char *p1=NULL;
 char *t=NULL;
 int i,j,r,f,t1,l,w,index;
 FILE *fp=fopen("uncompress_input.txt","r");
 FILE *ft=fopen("compress_output.txt","w");
 j=0;
 t1=255;
 for (i=0;i<256;i++)                   
   {
		t =(char*)calloc(2,sizeof(char));
		*t=(char)i;
		c[i]=t;
		t=NULL;
   }

//.......................................................
// for ( i=0;i<256;i++)
     //{
      //printf("%d    ",i);
      //puts(c[i]);
     //}
//.......................................................  
  char nc[size];
  unsigned char *s=calloc(size,sizeof(char));
  char *cc=calloc (size,sizeof(char));
  /*puts("ip");
  gets(s);*/
  index=0;
  while(!feof(fp))
  {
        fscanf(fp, "%d ", &s[index++]);
     
   }
   s[index]='\0';
  
  char p;
  char q;
 
  p=s[j++];
  q=s[j];
  cc[0]=p;
  cc[1]='\0';
  nc[0]=q;
  nc[1]='\0';
//.......................................................
 while (s[j]!='\0')
  {
	  char tf[size]; 
	  strcpy(tf,cc);
	  strcat(cc,nc);
	  f=0;
      for (i=0;i<=t1;i++)
      {   
          r=strcmp(c[i],cc);
          //printf("%d",r);
          if (r==0)
          {
              f=1;
              break;
          }
       }
       if (f==0)
       {   
           l=strlen(cc);
           p1=(char*)calloc(l,sizeof(char));
           strcpy(p1,cc);
           //puts("----");
           //puts(cc);
		   c[++t1]=p1;
		   cc[0]=nc[0];
           cc[1]='\0';
		   nc[0]=s[++j];
           nc[1]='\0';
           //puts(cc);
           //puts(nc);
       for ( i=0;i<=t1;i++)
        {
		 w=strcmp(c[i],tf);
		 if(w==0)
         fprintf(ft,"%d ",i);
         //puts(c[i]);
        }
	   }
       else
       {    
          // puts("****");
          // puts(cc);
           nc[0]=s[++j]; 
		   nc[1]='\0';
       } 
  }
  strcat(cc,nc);
  for ( i=0;i<=t1;i++)
        {
		 w=strcmp(c[i],cc);
		 if(w==0)
         fprintf(ft,"%d ",i);
         
        }
    
  /* for ( i=256;i<=t1;i++)
     {
      printf("\n%d  ",i);
      puts(c[i]);
     }*/
	 fclose(ft);
	 fclose(fp);
     return(0);
}