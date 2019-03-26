#include <pcap.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *device; /* Name of device (e.g. eth0, wlan0) */
    char error_buffer[PCAP_ERRBUF_SIZE]; /* Size defined in pcap.h */

    /* Find a device */
    device = pcap_lookupdev(error_buffer);
    if (device == NULL) {
        printf("Error finding device: %s\n", error_buffer);
        return 1;
    }
    printf("Device: %s\n",device );

    unsigned char ip_address[15],old_ip_address[15];
    int fd;
    struct ifreq ifr;		//Socket interface structure
    struct sockaddr_in *addr;
     
     
    /*AF_INET - to define network interface IPv4*/
    /*Creating soket for it.*/
    fd = socket(AF_INET, SOCK_DGRAM, 0);	//(IPV4_protocol,UDP(unreliable),IP)
     
    /*AF_INET - to define IPv4 Address type.*/
    ifr.ifr_addr.sa_family = AF_INET;
     
    /*device_name - define the ifr_name - port name
    where network attached.*/
    memcpy(ifr.ifr_name, device, IFNAMSIZ-1);
     
    /*defining the sockaddr_in*/
    addr=(struct sockaddr_in *)&ifr.ifr_addr;

    //Display old address
    memset((unsigned char*)old_ip_address,0x20,15);
    ioctl(fd, SIOCGIFADDR, &ifr);
    /*Extracting Ip Address*/
    strcpy(old_ip_address,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
    printf("Old ip address%s\n",old_ip_address );

     /*Read IP Address*/
    printf("Enter Ip Address: ");   //New IP address
    scanf("%s",ip_address);
    
    /*convert ip address in correct format to write.. Convert to binary*/
    inet_pton(AF_INET,ip_address,&addr->sin_addr); //(ipv4,source,destination)
     
    /*Setting the Ip Address using ioctl*/
    int io= ioctl(fd, SIOCSIFADDR, &ifr);	//Set ip address

    close(fd);
	printf("IP Address updated sucessfully.\n");

     
    /*Getting the Ip Address after Updating.*/
     
    /*clear ip_address buffer with 0x20- space*/
    memset((unsigned char*)ip_address,0x20,15);
    ioctl(fd, SIOCGIFADDR, &ifr);
    /*Extracting Ip Address*/
    strcpy(ip_address,inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
     
    printf("Updated IP Address is: %s\n",ip_address);
     
    return 0;
}