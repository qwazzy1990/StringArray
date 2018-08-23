
#include "StringArray.h"
#include <stdarg.h>





/*****STATIC****/
int _____strcmp(const void* a, const void* b)
{
    String first = (String)a;
    String second = (String)b;
    return strcmp(first, second);
}
/****CONSTRUCTORS*****/

StringArray new_string_array(PrintFunc p, DeleteFunc d)
{
    new_object(StringArray, a, 1);
    a->printData = p;
    a->deleteData = d;
    a->compare = string_compare;
    a->strings = NULL;
    a->size = 0;

    a->get_size = get_string_array_size;
    a->get_string = get_string;
    a->get_index = get_string_index;

    a->destroy_string_array = destroy_string_array_real;
    a->remove = remove_string_real;
    a->remove_at = remove_string_at_real;
    a->remove_once = remove_string_once_real;

    a->add = add_string;
    a->concat = concat_string_array;
    a->sort = sort_string_array;

    a->to_string = string_array_to_string;
    a->print = print_string_array;

    a->empty = is_empty_string_array;
    a->contains = contains_string;
    /***DO FUNCTION POINTER SHIT**/
    return a;
}


StringArray new_default_string_array()
{
    new_object(StringArray, a, 1);

    a->size  = 0;
    a->strings = NULL;

    a->printData = print_string;
    a->deleteData = clear_real;
    a->compare = string_compare;
    
    a->get_size = get_string_array_size;
    a->get_string = get_string;
    a->get_index = get_string_index;

    a->destroy_string_array = destroy_string_array_real;
    a->remove = remove_string_real;
    a->remove_at = remove_string_at_real;
    a->remove_once = remove_string_once_real;

    a->add = add_string;
    a->concat = concat_string_array;
    a->sort = sort_string_array;


    a->to_string = string_array_to_string;
    a->print = print_string_array;


    a->empty = is_empty_string_array;
    a->contains = contains_string;

    /***DO FUNCTION POINTER SHIT***/
    return a;
}

StringArray new_string_array_clone(PrintFunc p, DeleteFunc d, CloneFunc cl)
{
    new_object(StringArray, a, 1);
    a->printData = p;
    a->deleteData = d;
    a->compare = string_compare;
    a->cloneData = cl;
    a->strings = NULL;
    a->size = 0;   

    
    a->get_size = get_string_array_size;
    a->get_string = get_string;
    a->get_index = get_string_index;

    a->destroy_string_array = destroy_string_array_real;
    a->remove = remove_string_real;
    a->remove_at = remove_string_at_real;
    a->remove_once = remove_string_once_real;

    a->add = add_string;
    a->concat = concat_string_array;

    a->to_string = string_array_to_string;
    a->print = print_string_array;
    a->sort = sort_string_array;

    a->empty = is_empty_string_array;
    a->contains = contains_string;

    return a;
}


StringArray string_split(String s, String delims)
{
    int j = 0;

     //errorcheck
     if(badstring(s))return NULL;

     //errorcheck
     if(badstring(delims))return NULL;
     //while
     while(isdelim(s[j], delims))
        j++;
     //endwhile

     //parameter and varaible setup
     int mem_size = 1;
     int row = 0;
     int col = 0;
     char c = 0;
     char p = 0;
     new_object(StringArray, tokens, 1);
     if(tokens == NULL)return NULL;

     tokens->printData = print_string;
     tokens->deleteData = clear_real;
     tokens->cloneData = NULL;
     tokens->compare = string_compare;

    tokens->get_size = get_string_array_size;
    tokens->get_string = get_string;
    tokens->get_index = get_string_index;

    tokens->destroy_string_array = destroy_string_array_real;
    tokens->remove = remove_string_real;
    tokens->remove_at = remove_string_at_real;
    tokens->remove_once = remove_string_once_real;

    tokens->add = add_string;
    tokens->concat = concat_string_array;
    tokens->sort = sort_string_array;

    tokens->to_string = string_array_to_string;
    tokens->print = print_string_array;

    tokens->empty = is_empty_string_array;
    tokens->contains = contains_string;



     tokens->strings = (Strings)calloc(mem_size, sizeof(String));



     tokens->strings[row] = createvoidstring();
     //for
     for(int i = j; i < strlen(s); i++){
         //if
         if(i == 0){
             c = s[i];
             p = c;
         }//endif
         c = s[i];
         //if
         if(isdelim(c, delims) && isdelim(p, delims)){
             p = c;
             continue;
         }//endif
         //if
         if((isdelim(c, delims))&& (!isdelim(p, delims))){
             p = c;
             continue;
         }//endif
         //if
         if((!isdelim(c, delims))&&(isdelim(p, delims))){
             tokens->strings[row][col] = '\0';
             row++;
             col = 0;
             mem_size++;
             tokens->strings = (Strings)realloc(tokens->strings, sizeof(String)*mem_size);
             if(tokens->strings == NULL)return NULL;
             tokens->strings[row] = createvoidstring();
             tokens->strings[row][col] = c;
             col++;
         }//endif
         //if
         if(!isdelim(c, delims) && !isdelim(p, delims)){
             tokens->strings[row][col] = c;
             col++;
         }//endif
         p = c;
     }//endfor
   
    tokens->size = mem_size;

   
    
    return tokens;
}

