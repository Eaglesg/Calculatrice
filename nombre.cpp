
#include "nombre.h"

/**
* \fn nombre::nombre()
* \brief Constructeur par defaut de la classe nombre
*
* construit un nombre 'vide' de valeur 0,
* avec une precision maximale de 100 chiffres sur les decimale.
*/
nombre::nombre()
{
  i_precision=100;
	c_signe=0;
	v_entiere.clear();
	v_decimale.clear();
}

/**
* \fn nombre::nombre(int in_i_precision)
* \brief Constructeur de la classe nombre
* \param in_i_precision entier designant le nombre maximale de chiffre apres la vigule, si il est negatif il est compte comme 0.
*
* construit un nombre 'vide' de valeur 0,
* avec une precision maximale de 100 chiffres sur les decimale.
*/
nombre::nombre(int in_i_precision)
{
	i_precision=in_i_precision;
	if(i_precision<0)
		i_precision = 0;
	c_signe=0;
	v_entiere.clear();
	v_decimale.clear();
}
/**
* \fn nombre::nombre(char *C_nombre)
* \brief constructeur de la classe nombre
* \param C_nombre nomnbre, sur forme d'une chaine de caracteres, a stocker dans le nombre construit
*
*/
nombre::nombre(char *C_nombre)
{
	i_precision=100;
	if( C_nombre == 0 )
	{
		c_signe=0;
		v_entiere.clear();
		v_decimale.clear();
		return;
	}
	int i=0;
	c_signe = C_nombre[i];
	for(i=1; C_nombre[i]>='0' && C_nombre[i]<='9'; i++) {}

	const int i_virgule = i;
	v_entiere.resize(i_virgule-1);
	int j=0;
	i--;
	while( i>0 )
	{
		v_entiere[j] = C_nombre[i] -'0';
		j++;
		i--;
	}
	j=0;
	for(i=i_virgule+1; C_nombre[i]>='0' && C_nombre[i]<='9' && j<i_precision; i++) { j++; }
	v_decimale.resize(j);
	j=0;
	for(i=i_virgule+1; C_nombre[i]>='0' && C_nombre[i]<='9' && j<i_precision; i++)
	{
		v_decimale[j] = C_nombre[i] -'0';
		j++;
	}
}
/**
* \fn nombre::nombre(int in_i_precision, char *C_nombre)
* \brief constructeur de la classe nombre
* \param in_i_precision entier designant le nombre maximale de chiffre apres la vigule, si il est negatif il est compte comme 0
* \param C_nombre nomnbre, sur forme d'une chaine de caracteres, a stocker dans le nombre construit
*
*/
nombre::nombre(int in_i_precision, char *C_nombre)
{
	i_precision=in_i_precision;
	if(i_precision<0)
		i_precision = 0;
	if( C_nombre == 0 )
	{
		c_signe=0;
		v_entiere.clear();
		v_decimale.clear();
		return;
	}
	int i=0;
	c_signe = C_nombre[i];
	for(i=1; C_nombre[i]>='0' && C_nombre[i]<='9'; i++) {}

	const int i_virgule = i;
	v_entiere.resize(i_virgule-1);
	int j=0;
	i--;
	while( i>0 )
	{
		v_entiere[j] = C_nombre[i] -'0';
		j++;
		i--;
	}
	j=0;
	for(i=i_virgule+1; C_nombre[i]>='0' && C_nombre[i]<='9' && j<i_precision; i++) { j++; }
	v_decimale.resize(j);
	j=0;
	for(i=i_virgule+1; C_nombre[i]>='0' && C_nombre[i]<='9' && j<i_precision; i++)
	{
		v_decimale[j] = C_nombre[i] -'0';
		j++;
	}
}
//***************************************************************/
/*								*/
/*			FIN CONSTRUCTEURS			*/
/*								*/
//***************************************************************/

//***************************************************************/
/*  							*/
/*		DEBUT DES FONCTIONS DE CONVERSION		*/
/*		nombrchainee <-> vector<char>			 	*/
/*								*/
//***************************************************************/

