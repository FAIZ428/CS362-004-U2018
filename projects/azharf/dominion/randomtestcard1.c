#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>





int cardEffectsFail = 0; 
int discardCardFails = 0 ; 
int drawCardFail = 0 ; 
int deckHandCountFail = 0; 
int numFail = 0 ; 
int Opponent_Player_Hand_Fail = 0 ; 


// function to test the council room 

void council_roomTesting( int p, struct gameState *after){

  int a;
  
  int b;
  
   int c;
  
  int d; 
  
  int e; 
  
  int f;
  int g;
  
  int h ;

  int bonus_play = 0 ; 

  // take the functions functionality
  struct gameState before; 


  memcpy(&before,after, sizeof(struct gameState));

  // call the card to run with the smithycard function 
  a = cardEffect(council_room,0,0,0, after,0,&bonus_play);


  // call the cards 
  b = drawCard(p,&before);
  c = drawCard(p,&before); 
  d = drawCard(p , &before); 
  e = drawCard(p,&before); 

  before.numBuys ++; 

  for (h = 0; h<before.numPlayers;h++){

    if (h != p){
      f = drawCard(h, &before);

      // verify drawcard

      if ( f == -1 && before.deckCount[h] != 0){
        drawCardFail ++ ; 
      }
    }
  }


    g = discardCard(0,p, &before, 0); 


  int afterHC = after->handCount[p];
  
  int afterDC = after->handCount[p]; 

  int beforeHC = before.handCount[p];
  
  int beforeDC =  before.deckCount[p];



  if (before.numBuys != after->numBuys){

    numFail++ ; 
  }

  if ( b == -1 && before.deckCount[p] != 0){
      drawCardFail++;
  }

  if( c == -1 && before.deckCount[p] != 0){
      drawCardFail++; 
  }

  if (d == -1 && before.deckCount[p] != 0){

      drawCardFail++;
  }

  if (e == -1 && before.deckCount[p] != 0){
      drawCardFail++; 
  }


  // compare the cardeffect or discard to see if it fails

  if(!(a == 0 && g == 0)){

    if (a){
      cardEffectsFail++;
    }

    if(g){
      discardCardFails++;
    }
  }

  // check for match found
if(!(afterDC == beforeHC && afterDC == beforeDC)){

    deckHandCountFail++; 
}


    for ( h = 0; h < before.numPlayers; h ++){

      if( h != p){

        if (!(after->handCount[h] == before.handCount[h] && after->deckCount[h] == before.deckCount[h])){

          Opponent_Player_Hand_Fail++; 
        }
      }
    }

}


int main()


{

   
    printf(" THE RANDOM TEST OF Function: council_room()\n");
    
    int player;
    int times = 10000;
    int players [] = {2,3,4};
    int  gamePlayers;
    int handCount;
    int deckCount;
    int discardCount;
    
    struct gameState state;
    
    srand(time(NULL));

    for (int n = 0; n < times; n++) {
        
        for (  int i = 0; i < sizeof(struct gameState); i++) {
           
            ((char*)&state)[i] = floor(Random() * 256);
        
        }
    
    state.numPlayers   = players[rand() % 3 ] ; 
     state.numBuys = 1; 
        state.playedCardCount = floor(Random() * (MAX_DECK-1));
        
        player = state.numPlayers - 2; 

        deckCount = floor(Random() * MAX_DECK);
        handCount = floor(Random() * MAX_HAND);

        discardCount = floor(Random() * MAX_DECK);
        state.whoseTurn = player; 



          for ( int i = 0 ; i < state.numPlayers; i++){
              state.deckCount[i] = deckCount;
              state.handCount[i] = handCount;
              state.discardCount[i] = discardCount;
          }


          council_roomTesting(player, & state);



}





    int Fail_of_cards = cardEffectsFail + discardCardFails +
                        drawCardFail + deckHandCountFail + numFail;
   
    




printf("\n RESULTS\n");

printf("PASSED TESTS: %d\n",times - Fail_of_cards);

printf("FAILED TEST: %d\n", Fail_of_cards);





if (Fail_of_cards == 0) {
       
        printf (" PASSED RANDOM TEST \n\n");
    }
    
    else {
       
        printf("\n $$$$$$ FAILURE  DETAILS $$$$$$\n");
       
        printf("drawCard() fail: %d\n",drawCardFail);
        
        printf("cardEffect() fail: %d\n",cardEffectsFail);
        
        printf("discardCard() fail: %d\n",discardCardFails);
        
        printf(" numFail count mismatch: %d\n",numFail);


        printf("The Opponent_Player_Hand_Fail count mismatch: %d\n", Opponent_Player_Hand_Fail);
       
        printf("Deck hand count mismatch: %d\n", deckHandCountFail);



    }

      



        return 0; 


}

