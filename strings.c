#include<stdio.h>
#include<stdlib.h>

struct vector{
    int size;
    int capacity;
    char *arr;
};

void resize(struct vector *X);
int strLen(char *Y);
void output(struct vector *X);

void initString(struct vector *X, char *Y);
void concatenate(struct vector *combined, struct vector *a, struct vector *b);
void slice(struct vector *sliced, struct vector *source, int start, int end);

int main(){

    //Asks the user for their choices
    int input;
    printf("What do you want to do?\n[1]Concatenate\n[2]Slice\n");
    scanf("%i", &input);

    if(input == 1){
        
        //Initializing values
        struct vector one = { 0 };
        struct vector two = { 0 };
        struct vector combined = { 0 };

        char textOne[50];
        char textTwo[50];

        //Using functions
        printf("Enter text: ");
        scanf_s("%s", textOne, 50);
        initString(&one, textOne);

        printf("\nEnter text: ");
        scanf_s("%s", textTwo, 50);
        initString(&two, textTwo);

        concatenate(&combined, &one, &two);
        output(&combined);

    }else if(input == 2){

        //Initializing values
        struct vector source = { 0 };
        struct vector sliced = { 0 };

        int start = 0, end = 0;
        char text[50];

        //Using functions
        printf("Enter text: ");
        scanf_s("%s", text, 50);
        initString(&source, text);

        //Looping in cas user does not place correct values
        do{
            printf("Enter start index: ");
            scanf("%i", &start);
        }while(start < 0 || start > 9);

        do{
            printf("Enter end index: ");
            scanf("%i", &end);
        }while(end < 0 || end > 9);

        slice(&sliced, &source, start, end);
        output(&sliced);
   
    }else{
        printf("Invalid input.");
    }

    return 0; 

}

//Expands the maximum threshold to twice the original value
void resize(struct vector *X){

    //Doubling the max threshold
    int newCapacity = 2*X->size;
    char *newArr = (char*)malloc(sizeof(char)*newCapacity);

    //Moving all the characters from the old array into the new bigger one
    for(int i = 0; i< X->size; i++){
        newArr[i] = X->arr[i];
    }

    //Updating variables with their new values
    X->capacity = newCapacity;
    free(X->arr);
    X->arr = newArr;

}

//Counts the length of the string
int strLen (char *Y){

    int i = 0;
    while(Y[i] != '\0'){
        i++;
    }
    return i;

}

//Prints out the vector string
void output(struct vector *X){

    printf("\n");

    for(int i = 0; i < X->size; i++){
        printf("%c", X->arr[i]);
    }

}

//Accepts a string and inserts all the character array's characters in the vector
void initString(struct vector *X, char *Y){

    //Initializing 
    X->size = strLen(Y);
    X->capacity = 10;
    X->arr = (char*)malloc(sizeof(char)*X->capacity);

    //When the max threshold is not enough, we update it by resizing the whole vector
    while(X->capacity < X->size){
      resize(X);
    }

    //Transferring the inputted values from the user to the vector
    for(int i = 0; i < X->size; i++) {
        X->arr[i] = Y[i]; 
    }
    
}

void concatenate(struct vector *combined, struct vector *a, struct vector *b){

    //Initializing
    //Combining the sizes of the a.vector and b.vector
    int finalSize = a->size + b->size;

    combined->size = finalSize;
    combined->capacity = 10;
    combined->arr =(char*)malloc(sizeof(char)*combined->capacity);

    //Expand the max threshold if necessary
    while(combined->capacity < finalSize){
        resize(combined);
    }

    int i = 0, index = 0;

    //Going through the first vector and placing all of a.vectors value inside the combined vector
    for(i = 0; i < a->size; i++){
        combined->arr[i] = a->arr[i];
    }

    //retaining the last digit while going though the loop so we do not replace the already placed characters and start going through the next vector from the last position
    index = i;

    //Going through the second vector and placing all its values to the combined vector
    for(int i = 0; i < b->size; i++){
        combined->arr[index + i] = b->arr[i];
    }

}

//Takes a portion of the vector array from a starting index to the end index - 1
void slice(struct vector *sliced, struct vector *source, int start, int end){

    //Initializing
    sliced->size = source->size;
    sliced->capacity = 10;
    sliced->arr = (char*)malloc(sizeof(char)*sliced->capacity);

    while(sliced->capacity < sliced->size){
        resize(sliced);
    }

    //Using start and end as reference for which part of the source array should be placed in the sliced array
    int i = 0;
    for(start, end, i; start <= end - 1; start++, i++){
        //Using i for the sliced array
        //Incrementing start until it reaches end-1
        sliced->arr[i] = source->arr[start];
    }
    
}