/**
* \fn void nombre::of_vectorChar(vector <char>&v)
* \brief transforme un vector<char> en un nombre
* \param v chaine de caractere a stocker dans le nombre qui appel la fonction
*
* Le vactor v, pris par reference, contient un nombre sous forme d'une chaine de caractere, ou chaque caractere contient le code aski du chiffre ou du signe correspondant.
* Lorsqu'il n'y a pas de signe, le nombre est considere comme positif.
* Les zeros inutils ne sont pas pris en compte.
* Les separateurs entre la partie entiere et la partie decimale sont ',' ou '.', il peut ne pas y en avoir.
*/
void nombre::of_vectorChar(vector <char>&v)
{

	const int size_limite=v.size();
	int it=0;

	if(v[it] > '9' || v[it] < '0')
	{
		c_signe = v[it];
		it++;
	}
	else
		c_signe = '+';
	int size=0;
	for(int i=it; v[i] <= '9' && v[i] >= '0'; i++)
		size++;

	v_entiere.resize(size);
	for(int i=size-1; i>=0; i--)
	{
		v_entiere[i] = v[it] - '0';
		it++;
	}

	if(v[it] != ',' && v[it] != '.')
		return;
	it++;

	size = size_limite - it;
	v_decimale.resize(size);
	for(int i=0; i<size && it <size_limite; i++)
	{
		v_decimale[i] = v[it] - '0';
		it++;
	}
	nombre::nettoyer();
}

/**
* \fn void nombre::to_vectorChar(vector <char>&v)
* \brief stock  le nombre dans le vector <char>
* \param v vector<char> qui recevra le nombre qui appel la fonction
*
* Le vactor v, pris par reference, recevra le nombre sous forme d'une chaine de caractere, ou chaque caractere contient le code aski du chiffre ou du signe correspondant.
* Lorsque le nombre est positif, aucun signe ne sera stcke dans le vector.
* Les zeros inutils ne sont pas pris en compte.
* Le separateur entre la partie entiere et la partie decimale est ',', s'il y en a besion.
*/
void nombre::to_vectorChar(vector <char>&v)
{
	nombre::nettoyer();
	int size = v_entiere.size() + v_decimale.size();
	unsigned int it=0;
	if(v_entiere.size()==0)
		size++;
	if(v_decimale.size()!=0)
		size++;
	if(c_signe == '-')
	{
		v.resize(size+1);
		v[it] = '-';
		it++;
	}
	else
	{
		v.resize(size);
	}
	if(v_entiere.size()==0)
	{
		v[it] = '0';
		it++;
	}
	else
	{
		for(int i=v_entiere.size()-1; i>=0; i--)
		{
			v[it] = v_entiere[i] + '0';
			it++;
		}
	}
	const int size_decimale = v_decimale.size();
	if(size_decimale == 0)
		return;
	v[it] = ',';
	it++;
	for(int i=0; i<=size_decimale; i++)
	{
		v[it] = v_decimale[i] + '0';
		it++;
	}
}


//***************************************************************/
/*								*/
/*		FIN DES FONCTIONS DE CONVERSION			*/
/*		nombre <-> vector<char>			 	*/
/*								*/
//***************************************************************/

/**
* \fn void nombre::precision(int in_i_precision)
* \brief modifi le nombre maximal de chiffre significatif de la partie decimale
* \param in_i_precision l'entier qui deviendra la nouvelle precision
*/
void nombre::precision(int in_i_precision)
{
  i_precision = in_i_precision;
	if(i_precisool 	operator<= (nombre &n_a)ion<0)
		i_precision = 0;
}

/**
* \fn int nombre::precision()
* \brief permet de connaitre le nombre maximal de chiffre significatif de la partie decimale
* \return retourne le nombre maximal de chiffre significatif de la partie decimale
*/
int nombre::precision()
{
	return i_precision;
}

