//big integer.c version 2

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
 
typedef int bool;
#define true 1
#define false 0
 
#define positive 0;
#define negative 1;
 
struct BigInteger {
        unsigned int* array;
        int length;
        char flags;
};
 
// Helper methods
unsigned int* extendArray(unsigned int* original, int originalLength, int newLength);
unsigned int* shrinkArray(unsigned int* original, int originalLength);
//unsigned int* shift(unsigned int* original)
//initialize a new array
 
// BigInteger operations
struct BigInteger add(struct BigInteger a, struct BigInteger b);
struct BigInteger subtract(struct BigInteger a, struct BigInteger b);
struct BigInteger multiply(struct BigInteger a, struct BigInteger b);
 
int main() {
 
        struct BigInteger a;
        unsigned int aArray[4];
        aArray[0] = 4042531800;
        aArray[1] = 78871649;
        aArray[2] = 2739546731;
        aArray[3] = 2354282496;
        a.array = aArray;
        a.length = 4;
        a.flags = positive;
 
        struct BigInteger b;
        unsigned int bArray[4];
        bArray[0] = 252435495;
        bArray[1] = 4216084804;
        bArray[2] = 1462113022;
        bArray[3] = 2259465149;
        b.array = bArray;
        b.length = 4;
        b.flags = positive;
 
        struct BigInteger sum = add(a, b);
 
        for (int i=0; i<sum.length; i++) {
                printf("%u ", sum.array[i]);
        }
 
        return 0;
}
 
// why have the for loop i increase by the index decrease
// i don't like declaring variables inside a for loop 
unsigned int* extendArray(unsigned int* original, int originalLength, int newLength) {
 
        if (newLength < originalLength) {
                printf("extendArray error: newLength must be greater or equal to originalLength");
                return NULL;
        }
 
        static unsigned int* copy;
        copy = malloc(newLength * sizeof(unsigned int));
 
        for (int i=1; i<=newLength; i++) {
                int originalIndex = originalLength - i;
                int newIndex = newLength - i;
                if (originalIndex < 0) {
                        copy[newIndex] = 0;
                } else {
                        copy[newIndex] = original[originalIndex];
                }
        }
 
        return copy;
}
 
unsigned int* shrinkArray(unsigned int* original, int originalLength) {
 
}
 
struct BigInteger add(struct BigInteger a, struct BigInteger b) {
 
        unsigned int* x;
        unsigned int* y;
 
        // Make sure the two arrays
        // we are working with (x, y)
        // are of the same length.
 
        // Make sure the sum array is
        // one longer than the longer
        // of a and b (account for carry)
 
        int sumLength;
        if (a.length == b.length) {
                sumLength = a.length + 1;
                x = a.array;
                y = b.array;
        } else if (a.length > b.length) {
                sumLength = a.length + 1;
                x = a.array;
                y = extendArray(b.array, b.length, a.length);
        } else {
                sumLength = b.length + 1;
                x = extendArray(a.array, a.length, b.length);
                y = b.array;
        }
 
        static unsigned int* sum;
        sum = (unsigned int*) malloc(sumLength * sizeof(unsigned int));
        sum[0] = 0;
 
        struct BigInteger result;
        result.array = sum;
        result.length = sumLength;
        result.flags = positive;
 
        bool carry = false;
        for (int i=sumLength-2; i>=0; i--) {
                unsigned int indexSum = x[i] + y[i];
                if (carry == true) {
                        indexSum ++;
                        carry = false;  // consume the carry
                }
                if (x[i] > (UINT_MAX - y[i])) {
                        indexSum -= (UINT_MAX + 1);
                        if (i == 0) {
                                sum[0] = 1;
                        } else {
                                carry = true;
                        }
                }
                sum[i+1] = indexSum;
        }
 
        if (x != a.array) {
                free(x);       
        }
 
        if (y != b.array) {
                free(y);
        }
 
        return result;
}
/* 
unsigned int bits[32] = {
        1,2,4,8,16,32,64,128,256,512,1024,2048,4096,
    8192,16384,32768,65536,131072,262144,524288,
    1048576,2097152,4194304,8388608,16777216,
    33554432,67108864,134217728,268435456,536870912,
    1073741824,2147483648
}
 */
struct BigInteger multiply(struct BigInteger a, struct BigInteger b) {
 
        int productLength = a.length + b.length;
        static unsigned* product;
        product = (unsigned int*) malloc(productLength * sizeof(unsigned int));
        for (int i=0; i<productLength; i++) {
                product[i] = 0;
        }
 
        struct BigInteger result;
        result.array = product;
        result.length = productLength;
        result.flags = a.flags ^ b.flags;
 
        unsigned int* x;
        x = extendArray(a.array, a.length, productLength);
 
 
}