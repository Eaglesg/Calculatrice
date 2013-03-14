#include <iostream>
#include <vector> 
typedef double integer;
class Expression
{
        private:
                std::vector<char> expressionMath;
        public:
                Expression();
                Expression(char *exp, unsigned int taille);
                ~Expression();
                integer calculExpr();
                void calculExpr(std::vector<char>::iterator i);
                integer calculSelec(std::vector<char>::iterator i, std::vector<char>::iterator j); 
                void afficher(); 
                integer vectorToInteger(std::vector<char> T);
                int remplacer(std::vector<char> &A, std::vector<char> &B, std::vector<char>::iterator &it, std::vector<char>::iterator &ot);    
                bool isNumber(char &l);
};
