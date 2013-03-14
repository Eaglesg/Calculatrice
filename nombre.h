#ifndef __NOMBRE_H__
#define __NOMBRE_H__

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class nombre
{
private:
  int i_precision;
	char c_signe;
	std::vector<char> v_entiere;
	std::vector<char> v_decimale;
public:
	nombre();					// precision = 100
	nombre(int in_i_precision);			// precision = in_i_precision
	nombre(char *C_nombre);				// precision = 100 et ne saisi pas au-delà
	nombre(int in_i_precision, char *C_nombre);	// precision = in_i_precision et ne saisi pas au-delà

	void to_vectorChar(vector <char>&v);		// convertit un nombre en vector <char>
	void of_vectorChar(vector <char>&v);		// convertit un vector <char> en nombre

	void precision(int in_i_precision);		// in_i_precision devient la nouvelle precision
	int  precision();				// retourne la precision
	void nettoyer();				// supprime les zéros inutils

	void afficher(std::ostream &flux);		// n'affiche pas la precision explicitement
	void saisir(std::istream &flux);		// ne saisis pas la precision

	void operator= (nombre n_source);		// copie avec la precision de n_source : nombre n_2=n_1; marche
	void operator= (int i_nb);			// nombre n=i; avec i un entier, ne marche pas
	nombre& operator+= (nombre n_b);
	nombre& operator-= (nombre n_a);
	nombre& operator*= (nombre n_a);
	nombre& operator/= (nombre n_a);
	nombre& operator%= (nombre n_a);


/*		opérateurs de comparaison		*/
	bool operator== (nombre &n_a);
	bool operator!= (nombre &n_a);
	bool operator<  (nombre &n_a);
	bool operator<= (nombre &n_a);
	bool operator>  (nombre &n_a);
	bool operator>= (nombre &n_a);
	bool operator== (int i_nb);
	bool operator!= (int i_nb);
	bool operator<  (int i_nb);
	bool operator<= (int i_nb);
	bool operator>= (int i_nb);
	bool operator>  (int i_nb);
};

ostream &operator<< (ostream &flux, nombre &n_a);
istream &operator>> (istream &flux, nombre &n_a);

nombre operator+ (nombre &n_a, nombre &n_b);
nombre operator- (nombre &n_a, nombre &n_b);
nombre operator* (nombre &n_a, nombre &n_b);
nombre operator/ (nombre &n_a, nombre &n_b);
nombre operator% (nombre &n_a, nombre &n_b);


#endif
