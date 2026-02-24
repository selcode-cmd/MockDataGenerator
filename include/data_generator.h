#ifndef DATA_GENERATOR_H
#define DATA_GENERATOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum DataType {ID = 1, INT, DOUBLE, STRING, BOOL} DataType;
typedef struct {
    DataType type;
    int stringLength;
    char fieldName[30];
} FieldDefinition;

void fillHeader(FieldDefinition** schema, int index, int choose);
void menu(FieldDefinition** schema, int* fieldCount, int* rowCount);
int randomInt(int min, int max);
double randomFloat(double min, double max);
char* randomString(int length);
void generate(FieldDefinition* schema, int fieldCount, int rowCount);
#endif