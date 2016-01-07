// bigninteger.c

#include <stdio.h>
#include <limits.h>
#include <math.h>

// must test to see if malloc automatic create an array of 0s


void printraw(unsigned int* number, int numbersize){
	for(int i = 1; i<numbersize; i++){
		printf("%u,",  number[i]);
	}
	printf("\n");
}

// the sum's number of element would equal to 
unsigned int* add(unsigned int* number1, int size1, unsigned int* number2, int size2){
	static unsigned int* sum;
	int sumsize;
	int num1curindex, num2curindex, sumindex, checkoverflow;
	int carryover = 0;

	if (size1 > size2){
		sumsize = size1+1;
	}else{
		sumsize = size2+1;
	}

	sum = (unsigned int*)malloc(sumsize * sizeof(unsigned int));

	for( int currentindex = sumsize; currentindex>1; currentindex--){
		printf("currentindex = %d\n", currentindex);
		sumindex = currentindex-1;
		num1curindex = currentindex - (sumsize-size1) -1;
		num2curindex = currentindex - (sumsize-size2) -1;

		sum[sumindex] = carryover;
		printf("sum = %u\n", sum[sumindex]);
		carryover = 0;

		if(num1curindex>0){
			printf("adding number 1\n");
			if(number1[num1curindex]>(UINT_MAX-sum[sumindex])){
				// i am adding a negative number for the next line
				sum[sumindex] += (number1[num1curindex] - UINT_MAX-1);
				printf("max: sum = %u\n", sum[currentindex]);
				checkoverflow = sum[sumindex];
				carryover++;
			}else{
				sum[sumindex] += number1[num1curindex];
				printf("notmax: sum %u\n", sum[sumindex]);
				checkoverflow = sum[sumindex];
			}
		}else{
			printf("num1 not added\n");
			checkoverflow = 0;
		}

		if(num2curindex>0){
			printf("adding number 2\n");
			printf("max-overflower = %u\n", UINT_MAX-checkoverflow);
			printf("number2[num2]  = %u\n", number2[num2curindex]);
			if((UINT_MAX-checkoverflow)<number2[num2curindex]){
				carryover++;
				sum[sumindex] += (number2[num2curindex]-UINT_MAX-1);
				printf("max: sum = %u\n", sum[sumindex]);
			}else{
				sum[sumindex] += number2[num2curindex];
				printf("notmax: sum =%u\n", sum[sumindex]);
			}
		}
		printf("carryover =%d\n\n", carryover);

	}

	return sum;
}

unsigned int* addM(unsigned int* number1, unsigned int* number2, int size){
	static unsigned int* sum;
	int checkoverflow;
	int carryover = 0;

	sum = (unsigned int*)malloc(size * sizeof(unsigned int));

	for( int currentindex = size-1; currentindex>0; currentindex--){
		//printf("currentindex = %d\n", currentindex);
		
		sum[currentindex] = carryover;
		//printf("sum = %u\n", sum[currentindex]);
		carryover = 0;

		if(currentindex>0){
			//printf("adding number 1\n");
			if(number1[currentindex]>(UINT_MAX-sum[currentindex])){
				// i am adding a negative number for the next line
				sum[currentindex] += (number1[currentindex] - UINT_MAX-1);
				//printf("max: sum = %u\n", sum[currentindex+1]);
				checkoverflow = sum[currentindex];
				carryover++;
			}else{
				sum[currentindex] += number1[currentindex];
				//printf("notmax: sum %u\n", sum[currentindex]);
				checkoverflow = sum[currentindex];
			}
		}else{
			//printf("num1 not added\n");
			checkoverflow = 0;
		}

		if(currentindex>0){
			/*
			printf("adding number 2\n");
			printf("max-overflower = %u\n", UINT_MAX-checkoverflow);
			printf("number2[num2]  = %u\n", number2[currentindex]);
			*/
			if((UINT_MAX-checkoverflow)<number2[currentindex]){
				carryover++;
				sum[currentindex] += (number2[currentindex]-UINT_MAX-1);
				//printf("max: sum = %u\n", sum[currentindex]);
			}else{
				sum[currentindex] += number2[currentindex];
				//printf("notmax: sum =%u\n", sum[currentindex]);
			}
		}
		//printf("carryover =%d\n\n", carryover);

	}

	return sum;
}

