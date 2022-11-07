/*
Author: Shyam Prasad Reddy
Email: sr2949@nau.edu
Web: https://yennashyamprasadreddy.com
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Image_File 
{
    char header[4];
    int width_of_image;
    int height_of_image;
    char data[10];
};

void stack_operation(){
    char buff[0x1000];
    while(1){
        stack_operation();
    }
}

int ProcessImage_File(char* filename){
    FILE *fp;
    struct Image_File img;

    fp = fopen(filename,"r");            //In this function processImage image will be processed.

    if(fp == NULL)
    {
        printf("\nCan't open file or file doesn't exist.\r\n");
        exit(0);
    }

    while(fread(&img,sizeof(img),1,fp)>0)
    {
        
            printf("\n\tHeader\twidth_of_image\theight\tdata\t\r\n");

            printf("\n\t%s\t%d\t%d\t%s\r\n",img.header,img.width_of_image,img.height_of_image;,img.data);
            //integer overflow 0x7FFFFFFF+1=0. Here we get crash for integer overflow

            int size1 = img.width_of_image + img.height_of_image;
            char* buff1=(char*)malloc(size1);

            //This causes heap buffer overflow vulnerability 
            memcpy(buff1,img.data,sizeof(img.data));
            free(buff1);

            //This causes double free   
            if (size1/2==0){
                free(buff1);
            }
            else{
                //this will cause use after free
                if(size1/3 == 0){
                    buff1[0]='a';
                }
            }
            //integer underflow 0-1=-1
            //negative so will cause very large memory allocation. Here we may get integer underflow crash.
            int size2 = img.width_of_image - img.height_of_image;+100;
            char* buff2=(char*)malloc(size2);

            //Here we may get heap buffer overflow
            memcpy(buff2,img.data,sizeof(img.data));

            //here we might get divide by zero
            int size3= img.width_of_image/img.height_of_image;

            char buff3[10];
            char* buff4 =(char*)malloc(size3);
            memcpy(buff4,img.data,sizeof(img.data));

            //OOBR read bytes past stack/heap buffer overflow
            char OOBR = buff3[size3];
            char OOBR_heap = buff4[size3];

            //OOBW write bytes past stack/heap buffer overflow
            buff3[size3]='c';
            buff4[size3]='c';

            if(size3>10){
                //memory leak here
                buff4=0;
            }
            else{
                free(buff4);
            }
            int size4 = img.width_of_image * img.height_of_image;
            if(size4/2==0){
                //stack exhaustion here
                stack_operation();
            }
            else{
                //heap exhaustion here
                char *buff5;
                do{
                buff5 = (char*)malloc(size4);
                }while(buff5);
            }
            free(buff2);
        

    }
    fclose(fp);
    return 0;
}

int main(int argc,char **argv)
{
    ProcessImage_File(argv[1]);
}