StringArrayDestroyer new_string_array_destroyer(StringArrayError (*d)(struct sa**))
{
    new_object(StringArrayDestroyer, destroyer, 1);
    destroyer->destroy = d;
    return destroyer;
}
/****END CONSTRUCTORS***/

/***ACCESSORS**/

unsigned int get_string_array_size(StringArray a)
{
    if(a == NULL){
        return 0;
    }else{
        return a->size;
    }
}

String get_string(StringArray a, int index)
{
    if(a == NULL)return NULL;
    if(a->size <= 0)return NULL;
    if(index < 0)return NULL;
    if(index >= a->size)return NULL;
    return a->strings[index];
}

Int get_string_index(StringArray a, String s)
{
    if(a == NULL)return NULL;
    if(s == NULL)return NULL;
    if(a->size <= 0)return NULL;
    if(contains_string(a, s)==false)return NULL;

    new_object(Int, index, 1);
    int count = 0;
    forall(a->size)
    {
        if(a->compare(a->strings[x], s, CASE_SENSITIVE)==0){
            index[count] = x;
            count++;
        }
    }
    return index;
}
/**END ACCESSORS***/


/***DESTROYERS***/

StringArrayError remove_string_real(StringArray* a, int n, ...)
{
    if(a == NULL)return DNE_STRING_ARRAY;
    //if(s == NULL)return DNF_STRING_ARRAY;
    if((*a)->size <= 0)return DNF_STRING_ARRAY;
    if(n <= 0)return FAIL_DELETE_STRING_ARRAY;
    //if(contains_string(*a, s)==false)return FAIL_DELETE_STRING_ARRAY;
    int count = 0;

    va_list myList;
    va_start(myList, n);

    new_object(char**, s, n);
    forall(n){
        s[x] = calloc(1000, sizeof(char));
    }
    forall(n){
        //new_object(String, temp, 1000);
        String temp = va_arg(myList, char*);
        s[x] = stringcopy(temp);
        //free(temp);
    }
    new_object(StringArray, sa, 1);
   
    for(int i = 0; i < n; i++)
        forall((*a)->size){
                if((*a)->compare((*a)->strings[x], s[i], CASE_SENSITIVE)==0)
                {
                    clear((*a)->strings[x]);
                    count++;
                }
        }
    sa->size = (*a)->size - count;
    sa->strings = calloc(sa->size, sizeof(char*));
    int index = 0;
    forall((*a)->size){
        if((*a)->strings[x] != NULL){
            sa->strings[index] = stringcopy((*a)->strings[x]);
            index++;
        }
    }
    forall((*a)->size){
        clear((*a)->strings[x]);
    }
    clear((*a)->strings);
    char** temp = sa->strings;
    (*a)->strings = temp;
    (*a)->size -= count;
    clear(sa);

    forall(n)
    {
        clear(s[x]);
    }
    clear(s);
    va_end(myList);
    return OK_STRING_ARRAY;
}