unsigned int* complementOfTwo( unsigned int* number, int size){
	static unsigned int* result;
	result = (unsigned int*)(malloc(size * sizeof(unsigned int )));

	int carryover= 1;

	for (int currentindex = size-1; currentindex > 0; currentindex--){
		result[currentindex] = ~number[currentindex]; 
		
		if (result[currentindex]==UINT_MAX){
			if (carryover == 1){
				result[currentindex] = 0;
				carryover = 1;
			}else{
				carryover = 0;
			}

		}else{
			result[currentindex] += carryover;
			carryover = 0;
		}
	}

	return result;
}

unsigned int* copy(unsigned int* original, int originalSize, int newSize){
	if (newSize<originalSize){
		printf("copy error: newSize is too small");
	}

	static unsigned int* copy;
	copy = (unsigned int*)(malloc(newSize * sizeof(unsigned int)));
	copy[0] =  original[0];

	for( int i = 1; i < newSize; i++){
		if (i<=(newSize - originalSize)){
			copy[i] = 0;
		}else{
			copy[i] = original[i-(newSize - originalSize)];
		}
	}

	return copy;
}

unsigned int* absSubtraction(unsigned int* number1, int size1, unsigned int* number2, int size2){
	static unsigned int* storenumber2;
	storenumber2 = (unsigned int*)(malloc(size1 * sizeof(unsigned int)));
	storenumber2 = copy(complementOfTwo(number2, size2), size2, size1);

	static unsigned int* difference;
	difference = (unsigned int*)(malloc(size1 * sizeof(unsigned int)));

	difference = addM(number1, storenumber2, size1);

	return difference;
}
// slightly broken do not use
unsigned int* subtract(unsigned int* number1, int size1, unsigned int* number2, int size2){
	// find out difference's array size
	int differenceSize;
	if (size1>size2){
		differenceSize = size1;
	} else{
		differenceSize = size2;
	}

	// checks to see if the final answer is negative
	// by checking which number is bigger
	// something is wrong with this shit
	int scenario = 0;
	for (int i = 1; i<differenceSize; i++){
		//printf("this is the first index = %d\n", i);
		if ((i+size1-differenceSize)>0 && (i+size2-differenceSize)>0){
			if (number1[i+size1-differenceSize]>number2[i+size2-differenceSize]){
				scenario = 1;
				break;
			}else if(number2[i+size2-differenceSize]>number1[i+size1-differenceSize]){
				scenario = 2;
				break;
			}
		}else{
			if((i+size1-differenceSize)>0 && number1[i+size1-differenceSize]!=0){
				scenario = 1;
				break;
			}else if((i+size2-differenceSize)>0 && number2[i+size1-differenceSize]!=0){
				scenario = 2;
				break;
			}
		}
	}


	static unsigned int* difference;
	difference = (unsigned int*)(malloc(differenceSize * sizeof(unsigned int)));


	switch (scenario){
		case 1:
			difference = absSubtraction(number1, size1, number2, size2);
			break;
		case 2:
			difference = absSubtraction(number2, size2, number1, size1);
			difference[0] = 1;
			break;
		case 0:
		default:
			printf("Error or the two nubmers are the same\n");
			difference[0] = UINT_MAX;		
	}

	return difference;
}

int shrink(unsigned int* number, int size){
	int emptyindex = 0;

	for(int currentindex = 1; currentindex<size&&number[currentindex]==0; currentindex++){
		emptyindex++;
	}

	for (int currentindex = 1; currentindex<(size-emptyindex); currentindex++){
		number[currentindex] = number[currentindex+emptyindex];
	}

	return size-emptyindex;
}

