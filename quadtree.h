// ADS101 Algoritmer og Datastrukturer for spill 2020
// Dag Nylund, Høgskolen i Innlandet
// Quadtre - noe er gjort om fra Rectangle eksempel
#ifndef QUADTRE_H
#define QUADTRE_H

#include <vector>
#include <string>
#include <list>

namespace gsml
{
    typedef std::pair<double, double> Point2D; // Erstatter Vector2D klasse

    // Dette er hovedklassen, med litt fra Rectangle og litt fra
    // binærtreklassen
    template <class ID, class T>
    class QuadTre
    {
    private:

        // Punkter som definerer hjørnene til objektet
        // i samme rekkefølge som pekerne til subtrær
        Point2D  m_a;
        Point2D  m_b;
        Point2D  m_c;
        Point2D  m_d;
        // Pekere til subtrær er nødvendig i en dynamisk
        // quadtre implementering. Vi kunne ha lagt det
        // i array også
        QuadTre* m_sv;
        QuadTre* m_so;
        QuadTre* m_no;
        QuadTre* m_nv;

        // Hvert quad lagrer sine egne objekter
        // (vi bør endre til pekere eller referanser)
        std::list<std::pair<ID,T>> m_objects;
        std::vector<T> m_all_objects; // skulle vært static

        bool isLeaf() const;

        // Hjelpefunksjon - preorder traversering av subtre
        void traverse_all(std::vector<T>& all_objects);

    public:
        QuadTre();
        QuadTre(const Point2D &v1, const Point2D &v2, const Point2D &v3, const Point2D & v4);
        void init(const Point2D &v1, const Point2D &v2, const Point2D &v3, const Point2D & v4);
        void subDivide(int n);
        void print() const;
        void print_all() const;

        QuadTre* insert(const Point2D& point, const ID& id, const T& object);
        QuadTre* find(const Point2D& p);
        const QuadTre* find(const Point2D& p) const;
        T& find(const ID& id);
        T& operator[] (ID id);

        typename std::vector<T>::iterator begin()
        {
            traverse_all(m_all_objects);
            return m_all_objects.begin();
        }
        typename std::vector<T>::iterator end()
        {
            return m_all_objects.end();
        }

        void testdata();
        void split(int n);
};

}

#endif // QUADTRE_H
