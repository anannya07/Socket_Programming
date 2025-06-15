#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include<arpa/inet.h>
int main(){
    int sd,cd,cad1;
    struct sockaddr_in sad,cad;
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(10000);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    bind(sd,(struct sockaddr *)&sad,sizeof(sad));
    listen(sd,10);
    cad1=sizeof(cad);
    cd=accept(sd,(struct sockaddr *)&cad,&cad1);
    char code[50],icodeword[50];
    int codeword[50];
    recv(cd,code,sizeof(code),0);
    printf("The received codeword is :%s",code);
    printf("Enter the codeword:");
    scanf("%s",icodeword);
    int m=strlen(icodeword);
    for(int i=1;i<=m;++i){
        codeword[i]=icodeword[i-1]-'0';
    }
    int totalbits=m;
    int r=0;
    while(pow(2,r)< totalbits + 1) r++;
    printf("The no of parity bits is %d\n",r);
    int pos;
    int errorpos=0;
    for(int i=0;i<r;++i){
        pos=pow(2,i);
        int parity=0;
        for(int j=1;j<=totalbits;++j){
            if(j & pos){
                parity^=codeword[j];
            }
        }
        if(parity!=0){
            errorpos+=pos;
        }
    }
    if(errorpos==0){
        printf("No Error\n");
    }
    else{
        printf("The error position is position %d\n",errorpos);
        codeword[errorpos]^=1;
       for(int i=1;i<=totalbits;++i){
        icodeword[i-1]=codeword[i]+'0';
       }
       printf("The corrected code word is %s \n",icodeword);
    }
    close(cd);
    close(sd);
}
