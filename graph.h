#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <map>
#include <string>
#include <memory>

#include <iostream>
#include <stack>
#include "grman/grman.h"

/***************************************************
                    VERTEX
****************************************************/

class VertexInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Vertex;
    friend class EdgeInterface;
    friend class Graph;

    private :
        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        // La boite qui contient toute l'interface d'un sommet: boite totale de la widget
        grman::WidgetBox m_top_box;
        // Un slider de visualisation/modification de la valeur du sommet : jauge pour la valeur de la boite
        grman::WidgetVSlider m_slider_value;
        // Un label de visualisation de la valeur du sommet : nombre affiché en bas à gauche qui se modifie
        grman::WidgetText m_label_value;
        // Une image de "remplissage" : l'image de la widget
        grman::WidgetImage m_img;
        // Un label indiquant l'index du sommet : nombre affiché en bas à droite qui se bouge pas, le numéro du sommet
        grman::WidgetText m_label_idx;
        // Une boite pour le label pr�c�dent : boite avec le numéro du sommet dedans
        grman::WidgetText m_box_label_idx;

    public :
        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        VertexInterface(int idx, int x, int y, std::string pic_name="", int pic_idx=0);
};

class Vertex
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Graph;
    friend class VertexInterface;
    friend class Edge;
    friend class EdgeInterface;

    private :
        /// liste des indices des arcs arrivant au sommet : acc�s aux pr�d�cesseurs
        std::vector<int> m_in; // plusieurs fleche qui arrive
        /// liste des indices des arcs partant du sommet : acc�s aux successeurs
        std::vector<int> m_out; // plusieurs fleche qui parte
        /// un exemple de donn�e associ�e � l'arc, on peut en ajouter d'autres...
        double m_value; // poids

        int m_id; // identifiant
        int m_x,m_Y; //coordonnées
        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<VertexInterface> m_interface = nullptr;


    public :
        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Vertex (double _value=0,VertexInterface *interface=nullptr) :
            m_value(_value),m_interface(interface)  {  }

        /// Vertex �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        /// le pre_update et post_update de Vertex (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Graph::update dans le .cpp
        void pre_update();
        void post_update();
};

/***************************************************
                    EDGE
****************************************************/

class EdgeInterface
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Edge;
    friend class Graph;

    private :
        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        // Le WidgetEdge qui "contient" toute l'interface d'un arc
        grman::WidgetEdge m_top_edge;
        // Une boite pour englober les widgets de r�glage associ�s càd les jauges
        grman::WidgetBox m_box_edge;
        // Un slider de visualisation/modification du poids valeur de l'arc : jauge pour la valeur d'un arc
        grman::WidgetVSlider m_slider_weight;
        // Un label de visualisation du poids de l'arc : nombre affiché en dessous de la jauge
        grman::WidgetText m_label_weight;

    public :
        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        EdgeInterface(Vertex& from, Vertex& to);
};

class Edge
{
    // Les (methodes des) classes amies pourront acc�der
    // directement aux attributs (y compris priv�s)
    friend class Graph;
    friend class EdgeInterface;

    private :
        /// indice du sommet de d�part de l'arc
        int m_from;
        /// indice du sommet d'arriv�e de l'arc
        int m_to;
        /// un exemple de donn�e associ�e � l'arc, on peut en ajouter d'autres...
        double m_weight; //poids
        int m_i; // identifiant
        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<EdgeInterface> m_interface = nullptr;

    public :
        /// Les constructeurs sont � compl�ter selon vos besoin...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Edge (double weight=0, EdgeInterface *interface=nullptr) :
            m_weight(weight), m_interface(interface)  {  }
        /// Edge �tant g�r� par Graph ce sera la m�thode update de graph qui appellera
        /// le pre_update et post_update de Edge (pas directement la boucle de jeu)
        /// Voir l'impl�mentation Graph::update dans le .cpp
        void pre_update();
        void post_update();
};

/***************************************************
                    GRAPH
****************************************************/

class GraphInterface
{
    friend class Graph;

    private :
        /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
        /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
        /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

