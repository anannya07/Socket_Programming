#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
int sd,cd,cadl;
struct sockaddr_in sad,cad;
char dataword[50],generator[50],crc[50];
int i,k,len;
sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
sad.sin_family=AF_INET;
sad.sin_port=htons(5779);
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
bind(sd, (struct sockaddr *)&sad, sizeof(sad));
listen(sd,1);
cadl=sizeof(cad);
cd=accept(sd, (struct sockaddr *)&cad, &cadl);
printf("Enter the dataword:");
scanf("%s",dataword);
send(cd, dataword, sizeof(dataword), 0);
strcpy(crc,dataword);
printf("Enter the generator or in polynomial form:");
scanf("%s",generator);
send(cd, generator, sizeof(generator), 0);
int dsize=strlen(dataword);
int gsize=strlen(generator);
// first add 0's for generator-1
    for( i=0;i<gsize-1;++i){
        dataword[dsize+i]='0';
    }
    dataword[dsize+gsize-1]='\0';
    printf("%s\n",dataword);
    // now perfprm the modulo 2 division
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

    fflush(stdin);

printf("The dataword with crc is %s\n",dataword);
send(cd, dataword, sizeof(dataword), 0);
strcat(crc,dataword);

printf("The dataword transmitted is: %s\n",crc);
send(cd,crc,sizeof(crc),0);
close(cd);
close(sd);
}