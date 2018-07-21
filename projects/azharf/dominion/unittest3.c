#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// verify the test
int counterVariable = 0 ; 


// assertTrue function to collect coverage
void assertTrueFunction(int x, int y){

     if (x == y){
          printf("Test: PASSED\n" );
     }


     else {
          printf("Test: FAILED" );
  
     counterVariable++; 
}

}


// main driver to test out the function

int main(){

	int r;
	int numPlayers = 2;

	// the kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};


     struct gameState G;
     int seed = 2000;

     printf ("TESTING isGameOver():\n");

     memset(&G,23,sizeof(struct gameState));   // clear the game state

     r = initializeGame(numPlayers,k,seed,&G);

     G.supplyCount[province] = 1;

     G.supplyCount[0] = 0;

     G.supplyCount[1] = 0; 

     G.supplyCount[2] = 0; 

     printf("\nThree empty piles given\n");


     assertTrueFunction(isGameOver(&G),1);

   	// verify that cards empty  
     G.supplyCount[0] = 1; 

     G.supplyCount[1] = 1; 

     G.supplyCount[2] = 1; 


     printf("\n The province Cards arent empty\n");
     printf("\n The Three supply piles arent empty\n");


     assertTrueFunction(isGameOver(&G),0);


     if (counterVariable){

     	printf("Test: Test Failed\n");
     	printf("Test: Test Failed %d\n",counterVariable);
     
     }

     else {
     	printf("\nTest: Test passed\n\n");
     }


     return 0 ; 







}