/**
* \fn void nombre::nettoyer()
* \brief supprime les zeros inutils
*/
void nombre::nettoyer()
{
	while(v_entiere.size()!=0)
	{
		if(v_entiere.back()!=0)
			break;
		v_entiere.pop_back();
	}
	while(v_decimale.size()!=0)
	{
		if(v_decimale.back()!=0)
			break;
		v_decimale.pop_back();
	}
}
//***************************************************************************************/
//***************************************************************************************/
/*											*/
/*			DEBUT DE LA SURCHARGE DES OPERATEURS				*/
/*											*/
//***************************************************************************************/




//***************************************************************/
/*								*/
/*	DEBUT DE LA SURCHARGE DES OPERATEURS DE FLUX		*/
/*								*/
//***************************************************************/

/**
* \fn void nombre::afficher(std::ostream &flux)
* \brief ecrit le nombre via le flux
* \param flux avec lequel sera ecrit le nombre
*
* Si le signe est negatif, il sera ecrit, sinon non.
* S'il n'y a pas de partie decimale, il ne sera pas ecrit ',0' a la fin.
* La precision ne sera pas ecrite.
*/
void nombre::afficher(std::ostream &flux)
{
	nombre::nettoyer();
	if(c_signe=='-')
		flux << '-';
	int i_size=v_entiere.size();
	if(i_size == 0)
		flux << "0";
	else
		for(int i=i_size-1; i>=0; i--)
		{
			flux << v_entiere[i]+'0'-48;
		}
	i_size=v_decimale.size();
	if(i_size == 0)
		return;
	flux << ",";
	for(int i=0; i < i_size; i++)
	{
		flux << v_decimale[i]+'0'-48;
	}
}
/**
* \fn ostream &operator<< (ostream &flux, nombre &n_a)
* \brief surcharge de l'operateur de flux d'ecriture <<
* \param le flux d'ecriture par reference et le nombre a ecrire par refernce
* \return la flux modifie par reference
*/
ostream &operator<< (ostream &flux, nombre &n_a)
{
	n_a.afficher(flux);
	return flux;
}

/**
* \fn void nombre::saisir(std::istream &flux)
* \brief lit le nombre via le flux
* \param flux avec lequel sera lu le nombre
*
* Si il n'y a pas de signe, il sera considere comme positif.
* Si il n'y a pas de ',' ou de '.', la partie decimale sera vide.
* La precision n'est pas lue.
* les zeros inutils sont supprimes
*/
void nombre::saisir(std::istream &flux)			/* saisir une chane de char et la convertir en nombre */
{
	string str_buffer;
	flux >> str_buffer;

	bool pasDeSigne=false;
	if(str_buffer[0]!='+' && str_buffer[0]!='-')
	{
		string str_tmp=str_buffer;
		str_buffer = '+';
		str_buffer += str_tmp;
		pasDeSigne=true;
	}
	int i=0;
	c_signe = str_buffer[i];
	for(i=1; str_buffer[i]>='0' && str_buffer[i]<='9'; i++) {}

	const int i_virgule = i;
	v_entiere.resize(i_virgule-1);
	int j=0;
	i--;
	int endWhile=0;
	if(pasDeSigne)
		endWhile=-1;
	while( i>endWhile )
	{
		v_entiere[j] = str_buffer[i] -'0';
		j++;
		i--;
	}

	if(str_buffer[i_virgule] != ',' && str_buffer[i_virgule] != '.')
	{
		v_decimale.clear();
		return;
	}
	j=0;
	for(i=i_virgule+1; str_buffer[i]>='0' && str_buffer[i]<='9' && j<i_precision; i++) { j++; }
	v_decimale.resize(j);
	j=0;
	for(i=i_virgule+1; str_buffer[i]>='0' && str_buffer[i]<='9' && j<i_precision; i++)
	{
		v_decimale[j] = str_buffer[i] -'0';
		j++;
	}
	nombre::nettoyer();
}
/**
* \fn istream &operator>> (istream &flux, nombre &n_a)
* \brief surcharge de l'operateur de flux de lecture >>
* \param le flux de lecture par reference et le nombre a lire par refernce
* \return la flux modifie par reference
*
* les zeros inutils sont supprimes
*/
istream &operator>> (istream &flux, nombre &n_a)
{
	n_a.saisir(flux);
	return flux;
}
//***************************************************************/
/*								*/
/*	FIN DE LA SURCHARGE DES OPERATEURS DE FLUX		*/
/*								*/
//***************************************************************/





