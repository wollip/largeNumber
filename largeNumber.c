#include <stdio.h>
#include <math.h>
#include <string.h>


//prints the largeNumber array
int printnumber(int *largeNumber, int limit){
	int boolean = 0;
	//going through each index
	//printf("function printnumber called\n");
	for (int i =0; i < limit ; i++){
		// does not print the zeros in front of the number
		if(largeNumber[i]==0 && boolean == 0){
			continue;
		}else{
			boolean++;
		}
		// begins print the array
		//printf("begin printing largeNumber\n");
		printf("%d", largeNumber[i]);
		// adds a comma for every 3 digits so it is easier to read.
		if (i%3 == 0){
			printf(",");
		}

	}
	printf("\n");
	return boolean;
}
//adds 2 largeNumber
int* add(int *number1, int limit1, int *number2, int limit2){
	int currentplace, nextplace = 0;
	static int *sum;
	char run;

	//printf("limit1 = %d; limit 2 = %d\n", limit1, limit2);
	//checks which number is bigger
	int difference = limit1 - limit2;
	//printf("the difference between araysize is %d\n", difference);
	if (difference>0){
		run = 'a';
	}else if(difference == 0){
		run = 'b';
	}else{
		run = 'c';
	}
	// for how program works, refer to case (case>0)
	switch (run){
		// when limit 2 is bigger
		case 'c':
			printf("limit2 is bigger\n");
			sum = (int*)malloc((limit2) * sizeof(int));
			
			for (int i = 0;  i < limit1 ; i++){
				currentplace = nextplace + number1[limit1 - i - 1] + number2[limit2 - i -1];
				sum[limit2 - i - 1]  = currentplace%10;
				nextplace = currentplace/10;
			}
			for (int i = limit1 ; i <limit2; i++){
				currentplace = number2[limit2 - i - 1] + nextplace;
				sum[limit2 - i - 1] = currentplace%10;
				nextplace = currentplace/10;
			}
			
			break;
		// when the limits are equal
		case 'b':
			printf("limits are the same\n");
			sum = (int*)malloc((limit1+1) * sizeof(int));
			
			for (int i = 0;  i < limit2 ; i++){
				currentplace = nextplace + number1[limit1 - i - 1] + number2[limit2 - i -1];
				sum[limit1 - i]  = currentplace%10;
				nextplace = currentplace/10;
			}
			sum[limit1 - limit2] = nextplace;
			break;
		// when the first limit is bigger
		case 'a':
			printf("limit 1 is bigger\n");
			//creates an array to store the values
			sum = (int*)malloc(limit1 * sizeof(int));
			//begins adding the values
			for (int i = 0;  i < limit2 ; i++){
				//nextplace = the value that carried from the previous digit
				//currentplace = the sum of all the values at the current digit
				currentplace = nextplace + number1[limit1 - i - 1] + number2[limit2 - i -1];
				//set the correct current place value(ie only 1 digits not 2)
				sum[limit1 - i - 1]  = currentplace%10;
				//set the nextplace or the carrying over digits.
				nextplace = currentplace/10;
			}
			for (int i = limit2 ; i <limit1; i++){
				currentplace = number1[limit1 - i - 1] + nextplace;
				sum[limit1 - i - 1] = currentplace%10;
				nextplace = currentplace/10;
			}
			break;
	}
	return sum;
}
// converts a char array(string) filled with ints to an int array
// return length limit
int* stringToInt( char * number , int limit ){
	// creates a variable array
	static int *array;
	array = (int*)malloc(limit * sizeof(int));

	//convert each char into a int
	for ( int i = 0; i < limit; i++ ){
		array[i] = number[i] - '0';
	}
	return array;
}
// multiply 2 large number arrays with known limit and returns a new array
//return length limit1 + limit2
int* multiply( int * array1, int limit1, int * array2, int limit2 ){
	// finds the maxium possible length
	int totallimit = limit1 + limit2;
	//creates a variable array
	static int * multiple;
	multiple = (int*)malloc(totallimit * sizeof(int));
	// make sure the variable array has an initial value of 0, not garbage value
	for (int i =0; i < totallimit; i++){
		multiple[i] = 0;
	}
	// begin multiplication starting from largest smallest units
	int placement =0, storing;
	for (int i = 0; i < limit1 ; i++){		//for every number of array1
		for (int x = 0; x < limit2; x++){	//multiply it by everynumber of array2
			storing = array1[i] * array2[x];//value to be stored, could be double digit
			placement = x + i + 1;			//place to store value
			multiple[placement] += storing; //storing value
		}
	}
	//make sure every index of the array is only 1 digit long, starts from unit digit
	int up1place = 0, place;
	for (int i = 0; i < totallimit; i++){
		place = totallimit - i - 1; 		//find placement
		multiple[place] += up1place;		//adds the none unit digits value from the previous index
		up1place = multiple[place] /10;		//takes away the non unit digits to add to next index
		multiple[place] %= 10;				//convert the current index to a unit digit
	}

	return multiple;
}
//finds the factorial up to the factorial of 99
//return array length 2n+2
int* factorial(int n){
	//declaring variables
	int currentnumber[2];
	int x[2] = {0,1};
	int *returnvalue = x;
	// begins multiplying the values one by one
	for (int i = 1; i <= n; i++){
		//set up the current number to be multiplied
		currentnumber[0] = i/10;
		currentnumber[1] = i%10;
		int *pointer = currentnumber;
		// multiplying the value to the previous value.
		returnvalue = multiply(returnvalue, i*2, currentnumber, 2);	
	}
	return returnvalue;
}
// finds the base up to 99
// array limit = 2*exponenet
int* power(int base0, int exponent0){
	int base[2] = {base0/10,base0%10};
	printf("the base is %d%d\n", base[0], base[1]);
	int* product = base;
	if(exponent0==0){
		int whatever[] = {1};
		int* product = whatever;
		return product;
	}
	
	for (int i = 0; i<(exponent0-1); i++){
		product = multiply(product, 2*(i+1) ,base, 2);

		printnumber(product, 2*(1+i)+2);
	}
	printf("power ran\n");
	return product;
}
//term 1 = 1; term 2 = 1; term 3 = 2
int* fibonacci(int term){
	int arraysize1 =1;
	int arraysize2 =1;
	int sumsize, currentterm;
	int hi[]= {1};
	int hi1[] ={1};
	int *term1 = hi;
	int *term2 = hi1;
	int *sum;
	printf("arraysize1 = %d; arraysize2 = %d\n", arraysize1, arraysize2);
	for (currentterm =3; currentterm<=term; currentterm++){
		if (arraysize1 == arraysize2){
			sumsize = arraysize1+1;
		}else if (arraysize2 > arraysize1){
			sumsize = arraysize2;
		}
		sum = add(term1, arraysize1, term2, arraysize2);
		
		term1 = term2;
		arraysize1 = arraysize2;
		term2 = sum;
		arraysize2 = sumsize;

		int boolean = printnumber(term2, arraysize2);
		printf("currentterm = %d\n", currentterm);
		if (boolean == 1000){
			break;
		}
	}

	return sum;
}
int main(void){
	
	fibonacci(1000000);

	return 0;
}

