#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef enum {ID, INT, DOUBLE, STRING, BOOL} DataType;

typedef struct {
    DataType type;
    int stringLength;
    char fieldName[30];
} FieldDefinition;

void fillHeader(FieldDefinition** schema, int index, int choose) {
    if(choose < 1 || choose > 3) {
        printf("Invalid selection!\n");
        return;
    }

    if(choose == 5) (*schema)[index].type = BOOL;
    else if(choose == 4) (*schema)[index].type = STRING;
    else if(choose == 3) (*schema)[index].type = DOUBLE;
    else if(choose == 2)(*schema)[index].type = INT;
    else (*schema)[index].type = ID;

    if(choose == 4) {
        printf("Enter string length: ");
        scanf("%d", &(*schema)[index].stringLength);
    }

    printf("Enter field name: ");
    getchar();
    fgets((*schema)[index].fieldName, 30, stdin);
    
    (*schema)[index].fieldName[strcspn((*schema)[index].fieldName, "\n")] = '\0';
}

void menu(FieldDefinition** schema, int* fieldCount, int* rowCount) {
    printf("--- Mock Data Generator ---\n");
    printf("How many fields do you want to define: ");
    scanf("%d", fieldCount);

    *schema = (FieldDefinition*)malloc(sizeof(FieldDefinition) * (*fieldCount));
    if(schema == NULL) return;

    for(int i = 0; i < *fieldCount; i++) {
        int choose;
        printf("\nField %d type (1:ID, 2:Int, 3:Double, 4:String, 5:Boolean): ", i + 1);
        scanf("%d", &choose);
        fillHeader(schema, i, choose);
    }
    
    printf("\nHow many rows of data to generate: ");
    scanf("%d", rowCount);
    
    printf("\nSchema created. Ready to generate %d rows.\n", *rowCount);
}

int randomInt(int min, int max) {
    return min + rand() / RAND_MAX * (max - min);
}

double randomFloat(double min, double max) {
    return min + (double)rand() / RAND_MAX * (max - min);
}

char* randomString(int length) {
    if (length <= 0) return NULL;

    char* str = (char*)malloc(sizeof(char) * (length+1));
    if (str == NULL) {
        printf("Error: Memory could not be allocated!\n");
        exit(1);
    }
    
    for (int i = 0; i < length; i++) {
        str[i] = (rand() % 2) ? ('A' + rand() % 26) : ('a' + rand() % 26);
    }

    str[length] = '\0';
    return str;
}

void generate(FieldDefinition* schema, int fieldCount, int rowCount) {
    FILE* file = fopen("deneme.csv", "w");
    if (file == NULL) {
        printf("Error: Could not create file!\n");
        return;
    }

    for(int i = 0; i < fieldCount; i++) {
        fprintf(file, "%s", schema[i].fieldName);
        if(i < fieldCount - 1) fprintf(file, ";");
    }
    fprintf(file, "\n");

    for(int i = 1; i <= rowCount; i++){
        for(int j = 0; j < fieldCount; j++) {
            if(schema[j].type == ID) fprintf(file, "%d", i);
            else if(schema[j].type == INT) fprintf(file, "%d", randomInt(0, rowCount));
            else if(schema[j].type == DOUBLE) fprintf(file, "%.2f", randomFloat(0, (double)rowCount));
            else if (schema[j].type == BOOL) fprintf(file, "%d", rand() % 2);
            else{
                char* str = randomString(schema[j].stringLength);
                if(str != NULL) {
                    fprintf(file, "%s", str);
                    free(str);
                }
            }
            if(j < fieldCount - 1) fprintf(file, ";");
        }
        fprintf(file, "\n");
    }
    fclose(file);
    printf("\ndeneme.csv created successfully.\n");
}