//***************************************************************/
/*        							*/
/*	DEBUT DE LA SURCHARGE DES OPERATEURS D'AFFECTATION	*/
/*								*/
//***************************************************************/

/**
* \fn void nombre::operator= (nombre n_a)
* \brief copie un nombre en parametre dans le nombre que appel la fonction
* \param un nombre a copier
*
* copie la precision sur les decimale, le signe, les parties entiere et decimale.
*/
void nombre::operator= (nombre n_a)
{
	i_precision = n_a.i_precision;
	c_signe = n_a.c_signe;
	v_entiere = n_a.v_entiere;
	v_decimale = n_a.v_decimale;
}
/**
* \fn void nombre::operator= (int i_nb)
* \brief copie et converti un entier dans un nombre
* \param entier a stocker dans le nombre qui appel la fonction
*
* la precision sur les decimale est inchange
*/
void nombre::operator= (int i_nb)
{
	c_signe='+';
	if(i_nb<0)
	{
		c_signe='-';
		i_nb*=-1;
	}
	v_entiere.resize(10);
	for(int i=0; i<10; i++)
	{
		v_entiere[i] = i_nb%10;
		i_nb/=10;
	}
	v_decimale.clear();
	nombre::nettoyer();
}
//***************************************************************/
/*								*/
/*	FIN DE LA SURCHARGE DES OPERATEURS D'AFFECTATION	*/
/*								*/
//***************************************************************/




//***************************************************************/
/*								*/
/*	DEBUT DE LA SURCHARGE DES OPERATEURS DE CALCUL		*/
/*								*/
//***************************************************************/

//******************* DEBUT OPERATEUR + *************************/
nombre operator+(nombre & n_a, nombre & n_b)
{
	nombre copie;
	copie = n_a;
    	copie += n_b;
    	return copie;
}

nombre& nombre::operator+= (nombre  n_b)
{
	nombre::nettoyer();
	n_b.nettoyer();

	int a, b, i, retenue;
	if(c_signe!=n_b.c_signe)
	{
		if(c_signe == '+')
		{
			n_b.c_signe = '+';
			nombre::operator -= (n_b);
		}
		else
		{
			c_signe = '+';
			nombre buffer;
			buffer.i_precision = i_precision;
			buffer.c_signe = c_signe;
			buffer.v_entiere = v_entiere;
			buffer.v_decimale = v_decimale;
			(n_b) -= buffer;
			nombre::operator = (n_b);
		}
	}
	else
	{
		a = v_decimale.size(); b = n_b.v_decimale.size();
		i = b;
		if (b>a)
			v_decimale.resize(b);
		retenue = 0;
		for(i=b-1;i>=0;i--)
		{
			retenue = v_decimale[i] + n_b.v_decimale[i] + retenue;
			v_decimale[i] = retenue % 10;
			retenue /= 10;
		}
		a = v_entiere.size(); b = n_b.v_entiere.size();
		if (b>a)
			v_entiere.resize(b);
		for(i=0;i<b;i++)
		{
			retenue = v_entiere[i] + n_b.v_entiere[i] + retenue;
			v_entiere[i] = retenue % 10;
			retenue /= 10;
		}
		if(retenue != 0 && (v_entiere.size() <= i))
			v_entiere.push_back(retenue);
		else
			v_entiere[i] += retenue;
	}
	return *this;
}
//******************** FIN OPERATEUR + **************************/
/*								*/
//******************* DEBUT OPERATEUR - *************************/
nombre operator-(nombre & n_a, nombre & n_b)
{
	nombre copie;
	copie = n_a;
    	copie -= n_b;
    	return copie;
}