unsigned int* shift(unsigned int* number, int numberindex, int shiftamount){
	unsigned int* shiftednumber;
	shiftednumber = (unsigned int*)(malloc(numberindex * sizeof(unsigned int)));

	int split = shiftamount%32;
	int indexmove = shiftamount/32;

	unsigned int splitfront = 0;
	unsigned int splitback =0;
	for (int i = 0; i<32; i++){
		if(i<split){
			splitfront += pow(2, 31-i);
		}else{
			splitback += pow(2, 31-i);
		}
	}	

	unsigned int front;
	unsigned int back;
	for (int currentindex =1; currentindex<numberindex; currentindex++){
		
		if (currentindex+indexmove+1<numberindex){
			front =  ((number[currentindex+indexmove+1] & splitfront) >> (32-split));
		}else{
			front = 0;
		}

		if (currentindex+indexmove<numberindex){
			back = ((number[currentindex+indexmove] & splitback) << split);
		}else{
			back = 0;
		}	

		shiftednumber[currentindex] = back+front;
	}

	return shiftednumber;
}

void divideby2(unsigned int* number, int size){

	for (int i = size-1; i>0; i--){
		//printf("current i = %d\n", i);

		// separate number into 2 to catch overflow
		unsigned int splitfront = number[i] & (UINT_MAX-1);
		unsigned int splitback = number[i] & 1;

		//printf("front = %u, back = %u\n", splitfront, splitback);

		// shift the numbers to the correct places
		splitfront >>= 1;
		splitback <<= 31;

		//printf("front = %u, back = %u\n", splitfront, splitback);


		if ( i+1 < size){
			number[i+1] += splitback;
		}
		number[i] = splitfront;

		//printf("current number = %u\n", number[i]);
	}	 
}

// return 1 if number 1 is bigger and 0 for number2
int isbigger(unsigned int* number1, int size1, unsigned int* number2, int size2){
	int result;

	int biggersize;

	if (size1>size2){
		biggersize = size1;
	} else{
		biggersize = size2;
	}

	for (int i = 1; i<biggersize; i++){
		if ((i-biggersize+size1)>0 && (i-biggersize+size2) > 0){
			if (number1[i-biggersize+size1]>number2[i-biggersize+size2]){
				result = 1;
				break;
			}else if(number2[i-biggersize+size2]>number1[i-biggersize+size1]){
				result = 0;
				break;
			}
		}else{
			if((i-biggersize+size1)>0 && number1[i-biggersize+size1]!= 0){
				result = 1;
				break;
			}else if ((i-biggersize+size2) > 0 && number2[i-biggersize+size2]!=0){
				result = 0;
				break;
			}
		}
	}

	return result;
}

unsigned int* multiply(unsigned int* number1, int size1, unsigned int* number2, int size2){
	//printf("\nmultiplying starts here\n");

	unsigned int bits[32] =  {
			1,2,4,8,16,32,64,128,256,512,1024,2048,4096,
			8192,16384,32768,65536,131072,262144,524288,
			1048576,2097152,4194304,8388608,16777216,
			33554432,67108864,134217728,268435456,536870912,
			1073741824,2147483648
		};

	static unsigned int* product;

	int productsize; 

	productsize = size1 + size2;
	product = (unsigned int*)(malloc(productsize * sizeof(unsigned int)));
	for(int i = 1; i<productsize; i++){
		product[i]=0;
	}

	static unsigned int* storenumber1;
	//storenumber1 = (unsigned int*)(malloc(productsize * sizeof(unsigned int)));
	storenumber1 = copy(number1, size1, productsize);
	/*for (int i = 1; i<productsize; i++ ){
		if(i<=size1){
			storenumber1[i]=0;
		}else{
			storenumber1[i] = number1[i-size1];
			//printf("store number = %u,", storenumber1[i]); 
		}
	}*/
	/*printf("\n\n");
	for(int i = 1; i<productsize; i++){
		printf("%u,", storenumber1[i]);
	}
	printf("\n");*/


	unsigned int* shiftresult;
	for (int num2curindex = 1; num2curindex<size2; num2curindex++){
		//printf("current index of number 2 = %d\n", num2curindex );

		for (int currentbit = 31; currentbit>=0; currentbit--){
			//printf("currentbit = %d\n", currentbit);

			if((bits[currentbit] & number2[num2curindex])==bits[currentbit]){
				//printf("shifting\nprinting current product :\n");
				shiftresult = shift(storenumber1, productsize, currentbit+(32*(size2-num2curindex-1)));
				product = addM(product, shiftresult, productsize);

				/*for(int i = 1; i<productsize; i++){
					printf("%u,", product[i]);
				}
				printf("\n\n");*/
			}
		}
	}

	return product;
}

