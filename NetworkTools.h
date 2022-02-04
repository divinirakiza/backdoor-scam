#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>

using namespace std;

class NetworkTools {
   private:
        string ip_address;
        
        static void check_host_name(int hostname) {
            if (hostname == -1) {
                perror("gethostname");
                exit(1);
            }
        }
        static  void check_host_entry(struct hostent * hostentry) { 
            if (hostentry == NULL){
                perror("gethostbyname");
                exit(1);
            }
        }

    public:
         static string getIPAddress() {
            char host[256];
            struct hostent *host_entry;
            int hostname;

            hostname = gethostname(host, sizeof(host)); //find the host name
            check_host_name(hostname);
            host_entry = gethostbyname(host); //find host information
            check_host_entry(host_entry);

            return inet_ntoa(*((struct in_addr*) host_entry->h_addr_list[0]));;
        }
};