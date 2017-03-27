#include "iostream"
#include "stdio.h"
#define rows 2
#define columns 10
using namespace std;

//Structures declarations
struct letterOccurence{
  char letter;
  int occurene;
};

struct wordOccurence{
  char word[20];
  int occurence;
};






//Prototypes of the program functions
void enterText(char text[rows][columns]);
int ifCharNotRebeated(char, letterOccurence* , int);
void countAndDisplayLettersOccurence(char [][columns], letterOccurence*);
int ifWordNotRebeated(char [20], wordOccurence* , int);
void DisplayWordsOccurenceAndClassify(char [][columns], wordOccurence*);
int strCompare(const char* string1, const char* string2);
char cabitalize(char);


//Code:
void enterText(char text[rows][columns]) {// for entering the text
    cout << "enter the paragraph:\n";
    for(int i = 0; i < rows; i++){
        gets(text[i]);
    }
}

char cabitalize(char a){//for case sensitivity
    if (a > 'a' && a < 'z'){
        a -= 32;
    }
    return a;
}

int strCompare(const char* string1, const char* string2){// compares 2 strings, not case sensitive
    for (; (*string1) && (*string2) && (cabitalize(*(string1)) == cabitalize(*(string2))); string1++, string2++);
    if(*string1 == NULL && *string2 == NULL){
        return 0;
    }
    if(cabitalize(*(string1)) > cabitalize(*(string2))){
        return 1;
    }
    else{
        return -1;
    }
}

int ifCharNotRebeated(char character, letterOccurence* occurences, int size) {//for checking if the character is rebeated or not
    for(int i = 0; i < size; i++) {
        if (occurences[i].letter == character) {
            return 0;
        }
    }
    return 1;
}



void countAndDisplayLettersOccurence(char text[][columns], letterOccurence* occurences) {
    int counter = 0, rLoc = 0, cLoc = 0, letters = 0;
    for(; rLoc < rows; rLoc++){// to calculate each letter occurence
        for(; cLoc < columns; cLoc++){
            if(ifCharNotRebeated(text[rLoc][cLoc], occurences, letters)){
                for(int i = 0; i < rows; i++){
                    for(int j = 0; j < columns; j++){
                        if(text[rLoc][cLoc] == text[i][j]){
                            counter++;
                        }
                    }
                }
                occurences[letters].letter = text[rLoc][cLoc];
                occurences[letters].occurene = counter;
                cout << letters + 1 << "-'" << occurences[letters].letter << "' occured: " << occurences[letters].occurene << " times\n";
                counter = 0;
                letters++;
            }
        }
    }
}

int ifWordNotRebeated(char word[20], wordOccurence* w_occurences2, int words) {
    for(int i = 0; i < words; i++){ //to check word occurence
        if (!strCompare(w_occurences2[i].word, word)){
            return 0;
        }
    }
    return 1;
}

void DisplayWordsOccurenceAndClassify(char text[][columns], wordOccurence* w_occurences) {
  //Words occurence:
    int words = 0, s = 0, n = 0, j, start;
    int oneLetterW = 0, twoLetterW = 0, threeLetterW = 0;
    for(int i = 0; i < rows; i++) {
        start = 0;
        for(j = 0; j < columns; j++) {
            if ((j != columns - 1 && text[i][j] == ' ') && (text[i][j + 1] != ' ')) {
                for(int k = start; k < j; k++, n++) {
                    w_occurences[words].word[n] = text[i][k];
                }
                start = j + 1;
                n = 0;
                words++;
            }
        }
        for(int k = start; k < columns; k++, n++) {
            w_occurences[words].word[n] = text[i][k];
        }
        n = 0;
        words++;
    }
    cout << "\n********************\n";
    wordOccurence* w_occurences2 = new wordOccurence[50];
    for(int i = 0; i < words; i++){
        if(ifWordNotRebeated(w_occurences[i].word, w_occurences2, s + 1)) {
            w_occurences2[s] = w_occurences[i];
            for(int f = 0; f < words; f++){
                if(!strCompare(w_occurences2[s].word, w_occurences[f].word)) {
                    w_occurences2[s].occurence++;
                }
            }
            cout << s + 1 << "-\"" << w_occurences2[s].word << "\": " << w_occurences2[s].occurence << "\n";
            s++;
        }
    }
    cout << "\n*********************************\n";
  //Classifying: into: 1-letter word, 2-letters  word, 3-letters word..etc
    for(int p = 0; p < s; p++){
      if(strlen(w_occurences2[p].word) == 1){
        oneLetterW +=  w_occurences2[p].occurence;
      }
      if(strlen(w_occurences2[p].word) == 2){
        twoLetterW +=  w_occurences2[p].occurence;
      }
      if(strlen(w_occurences2[p].word) == 3){
        threeLetterW +=  w_occurences2[p].occurence;
      }
    }
    cout << "Number of:\n"
         <<  "One-letter words: " << oneLetterW << "\n"
         << "Two-letters words: " << twoLetterW << "\n"
          << "Three-letters words: " << threeLetterW << "\n";

}

int main() {
    char text[rows][columns];
    enterText(text);
    cout << "\n";
    letterOccurence* occurences = new letterOccurence [50];
    wordOccurence* w_occurences = new wordOccurence [50];
    countAndDisplayLettersOccurence(text, occurences);
    DisplayWordsOccurenceAndClassify(text, w_occurences);
    return 0;
}