        /// La boite qui contient toute l'interface d'un graphe
        grman::WidgetBox m_top_box;
        /// Dans cette boite seront ajout�s les (interfaces des) sommets et des arcs...
        grman::WidgetBox m_main_box;
        /// Dans cette boite seront ajout�s des boutons de contr�le etc...
        grman::WidgetBox m_tool_box;
        // A compl�ter �ventuellement par des widgets de d�coration ou
        // d'�dition (boutons ajouter/enlever ...)

        grman::WidgetButton m_boutonAjout;
        grman::WidgetImage m_boutonAjout_image;
        grman::WidgetButton m_boutonSupp;
        grman::WidgetImage m_boutonSupp_image;
        grman::WidgetButton m_boutonCharger;
        grman::WidgetImage m_boutonCharger_image;
        grman::WidgetButton m_boutonSauvegarder;
        grman::WidgetImage m_boutonSauvegarder_image;
        grman::WidgetButton m_boutonQuitter;
        grman::WidgetImage m_boutonQuitter_image;
        grman::WidgetButton m_boutonAlgoChoix;
        grman::WidgetImage m_boutonAlgoChoix_image;
        grman::WidgetText m_algo;
        grman::WidgetText m_algo2_1;
        grman::WidgetText m_algo2_2;
        grman::WidgetText m_algo2_3;
        grman::WidgetText m_algo2_4;

    public :
        // Le constructeur met en place les �l�ments de l'interface
        // voir l'impl�mentation dans le .cpp
        GraphInterface(int x, int y, int w, int h);
};

class Graph
{

    public :
        /// La "liste" des ar�tes
        std::map<int, Edge> m_edges; //indice et arrete
        /// La liste des sommets
        std::map<int, Vertex> m_vertices;

        int m_ordre;
        int m_arete;

        /// le POINTEUR sur l'interface associ�e, nullptr -> pas d'interface
        std::shared_ptr<GraphInterface> m_interface = nullptr;

        /// Les constructeurs sont � compl�ter selon vos besoins...
        /// Ici on ne donne qu'un seul constructeur qui peut utiliser une interface
        Graph (GraphInterface *interface=nullptr) :
            m_interface(interface){  }

        void add_interfaced_vertex(int idx, double value, int x, int y, std::string pic_name="");
        void add_interfaced_edge(int idx, int vert1, int vert2, double weight=0);

        /// M�thode sp�ciale qui construit un graphe arbitraire (d�mo)
        /// Voir impl�mentation dans le .cpp
        /// Cette m�thode est � enlever et remplacer par un syst�me
        /// de chargement de fichiers par exemple.

        /// La m�thode update � appeler dans la boucle de jeu pour les graphes avec interface
        int update(int what);
        void make_example();
        void recuperation1();
        void recuperation2();
        void recuperation3();
        void sauvegarde1();
        void sauvegarde2();
        void sauvegarde3();
        void rajout1();
        void rajout2();
        void rajout3();
        void supprimer_edge(int edx);
        void supprimer_Sommet(int idx);
};

class Menu
{
    friend class Graph;

    public :
    /// Les widgets de l'interface. N'oubliez pas qu'il ne suffit pas de d�clarer
    /// ici un widget pour qu'il apparaisse, il faut aussi le mettre en place et
    /// le param�trer ( voir l'impl�mentation du constructeur dans le .cpp )

    /// La boite qui contient toute l'interface d'un graphe
    grman::WidgetBox m_top_box;
    /// Dans cette boite seront ajout�s les (interfaces des) sommets et des arcs...
    grman::WidgetBox m_main_box;
    /// Dans cette boite seront ajout�s des boutons de contr�le etc...
    grman::WidgetBox m_tool_box;


    grman::WidgetBox m_Menu;
    grman::WidgetImage m_Menu_image;
    grman::WidgetButton m_boutonReseau1;
    grman::WidgetButton m_boutonReseau2;
    grman::WidgetButton m_boutonReseau3;
    grman::WidgetButton m_boutonMenuQuitter;

      Menu();
      int update(Graph g);
};

#endif // GRAPH_H_INCLUDED