nombre& nombre::operator-= (nombre  n_b)
{
	nombre::nettoyer();
	n_b.nettoyer();

	int a, b, i, retenue;
	a = v_decimale.size(); b = n_b.v_decimale.size();
	i = b;
	if(c_signe!=n_b.c_signe)
	{
		if(c_signe == '+')
		{
			n_b.c_signe = '+';
			nombre::operator += (n_b);
		}
		else
		{
			n_b.c_signe = '-';
			nombre::operator += (n_b);
		}
	}
	else
	{
		if((nombre::operator>= (n_b) && (c_signe == '+')) or (nombre::operator<= (n_b) && (c_signe == '-')))
		{
			if (b>a)
				v_decimale.resize(b);
			retenue = 0;
			for(i=b-1;i>=0;i--)
			{
				retenue = 10 + v_decimale[i] - n_b.v_decimale[i] - retenue;
				v_decimale[i] = retenue % 10;
				retenue /= 10;
				if (retenue == 1)
					retenue = 0;
				else
					retenue = 1;
			}
			a = v_entiere.size(); b = n_b.v_entiere.size();
			if (b>a)
				v_entiere.resize(b);
			for(i=0;i<b;i++)
			{
				retenue = 10 + v_entiere[i] - n_b.v_entiere[i] - retenue;
				v_entiere[i] = retenue % 10;
				retenue /= 10;
				if (retenue == 1)
					retenue = 0;
				else
					retenue = 1;
			}
			if (retenue == 1)
				v_entiere[i]--;
		}
		else
		{
			nombre buffer;
			buffer.i_precision = i_precision;
			buffer.c_signe = c_signe;
			buffer.v_entiere = v_entiere;
			buffer.v_decimale = v_decimale;
			(n_b) -= buffer;
			nombre::operator = (n_b);
			if (c_signe == '+')
				c_signe = '-';
			else
				c_signe = '+';
		}
	}
	return *this;
}
//******************** FIN OPERATEUR - **************************/
/*								*/
//******************* DEBUT OPERATEUR * *************************/
nombre operator*(nombre & n_a, nombre & n_b)
{
	nombre copie;
	copie = n_a;
    	copie *= n_b;
    	return copie;
}

nombre& nombre::operator*= (nombre n_b)
{
	int a, b, c, d, i, j, retenue;
	nombre n_retenue, n_resultat;

	a = v_decimale.size(); b = n_b.v_decimale.size();
	c = v_entiere.size(); d = n_b.v_entiere.size();

	n_resultat = 0;

	for(i=a-1;i>=0;i--)
	{
		retenue = 0;
		n_retenue = 0;
		n_retenue.v_decimale.resize(i+b+1);
		if ((d-i) > 0)
			n_retenue.v_entiere.resize(d-i);
		else
			n_retenue.v_entiere.resize(0);
		for(j=b-1;j>=0;j--)
		{
			retenue = v_decimale[i] * n_b.v_decimale[j] + retenue;
			n_retenue.v_decimale[i+j+1] = retenue % 10;
			retenue /= 10;
		}
		for(j=0;j<d;j++)
		{
			retenue = v_decimale[i] * n_b.v_entiere[j] + retenue;
			if (i-j >=0)
			{
				n_retenue.v_decimale[i-j] = retenue % 10;
				retenue /= 10;
			}
			else
			{
				n_retenue.v_entiere[j-i-1] = retenue % 10;
				retenue /= 10;
			}
		}
		if (i-j >=0)
			n_retenue.v_decimale[i-j] = retenue;
		else
			n_retenue.v_entiere[j-i-1] = retenue;
		n_resultat += n_retenue;
	}
	for(i=0;i<c;i++)
	{
		retenue = 0;
		n_retenue = 0;
		n_retenue.v_decimale.resize(c-i+b);
		n_retenue.v_entiere.resize(i+d+1);
		for(j=b-1;j>=0;j--)
		{
			retenue = v_entiere[i] * n_b.v_decimale[j] + retenue;
			if (j-i >=0)
			{
				n_retenue.v_decimale[j-i] = retenue % 10;
				retenue /= 10;
			}
			else
			{
				n_retenue.v_entiere[i-j-1] = retenue % 10;
				retenue /= 10;
			}
		}
		for(j=0;j<d;j++)
		{
			retenue = v_entiere[i] * n_b.v_entiere[j] + retenue;
			n_retenue.v_entiere[i+j] = retenue % 10;
			retenue /= 10;
		}
		n_retenue.v_entiere[i+j] = retenue;
		n_resultat += n_retenue;
	}
	if(c_signe==n_b.c_signe)
		n_resultat.c_signe='+';
	else
		n_resultat.c_signe='-';
	nombre::operator = (n_resultat);
	return *this;
}
//******************** FIN OPERATEUR * **************************/
/*								*/
//******************* DEBUT OPERATEUR / *************************/
nombre operator/(nombre & n_a, nombre & n_b)
{
        nombre copie;
	copie = n_a;
    	copie /= n_b;
    	return copie;
}

