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
    return ~sum;
}
int main(){
int sd,cadl;
struct sockaddr_in sad,cad;
char codeword[41] ;
char dataword[40];
char udataword[50]={0};
sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
sad.sin_family=AF_INET;
sad.sin_port=htons(9999);
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sd, (struct sockaddr *)&sad, sizeof(sad));
printf("Enter the dataword:");
scanf("%s",dataword);
int SEGMENT_LENGTH;
int i;
strcpy(codeword, dataword);
printf("Enter the segment length:");
scanf("%d",&SEGMENT_LENGTH);
 if(strlen(dataword) % SEGMENT_LENGTH!=0){
     int padding=SEGMENT_LENGTH-(strlen(dataword)%SEGMENT_LENGTH);
     for(i=0;i<padding;++i){
         udataword[i]='0';
     }
 }
 strcat(udataword,dataword);
 strcpy(dataword,udataword);
unsigned char checksum = calculate_checksum(dataword, strlen(dataword),SEGMENT_LENGTH);

printf("Checksum: ");
for (int i = SEGMENT_LENGTH-1; i >= 0; i--) {
    printf("%d", (checksum >> i) & 1);
}
printf("\n");


char checksum_binary[9] = {0};
for (int i = SEGMENT_LENGTH-1; i >= 0; i--) {
    checksum_binary[(SEGMENT_LENGTH-1) - i] = ((checksum >> i) & 1) + '0';
}
strcat(codeword, checksum_binary);
printf("Codeword: %s\n", codeword);


send(sd, codeword, sizeof(codeword), 0);
/*recv(cd, str, sizeof(str), 0);
printf("\nRecieved data is : %s\n", str);*/
close(sd);
}
/*gcc checksumclient.c -o cclient -lm

./cclient
*/
