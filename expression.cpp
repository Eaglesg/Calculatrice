#include "expression.h"
typedef double integer;
Expression::Expression()
{
}

Expression::Expression(char *exp, unsigned int taille)
{
        for(unsigned int i = 0; i < taille; i++)
        {
                expressionMath.push_back(exp[i]);
        }
}
Expression::~Expression()
{

}

integer Expression::calculExpr()
{
        calculExpr(expressionMath.begin());
}

void Expression::afficher()
{
        for(std::vector<char>::iterator i = expressionMath.begin(); i != expressionMath.end(); i++)
        {
                std::cout << *i << ",";
        }
        std::cout << std::endl;
}

void Expression::calculExpr(std::vector<char>::iterator i)
{
        // - difference : Permet d'avoir une différence pour refoutre le pointeur au bon endroit
        integer i_resultat;
        std::vector<char> resultat;
        int difference = 0;
        for(std::vector<char>::iterator j = i; j != expressionMath.end(); j++)
        {
                if(*j == '(')
                {
                        std::cout << "(" << std::endl;
                        calculExpr(j+1);
                }
                else if(*j == ')')
                {
                        std::cout << ")" << std::endl;
                        // Alors on fait le calcul entre i et j
                        i_resultat = calculSelec(i, j);
                        // Transformation de i_resultat en vector dans resultat
                        // resultat = i_resultat.toVector();
                        difference = remplacer(expressionMath, resultat, i, j);
                        // Puis on recale au où il y ait une différence
                        return;
                }
        }
}

integer Expression::calculSelec(std::vector<char>::iterator i, std::vector<char>::iterator j)
{
        std::vector<char> v_number1, v_number2, v_resultat;
        bool b_calculating = true;
        integer i_resultat, i_number1, i_number2;
        for(std::vector<char>::iterator it = i; it != j; it++)
        {
                if(isNumber(*it)) // 0-9 et ,
                {
                        v_number1.push_back(*it);
                }
                else
                {
                        if(*it == '*' || *it == '/')
                        {
                                // On fait les calculs.
                                for(std::vector<char>::iterator it2 = it ++; it2 != j || b_calculating ; it2 ++)
                                {
                                        if(isNumber(*it))
                                                v_number2.push_back(*it2); // On crée le nombre2
                                        else
                                        {
                                                i_number1 = vectorToInteger(v_number1);
                                                i_number2 = vectorToInteger(v_number2);
                                                switch(*it)
                                                {
                                                        case '*':
                                                                i_resultat = i_number1 * i_number2;
                                                        break;
                                                        case '/':
                                                                i_resultat = i_number1 / i_number2;
                                                        break;
                                                }
                                                b_calculating = false;
                                        }
                                }
                        }
                        else
                                v_number1.clear(); // Ce n'était pas le bon nombre
                }

        }
 for(std::vector<char>::iterator it = expressionMath.begin(); it != expressionMath.end(); it++)
        {
                if(*it == '+')
                {
                        // De même 

                }
                else if(*it == '-')
                {
                         // De même

                }
        }
        return i_resultat;
}

int Expression::remplacer(std::vector<char> &A, std::vector<char> &B, std::vector<char>::iterator &it, std::vector<char>::iterator &ot)
{

        A.erase(it, ot);
        for(std::vector<char>::iterator i= B.begin(); i != B.end(); i++)
        {
                A.insert(it, *i);
                std::advance(it,1);
        }

}

bool Expression::isNumber(char &l)
{
        if((l >= 0 && l <= 9)||l==',')
                return true;
        return false;
}