nombre& nombre::operator/= (nombre n_b)
{
	int i;
	nombre n_resultat, dix, zero;
	dix = 10;
	zero = 0;

	n_resultat = 0;
	i = 0;
	if(c_signe==n_b.c_signe)
		n_resultat.c_signe='+';
	else
		n_resultat.c_signe='-';

	c_signe = '+';
	n_b.c_signe = '+';

	while (nombre::operator >= (n_b))
	{
		i++;
		n_b*=dix;
	}
	nombre::operator*=(dix);
	i--;
	if(i>=0)
		n_resultat.v_entiere.resize(i+1);
	while (i>=0)
	{
		while (nombre::operator >= (n_b))
		{
			nombre::operator -= (n_b);
			n_resultat.v_entiere[i]++;
		}
		nombre::operator*=(dix);
		i--;
	}
	i = 0;
	while (i<i_precision & nombre::operator != (zero))
	{
		n_resultat.v_decimale.push_back(0);
		while (nombre::operator >= (n_b))
		{
			nombre::operator -= (n_b);
			n_resultat.v_decimale[i]++;
		}
		nombre::operator*=(dix);
		i++;
	}
	nombre::operator = (n_resultat);

	return *this;
}

//******************** FIN OPERATEUR / **************************/
/*								*/
//******************* DEBUT OPERATEUR % *************************/
nombre operator%(nombre &n_a, nombre &n_b)
{
	nombre copie;
	copie = n_a;
    	copie %= n_b;
    	return copie;
}

nombre& nombre::operator%= (nombre n_b)
{
	int i;
	nombre n_resultat, dix, zero;
	dix = 10;
	zero = 0;

	i = 0;

	n_b.c_signe = '+';
	if (c_signe == '-')
	{
		c_signe = '+';
		while (nombre::operator >= (n_b))
		{
			i++;
			n_b*=dix;
		}
		n_b/=dix;
		i--;
		while (i>=0)
		{
			while (nombre::operator >= (n_b))
			{
				nombre::operator -= (n_b);
			}
			n_b/=(dix);
			i--;
		}
		c_signe = '-';
	}
	else
	{
		while (nombre::operator >= (n_b))
		{
			i++;
			n_b*=dix;
		}
		n_b/=dix;
		i--;
		while (i>=0)
		{
			while (nombre::operator >= (n_b))
			{
				nombre::operator -= (n_b);
			}
			n_b/=(dix);
			i--;
		}
	}

	return *this;
}
//******************** FIN OPERATEUR % **************************/

//***************************************************************/
/*								*/
/*	FIN DE LA SURCHARGE DES OPERATEURS DE CALCUL		*/
/*								*/
//***************************************************************/





