#include "portugol.cpp"

int main()
{
    int currentState = 1;
    int lastFinalState;
    int currentFinalIndex;
    string input;
    char simbolo;

    while(cin.get(simbolo))
    {
        input += simbolo;
    }
    
    input += '\0';

    Automaton automato(1);
    automato.Analyze(input);
    
    return 0;
}