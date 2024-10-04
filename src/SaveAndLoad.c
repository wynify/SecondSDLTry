#include "SaveAndLoad.h"

void save_to_file(const char *filename, const char *data){
    FILE *file = fopen(filename, "w");
    if(file == NULL){
        printf("Can't save file! %s\n", filename);
        return;
    }

    int len = strlen(data);
    if (len > 0 && data[len - 1] != '\n'){
        // Write the data to the file with an explicit newline if missing
        fprintf(file, "%s\n", data);
    } else {
        // Write the data as is if it already ends with a newline
        fprintf(file, "%s", data);
    }

    fclose(file);
    printf("Data successfully saved to %s\n", filename);
}

char* load_from_file(const char *filename){
    FILE *file = fopen(filename, "r");
    if(file == NULL){
        printf("Can't open file! %s\n", filename);
        exit(-1);
    }

    fseek(file, 0, SEEK_END);       //Move the file pointer to the end
    long file_size = ftell(file);   // Get the size of the file
    rewind(file);                   // Move the file pointer back to the beginning

    char *data = (char*)malloc((file_size + 1) * sizeof(char));
    if(data == NULL){
        printf("Error: memory allocated error\n");
        fclose(file);
        return NULL;    
    }

    fread(data, sizeof(char), file_size, file);
    data[file_size] = '\0';
    fclose(file);

    return data;
}