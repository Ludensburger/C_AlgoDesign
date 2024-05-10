#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MAX_TRIES 6
#define MAX_WORD_LENGTH 20

// Function prototypes
void initialize(char *secretWord, char *guessedWord);
void updateGuessedWord(char *secretWord, char *guessedWord, char letter);
int isSecretWordGuessed(char *secretWord, char *guessedWord);
void playGame(char *secretWord, char *guessedWord);
void convertToUpperCase(char *str);

int main() {
    char secretWord[MAX_WORD_LENGTH];
    char guessedWord[MAX_WORD_LENGTH];

    printf("Welcome to Hangman!\n");
    initialize(secretWord, guessedWord);
    playGame(secretWord, guessedWord);
    return 0;
}

void initialize(char *secretWord, char *guessedWord) {
    printf("Enter the word to guess (up to %d characters): ", MAX_WORD_LENGTH);
    scanf("%s", secretWord);
    convertToUpperCase(secretWord);

    // Initialize the guessed word with dashes
    for (int i = 0; i < strlen(secretWord); i++) {
        guessedWord[i] = '-';
    }
    guessedWord[strlen(secretWord)] = '\0';
}

void convertToUpperCase(char *str) {
    for (int i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

void updateGuessedWord(char *secretWord, char *guessedWord, char letter) {
    for (int i = 0; i < strlen(secretWord); i++) {
        if (secretWord[i] == letter) {
            guessedWord[i] = letter;
        }
    }
}

int isSecretWordGuessed(char *secretWord, char *guessedWord) {
    return strcmp(secretWord, guessedWord) == 0;
}

void playGame(char *secretWord, char *guessedWord) {
    int tries = 0;
    char guess;

    while (tries < MAX_TRIES && !isSecretWordGuessed(secretWord, guessedWord)) {
        printf("\nSecret word: %s\n", guessedWord);
        printf("Enter a letter to guess: ");
        scanf(" %c", &guess);
        guess = toupper(guess);

        if (strchr(secretWord, guess) != NULL) {
            printf("Good guess!\n");
            updateGuessedWord(secretWord, guessedWord, guess);
        } else {
            printf("Sorry, the letter '%c' is not in the word.\n", guess);
            tries++;
        }
    }

    if (isSecretWordGuessed(secretWord, guessedWord)) {
        printf("\nCongratulations, you guessed the word: %s\n", secretWord);
    } else {
        printf("\nSorry, you've run out of tries. The word was: %s\n", secretWord);
    }
}