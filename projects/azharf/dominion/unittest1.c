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

	int player; 
	
	int numPlayers = 2;

	// the kingdom cards
	int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};


     struct gameState G;
     int seed = 2000;

     printf ("TESTING shuffle():\n");
	
     memset(&G,23,sizeof(struct gameState));   // clear the game state
	
     initializeGame(numPlayers,k, seed, &G);
     
     G.deckCount[player] = 0; 
	
     printf("\nPlayer deck count = 0\n");
    
     assertTrueFunction(shuffle(player,&G),-1);
	 

     
	printf("\n The player decks is 10 previously and post shuffle\n");
	
    G.deckCount[player] = 10; 
	
    shuffle(player,&G);
   
    assertTrueFunction(G.deckCount[player],10); 

   	
   	 printf("\n The cards have been shuffled\n");
     
     int before_shuffledCard = G.deck[player][0];
     
     shuffle(player,&G);
     
     int after_suffledCard = G.deck[player][0];

     if(before_shuffledCard != after_suffledCard){

     	assertTrueFunction(1,1);
     }

     else {
     			assertTrueFunction(0,1);
     }



     if (counterVariable){

     	printf("\nTest: Test Failed\n");
     	printf("Test: Test Failed %d\n",counterVariable);
     
     }

     else {
     	printf("\nTest: Test passed\n\n");
     }


     return 0 ; 







}