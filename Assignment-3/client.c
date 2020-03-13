// Client side C/C++ program to demonstrate Socket programming 
#include <stdio.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <unistd.h> 
#include<ctype.h>
#include <string.h> 
#include<stdlib.h>
int PORT=0; 

#define MAXLINE 1024

int main(int argc, char const *argv[]) 
{ 
	//Checking Command line argument
	if(argc<3)
	{
		perror("IP/PORT MISSING\n");
		return 0;
	}

	for(int i=0;argv[2][i]!='\0';i++)
	{
		if(!isdigit(argv[2][i]))	//Invalid PORT
		{
			perror("INVALID PORT\n");
			return 0;
		}
		PORT*=10;
		PORT+=(argv[2][i]-48);
	}

	int sock = 0, valread; 
	struct sockaddr_in serv_addr; 
	struct sockaddr_in servaddr, cliaddr; 
	char *ask_udp_port = "1"; 
	char buffer[1024] = {0}; 
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
	{ 
		printf("\n Socket creation error \n"); 
		return -1; 
	} 

	serv_addr.sin_family = AF_INET; 
	serv_addr.sin_port = htons(PORT); 
	
	// Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, argv[1], &serv_addr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 
	printf("Connecting with Server...\n");
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{ 
		printf("\nConnection Failed \n"); 
		return -1; 
	} 
	printf("Connected\n");
	int udp_port=0;
	while(1){
		printf("Asking UDP PORT\n");
		send(sock , ask_udp_port , strlen(ask_udp_port) , 0 ); 
		valread = read( sock , buffer, 1024); 
		printf("Message Recieved:%s\n",buffer );
		if(buffer[0]=='2')
		{printf("TYPE-2 Message Recieved\n");
			int len=buffer[1]-48;
			int i=3;
			while(len>0&&isdigit(buffer[i]))
			{
				udp_port*=10;
				udp_port+=(buffer[i++]-48);
				len--;
			}
			printf("len: %d\n",len);
			if(len==0)
				break;
			udp_port=0;
		}
	}
	printf("UDP PORT: %d\n",udp_port);
	printf("Closing existing TCP Connection\n");
	close(sock);
	printf("Enter message to send(Maximum 500 characters):\n");
	printf("Message Length(>0):");
	
	int len2;
	scanf("%d",&len2);
	if(len2<=0)
	{
		perror("INVALID LENGTH\n");
			return 0;
	}
	
	printf("\n");
	//Reading remaining \n
	char c;
	scanf("%c",&c);
	printf("Length: %d\n",len2);
	printf("Message:");
	char msg[1000];
	int i=0;
	msg[0]='3';
	char temp[4];
	int len3=len2;
	while(len2!=0)
	{
		temp[i++]=(len2%10+48);
		len2/=10;
	}
	int j=1;
	i--;
	while(i>=0)
	{
		msg[j++]=temp[i--];
	}
	msg[j++]='$';
	i=j;
	len2=len3;
	j=0;
	while(j<len2)
	{
		scanf("%c",msg+i);
		i++;
		j++;
	}
	msg[i]='\0';
	printf("Sending TYPE-3 Message:");
	for(int i=0;msg[i]!='\0';i++)
		printf("%c",msg[i]);
	printf("\n");
	// Creating socket file descriptor for UDP
    if ( (sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 

    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_port = htons(udp_port); 
    // Convert IPv4 and IPv6 addresses from text to binary form 
	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr)<=0) 
	{ 
		printf("\nInvalid address/ Address not supported \n"); 
		return -1; 
	} 

    printf("Sending message to Server\n");
    sendto(sock, msg, strlen(msg), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr));

    int n,len;
    while(1)
    {
    	n = recvfrom(sock, (char *)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
    buffer[n] = '\0'; 
    printf("Message Recieved : %s\n", buffer);
    if(buffer[0]=='4'){
    	printf("TYPE-4 Message Recieved\n");
    	break;
    }
    }

    close(sock);
    printf("Removing UDP Socket\n");


	
	return 0; 
} 
