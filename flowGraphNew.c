#include <stdio.h>
#include <string.h>

char tac[100][100];
int leaders[100] = {0}, total = 0;

void mark_leaders() {
    leaders[0] = 1; // First line is always a leader

    for (int i = 0; i < total; i++) {
        // Mark labels (e.g., L1:) as leaders
        if (strchr(tac[i], ':')) {
            leaders[i] = 1;
        }

        // Handle goto and conditional jumps
        if (strstr(tac[i], "goto")) {
            // Next instruction is a leader (fallthrough)
            if (i + 1 < total) {
                leaders[i + 1] = 1;
            }

            // Jump target (e.g., goto L1)
            char label[20];
            sscanf(tac[i], "%*[^g]goto %s", label);
            for (int j = 0; j < total; j++) {
                if (strncmp(tac[j], label, strlen(label)) == 0 && tac[j][strlen(label)] == ':') {
                    leaders[j] = 1;
                }
            }
        }
    }
}

void print_blocks() {
    printf("\nBasic Blocks:\n");
    for (int i = 0; i < total; i++) {
        if (leaders[i]) printf("\nBlock:\n");
        printf("  %s\n", tac[i]);
    }
}

int main() {
    FILE *fp = fopen("inputflow.txt", "r");
    if (!fp) {
        printf("Error: Could not open input.txt\n");
        return 1;
    }

    while (fgets(tac[total], sizeof(tac[0]), fp)) {
        tac[total][strcspn(tac[total], "\n")] = '\0'; // Remove newline
        total++;
    }
    fclose(fp);

    mark_leaders();
    print_blocks();
    return 0;
}