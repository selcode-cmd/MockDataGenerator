#include "data_generator.h"

int main(void) {
    srand(time(NULL));

    FieldDefinition* schema = NULL;
    int fieldCount, rowCount;
    
    menu(&schema, &fieldCount, &rowCount);

    generate(schema, fieldCount, rowCount);

    if (schema != NULL) free(schema);
    return 0;
}