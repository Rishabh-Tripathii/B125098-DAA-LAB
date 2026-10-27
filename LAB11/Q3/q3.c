#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100005
#define HASH_SIZE 262144

char words[MAX_WORDS][11];
int hashTable[HASH_SIZE];

int distA[MAX_WORDS];
int distB[MAX_WORDS];

int wordCount = 0;
int wordLength;

// Hash function for lowercase words.
unsigned int hashWord(const char *s) {
    unsigned int h = 0;

    while (*s) {
        h = (h * 31u + (unsigned int)(*s - 'a' + 1))
            & (HASH_SIZE - 1);
        s++;
    }

    return h;
}

// Find a word's index. Returns -1 if absent.
int findWord(const char *s) {
    unsigned int pos = hashWord(s);

    while (hashTable[pos] != 0) {
        int idx = hashTable[pos] - 1;

        if (strcmp(words[idx], s) == 0)
            return idx;

        pos = (pos + 1) & (HASH_SIZE - 1);
    }

    return -1;
}

// Insert a word that is not already present.
void insertWord(const char *s) {
    unsigned int pos = hashWord(s);

    while (hashTable[pos] != 0) {
        pos = (pos + 1) & (HASH_SIZE - 1);
    }

    strcpy(words[wordCount], s);
    hashTable[pos] = wordCount + 1;
    wordCount++;
}

// Expand one complete BFS layer.
int expandLayer(
    int frontier[],
    int frontierSize,
    int nextFrontier[],
    int *nextSize,
    int distThis[],
    int distOther[]
) {
    int best = -1;
    *nextSize = 0;

    for (int i = 0; i < frontierSize; i++) {
        int u = frontier[i];
        char candidate[11];

        strcpy(candidate, words[u]);

        for (int pos = 0; pos < wordLength; pos++) {
            char original = candidate[pos];

            for (char ch = 'a'; ch <= 'z'; ch++) {
                if (ch == original)
                    continue;

                candidate[pos] = ch;

                int v = findWord(candidate);

                if (v == -1)
                    continue;

                // The searches have connected.
                if (distOther[v] != -1) {
                    int total =
                        distThis[u] + 1 + distOther[v];

                    if (best == -1 || total < best)
                        best = total;
                }

                // Add each vertex to this search only once.
                if (distThis[v] == -1) {
                    distThis[v] = distThis[u] + 1;
                    nextFrontier[(*nextSize)++] = v;
                }
            }

            candidate[pos] = original;
        }
    }

    return best;
}

int bidirectionalBFS(int start, int target) {
    int frontA[MAX_WORDS];
    int nextA[MAX_WORDS];
    int frontB[MAX_WORDS];
    int nextB[MAX_WORDS];

    for (int i = 0; i < wordCount; i++) {
        distA[i] = -1;
        distB[i] = -1;
    }

    if (start == target)
        return 0;

    int *frontAptr = frontA;
    int *nextAptr = nextA;
    int *frontBptr = frontB;
    int *nextBptr = nextB;

    int sizeA = 1;
    int sizeB = 1;

    frontAptr[0] = start;
    frontBptr[0] = target;

    distA[start] = 0;
    distB[target] = 0;

    while (sizeA > 0 && sizeB > 0) {
        int nextSize;
        int answer;

        // Expand the smaller frontier.
        if (sizeA <= sizeB) {
            answer = expandLayer(
                frontAptr, sizeA, nextAptr, &nextSize,
                distA, distB
            );

            if (answer != -1)
                return answer;

            int *temp = frontAptr;
            frontAptr = nextAptr;
            nextAptr = temp;
            sizeA = nextSize;
        } else {
            answer = expandLayer(
                frontBptr, sizeB, nextBptr, &nextSize,
                distB, distA
            );

            if (answer != -1)
                return answer;

            int *temp = frontBptr;
            frontBptr = nextBptr;
            nextBptr = temp;
            sizeB = nextSize;
        }
    }

    return -1;
}

int main(void) {
    int N;
    char A[11], B[11];

    printf("Enter number of dictionary words:\n");

    if (scanf("%d", &N) != 1 || N <= 0 ||
        N >= MAX_WORDS) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter dictionary words:\n");

    for (int i = 0; i < N; i++) {
        char word[11];

        if (scanf("%10s", word) != 1) {
            printf("Invalid input.\n");
            return 1;
        }

        int len = (int)strlen(word);

        if (i == 0)
            wordLength = len;

        if (len != wordLength || len < 1 || len > 10) {
            printf("All words must have equal length.\n");
            return 1;
        }

        for (int j = 0; j < len; j++) {
            if (word[j] < 'a' || word[j] > 'z') {
                printf("Words must contain lowercase letters.\n");
                return 1;
            }
        }

        if (findWord(word) != -1) {
            printf("Dictionary words must be unique.\n");
            return 1;
        }

        insertWord(word);
    }

    printf("Enter starting word A and target word B:\n");

    if (scanf("%10s %10s", A, B) != 2) {
        printf("Invalid input.\n");
        return 1;
    }

    if ((int)strlen(A) != wordLength ||
        (int)strlen(B) != wordLength) {
        printf("A and B must have the dictionary word length.\n");
        return 1;
    }

    for (int j = 0; j < wordLength; j++) {
        if (A[j] < 'a' || A[j] > 'z' ||
            B[j] < 'a' || B[j] > 'z') {
            printf("Words must contain lowercase letters.\n");
            return 1;
        }
    }

    int target = findWord(B);

    if (target == -1) {
        printf("Minimum mutations: -1\n");
        return 0;
    }

    int start = findWord(A);

    // A may be outside the dictionary.
    if (start == -1) {
        insertWord(A);
        start = wordCount - 1;
    }

    int answer = bidirectionalBFS(start, target);

    printf("Minimum mutations: %d\n", answer);

    return 0;
}
