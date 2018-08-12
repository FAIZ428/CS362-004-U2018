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
int shuffle_fail = 0 ; 
int drawCardFail = 0 ; 
int deckHandCountFail = 0; 
int treasureFail = 0; 



//

void adventurererTesting(int p, struct gameState *after ){

	
	int postTreasure = 0; 
	
	int preTresure = 0; 
	

	int tempHand[MAX_HAND];

	int drawntreasure = 0 ; 

	// initilize variables for gamestate
	struct gameState before; 
	int cardDraw; 
	int card; 
	int bonus = 0 ; 

	int a ; 
	int b ; 
	int c ; 
	int d; 

	int z = 0; 

	memcpy(&before, after, sizeof(struct gameState)); 

	// call the cardeffect 
	a = cardEffect(adventurer,0,0,0,after,0,&bonus);

	if(a){
			cardEffectsFail++;
	}

	while(drawntreasure < 2){

		if(before.deckCount[p] < 1){

			b = shuffle(p,&before);

			if(b == -1 && before.deckCount[p] >=1){
				shuffle_fail++;

			}
		}

		c = drawCard(p,&before);
	

	




	if( c == -1 && before.deckCount[p] != 0){

		drawCardFail++;


	}

	cardDraw = before.hand[p][before.handCount[p] - 1];
	if (cardDraw == copper || cardDraw == silver || cardDraw == gold)
				drawntreasure++;

		else{
			
			tempHand[z] = cardDraw;
			
			before.handCount[p] --; 
			
			z++; 
		}

	
}





   while(z - 1 >= 0) {
            before.discard[p][before.discardCount[p]++] = tempHand[z - 1]; // discard all cards in play that have been drawn
            z = z - 1;
    }

   
 	for (d = 0; d < after->handCount[p]; d++){
 		card = before.hand[p][d]; 

 		if ( card == copper || card == silver || card == gold){
 			preTresure ++ ; 
 		}
 	}


 			if ( postTreasure != preTresure){
 				treasureFail++; 
 			}




  int afterHC = after->handCount[p];
  
  int afterDC = after->deckCount[p]; 
  int afterDCC = after->discardCount[p];
  
  int beforeHC = before.handCount[p];
  
  int beforeDC =  before.deckCount[p];

  int beforeDCC = before.discardCount[p];

   if( !( afterHC == beforeHC && afterDC == beforeDC && afterDCC == beforeDCC)){

   	deckHandCountFail++;

   } 
}





	 int main() { 


printf(" THE RANDOM TEST OF Function: adventurer, adventurererTesting()\n");

int times = 10000; 

int treasure[] = {copper,silver,gold}; 

int numTreasures;

int player; 

struct gameState state; 

int minimum = 3; 

srand(time(NULL));


//generate  game

for (int e = 0; e < times; e++){
	for (int i = 0; i < sizeof(struct gameState); i++){

		((char*)&state)[i] = floor(Random() * 256);

	}





		//random testing values
	player = floor(Random() * MAX_PLAYERS);
	



	state.deckCount[player] = floor(Random() * ((MAX_DECK - minimum) + 1) + minimum);
	
	





	numTreasures = floor(Random() * ((state.deckCount[player] - minimum) + 1) +  minimum); 


	


		for(int i = 0; i<numTreasures; i++){

			state.deck[player][i] = treasure[rand() % 3];





		}

		state.discardCount[player] = 0; 
		
		state.handCount[player] = floor (Random() * (( MAX_HAND - minimum) + 1) + minimum);
		
		state.whoseTurn = player;



			adventurererTesting(player, & state); 













	 }


	  int Fail_of_cards = cardEffectsFail + drawCardFail 

	+ shuffle_fail + deckHandCountFail + treasureFail; 





		if(times - Fail_of_cards <= 0) {

			printf("\nTHE TEST RESULTS OF THE ADVENTURER CARD\n");
			printf("PASSES TEST:  %d\n",0);
			printf("FAILED TEST:  %d\n", times);
		}








		else {

			printf("\nTHE RESULTS OF THE ADVENTURER CARD\n");
			printf("PASSES TEST:   %d\n", times - Fail_of_cards);
			printf("FAILED TEST: %d\n", Fail_of_cards);
		}




		if (Fail_of_cards == 0){
			printf("THE RANDOM TEST HAS PASSED \n\n");
		}







		else{
			printf("\n$$$$$$ FAILURE  DETAILS $$$$$$\n");
			printf(" shuffle () FAIL: %d\n",shuffle_fail);


			printf("drawCard() FAIL %d\n",drawCardFail);





			printf("cardEffect FAIL %d\n", cardEffectsFail);

			printf("Treasure   FAIL %d\n", treasureFail);

			printf("Hand and deck fail %d\n ", deckHandCountFail);

			printf("THE RANDOM TEST HAS FAILED \n\n\n") ;
		}

	




return 0 ; 

}
















