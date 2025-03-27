#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>

int main(){
int sd,cd,cadl;
struct sockaddr_in sad,cad;
char ocodeword[40];// Ensures all elements are initialized to '\0'
char codeword[41]; // 32-bit dataword + 8-bit checksum + null terminator
char generator[12];
sd=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
sad.sin_family=AF_INET;
sad.sin_port=htons(9998);
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
bind(sd, (struct sockaddr *)&sad, sizeof(sad));
listen(sd,10);
cadl=sizeof(cad);
cd=accept(sd, (struct sockaddr *)&cad, &cadl);
recv(cd,ocodeword,sizeof(ocodeword),0);
printf("The received codeword is %s\n",ocodeword);
printf("Enter the codeword:");
scanf("%s",codeword);
printf("Enter the generator :\n");
scanf("%s",generator);
int i, k, len;
    int csize = strlen(codeword);
    int gsize = strlen(generator);
    
    do {
        for (i = 0; i < gsize; ++i) {
            codeword[i] = (codeword[i] == generator[i]) ? '0' : '1';
        }
        
        k = 0;
        for (i = 0; i < csize; ++i) {
            if (codeword[i] == '0') {
                k++;
            }
        }
        
        if (k == csize) {
            break;
        }
        
        while (strlen(codeword) > (gsize - 1) && codeword[0] != '1') {
            for (i = 0; i < csize; ++i) {
                codeword[i] = codeword[i + 1];
            }
            csize--;
        }
        
        len = csize;
    } while (len > gsize - 1);
    
    codeword[len] = '\0';
    
    int error_detected = 0;
    for (i = 0; i < strlen(codeword); ++i) {
        if (codeword[i] != '0') {
            error_detected = 1;
            break;
        }
    }
    
    if (error_detected) {
        printf("Error detected in entered codeword!\n");
    } else {
        printf("No errors detected. Codeword is valid.\n");
    }
close(cd);
close(sd);
}

