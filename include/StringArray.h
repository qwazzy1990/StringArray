#ifndef _STRING_ARRAY_
#define _STRING_ARRAY_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "DynamicString.h"
#include "utilities.h"



#define remove_string(a, b, ...) remove_string_real(&a, b, __VA_ARGS__)
#define remove_string_at(a, b, ...) remove_string_at_real(&a, b, __VA_ARGS__)
#define remove_at(a, b, ...) remove_at(&a, b, __VA_ARGS__)
#define remove(a, b, ...) remove(&a, b, __VA_ARGS__)
#define destroy_string_array(a) destroy_string_array_real(&a)

//#define destroy_string_array(a) destroy_string_array_real(&a)
enum SAE{
    OK_STRING_ARRAY,
    DNF_STRING_ARRAY, 
    DNE_STRING_ARRAY,
    MEM_ERR_STRING_ARRAY,
    FAIL_DELETE_STRING_ARRAY,
    FAIL_ADD_STRING_ARRAY
};typedef enum SAE StringArrayError;


struct sa{
    String* strings;
    unsigned int size;
    PrintFunc printData;
    DeleteFunc deleteData;
    CloneFunc cloneData;

    /**FUNCTION POINTERS FOR OBJECT ORIENTED APPROACH***/

    /***CONSTRUCTOR FP***/
    struct sa* (*split)(String, String);

    /***ACCESSOR FP***/
    unsigned int (*get_size)(struct sa*);
    String (*get_string)(struct sa*, int);
    Int (*get_index)(struct sa*, String);

    /****COMPARATOR*****/
    int (*compare)(AnyData, AnyData, CaseSensitivity);

    /**DESTROYER FP***/

    StringArrayError (*destroy_string_array)(struct sa**);
    StringArrayError (*remove)(struct sa**, int n, ...);
    StringArrayError (*remove_at)(struct sa**, int n, ...);
    StringArrayError (*remove_once)(struct sa**, String);

    /**SETTER FP***/
    StringArrayError (*add)(struct sa*, int n, ...);
    struct sa* (*concat)(struct sa*, struct sa*);

    /***SORTERS***/
    void (*sort)(struct sa*, CaseSensitivity);

    /***MUTATOR FP***/
    String (*to_string)(AnyData);
    void (*print)(AnyData);

    /***VALIDATOR FP***/
    bool (*empty)(struct sa*);
    bool (*contains)(struct sa*, String);


};typedef struct sa SA;
typedef SA* StringArray;

struct sad
{
    StringArrayError (*destroy)(struct sa**);
};

typedef struct sad SAD;

typedef SAD* StringArrayDestroyer;

StringArrayDestroyer STRING_ARRAY_DESTROYER;

/*****CONSTRUCTORS***/
StringArray new_string_array(PrintFunc p, DeleteFunc d);

StringArray new_default_string_array( void );

StringArray new_string_array_clone(PrintFunc p, DeleteFunc d, CloneFunc cl);

StringArray string_split(String s, String delims);

StringArrayDestroyer new_string_array_destroyer(StringArrayError (*d)(StringArray*));
/****END CONSTRUCTORS***/

/****ACCESSORS*****/

unsigned int get_string_array_size(StringArray a);

String get_string(StringArray a, int index);

Int get_string_index(StringArray a, String s);

/*****END ACCESSORS***/
/***COMPARATORS***/

int string_compare(AnyData a, AnyData b, CaseSensitivity c);

/***END COMPARATORS***/
/****DESTROYERS*****/

StringArrayError destroy_string_array_real(StringArray* a);

StringArrayError remove_string_real(StringArray* a, int n, ...);

StringArrayError remove_string_once_real(StringArray* a, String s);

StringArrayError remove_string_at_real(StringArray* a, int n, ...);


/***END DESTROYERS****/

/****SETTERS****/

StringArrayError add_string(StringArray a, int n, ...);

StringArray concat_string_array(StringArray dest, StringArray source);

/***END SETTERS***/

/*****MUTATORS****/

    /***STRINGIFY***/
        String string_array_to_string(AnyData d);
    /***END STRINGIFY***/

    /****PRINTERS****/
        String print_string(AnyData d);
        void print_string_array(AnyData d);
    /***END PRINTERS***/

    /***SORTERS***/
        void sort_string_array(StringArray a, CaseSensitivity mode);
    /***END SORTERS***/
/****END MUTATORS***/

/***VALIDATORS****/
    bool is_empty_string_array(StringArray a);
    bool contains_string(StringArray a, String s);
/***END VALIDATORS***/



#endif