
#include <iostream>
#define size 6


int main(){

    int original [size] = {4, 6, 5, 9, 1, 3};
    int ldns [size] = {1, 1, 1, 1, 1, 1};

    for (int j = 0; j < size; j++)
    {
        for (int i = j + 1; i < size; i++)
        {   
            if (original [j] <= original[i])
            {
                ldns[i] = ldns[j]+1;
            }
          
        }
    }
    
    for (size_t i = 0; i < size; i++)
    {
        printf("%i ", ldns[i]);
    }
    

    return 0;
}