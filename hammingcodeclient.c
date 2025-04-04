#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<math.h>
int main(){
int sd,cadl;
struct sockaddr_in sad,cad;

    char data[100];
	int data1[100],data2[100];
	int dl,r,i=0,j=0,k=0,z,c;


sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
sad.sin_family=AF_INET;
sad.sin_port=htons(9997);
sad.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sd, (struct sockaddr *)&sad, sizeof(sad));




printf("\n Enter the dataword: "); //taking input in string	
scanf("%s",data);
dl=strlen(data);	//length of the input string

while(1)	//finding number of parity bits
{
    if(pow(2,i)>=dl+i+1)
        break;
    i++;	
}
r=i;	//storing number of parity bits into r variable
printf("\n No of redundant bits: %d \n",r);

for(i=0;i<dl;i++)	//conversion of string data into integer
{
    data1[i]=data[i]-48;    //data1 array is used to store only integer data
}

for(i=0;i<r;i++)	//initialising parity bits' positions with some value (say 999) in data2 array
    {
        z=pow(2,i);
        data2[z]=999;	//data2 array is used to store data+parity bits
    }
    
for(i=dl+r;i>=1;i--)	//this loop is used to place the data bits and parity bits at fixed positions 
{
    if(data2[i]!=999)	
        {
        data2[i]=data1[j];	//if it's not a parity bit, store the data bit in reverse order
        j++;
        }    
}

for(i=0;i<r;i++)	//outer loop is used to find the values for each parity bit
{
    z=pow(2,i);		//finding position of each parity bit
    c=0;			//initializing counter c
    //printf("for %d iteration :",i+1);
    for(j=z;j<=dl+r;j=z+k)	//inner loop is used to add data bits related to each parity bit
    {	
        //printf("j=%d\n",j);
        for(k=j;k<z+j;k++)	//this loop is for part by part parity calculation
        {
            //printf("k=%d\n",k);
            if(k<=dl+r)
            {
                if(data2[k]!=999)	//if k is not a parity bit
                {
                    c=c+data2[k];	//add the value of that position with counter c
                }	
            }		
        }
    }
    data2[z]=c%2;	//parity bit value
}

printf("\n The codeword is: ");
j=0;

for(i=dl+r;i>=1;i--)
    {
    printf("%d",data2[i]);
    }
    char codeword[20];
    
    // Assuming `dl + r` is within array bounds
    for (i = dl + r; i >= 1; i--) {
        codeword[dl+r-i] = data2[i] + '0'; // Fix indexing
    }
    
    codeword[dl + r] = '\0';  // Null-terminate the string
    
   // printf("\n%s\n", codeword);
    send(sd, codeword, sizeof(codeword), 0); // Send only the meaningful part
/*recv(cd, str, sizeof(str), 0);
printf("\nRecieved data is : %s\n", str);*/
close(sd);
}
/*gcc checksumclient.c -o cclient -lm

./cclient
*/
