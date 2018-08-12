#include<stdio.h>
#include<string.h>
#include<math.h>
#include<stdlib.h>

unsigned int dim_r,dim_c;
unsigned int comp_mat[1024][1024],uncomp_mat[1024][1024];

int main(int argc,char *argv[]){
FILE *cpf=NULL,*msf=NULL,*ucf=NULL;
int a=0,b=0,i=0,j=0,p=0,q=0,m=4,n=4,val_c=0,val_r=0,*tp=NULL,mean=0,k=0,blk=0,var_n=0,blk_row=0,l=0,b_mat[4][1024];
char f_name[20],header_str[]={'P','2','\n','\0'},c,f_typ[]={'.','p','g','m'};
if(argc != 2){
    printf("\n*********PLEASE PROVIDE A FILE NAME FOR DECOMPRESSED FILE*********\n\n");
            exit(0);
}
strcpy(f_name,argv[1]);
strcat(f_name,f_typ);        
cpf=fopen("comp","r");
msf=fopen("me_sdev","r");
ucf=fopen(f_name,"w");
if(cpf == NULL || msf == NULL){
    printf("\n\nUNABLE TO OPEN COMPRESSED FILE..\n\n\nPLEASE CHECK FOR THE COMPRESSED FILE...\n");
    exit(0);
}
if(ucf == NULL){
    printf("\n\nUNABLE TO CREATE DECOMPRESSED FILE...");
    exit(0);
}
fscanf(cpf,"%d",&dim_r);
fgetc(cpf);
fscanf(cpf,"%d",&dim_c);
fgetc(cpf);
if(dim_c%n == 0)
	val_c = dim_c;
else{
	val_c = dim_c+n;		
	val_c = val_c-(val_c%n);
}
if(dim_r%m == 0)
	val_r = dim_r;
else{
	val_r = dim_r+m;
	val_r = val_r-(val_c%m);
}
for(i=0;i<val_r;i++){
	for(j=0;j<val_c;j++){
                c=fgetc(cpf);
		if(c=='\n')
			c=fgetc(cpf);
                if(c=='1')
			comp_mat[i][j]=1;
		else
			comp_mat[i][j]=0;
                }
}
fclose(cpf);
printf("/*\n\nDATA EXTRACTION COMPLETED*/");

fprintf(ucf,"%s%c%d%c%d%c%d%c",header_str,'\n',dim_r,' ',dim_c,'\n',255,'\n');		/*HEADER OF REGENERATED IMAGE*/
tp=(int *)malloc((m*n)*sizeof(int));
/*PERFORMING DECOMPRESSION*/
printf("\n\nDECOMPRESSING");
for(blk_row=1;blk_row<=(val_r/m);blk_row++){
	for(i=(blk_row*m)-m,k=0;i<blk_row*m;i++,k++){
                for(j=0;j<val_c;j++){ 			        /*HERE EACH BLOCK IS RETRIEVED FROM MATRIX AND TEMPORARILY STORED IN A 2D ARRAY*/
			b_mat[k][j]=comp_mat[i][j];
                        }
	}
        for(blk=1;blk<=(val_c/n);blk++){
                q=0;
		for(l=0,k=0;l<m;l++){
			for(j=(blk*n)-n;j<blk*n;j++){
				//printf("%d",b_mat[l][j]);
				tp[k] = b_mat[l][j];
				k++;
			}
		}
		for(k=0;k<m*n;k++){
			if(tp[k]==1)
				q++;
		}
		fscanf(msf,"%d",&mean);				/*MEAN PICKED UP FROM FILE*/
		fgetc(msf);
		fscanf(msf,"%d",&var_n);				/*VARIANCE PICKED UP FROM FILE*/
		fgetc(msf);
                if(q==(m*n))
			b=mean;
		else	
			a = mean - ( var_n * sqrt(q / ((m*n) - q)));	/*COMPUTATION OF A*/
		if(q==0)
			a=mean;
		else
			b = mean + ( var_n * sqrt(((m*n) - q) / q));	/*COMPUTATION OF B*/
		for(l=0,k=0;l<m;l++){
			for(j=(blk*n)-n;j<blk*n;j++){
                		if(tp[k] == 0)
					b_mat[l][j] = a;
				else
					b_mat[l][j] = b;
                                k++;
			}
		}
		for(l=0,k=0;l<m;l++){
			for(j=(blk*n)-n;j<blk*n;j++){
				;
                        }
		}
	}
	for(i=(blk_row*m)-m;i<blk_row*m;i++,k++){
		for(j=0;j<val_c;j++){
			uncomp_mat[i][j] = b_mat[k][j];
		}
	}
	printf(".");
}
printf("\n\nDECOMPRESSION SUCCESFUL....\n\n\n");
for(i=0;i<dim_r;i++){
    for(j=0;j<dim_c;j++){
        fprintf(ucf,"%d%c",uncomp_mat[i][j],' ');
    }
}    
fclose(msf);
fclose(ucf);
return 0; 
} 