StringArrayError remove_string_once_real(StringArray* a, String s)
{
     if(a == NULL)return DNE_STRING_ARRAY;
    if(s == NULL)return DNF_STRING_ARRAY;
    if((*a)->size <= 0)return DNF_STRING_ARRAY;
    if(contains_string(*a, s)==false)return FAIL_DELETE_STRING_ARRAY;
    int (*c)(AnyData, AnyData, CaseSensitivity) = (*a)->compare;
    new_object(StringArray, sa, 1);
    
    forall((*a)->size){
        if(c((*a)->strings[x], s, CASE_SENSITIVE)==0){
            clear((*a)->strings[x]);
        }
    }
    sa->size = (*a)->size - 1;
    sa->strings = calloc(sa->size, sizeof(char*));
    forall((*a)->size){
        if((*a)->strings[x] != NULL){
            sa->strings[x] = stringcopy((*a)->strings[x]);
        }
    }
    forall((*a)->size){
        clear((*a)->strings[x]);
    }
    clear((*a)->strings);
    clear(*a);
    *a = sa;
    return OK_STRING_ARRAY;
}



StringArrayError remove_string_at_real(StringArray* a, int n, ...)
{
    if(a == NULL)return FAIL_DELETE_STRING_ARRAY;
    if(*a == NULL)return FAIL_DELETE_STRING_ARRAY;
    if(n < 0)return FAIL_DELETE_STRING_ARRAY;
    if(n >= (*a)->size)return FAIL_DELETE_STRING_ARRAY;
    new_object(StringArray, sa, 1);
    
    new_object(Int, index, n);

    va_list myList;
    va_start(myList, n);
    int count = 0;
    forall(n)
    {
        index[x] = va_arg(myList, int);
    }
    forall((*a)->size){
        for(int i = 0; i < n; i++){
            if(x == index[i]){
                clear((*a)->strings[x]);
                count++;
            }
        }
    }
    sa->size = (*a)->size - count;
    sa->strings = calloc(sa->size, sizeof(char*));
    int i = 0;
    forall((*a)->size){
        if((*a)->strings[x] != NULL){
            sa->strings[i] = stringcopy((*a)->strings[x]);
            i++;
        }
    }
    forall((*a)->size){
        clear((*a)->strings[x]);
    }
    clear((*a)->strings);
    (*a)->size = sa->size;
    (*a)->strings = sa->strings;
    clear(sa);
    clear(index);
    va_end(myList);
    return OK_STRING_ARRAY;
}

StringArrayError destroy_string_array_real(StringArray* a)
{
     if(a == NULL)return FAIL_DELETE_STRING_ARRAY;
     if(*a == NULL)return FAIL_DELETE_STRING_ARRAY;
     DeleteFunc d = (*a)->deleteData;

     if(d == NULL)printf("WHYY\n");
     forall((*a)->size){
            String temp = (*a)->strings[x];
           clear(temp);
     }
     (*a)->size = 0;
     clear((*a)->strings);
     clear(*a);
     return OK_STRING_ARRAY;
}
/***END DESTROYERS***/







/****SETTERS****/
StringArrayError add_string(StringArray a, int n, ...)
{
    if(a == NULL)return FAIL_ADD_STRING_ARRAY;
    if(n <=0 )return FAIL_ADD_STRING_ARRAY;

    va_list vaList;
    char** strings = calloc(n, sizeof(char*));
    va_start(vaList, n);
    forall(n){
        String temp = va_arg(vaList, char*);
        strings[x] = stringcopy(temp);
    }
    int count = a->size;
    a->size += n;
    if(count > 0){
        a->strings = realloc(a->strings, a->size*sizeof(char*));
    }else{
        a->strings = calloc(n, sizeof(char*));
    }
    forall(n)
    {
        a->strings[count] = stringcopy(strings[x]);
        count++;
    }
    forall(n){
        clear(strings[x]);
    }
    clear(strings);
    va_end(vaList);
    return OK_STRING_ARRAY;
}


StringArray concat_string_array(StringArray dest, StringArray source)
{
    if(source == NULL)return NULL;
    if(source->size == 0)return NULL;
    if(source->strings == NULL)return NULL;
    if(dest == NULL)
    {
        dest = calloc(1, sizeof(SA));
        dest->size = source->size;
        dest->strings = calloc(source->size, sizeof(char*));
        forall(source->size){
            dest->strings[x] = stringcopy(source->strings[x]);
        }
        return dest;
    }
    if(dest->size == 0 && dest->strings == NULL)
    {
        dest->size = source->size;
        dest->strings = calloc(source->size, sizeof(char*));
        forall(source->size){
            dest->strings[x] = stringcopy(source->strings[x]);
        }
        return dest;
    }
    if(dest->size <= 0 && dest->strings != NULL)
    {
        return NULL;
    }
    if(dest->strings == NULL && dest->size > 0)
    {
        return NULL;
    }

    int oldSize = dest->size;
    int index = dest->size;
    int sourceSize = source->size;
    int memSize = oldSize + sourceSize;

    dest->strings = realloc(dest->strings, memSize*sizeof(char*));
    forall(source->size)
    {
        dest->strings[index] = stringcopy(source->strings[x]);
        index++;
    }
    dest->size = memSize;
    return dest;
}
/**END SETTERS****/

