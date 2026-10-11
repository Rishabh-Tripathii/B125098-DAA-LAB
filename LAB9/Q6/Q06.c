#include <stdio.h>
#include <string.h>

#define MAX 1000
#define ALPHABET 26

typedef struct {
    char ch;
    int freq;
    int availableAt;
} Node;

void reorganizeString(char s[], int k) {
    int freq[ALPHABET] = {0};
    char result[MAX];
    Node waiting[MAX];

    int n = strlen(s);
    int front = 0, rear = 0;
    int resultIndex = 0;

    // Count character frequencies
    for (int i = 0; i < n; i++) {
        if (s[i] < 'a' || s[i] > 'z') {
            printf("Error: Use lowercase English letters only.\n");
            return;
        }
        freq[s[i] - 'a']++;
    }

    // If K is 0 or 1, no additional separation is needed
    if (k <= 1) {
        printf("Reorganised String: %s\n", s);
        return;
    }

    for (int pos = 0; pos < n; pos++) {

        // Find the available character with maximum frequency
        int best = -1;

        for (int c = 0; c < ALPHABET; c++) {
            if (freq[c] > 0) {
                int available = 1;

                for (int j = front; j < rear; j++) {
                    if (waiting[j].ch == (char)('a' + c)) {
                        available = 0;
                        break;
                    }
                }

                if (available &&
                    (best == -1 || freq[c] > freq[best])) {
                    best = c;
                }
            }
        }

        // No valid character is available
        if (best == -1) {
            printf("Reorganised String: \"\"\n");
            return;
        }

        char selected = (char)('a' + best);
        result[resultIndex++] = selected;
        freq[best]--;

        // Make the character unavailable for K positions
        if (freq[best] > 0) {
            waiting[rear].ch = selected;
            waiting[rear].freq = freq[best];
            waiting[rear].availableAt = pos + k;
            rear++;
        }

        // Remove characters whose waiting period has ended
        while (front < rear &&
               waiting[front].availableAt <= pos + 1) {
            front++;
        }
    }

    result[resultIndex] = '\0';

    printf("Reorganised String: %s\n", result);
}

int main() {
    char s[MAX];
    int k;

    printf("Enter the string (lowercase letters only): ");
    scanf("%999s", s);

    printf("Enter K: ");
    scanf("%d", &k);

    reorganizeString(s, k);

    return 0;
}