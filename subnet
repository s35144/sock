#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calculateSubnetAddresses(const char* ip, int numSubnets, char** subnetAddresses) {
    // Extracting the IP address and subnet mask from the input string
    char ipAddress[16];
    int subnetMask;
    sscanf(ip, "%[^/]/%d", ipAddress, &subnetMask);

    // Converting the IP address to octets
    char octets[4][4];
    sscanf(ipAddress, "%[^.].%[^.].%[^.].%[^.]", octets[0], octets[1], octets[2], octets[3]);

    // Calculating the number of host bits and subnet size
    int numHostBits = 32 - subnetMask;
    int subnetSize = 1 << numHostBits;

    // Calculating the subnet addresses
    int i;
    for (i = 0; i < numSubnets; ++i) {
        int subnetID = i * subnetSize;
        int octetIndex = subnetID / 256;
        int remainder = subnetID % 256;

        // Constructing the subnet address
        sprintf(subnetAddresses[i], "%s.%s.%s.%d", octets[0], octets[1], octets[2], remainder);

        // Updating the octets to reflect the next subnet
        if (subnetID / 256 > 0) {
            int carry = subnetID / 256;
            int j;
            for (j = 3; j >= octetIndex; --j) {
                int currentOctet = atoi(octets[j]);
                int newOctet = (currentOctet + carry) % 256;
                carry = (currentOctet + carry) / 256;
                sprintf(octets[j], "%d", newOctet);
            }
        }
    }
}

int main() {
    char ip[20];
    int numSubnets;
    int i;

    printf("Enter the classless IP address and number of subnets: ");
    scanf("%s %d", ip, &numSubnets);

    char** subnetAddresses = (char**)malloc(numSubnets * sizeof(char*));
    for (i = 0; i < numSubnets; ++i) {
        subnetAddresses[i] = (char*)malloc(16 * sizeof(char));
    }

    calculateSubnetAddresses(ip, numSubnets, subnetAddresses);

    printf("Subnet Addresses:\n");
    for (i = 0; i < numSubnets; ++i) {
        printf("%s\n", subnetAddresses[i]);
    }

    // Freeing the allocated memory
    for (i = 0; i < numSubnets; ++i) {
        free(subnetAddresses[i]);
    }
    free(subnetAddresses);

    return 0;
}
