#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
 
int ar_mean(int *,int);
int st_dev(int *,int,int);

/*DECLARATION OF GLOBAL VARIABLES AND ARRAYS*/
unsigned int dim_r,dim_c;
unsigned int mat[1024][1024];
unsigned int c_mat[1024][1024];

/*FUNCTION MAIN*/
int main()
{
	FILE *fp,*cp;						/*FILE POINTER FOR UNCOMPRESSED AND COMPRESSION FILE*/  
	int i,j,m=4,n=4,n_count=0,val_c=0,val_r=0,*tp=NULL,mean=0,k=0,blk=0,var_n=0,blk_row=0,l=0,b_mat[4][1024];
	char c,f_name[100],f_ty[]={'.','p','g','m','\0'};
        if(argc != 2){
            printf("\n*********PLEASE PROVIDE AN INPUT FILE NAME*********\n\n");
            exit(0);
        }
        strcpy(f_name,argv[1]);
        strcat(f_name,f_ty);
	fp = fopen(f_name,"r");				/*RAW IMAGE FILE OPENED*/	
	if(fp == NULL)
		printf("\n\nCann't open file");
	while(fgetc(fp)!='\n')
                ;
	/*IMAGE DIMENSION ROW AND COLUMN IS STORED*/
	fscanf(fp,"%d",&dim_r);					
	fgetc(fp);
	fscanf(fp,"%d",&dim_c);
	fgetc(fp);
	while(fgetc(fp)!='\n')
       		;
	/*COLUMN AND ROW DIMENSION CHECK*/
	if(dim_c%4 == 0)
		val_c = dim_c;
	else{
		val_c=dim_c+4;		
		val_c=val_c-(val_c%4);
	}
	if(dim_r%4 == 0)
		val_r = dim_r;
	else{
		val_r = dim_r+4;
		val_r = val_r-(val_c%4);
	}
	
	/*DATA EXTRACTION TO THE MATRIX FROM FILE*/
	for(i=0;i<dim_r;i++){
		for(j=0;j<dim_c;j++){
			fscanf(fp,"%d",&mat[i][j]);	/*DATA COPIED INTO MATRIX FROM FILE*/
			fgetc(fp);
			}
		for(;j<val_c;j++)
			mat[i][j]=0;
		}
	for(;i<val_r;i++){
		for(j=0;j<val_c;j++)
			mat[i][j]=0;
	}
	printf("\n\n\ndata extraction complete......\n\n");
	fclose(fp);					/*DATA EXTRACTION COMPLETE*/
	
	/*DATA COMPRESSION*/
	cp=fopen("comp","w");
	fp=fopen("me_sdev","w");				/*HERE FP USED TO WRITE MEAN AND S.D. IN A FILE*/  
	tp=(int *)malloc((m*n)*sizeof(int));
	fprintf(cp,"%d%c%d%c",dim_r,' ',dim_c,'\n');
	printf("\nCOMPRESSING IMAGE..");
	for(blk_row=1;blk_row<=(val_r/m);blk_row++){
		for(i=(blk_row*m)-m,k=0;i<blk_row*m;i++,k++){		
			for(j=0;j<val_c;j++){			/*HERE EACH BLOCK IS RETRIEVED FROM MATRIX AND TEMPORARILY STORED IN AN ARRAY*/ 
				b_mat[k][j] = mat[i][j];		
			}
		}
		for(blk=1;blk<=(val_c/n);blk++){
			for(l=0,k=0;l<m;l++){
				for(j=(blk*n)-n;j<blk*n;j++){
					tp[k] = b_mat[l][j];
					k++;
				}
			}
			mean = ar_mean(tp,m*n);
			var_n = st_dev(tp,mean,m*n);
			for(l=0,k=0;l<m;l++){
				for(j=(blk*n)-n;j<blk*n;j++){
					if(tp[k]>mean)
						b_mat[l][j] = 1;
					else
						b_mat[l][j] = 0;
				k++;
				}
			}
			fprintf(fp,"%d%c%d%c",mean,' ',var_n,' ');
		}
		for(i=(blk_row*m)-m,k=0;i<blk_row*m;i++,k++){
			for(j=0;j<val_c;j++){
				c_mat[i][j] = b_mat[k][j];
			}
		}
		fprintf(fp,"%c",'\n');				/*END OF A SUB ROW*/
                printf(".");
	}							/*END OF COMPRESSION*/	
	printf("\n\nIMAGE SUCCESFULLY COMPRESSED");
	printf("\n\n");
	for(i=0;i<val_r;i++){
                for(j=0;j<val_c;j++){
                        fprintf(cp,"%d",c_mat[i][j]);
		}
		fprintf(cp,"%c",'\n');
	}		
	fclose(fp);
	fclose(cp);
return 0;        
}

/*FUNCTION MEAN*/

int ar_mean(int *ap,int freq)
{
	int i,sum=0;
	for(i=0;i<freq;i++)
		sum=sum+ap[i];
	return(sum/freq);
}

/*FUNCTION STANDARD DEVIATION*/
int st_dev(int *ap,int mean,int freq)
{
	int sum=0,i,*tp=NULL;
	tp=(int *)malloc(freq*sizeof(int));
	for(i=0;i<freq;i++)
		tp[i]=mean-ap[i];
	for(i=0;i<freq;i++)
		sum=sum+pow(tp[i],2);
	return(sqrt(sum/freq));	
}
