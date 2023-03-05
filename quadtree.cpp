// ADS101 Algoritmer og Datastrukturer for spill 2020
// Dag Nylund, Høgskolen i Innlandet
// Gjort om fra PlainRectangle
#include "quadtree.h"
#include <iostream>

namespace gsml
{

//std::vector<QuadTre> QuadTre::m_rectangles;
template <class ID, class T>
QuadTre<ID,T>::QuadTre(const Point2D &v1, const Point2D &v2, const Point2D &v3, const Point2D &v4)
   : m_a{v1}, m_b{v2}, m_c{v3}, m_d{v4}, m_sv{nullptr}, m_so{nullptr}, m_no{nullptr}, m_nv{nullptr}
{
  //
}
template <class ID, class T>
void QuadTre<ID,T>::subDivide(int n) // uniform rekursiv subdivisjon, fyller alle nivåer
{
   if (n>0) {
       Point2D v1 = {(m_a.first+m_b.first)/2,(m_a.second+m_b.second)/2};
       Point2D v2 = {(m_b.first+m_c.first)/2,(m_b.second+m_c.second)/2};
       Point2D v3 = {(m_c.first+m_d.first)/2,(m_c.second+m_d.second)/2};
       Point2D v4 = {(m_d.first+m_a.first)/2,(m_d.second+m_a.second)/2};
       Point2D m = {(m_a.first+m_c.first)/2,(m_a.second+m_c.second)/2};
       m_sv = new QuadTre(m_a, v1, m, v4);
       m_sv->subDivide(n-1);
       m_so = new QuadTre(v1, m_b, v2, m);
       m_so->subDivide(n-1);
       m_no = new QuadTre(m, v2, m_c, v3);
       m_no->subDivide(n-1);
       m_nv = new QuadTre(v4, m, v3, m_d);
       m_nv->subDivide(n-1);
   }
}
template <class ID, class T>
void QuadTre<ID,T>::print() const
{
   Point2D c = {(m_a.first+m_c.first)/2,(m_a.second+m_c.second)/2};
   std::cout << "senter = (" << c.first << ", " << c.second << ")" << std::endl;
   for (auto it=m_objects.begin(); it!=m_objects.end(); it++)
       std::cout << it->m_navn << std::endl;
}
template <class ID, class T>
bool QuadTre<ID,T>::isLeaf() const
{
  return m_sv == nullptr && m_so == nullptr && m_no == nullptr && m_nv == nullptr;
}
template <class ID, class T>
QuadTre<ID,T> *QuadTre<ID,T>::insert(const Point2D& point, const ID& id, const T& object)
{
   if (isLeaf()) {
       m_objects.push_back(object);
       return this;
   }
   else {
       Point2D m = {(m_a.first+m_c.first)/2,(m_a.second+m_c.second)/2};
       if (object.getPosition().y < m.second)
       {
           if (object.getPosition().x < m.first)
           {
               m_sv->insert(object);

           }
           else
           {
               m_so->insert(object);

           }
       }
       else {
           if (object.getPosition().x < m.first)
           {
               m_nv->insert(object);

           }
           else
           {
               m_no->insert(object);

           }
       }
   }
}
template <class ID, class T>
QuadTre<ID,T>* QuadTre<ID,T>::find(const Point2D& p)
{
  if (isLeaf()) {
      return this;
  }
  else {
      Point2D m = {(m_a.first+m_c.first)/2,(m_a.second+m_c.second)/2};
      if (p.second < m.second)
      {
          if (p.first < m.first)
              m_sv->find(p);
          else
              m_so->find(p);
      }
      else {
          if (p.first < m.first)
              m_nv->find(p);
          else
              m_no->find(p);
      }
  }
}
template <class ID, class T>
const QuadTre<ID,T> *QuadTre<ID,T>::find(const Point2D& p) const
{
  if (isLeaf()) {
      return this;
  }
  else {
      Point2D m = {(m_a.first+m_c.first)/2,(m_a.second+m_c.second)/2};
      if (p.second < m.second)
      {
          if (p.first < m.first)
              m_sv->find(p);
          else
              m_so->find(p);
      }
      else {
          if (p.first < m.first)
              m_nv->find(p);
          else
              m_no->find(p);
      }
  }
}

}


