
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "DynamicString.h"
#include "utilities.h"
#include "StringArray.h"
#include <stdarg.h>


void test_func(int n, ...)
{
    va_list myList;
    va_start(myList, n);
    forall(n){
        int* p = va_arg(myList, int*);
        printf("%p\n", (void*)p);
    }
    int size =  sizeof(myList)/sizeof(int*);
    printf("%d\n", (int)size);
    va_end(myList);
}
int main(int argc, char* argv[])
{
    STRING_ARRAY_DESTROYER = new_string_array_destroyer(destroy_string_array_real);
    StringArray a = new_default_string_array();

    add_string(a, 3, "Bob", "Dave", "Bill");
    add_string(a, 1, "adam");
    add_string(a, 1, "22");
    // STRING_ARRAY_DESTROYER->destroy(&temp);
    //destroy_string_array(a);

    /*String data = stringcopy("June Patrick Disalvo 1990 27");
    StringArray tokens = string_split(data, " ,.");
    tokens->print(tokens);*/
    //tokens->sort(tokens, CASE_INSENSITIVE);
    //printf("Before sort\n");
    a->print(a);
    a->sort(a, CASE_INSENSITIVE);
    //printf("After sort\n");
    a->print(a);
    destroy_string_array(a);
    //tokens->remove(tokens, 2, "27", "Disalvo");
    //remove_string_at(tokens, 2, 0, 1);
    //tokens->print(tokens);
    //clear(data);
    //a->concat(a, tokens);
    //a->print(a);
    //clear(printer);
    
     //STRING_ARRAY_DESTROYER->destroy(&a);
     //STRING_ARRAY_DESTROYER->destroy(&tokens);

    // destroy_string_array(a);
    
    return 0;
}