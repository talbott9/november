int stickGameNumber = 30;
bool playerTurn = 1;
bool louisLosing;

LTexture gStickNumber;
void stickGame() {
	activeDialogue = 1;
	int rng = rand()%10 + 1;
	int maxTurnsLeft = stickGameNumber/2;
	int minTurnsLeft = stickGameNumber/5;
	gStickNumber.loadFromRenderedText(std::to_string(stickGameNumber), White, 0, gFancyFont);
	gStickNumber.render(textX + 500, textY + 30);
	if(maxTurnsLeft != 0 && minTurnsLeft != 0 && stickGameNumber/maxTurnsLeft%2 == 0 && stickGameNumber/minTurnsLeft%2 == 0) {
		louisLosing = 1;
	} else {
		louisLosing = 0;
	}
	if(playerTurn) {
		promptSelect = 1; 
		lineNumber = 31;
		if(trigger%2 != 0) {
			if(!bunki)
				stickGameNumber -= 2;
			else
				stickGameNumber -= 5;
			promptSelect = 0;
		}
	} else {
		if(louisLosing) {
			lineNumber = 32;
		} else {
			lineNumber = 33;
		}
		if(trigger% 2 == 0) {
			//printf("%i\n", maxTurnsLeft);
			switch(maxTurnsLeft) {
				case 1: stickGameNumber -= 2; break; //1, 2
				case 2: stickGameNumber -= 2; break; //3, 4, 5
				case 3: stickGameNumber -= 5; break; //6, 7
				case 4: if(stickGameNumber == 8)
						stickGameNumber -= 5;
					else
						stickGameNumber -= 2;
					break; //6, 7, 8
				case 5:	stickGameNumber -= 2;
					break; //9, 10, 11
				case 6: if(stickGameNumber != 12)
						stickGameNumber -= 5;
					else
						stickGameNumber -= 2; break; //12, 13, 14
				case 7: if(stickGameNumber != 14)
						stickGameNumber -= 2;
					else
						if(rng <= 8)
							stickGameNumber -= 2;
						else
							stickGameNumber -= 5;
					break; //15, 16, 17
				case 8:	if(stickGameNumber != 16)
						stickGameNumber -= 5;
					else
						stickGameNumber -= 2;
					break; //16, 17
				case 9: stickGameNumber -= 5; 
					break; //18, 19
				case 10: stickGameNumber -= 5;
					 break;
				default: stickGameNumber -= 2;
					 break;
			}
		}
	}

	if(trigger%2 == 0)
		playerTurn = 1;
	else
		playerTurn = 0;

	if(stickGameNumber <= 0) {
		if(playerTurn) {
			hillou = hillou1_1_1;
			indexScript(hildegardelouis1_1_1);
		} else {
	        	hillou = hillou1_1_2;
			indexScript(hildegardelouis1_1_2);
		}
		gStickNumber.free();
		stickGameNumber = 30; playerTurn = 1; resetScene();
	}

}
