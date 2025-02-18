#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(){
int sd,cadl;
struct sockaddr_in sad,cad;
char dataword[50];
sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
sad.sin_family=AF_INET;
sad.sin_port=htons(4557);
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sd, (struct sockaddr *)&sad, sizeof(sad));

printf("Enter the dataword: ");
fflush(stdout);

scanf("%s", dataword);
int c = 0;
for (int i = 0; i < strlen(dataword); ++i) {
    c = c ^ (dataword[i] - '0');
}

if (c == 0)
    strcat(dataword, "0");
else
    strcat(dataword, "1");

printf("\nEven parity bit: %d\n", c);
printf("\nOdd parity bit: %d\n", 1 ^ c);
printf("\nEven parity codeword: %s\n", dataword);

if (c == 0)
    dataword[strlen(dataword) - 1] = '1';
else
    dataword[strlen(dataword) - 1] = '0';

printf("\nOdd parity codeword: %s\n", dataword);

send(sd, dataword, strlen(dataword) + 1, 0);

close(sd);
}