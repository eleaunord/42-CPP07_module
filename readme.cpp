## Exercise 00: Start with a few functions

Function templates : generic functions that work with any data type. Defined in header files because must be available at compile time. 
Instead of writing separate functions for each type we define a template that the compiler can use to generate the necessary code. 

Safety : ensures both arguments are of the same type. 

template < typename T>
T max(T &x, T &y) // prendre par référence pour pas faire une copie de la classe et pas perdre en mémoire
{
  return (x >= y ? x : y);
}

Instancation explicit vs instancation implicit
Instancation explicit : appeler le fonction et mettre entre < > le type sur lequel on souhaite instancier notre template puis entre () les vraiables.
Mais pas de précision sur quel est le type de chaque variable.
Instancation implicit : on peut directement mettre le nom du template suivit entre () des variables sans préciser le type qui est évident dans ce cas ci (exemple max, min).

Fonctions templates, classes et structure templates. 

template < typename T > // peut être utiliser ensuite à la place du type effectif dans ma classe

class List // donne structure de classe qui 
  {
  public :
    List <T>(T const & content) {...} // constructeur qui prend une ref sur un élément cte (le contenue) à partir de laquelle on va pouvoir créer notre liste, le type T sera remplacer par le type effectif et deviendra excatement ce qu'il nous faut à l'instanciation de notre template
    List <T>(List <T> const & list) {...}
    ~List <T>(void) {...}
    ...
  private :
    T* _content; // T* comme type sur grosse structure mais peut etre enlever
    List<T> _next;
};

template de classe fonctionne comme template de fonction => pas de définition de classe mais de template de classe donc peut l'utiliser pour l'instancier qui donnera ensuite des classes spécialisés pour entiers/char/grosses structures/classes

Liste à deux dimensions possible : List < List <int> > c(a);

Possible de passer plusieurs paramètres de type : template < typename T, typename U> et à l'utilisation : List<int, float>

## Exercise 01: Iter

Default template : si pas de type définit sur une template, juste mettre template < typename T = float > pour considérer float comme le type de la template par default
Vertex<int> v2(12, 23, 23); // on précise
Vertex<> v2(12, 23, 23); // appelle du type par défault
mais on a qd passer des entiers alors que float est le type par default qu'est ce qui se passe ? la classe est instancier par un float donc conversion implicit va être faite et les entiers seront convertis en float

surchage operateur chevrons gauche surcher avec classe template

Specialization partielle
On spécifie entre <> les différents types que l'on va utiliser dans notre classe
template < typename U >
class Pair < int, U > {
  public : 
    Pair < int, U> (int lhs, U const & rhs) : _lhs(lhs), _rhs(rhs){...} // spécialization partiel sur les entiers
    ~Pair < int, U>(void) {}
      int fst(void) const {...};
      U const & scnd(void) const {...};
...
  }

Specialization complète
Les deux param de type sont specialisés aka dans tout les autre cas utilise le template générique mais si et seulement si les types que tu me donnes sont les suivants, alors utilise cette version du code.
template <> // puisque j'ai spécialisé chaque var de type, il n'y en a plus dans la liste
class Pair < bool, bool > {
  public : 
    Pair < bool, bool > (bool lhs, bool & rhs) : _lhs(lhs), _rhs(rhs){
      this->_n = 0;
      this->_n = static_cast<int>(lhs) << 0;
      this->_n = static_cast<int>(rhs) << 0;
      return ;
    } // spécialization complète
    ~Pair  < bool, bool > (void) {}
      int fst(void) const {...};
      U const & scnd(void) const {...};
...
  }

template <typename T, typename U>
std::ostream & operator << (std::ostream & o, Pair < T, U> const & p)
{
o << "Pair(" << p.fst() << " , " << p.snd() << " )";
return o;
}
std::ostream & operator << (std::ostream & o, Pair < bool, bool> const & p)
{
o << std::boolalpha << "Pair(" << p.fst() << " , " << p.snd() << " )";
return o;
}

Permets de gagner de la place en mémoire si on sait qu'on va utiliser des bool!




