#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<math.h>
#include<arpa/inet.h>
int main(){
    int sd,cad1;
    struct sockaddr_in sad,cad;
    sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    sad.sin_family=AF_INET;
    sad.sin_port=htons(10000);
    sad.sin_addr.s_addr=inet_addr("127.0.0.1");
    connect(sd,(struct sockaddr *)&sad,sizeof(sad));
    char data[50],data1[50],codeword[50];
    int code[50];
    printf("Enter the dataword:");
    scanf("%s",data);
    int r=0;
    int i,j,k;
    int m=strlen(data);
    while(pow(2,r)<(m+r+1)) r++;
    printf("The no of parity bits is %d\n",r);
    int totalbits=m+r;
    for( i=0;i<m;++i){
        data1[i]=data[i]-'0';
    }
    for(i=1,j=0,k=0;i<=totalbits;++i){
        if(i==pow(2,j)){
            code[i]=-1;
            j++;
        }
        else{
            code[i]=data1[k++];
        }
    }
    int pos;
    for(i=0;i<r;++i){
        pos=pow(2,i);
        int parity=0;
        for(j=pos;j<=totalbits;++j){
            if(j & pos && code[j]!=-1)
                parity^=code[j];
        }
        code[pos]=parity;
    }
    for(i=1;i<=totalbits;++i){
        codeword[i-1]=code[i]+'0';
    }
    codeword[totalbits]='\0';
    printf("The codeword is %s\n",codeword);
    send(sd,codeword,sizeof(codeword),0);
    close(sd);
}