//has some slight problems in flooring/ the answer
unsigned int* divide(unsigned int* number1, int size1, unsigned int* number2, int size2){
	printf("\ndivision stared\n");

	unsigned int bits[32] =  {
			1,2,4,8,16,32,64,128,256,512,1024,2048,4096,
			8192,16384,32768,65536,131072,262144,524288,
			1048576,2097152,4194304,8388608,16777216,
			33554432,67108864,134217728,268435456,536870912,
			1073741824,2147483648
		};

	int n = -1, m = -1;
	for (int i = 1; n==-1 ||m==-1 ; i++){
		//printf("current i = %d\n",i);
		for(int i2 = 31; i2>=0; i2--){
			//printf("current bit = %d\n", i2);

			if (number1[i] >= bits[i2] && n==-1){
				/*
				printf("i found n\n");
				printf("%u,%u\n", number1[i], bits[i2]);
				*/
				n = i2 + 32*(size1-i-1);
			}
			if (number2[i] >= bits[i2] && m ==-1){
				/*
				printf("i found m\n");
				printf("%u,%u\n", number2[i], bits[i2]);
				*/
				m = i2 + 32*(size2-i-1);		
			}
			if (n!=-1 && m!=-1){
				break;
			}
			//printf("\n");
		}
	}

	
	int k = n-m+1;
	//printf("n= %d, m = %d, k = %d\n", n, m,k);

	int dividedsize = 2+(k)/32;
	//printf("dividedsize = %d\n", dividedsize);

	unsigned int* divided;
	divided = (unsigned int*)(malloc(dividedsize * sizeof(unsigned int)));

	unsigned int* addminus;
	addminus = (unsigned int*)(malloc(dividedsize * sizeof(unsigned int)));
	
	for (int i = 0; i<dividedsize; i++){
		if (i == dividedsize - k/32 -1){
			addminus[i] = bits[k%32]; // not sure if i need to add 1;
			divided[i] = bits[k%32];
		}else{
			addminus[i] =0;
			divided[i] = 0;
		}
	}
	/*
	printf("addminus = ");
	printraw(addminus, dividedsize);
	*/
	// lots of memory leak here. got to do something.
	unsigned int* check;
	for (int i = 0; i<k+1; i++){
		check = multiply(number2, size2, divided, dividedsize);
		//printraw(check, size2+dividedsize);

		divideby2(addminus, dividedsize);
		//printraw(addminus, dividedsize);

		if (isbigger(check, size2+dividedsize, number1, size1)==1){
			if (i==k){
				if (divided[dividedsize-1]==0){
					printf("we got a problem while dividing");
				}else{
					divided[dividedsize-1] -=1;
				}	
			}else{
				//printf("we are subtracting\n");
				divided = absSubtraction(divided, dividedsize, addminus, dividedsize);
			}
			
		}else{
			//printf("we are adding\n");
			divided = addM(divided, addminus, dividedsize);
		}
		/*
		printraw(divided, dividedsize);
		printf("movingon\n\n");
		*/

	}
	
	return divided;	
}