//***************************************************************/
/*        							*/
/*	DEBUT DE LA SURCHARGE DES OPERATEURS DE COMPARAISON	*/
/*								*/
//***************************************************************/

//*************** DEBUT OPERATEUR == ET != **********************/

/**
* \fn bool nombre::operator== (nombre &n_a)
* \brief verifi si 2 nombres sont egaux
* \return retourne true si ils sont egaux et false sinon
*
* les zeros inutils des 2 nombres sont supprimes au passage.
*/
bool nombre::operator== (nombre &n_a)
{
	nombre::nettoyer();
	n_a.nettoyer();

	if(n_a.c_signe != c_signe)
		return false;
	const int i_size_entiere = v_entiere.size();
	const int i_size_entiere_n_a = n_a.v_entiere.size();

	if(i_size_entiere != i_size_entiere_n_a)
		return false;

	for(int i=0;i<i_size_entiere;i++)
		if(v_entiere[i] != n_a.v_entiere[i])
			return false;

	const int i_size_decimale = v_decimale.size();
	const int i_size_decimale_n_a = n_a.v_decimale.size();

	if(i_size_decimale != i_size_decimale_n_a)
		return false;

	for(int i=0;i<i_size_decimale;i++)
		if(v_decimale[i] != n_a.v_decimale[i])
			return false;

	return true;
}
/**
* \fn bool nombre::operator!= (nombre &n_a)
* \brief verifi si 2 nombres sont different
* \return retourne true si il sont different et false sinon
*
* les zeros inutils des 2 nombres sont supprimes au passage.
*/
bool nombre::operator!= (nombre &n_a)
{
	if(nombre::operator==(n_a))
		return false;
	return true;
}
/**
* \fn bool nombre::operator== (int i_nb)
* \brief verifi si 1 nombre est egale a un entier
* \return retourne true si ils sont egaux et false sinon
*
* les zeros inutils du nombre sont supprimes au passage.
*/
bool nombre::operator== (int i_nb)
{
	nombre n_nb=i_nb;
	return nombre::operator== (n_nb);
}
/**
* \fn bool nombre::operator!= (int i_nb)
* \brief verifi si 1 nombre est different d'un entier
* \return retourne true si ils sont different et false sinon
*
* les zeros inutils du nombre sont supprimes au passage.
*/
bool nombre::operator!= (int i_nb)
{
	nombre n_nb=i_nb;
	return nombre::operator!= (n_nb);
}
//**************** FIN OPERATEUR == ET != ***********************/
/*								*/
//************* DEBUT OPERATEUR <, <=, > ET >= ******************/

