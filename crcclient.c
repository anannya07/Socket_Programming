#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
int sd,cadl,i,k,len;
char rem[50];
struct sockaddr_in sad,cad;
char dataword[50],generator[50],fcrc[50],crc[50];
sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
sad.sin_family=AF_INET;
sad.sin_port=htons(5779);
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sd, (struct sockaddr *)&sad, sizeof(sad));
recv(sd, dataword, sizeof(dataword), 0);
recv(sd, generator, sizeof(generator),0);
recv(sd,crc,sizeof(crc),0);
recv(sd,fcrc,sizeof(fcrc),0);

printf("\nDataword  recv from sender is %s \n",dataword);
printf("\nGenerator  recv from sender is %s \n",generator);
fflush(stdin);
int dsize=strlen(dataword);
int gsize=strlen(generator);
char ch;
printf("Do you want to insert any remainder:?y/n\n");
scanf("%c",&ch);
if(ch=='y'){
    printf("Enter the remainder of generator-1 bits:\n");
    scanf("%s",rem);
    strcat(dataword,rem);
    do{
        for(i=0;i<gsize;++i){
            dataword[i]=(dataword[i]==generator[i])?'0':'1';
            }
        k=0;
        for(i=0;i<dsize+gsize-1;++i){
            if(dataword[i]=='0'){
                k++;
            }
        }
        if(k==dsize+gsize-1)
            break;
        while(strlen(dataword)>(gsize-1)  && dataword[0]!='1' ){
            for(i=0;i<dsize+gsize-1;++i){
                dataword[i]=dataword[i+1];
            }
            dsize--;
        }
        len=dsize+gsize-1;
    }while(len>gsize-1);
    dataword[len]='\0';
    //printf("%s",dataword);
    int error_detected = 0;
        for (i = 0; i < strlen(dataword); ++i) {
            //printf("%c",dataword[i]);
            if (dataword[i] != '0') {
                error_detected = 1;
                break;
            }
        }

        if (error_detected) {
            printf("Wrong CRC remainder!!\n");
            printf("Correct CRC received from sender: %s\n", fcrc);
        } else {
            printf("No errors detected in received data.\n");
        }
    } else {
        printf("Ultimate CRC received from sender: %s\n", crc);
    }
close(sd);
}