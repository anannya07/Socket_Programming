#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
int sd,cd,cadl;
struct sockaddr_in sad,cad;
char str[50];
char codeword[50];
int ch,n;
sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
sad.sin_family=AF_INET;
sad.sin_port=htons(4557);
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
bind(sd, (struct sockaddr *)&sad, sizeof(sad));
listen(sd,1);
cadl=sizeof(cad);
cd=accept(sd, (struct sockaddr *)&cad, &cadl);
recv(cd, str, sizeof(str), 0);
printf("\nRecieved even parity codeword is : %s\n", str);
close(cd);
close(sd);
fflush(stdin);
printf("Enter the codeword:");

scanf("%s",codeword);
printf("1.Even parity codeword\n");
printf("2.Odd parity codeword\n");
printf("Enter your choice:");
scanf("%d",&ch);
int c=0;
for (int i = 0; i < strlen(codeword); ++i) {
    c^= (codeword[i] - '0');
}
if((ch==1 && c==0)||(ch==2 && c==1)){
    printf("Accepted\n");
    codeword[strlen(codeword) - 1] = '\0';

    printf("The original dataword is %s",codeword);
}
else{
    printf("Rejected / wrong codeword received\n");
}


}