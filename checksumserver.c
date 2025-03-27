#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>
unsigned char calculate_checksum(char *dataword, int length,int SEGMENT_LENGTH ) {
    int sum = 0;
    for (int i = 0; i < length; i += SEGMENT_LENGTH) {
        unsigned char segment = 0;
        for (int j = 0; j < SEGMENT_LENGTH; j++) {
            segment = (segment << 1) | (dataword[i + j] - '0');
        }
        sum += segment;
    }
	int max_size=pow(2,SEGMENT_LENGTH)-1;
    // Wrap around carry
    while (sum > max_size) {
        sum = (sum & max_size) + (sum >> SEGMENT_LENGTH);
    }

    // One's complement of the sum
    return sum;
}

int main(){
int sd,cd,cadl;
struct sockaddr_in sad,cad;
char ucodeword[33]; // 32-bit dataword
char codeword[40];// Ensures all elements are initialized to '\0'
char codeword1[41]; // 32-bit dataword + 8-bit checksum + null terminator
char dataword[40];
sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
sad.sin_family=AF_INET;
sad.sin_port=htons(9999);
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
bind(sd, (struct sockaddr *)&sad, sizeof(sad));
listen(sd,10);
cadl=sizeof(cad);
cd=accept(sd, (struct sockaddr *)&cad, &cadl);
recv(cd,codeword,sizeof(codeword),0);
printf("The received codeword is %s\n",codeword);
printf("Enter the codeword:");
scanf("%s",codeword1);
    int SEGMENT_LENGTH;
    int i;
    printf("Enter the segment length:");
    scanf("%d",&SEGMENT_LENGTH);
     if(strlen(codeword1) % SEGMENT_LENGTH!=0){
     	int padding=SEGMENT_LENGTH-(strlen(codeword1)%SEGMENT_LENGTH);
	 	for(i=0;i<padding;++i){
	 		ucodeword[i]='0';
		 }
	 }
	 strcat(ucodeword,codeword1);
    // printf("%s\n",ucodeword);
    unsigned char checksum = calculate_checksum(ucodeword, strlen(ucodeword),SEGMENT_LENGTH);
	
    unsigned int mask=pow(2,SEGMENT_LENGTH)-1;
if (checksum ==(unsigned char)mask) {
    printf("Data received OK\n");
} else {
    printf("Data received with errors\n");
}

printf("Actual Data is: ");
strncpy(dataword,codeword1,strlen(codeword1)-SEGMENT_LENGTH);
printf("%s\n",dataword);

close(cd);
close(sd);
}
/* gcc checksumserver.c -o checksumserver -lm
rver -lm

./checksumserver*/
