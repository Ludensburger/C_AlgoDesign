// Author: Ryu R. Mendoza
// Date: May 8, 2024

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REGISTERS 1000
#define MAX_INSTRUCTIONS 20
#define MAX_INSTRUCTION_LENGTH 20 // Increased for better readability

typedef struct {
    int registers[MAX_REGISTERS];
    char instructions[MAX_INSTRUCTIONS][MAX_INSTRUCTION_LENGTH];
    int num_instructions;
} UnlimitedRegisterMachine;

void add_instruction(UnlimitedRegisterMachine *urm, char *instruction) {
    // Remove newline character if present
    char *newline = strchr(instruction, '\n');
    if (newline) {
        *newline = '\0';
    }

    // Ensure there's space for a new instruction
    if (urm->num_instructions < MAX_INSTRUCTIONS) {
        strncpy(urm->instructions[urm->num_instructions], instruction, MAX_INSTRUCTION_LENGTH - 1);
        urm->instructions[urm->num_instructions][MAX_INSTRUCTION_LENGTH - 1] = '\0'; // Ensure null termination
        urm->num_instructions++;
    }
}

void execute(UnlimitedRegisterMachine *urm) {
    int pc = 0;
    int instruction_counter = 0;
    int max_instructions = urm->num_instructions * 1000; // Arbitrary large number

    while (pc < urm->num_instructions) {
        // Check for infinite loop
        if (instruction_counter++ > max_instructions / 2) {
            printf("Infinite loop detected. Terminating program.\n");
            exit(1);
        }

        char op;
        int r1, r2, r3;
        // Parse the operation and registers
        sscanf(urm->instructions[pc], "%c(%d, %d, %d)", &op, &r1, &r2, &r3);

        switch (op) {
        case 'Z':
            urm->registers[r1] = 0;
            pc++;
            break;
        case 'S':
            urm->registers[r1]++;
            pc++;
            break;
        case 'T':
            urm->registers[r2] = urm->registers[r1];
            pc++;
            break;
        case 'J':
            if (urm->registers[r1] == urm->registers[r2]) {
                // For debugging purposes
                // printf("Jumping to instruction %d\n", r3 + 1);

                pc = r3 - 1; // Convert to 0-based index

            } else {
                pc++;
            }
            break;
        default:
            printf("Invalid operation: %c\n", op);
            exit(1);
        }
    }

    // Print output and non-zero registers
    printf("Output: %d\n", urm->registers[0]);

    // For debugging purposes
    // printf("\nNon-zero Registers: \n");
    // for (int i = 0; i < MAX_REGISTERS; i++) {
    //     if (urm->registers[i] != 0) {
    //         printf("R%d: %d\n", i, urm->registers[i]);
    //     }
    // }
}

int main() {
    UnlimitedRegisterMachine urm;

    // Initialize the structure manually
    memset(&urm, 0, sizeof(urm));

    printf("Welcome to Unlimited Register Machine!\n");
    printf("Enter Instructions here: \n");

    char instruction[MAX_INSTRUCTION_LENGTH];
    int ctr = 0;

    do {
        printf("%d. ", ++ctr);
        fgets(instruction, sizeof(instruction), stdin);

        // Stop reading when a blank line is encountered
        if (strcmp(instruction, "\n") == 0) {
            break;
        }
        add_instruction(&urm, instruction);
    } while (1);

    printf("\nInput: \n");
    ctr = 0;
    char input[10];

    while (fgets(input, sizeof(input), stdin) != NULL) {
        // Stop reading when a blank line is encountered
        if (strcmp(input, "\n") == 0) {
            break;
        }
        urm.registers[ctr++] = atoi(input);
    }

    execute(&urm);

    return 0;
}