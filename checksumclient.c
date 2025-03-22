#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>
unsigned char calculate_checksum(char *data, int length,int SEGMENT_LENGTH) {
    int sum = 0;
    for (int i = 0; i < length; i += SEGMENT_LENGTH) {
        unsigned char segment = 0;
        for (int j = 0; j < SEGMENT_LENGTH; j++) {
            segment = (segment << 1) | (data[i + j] - '0');
        }
        sum += segment;
    }
	int max_size=pow(2,SEGMENT_LENGTH)-1;
    // Wrap around carry
    while (sum > max_size) {
        sum = (sum & max_size) + (sum >> SEGMENT_LENGTH);
    }

    //no One's complement of the sum
    return sum;
}
int main(){
int sd,cadl;
struct sockaddr_in sad,cad;
char codeword[41] ;
char dataword[40];
char ucodeword[40]={0};
sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
sad.sin_family=AF_INET;
sad.sin_port=htons(9997);
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sd, (struct sockaddr *)&sad, sizeof(sad));
recv(sd, codeword, sizeof(codeword),0);
printf("\n codeword recv from sender is %s \n",codeword);
/*comment out this when user input*/
/* if u take user defined then remove comment out of the  following lines*/

 /*printf("Enter the codeword:");
scanf("%s",codeword);*/
 int SEGMENT_LENGTH;
  printf("Enter the segment length:");
scanf("%d",&SEGMENT_LENGTH);
if(strlen(codeword) % SEGMENT_LENGTH!=0){
     int padding=SEGMENT_LENGTH-(strlen(codeword)%SEGMENT_LENGTH);
     for(int i=0;i<padding;++i){
         ucodeword[i]='0';
     }
    // udataword[i] = '\0';
 }
 strcat(ucodeword,codeword);
 //printf("%s",ucodeword);
unsigned char checksum = calculate_checksum(ucodeword, strlen(ucodeword),SEGMENT_LENGTH);
//unsigned int mask=((1<<SEGMENT_LENGTH)-1);
unsigned int mask=pow(2,SEGMENT_LENGTH)-1;
if (checksum ==(unsigned char)mask) {
    printf("Data received OK\n");
} else {
    printf("Data received with errors\n");
}

printf("Actual Data is: ");
strncpy(dataword,codeword,strlen(codeword)-SEGMENT_LENGTH);
printf("%s\n",dataword);
close(sd);
}
/*gcc checksumclient.c -o cclient -lm

./cclient
*/