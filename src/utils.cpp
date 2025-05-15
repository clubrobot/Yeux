//
// Created by boris on 5/15/25.
//
#include "utils.h"
#include "alphabet.h"
#include <Arduino.h>

char** stringToPatterns(char *str){
	uint16_t size = strlen(str);
	char **ret = (char**)malloc(size * sizeof(char*));
	for(uint16_t i = 0;i<size;i++){
		switch (str[i]){
			case ' ': ret[i] = SPACE; break;
			case '0': ret[i] =NUM_0; break;
			case '1': ret[i] =NUM_1; break;
			case '2': ret[i] =NUM_2; break;
			case '3': ret[i] =NUM_3; break;
			case '4': ret[i] =NUM_4; break;
			case '5': ret[i] =NUM_5; break;
			case '6': ret[i] =NUM_6; break;
			case '7': ret[i] =NUM_7; break;
			case '8': ret[i] =NUM_8; break;
			case '9': ret[i] =NUM_9; break;
			case 'a': ret[i]=A;break;
			case 'A': ret[i]=A;break;
			case 'b': ret[i] = B; break;
            case 'B': ret[i] = B; break;
            case 'c': ret[i] = C; break;
            case 'C': ret[i] = C; break;
            case 'd': ret[i] = D; break;
            case 'D': ret[i] = D; break;
            case 'e': ret[i] = E; break;
            case 'E': ret[i] = E; break;
            case 'f': ret[i] = F; break;
            case 'F': ret[i] = F; break;
            case 'g': ret[i] = G; break;
            case 'G': ret[i] = G; break;
            case 'h': ret[i] = H; break;
            case 'H': ret[i] = H; break;
            case 'i': ret[i] = I; break;
            case 'I': ret[i] = I; break;
            case 'j': ret[i] = J; break;
            case 'J': ret[i] = J; break;
            case 'k': ret[i] = K; break;
            case 'K': ret[i] = K; break;
            case 'l': ret[i] = L; break;
            case 'L': ret[i] = L; break;
            case 'm': ret[i] = M; break;
            case 'M': ret[i] = M; break;
            case 'n': ret[i] = N; break;
            case 'N': ret[i] = N; break;
            case 'o': ret[i] = O; break;
            case 'O': ret[i] = O; break;
            case 'p': ret[i] = P; break;
            case 'P': ret[i] = P; break;
            case 'q': ret[i] = Q; break;
            case 'Q': ret[i] = Q; break;
            case 'r': ret[i] = R; break;
            case 'R': ret[i] = R; break;
            case 's': ret[i] = S; break;
            case 'S': ret[i] = S; break;
            case 't': ret[i] = T; break;
            case 'T': ret[i] = T; break;
            case 'u': ret[i] = U; break;
            case 'U': ret[i] = U; break;
            case 'v': ret[i] = V; break;
            case 'V': ret[i] = V; break;
            case 'w': ret[i] = W; break;
            case 'W': ret[i] = W; break;
            case 'x': ret[i] = X; break;
            case 'X': ret[i] = X; break;
            case 'y': ret[i] = Y; break;
            case 'Y': ret[i] = Y; break;
            case 'z': ret[i] = Z; break;
            case 'Z': ret[i] = Z; break;
		}
	}
	return ret;
}