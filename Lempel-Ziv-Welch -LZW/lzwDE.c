#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define size 100000
void main()
{
 unsigned char *c[65536];
 int i,index,j,l;
 char *t;
 char *p1=NULL;
 unsigned char o[size], n[size],ch[size];
 n[0]='\0';
 int  old, ne,id,t1,f,p;
 index=0;
 j=0;
 l=0;
 id=0;
 t1=255;
 FILE *Fp=fopen("compress_output.txt","r");
 FILE *Ft=fopen("decompress_output.txt","w");
 for (i=0;i<256;i++)
   {
		t =(char*)calloc(2,sizeof(char));
		*t=(char)i;
		c[i]=t;
		t=NULL;
   }
 int *s=calloc(size,sizeof(int));
 while(!feof(Fp))
   {
        fscanf(Fp,"%d ", &s[index++]);

   }
 for(i=0;i<7;i++)
        printf("%d  ",s[i]);  
	
 old=s[id];
 
 while(j!=old)
		j++;
 	
 fprintf(Ft,"%d ",c[j][0]);
 strcpy(o,c[j]);
 id=id+1;
 while(s[id]>0)
   {
	  ne=s[id];
	  f=0;
	  for(j=0;j<=t1;j++)
	  {
			if(j==ne)
			{
				f=1;
				break;
			}
	  } 
      if (f==0)
      {
		strcpy(n,o);	
        strcat(n,ch);
      }
	  else
	  {
		 strcpy (n,c[j]); 
	  }	  
      l=strlen(n);
      for(p=0;p<l;p++)
      fprintf(Ft,"%d ",n[p]);
	  ch[0]=n[0];
	  ch[1]='\0';
	  strcat(o,ch);
	  l=strlen(o);
	  p1=(char*)calloc(l,sizeof(char));
	  strcpy(p1,o);
      c[++t1]=p1;
      old=ne;
	  strcpy(o,n);
	  id++;
   }
}