#include <iostream>
#include "WordLib.h"
#include "Artical.h"
using namespace std;

int main(){
    Artical sampleText("./res/textSample.txt");
    Artical resText("./res/textResult.txt");
    WordLib myLib(2,1);
    myLib.UpdateLib(sampleText);
    resText.expand(myLib,200);
    resText.generateFile();
    return 0;
}