unsigned int* divideV2(unsigned int* number1, int size1, unsigned int* number2, int size2){
	printf("\ndivision version 2 started\n");

	unsigned int bits[32] =  {
			1,2,4,8,16,32,64,128,256,512,1024,2048,4096,
			8192,16384,32768,65536,131072,262144,524288,
			1048576,2097152,4194304,8388608,16777216,
			33554432,67108864,134217728,268435456,536870912,
			1073741824,2147483648
		};

	int n = -1, m = -1;
	for (int i = 1; n==-1 ||m==-1 ; i++){
		//printf("current i = %d\n",i);
		for(int i2 = 31; i2>=0; i2--){
			//printf("current bit = %d\n", i2);

			if (number1[i] >= bits[i2] && n==-1){
				/*
				printf("i found n\n");
				printf("%u,%u\n", number1[i], bits[i2]);
				*/
				n = i2 + 32*(size1-i-1);
			}
			if (number2[i] >= bits[i2] && m ==-1){
				/*
				printf("i found m\n");
				printf("%u,%u\n", number2[i], bits[i2]);
				*/
				m = i2 + 32*(size2-i-1);		
			}
			if (n!=-1 && m!=-1){
				break;
			}
			//printf("\n");
		}
	}

	
	int k = n-m+1;
	//printf("n= %d, m = %d, k = %d\n", n, m,k);

	int dividedsize = 2+(k)/32;
	//printf("dividedsize = %d\n", dividedsize);

	unsigned int* resultant;
	resultant = (unsigned int*)(malloc(dividedsize * sizeof(unsigned int)));

	unsigned int* tempStore;
	tempStore = (unsigned int*)(malloc(dividedsize * sizeof(unsigned int)));
	
	for (int i = 0; i<dividedsize; i++){
		if (i == dividedsize - k/32 -1){
			tempStore[i] = bits[k%32]; // not sure if i need to add 1;
		}else{
			tempStore[i] =0;
		}
		resultant[i] = 0;
	}

	unsigned int* check1;
	unsigned int* check2;
	for(int i = 0; i < k+1; i++){
		check1 = addM(resultant, tempStore, dividedsize);
		check2 = multiply(check1, dividedsize, number2, size2);
		if (isbigger(number1, size1, check2, dividedsize+size2)){
			resultant = addM(resultant, tempStore, dividedsize);
		}
		divideby2(tempStore, dividedsize);
	}

	resultant[0] = dividedsize;

	return resultant;
}

unsigned int* mod(unsigned int* number1, int size1, unsigned int* number2, int size2){
	unsigned int* quotient = divideV2(number1, size1, number2, size2);
	int quotientsize = quotient[0];

	unsigned int* multiple = multiply(number2, size2, quotient, quotientsize);
	int multiplesize = size2 + quotientsize;

	multiplesize = shrink(multiple, multiplesize);

	unsigned int* resultant = subtract(number1, size1, multiple, multiplesize);
	//int resultantsize = size1;

	return resultant;
}

void printint(unsigned int* number, int numbersize){
}


int main(void){
	printf("INT_MAX = %d\n", INT_MAX);
	printf("UINT_MAX = %u\n", UINT_MAX);
	printf("ULONG_MAX = %lu\n", ULONG_MAX);

	unsigned int pointer[5];
	pointer[0] = 0;
	pointer[1] = 40425;
	pointer[2] = 788719;
	pointer[3] = 275731;
	pointer[4] = 2354496;

	unsigned int pointer1[5];
	pointer1[0] = 0;
	pointer1[1] = 0;
	pointer1[2] = 425646;
	pointer1[3] = UINT_MAX;
	pointer1[4] = 0;

	printraw(pointer, 5);
	printraw(pointer1, 5);



	unsigned int* divided2 = divideV2(pointer, 5, pointer1, 5);
	printraw(divided2, 2);

	unsigned int* modded = mod(pointer, 5, pointer1, 5);
	printraw(modded, 4);

	
	return 0;
}