/***MUTATORS***/

String string_array_to_string(AnyData d)
{
    if(d == NULL)return NULL;
    StringArray a = d;
    if(a->empty(a))return NULL;
    if(a->strings == NULL)return NULL;
    String s = NULL;
    forall(a->size)
    {
        if(x==0){
            s = stringcopy(a->strings[x]);
        }
        else{
            s = stringcat(s, " ");
            s = stringcat(s, a->strings[x]);
        }
    }
    return s;
}

String print_string(AnyData d)
{
    if(d == NULL)return NULL;
    String printer = (String)d;
    if(stringlen(printer)<=0)return NULL;
    printf("%s\n", printer);
    return printer;
}

void print_string_array(AnyData d)
{
    String printer = string_array_to_string(d);
    if(printer == NULL)return;
    if(stringlen(printer)<=0)return;
    printf("%s\n", printer);
    clear(printer);
}


/***FIX ME***/
void sort_string_array(StringArray a, CaseSensitivity mode)
{
    if(a == NULL)return;
    if(a->size <= 1)return;
    if(a->strings == NULL)return;
    if(mode == CASE_INSENSITIVE)
    {
        StringArray temp = new_default_string_array();

        forall(a->size)
        {
            String lower = to_lower(a->strings[x]);
            temp->add(temp, 1, lower);
            clear(lower);
        }
        for(int i = 0; i < a->size; i++){
            for(int j = i+1; j < a->size -1; j++){
                if(string_compare(temp->strings[i], temp->strings[j], CASE_INSENSITIVE) > 0){
                    String t = temp->strings[i];
                    temp->strings[i] = temp->strings[j];
                    temp->strings[j] = t;
                }
            }
        }
        temp->print(temp);

        for(int i = 0; i < temp->size-1; i++){
            for(int j = i+1; j < temp->size; j++){
                if(string_compare(temp->strings[i], a->strings[j], CASE_INSENSITIVE)==0){
                    String temp = a->strings[j];
                    a->strings[j] = a->strings[i];
                    a->strings[i] = temp;
                }
            }
        }
        destroy_string_array(temp);

    }
    else{
        for(int i = 0; i < a->size - 1; i++){
            for(int j = i+1; j < a->size; j++){
                if(string_compare(a->strings[i], a->strings[j], 1)>0){
                    String temp = a->strings[i];
                    a->strings[i] = a->strings[j];
                    a->strings[j] = temp;
                }
            }
        }
    }
}

/***END MUTATORS***/

/****VALIDATORS*****/

bool contains_string(StringArray a, String s)
{
    int (*c)(AnyData, AnyData, CaseSensitivity) = a->compare;
    forall(a->size)
    {
        if(c(a->strings[x], s, CASE_SENSITIVE)==0)return true;
    }
    return false;
}

bool is_empty_string_array(StringArray a)
{
    if(a == NULL)return true;
    if(a->get_size(a)==0)return true;
    return false;
}

/****END VALIDATORS***/

/****COMPAREATORS****/

int string_compare(AnyData a, AnyData b, CaseSensitivity c)
{
    if(a == NULL)return -2;
    if(b == NULL)return -2;
    String first = (String)a;
    String second = (String)b;
    if(c == CASE_SENSITIVE){
        if(strcmp(first, second) < 0)return -1;
        else if(strcmp(first, second)==0)return 0;
        else return 1;
    }
    else{
        first = to_lower(first);
        second = to_lower(second);
        if(strcmp(first, second) < 0){
            clear(first);
            clear(second);
            return -1;
        }
        else if(strcmp(first, second)==0)
        {
            clear(first);
            clear(second);
            return 0;
        }
        else{
            clear(first);
            clear(second);
            return 1;   
        }
    }

}

