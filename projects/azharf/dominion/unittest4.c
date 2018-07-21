
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




int main() { 



    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

       int seed = 2000;


       
       struct gameState G;

         
         printf ("TESTING gainCard():\n");
            
              memset(&G, 23, sizeof(struct gameState));
         
          initializeGame(2, k, seed , &G);

         
         // empty out the gold pile 
         
         printf("\nGold pile empty\n");
         
         
         G.supplyCount[gold] = 0; 
                    assertTrueFunction(gainCard(gold,&G,0,0), - 1);
        

         G.supplyCount[gold] = 30; 

         



         printf("\n Card has been added to deck\n");
         
         int deckCount = G.deckCount[0];
         
         gainCard(gold,&G, 1 , 0); 
         
         assertTrueFunction(deckCount+1,G.deckCount[0]);


         printf("\nAdding card to hand\n");
         
         int handCount = G.handCount[0];
         
         gainCard(gold,&G, 2, 0 );
         
         assertTrueFunction(handCount + 1, G.handCount[0]);


        printf("\nAdding card to discard pile\n");
        
        int discardCount = G.discardCount[0];
        
        gainCard(gold,&G,0,0); 
        
        assertTrueFunction(discardCount+1, G.discardCount[0]);
    




        printf("\n Decreasing gold supply from hand\n");
        
        int goldSupply = G.supplyCount[gold];
       
        gainCard(gold, &G, 0, 0 ); 
        
        assertTrueFunction(goldSupply-1, G.supplyCount[gold]);



      if (counterVariable){

      printf("\nTest: Test Failed\n");
     
      printf("Test: Test Failed %d\n",counterVariable);
     
     }

     else {
      printf("\nTest: Test passed\n\n");
     }

     return 0 ; 






}