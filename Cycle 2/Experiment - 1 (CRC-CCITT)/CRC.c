#include <stdio.h>
#include <string.h>

char data[100], crc[16], gen[17];
int len, i, j;

void calc_crc() {
    for (i = 0; i < strlen(gen); i++)
        crc[i] = data[i];
    do {
        if (crc[0] == '1') {
            for (j = 1; j < strlen(gen); j++)
                crc[j] = ((crc[j] == gen[j]) ? '0' : '1');
        }
        for (j = 0; j < strlen(gen) - 1; j++)
            crc[j] = crc[j + 1];
        crc[j] = data[i++];
    } while (i <= len + strlen(gen) - 1);
}

int main() {
    printf("Enter Bit string: ");
    scanf("%s", data);
    len = strlen(data);
   
    printf("Enter generating polynomial (16 bits): ");
    scanf("%s", gen);
    if (strlen(gen) != 16) {
        printf("Generator polynomial must be 16 bits.\n");
        return 1;
    }
   
    printf("Generating Polynomial: %s\n", gen);

    for (i = len; i < len + strlen(gen) - 1; i++)
        data[i] = '0';
   
    printf("Modified Data is: %s\n", data);
    calc_crc();
    printf("Checksum is: %s\n", crc);

    for (i = len; i < len + strlen(gen) - 1; i++)
        data[i] = crc[i - len];

    printf("Final Codeword is: %s\n", data);
    printf("Test Error detection\n1(Yes) / 0(No)? : ");
    scanf("%d", &i);

    if (i == 1) {
        printf("Enter position to insert an error: ");
        scanf("%d", &i);
        data[i] = (data[i] == '0') ? '1' : '0';
        printf("Erroneous data: %s\n", data);
    }

    calc_crc();

    for (i = 0; (i < strlen(gen) - 1) && (crc[i] != '1'); i++);

    if (i < strlen(gen) - 1)
        printf("Error detected.\n");
    else
        printf("No Error Detected.\n");

    return 0;
}