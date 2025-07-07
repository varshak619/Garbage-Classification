#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    FILE *fp1, *fp2; 
    int i, j, hexaddr;
    char ch, line[50], addr[10];

    // Open the input file and check if it's successfully opened
    fp1 = fopen("H.txt", "r");
    if (fp1 == NULL) {
        printf("Error opening input file!\n");
        return 1;
    }

    do {
        // Read a line from the input file
        fscanf(fp1, "%s", line);
        
        // If the line starts with 'T'
        if (line[0] == 'T') {
            // Extract the address from the line
            for (i = 1, j = 0; i <= 6; i++, j++) {
                addr[j] = line[i];
            }
            addr[j] = '\0'; // Null-terminate the address string

            // Open the temporary file for reading
            fp2 = fopen("temp.txt", "r+");
            if (fp2 == NULL) {
                printf("Error opening temp file!\n");
                fclose(fp1);
                return 1;
            }

            // Write the address to the temp file
            fprintf(fp2, "%s", addr);

            // Rewind the temp file pointer to the beginning
            rewind(fp2);

            // Read the hexadecimal address from the temp file
            fscanf(fp2, "%x", &hexaddr);
            
            fclose(fp2); // Close the temp file

            i = 9; // Start reading data after the address part

            // Process the remaining characters in the line
            while (line[i] != '\0') {
                printf("%x \t%c%c\n", hexaddr, line[i], line[i+1]);

                hexaddr += 1;  // Increment the address
                i += 2;        // Move to the next pair of characters
            }
        }

    } while (!feof(fp1)); // Continue until end of file is reached

    fclose(fp1); // Close the input file

    return 0;
}
