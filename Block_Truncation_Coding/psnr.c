#include<stdio.h>
#include<math.h>

int main(int argc,char *argv[])
{
	FILE *or_fp,*re_fp;
	double error=0.0,psnr,pix;
	int i,j,a,b,im_r,im_c;
	char s[15],t[15];
	or_fp = fopen(argv[1], "r");
	re_fp = fopen(argv[2], "r");
        while(fgetc(or_fp)!= '\n')
            ;
        fscanf(or_fp,"%d",&im_r);
        fgetc(or_fp);
        fscanf(or_fp,"%d",&im_c);
        fgetc(or_fp);
        while(fgetc(or_fp)!= '\n')
            ;
        while(fgetc(re_fp)!= '\n')
            ;
        while(fgetc(re_fp)!= '\n')
            ;
        while(fgetc(re_fp)!= '\n')
            ;
	pix=(double)im_r*im_c;
	for(i=0;i<im_r;i++)
	{
		for(j=0;j<im_c;j++)
		{
                         fscanf(or_fp,"%d",&a);
                         fgetc(or_fp);
			 fscanf(re_fp,"%d",&b);
                         fgetc(re_fp);
			 error += (pow((a-b),2)/pix);
		}
	}
	error=sqrt(error);
	printf("RMSE = %lf",error);
	psnr = 20.0 * log10((255.0)/error);
	printf("PSNR = %lf",psnr);
        return 0;
} 