/**
* \fn bool nombre::operator< (nombre &n_a)
* \brief verifi si le nombre qui appel la fonction est strictement inferieur a un autre
* \return retourne true si le nombre qui appel la fonction est strictement inferieur a un l'autre et false sinon
*
* les zeros inutils des 2 nombres sont supprimes au passage.
*/
bool nombre::operator< (nombre &n_a)
{
	nombre::nettoyer();
	n_a.nettoyer();

	if(c_signe=='-' && n_a.c_signe=='+') return true;
	if((c_signe=='+' && n_a.c_signe=='-') || nombre::operator==(n_a)) return false;

	bool positif=false;
	if(c_signe=='+') positif=true;

	const int i_size_entiere = v_entiere.size();
	const int i_size_entiere_n_a = n_a.v_entiere.size();
	if(i_size_entiere > i_size_entiere_n_a)
		return !positif;
	if(i_size_entiere < i_size_entiere_n_a)
		return positif;
	for(int i=i_size_entiere-1; i>=0; i--)
	{
		if(v_entiere[i] < n_a.v_entiere[i])
			return positif;
		else if(v_entiere[i] > n_a.v_entiere[i])
			return !positif;
	}

	const int i_size_decimale = v_decimale.size();
	const int i_size_decimale_n_a = n_a.v_decimale.size();
	int plus_petit;
	if(i_size_decimale_n_a < i_size_decimale)
		plus_petit = i_size_decimale_n_a;
	else
		plus_petit = i_size_decimale;
	for(int i=0; i<plus_petit; i++)
	{
		if(v_decimale[i] < n_a.v_decimale[i])
			return positif;
		else if(v_decimale[i] > n_a.v_decimale[i])
			return !positif;
	}
	return positif;
}
/**
* \fn bool nombre::operator>= (nombre &n_a)
* \brief verifi si le nombre qui appel la fonction est superieur ou egale a un autre
* \return retourne true si le nombre qui appel la fonction est superieur ou egale a un l'autre et false sinon
*
* les zeros inutils des 2 nombres sont supprimes au passage.
*/
bool nombre::operator>= (nombre &n_a)
{
	if(nombre::operator<(n_a))
		return false;
	return true;
}
/**
* \fn bool nombre::operator> (nombre &n_a)
* \brief verifi si le nombre qui appel la fonction est strictement superieur a un autre
* \return retourne true si le nombre qui appel la fonction est strictement superieur a un l'autre et false sinon
*
* les zeros inutils des 2 nombres sont supprimes au passage.
*/
bool nombre::operator> (nombre &n_a)
{
	if(nombre::operator<(n_a) || nombre::operator==(n_a))
		return false;
	return true;
}
/**
* \fn bool nombre::operator<= (nombre &n_a)
* \brief verifi si le nombre qui appel la fonction est inferieur ou egale a un autre
* \return retourne true si le nombre qui appel la fonction est inferieur ou egale a un l'autre et false sinon
*
* les zeros inutils des 2 nombres sont supprimes au passage.
*/
bool nombre::operator<= (nombre &n_a)
{
	if(nombre::operator<(n_a) || nombre::operator==(n_a))
		return true;
	return false;
}
/**
* \fn bool nombre::operator< (int i_nb)
* \brief verifi si le nombre qui appel la fonction est strictement inferieur a un entier
* \return retourne true si le nombre qui appel la fonction est strictement inferieur a un l'entier et false sinon
*
* les zeros inutils du nombre sont supprimes au passage.
*/
bool nombre::operator< (int i_nb)
{
	nombre n_nb=i_nb;
	return nombre::operator< (n_nb);
}
/**
* \fn bool nombre::operator<= (int i_nb)
* \brief verifi si le nombre qui appel la fonction est inferieur ou egale a un entier
* \return retourne true si le nombre qui appel la fonction est inferieur ou egale a un l'entier et false sinon
*
* les zeros inutils du nombre sont supprimes au passage.
*/
bool nombre::operator<= (int i_nb)
{
	nombre n_nb=i_nb;
	return nombre::operator<= (n_nb);
}
/**
* \fn bool nombre::operator>= (int i_nb)
* \brief verifi si le nombre qui appel la fonction est superieur ou egale a un entier
* \return retourne true si le nombre qui appel la fonction est superieur ou egale a un l'entier et false sinon
*
* les zeros inutils du nombre sont supprimes au passage.
*/
bool nombre::operator>= (int i_nb)
{
	nombre n_nb=i_nb;
	return nombre::operator>= (n_nb);
}
/**
* \fn bool nombre::operator> (int i_nb)
* \brief verifi si le nombre qui appel la fonction est strictement superieur a un entier
* \return retourne true si le nombre qui appel la fonction est strictement superieur a un l'entier et false sinon
*
* les zeros inutils du nombre sont supprimes au passage.
*/
bool nombre::operator> (int i_nb)
{
	nombre n_nb=i_nb;
	return nombre::operator> (n_nb);
}
//************** FIN OPERATEUR <, <=, > ET >= *******************/

//***************************************************************/
/*								*/
/*	FIN DE LA SURCHARGE DES OPERATEURS DE COMPARAISON	*/
/*								*/
//***************************************************************/





