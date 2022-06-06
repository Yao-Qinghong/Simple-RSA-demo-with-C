#include <stdio.h>
#include<stdlib.h>
#include<math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

#define BUF_SIZE 128

int gcd(int numA, int numB);
void getPrimeNumberFromUser(int *p, int *q);
int getPrimeNumber(char msg[]);
bool isPrimeNumber(int userinput);
bool isNumber(char s[]);
int getEUser(int *phiN);
int modInverse(int numA, int numB);
int generatePrivateKey(int *phiN, int *e);

int main(void) {

        // Two random prime numbers
        int p ,q; 
        // int is used as by the properties of prime numbers they should be whole number and positivr integers
        int e; 

        int n;
        int phiN;
        int d;

        getPrimeNumberFromUser(&p,&q);
        n = p*q;
        phiN = (p-1)*(q-1);
        printf("Euler's Function [phi(n)] = %d\n\n",phiN);

        e = getEUser(&phiN);

        int temp = gcd(e,phiN);

        d = generatePrivateKey(&phiN ,&e);
        //printf("The gcd of %d and %d is %d\n",e ,phiN,temp );

        printf("\nYour Private key: (d = %d, n =%d)\n",d,n); 
        return 0;
}

/** @brief  reculsive function to find GCD of two number with  Euclidean algorithm
 *
 *  @param NumA 
 *  @param NumB 
 *  @return int
 */
int gcd(int numA, int numB){
        if (numB == 0)
                return numA;
        return gcd(numB, numA % numB);
}

/** @brief  funciton use to  get p and q from user to ensure that p and q are supposed to be different
 *
 *  @param *p function pointer pointing to the first prime number p 
 *  @param *q function pointer pointing to the second prime number q 
 *  @return void
 */
void getPrimeNumberFromUser(int *p, int *q) {
        *p = getPrimeNumber("prime number 1");
        *q = getPrimeNumber("prime number 2");
        while(*p ==*q){
                printf("Error: The two value has to be different\n\n");
                *p = getPrimeNumber("prime number 1");
                *q = getPrimeNumber("prime number 2");
        }

        printf("Primes:\n p = %d, q = %d \n\n",*p,*q);

}

/** @brief  function to obtain and check for the correctness of the prime numbers user entered.
 *
 *  @param msg[] get message to display prompt to user 
 *  @return int
 */
int getPrimeNumber(char msg[]){
        char temp[BUF_SIZE];
        do {
                printf("Enter %s: ",msg);
                scanf("%s",temp);
                if(isNumber(temp)){
                        if(isPrimeNumber(atoi(temp)) == true){
                                return atoi(temp);
                                break;
                        }
                        printf("Error: Please enter a valid prime number\n");

                }else{
                        printf("Error: Please enter a valid integer\n");
                }
        }while(true);
}

/*@brief  function to check if an user input is  a prime number 
 *
 *  @param userinput 
 *  @return bool
 */
bool isPrimeNumber(int userinput){
        // Iterate from 2 to sqrt(n)
        for (int i = 2; i <= sqrt(userinput); i++) {
                 // If n is divisible by any number between
                 // 2 and n/2, it is not prime
                 if (userinput % i == 0) {
                         return false;
                         break;
        }
    }
    return true;

}

/*@brief  function to check if an user input is numbers
 *
 *  @param s[] 
 *  @return bool
 */
bool isNumber(char s[]){
    for (int i = 0; s[i]!= '\0'; i++)
    {
        if (isdigit(s[i]) == 0)
              return false;
    }
    return true;
}

/*@brief  function to get e from user and ensure that it meets the 
 *
 *  @param *phiN 
 *  @return int
 */
int getEUser(int *phiN){
        int tempArray[BUF_SIZE];
        int i=0, counter =2;
        char tempInput[BUF_SIZE];

        printf("pick an e below such that 0<e<phi(n) and GCD(e,phi(n))=1:\n ");
        while(counter < *phiN && i < 12){ 
                // for demostration purpose the value of possible e is limited to the first 12 
                // numbers preventing this funtion to eat up too many system resourvces
               
                if(gcd(counter,*phiN) == 1){
                        tempArray[i] = counter;
                        printf("%d, ",tempArray[i]);
                        
                        i++;
                        if (i % 6 ==0){
                                printf("\n");
                        }
                }

                counter++;
        }
        printf("\n");
        
        do {
                printf("Enter e: ");
                scanf("%s",tempInput);
                if(isNumber(tempInput)){
                        for(int j = 0; j<= i; j++){
                                if( atoi(tempInput) ==tempArray[j]){
                                       return  atoi(tempInput);
                                       break;
                                }
                        }
                        printf("Error: Please enter a valid number as listed for e\n");

                }else{
                        printf("Error: Please enter a valid integer not alphabet\n");
                }
        }while(true);

}

/*@brief  function to generate the private key 
 *
 *  @param *phiN, *e
 *  @return int
 */
int generatePrivateKey(int *phiN, int *e){
        return modInverse(*e,*phiN);
}

/*@brief  function to calculate the inverse mod of 2 numbers
 *
 *  @param numA, numB
 *  @return int
 */
int modInverse(int numA, int numB){
        // Initialise 
        int inv, u1, u3, v1, v3, t1, t3, q, iter;
        u1 = 1,u3 = numA, v1 = 0, v3 = numB;
        
        // odd/even iterations 
        iter = 1;
        while (v3 != 0){
                // Divide and "Subtract" 
                q = u3 / v3;
                t3 = u3 % v3;
                t1 = u1 + q * v1;

                // Swap 
                u1 = v1; v1 = t1; u3 = v3; v3 = t3;
                iter = -iter;
        } 
        
        // Making sure u3 = gcd(numA,numB) == 1 
        if (u3 != 1){
                return 0;   // Error: No inverse exists 
        }
        
        // Ensure a positive result 
        if (iter < 0){
                inv = numB - u1;
        }else{
                inv = u1;
        }
        
        return inv;
}
