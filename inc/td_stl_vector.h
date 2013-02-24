/*

    TDolphin projects

    -> STL VECTOR <-

    (c) TDolphin 2007-2008

    td_stl_vector.h

    STL implementation by TDolphin for TDolphin's projets
    (it is very simple version, not all functionality is supported)
    author: Rafal Zabdyr / TDolphin


    created: 21.06.2007
       last: 28.01.2008

*/

#ifndef __TD_STL_VECTOR
#define __TD_STL_VECTOR

#ifdef WIN32
#include <vector>
#else // LINUX, MORPHOS
#include <cstdlib>
#include "td_stl_construct.h"

#ifndef __DEFAULT_VECTOR_CAPACITY
#define __DEFAULT_VECTOR_CAPACITY  128
#endif


namespace std
{

// STL exception classes
class out_of_range {}; // ...
class out_of_memory {}; // ...


template <class T>
class vector
{
public:

   class iterator;
   class reverse_iterator;

   typedef T value_type; // the type of object
   typedef value_type* pointer; // pointer to object
   typedef const value_type* const_pointer; // pointer to const
   typedef size_t size_type; // for capacity and size
   typedef value_type& reference;
   typedef const value_type& const_reference;

   // construct default vector with default capacity
   vector() : m_nSize(0), m_nCapacity(0), m_pArray(NULL)
   {
      // m_pArray = new T[__DEFAULT_VECTOR_CAPACITY ]; <--- it will call constructor of T many times ...
      m_pArray = (T*)new char[__DEFAULT_VECTOR_CAPACITY * sizeof(T)];
      if (!m_pArray) throw out_of_memory();
      m_nCapacity = __DEFAULT_VECTOR_CAPACITY;
   }

   // copy constructor
   vector(const vector<T>& _vec) : m_nSize(0), m_nCapacity(0)
   {
      internal_copy_from(_vec);
   }

   // vector destructor, call destructor for each element and then erase all allocated memory
   ~vector()
   {
      for (size_type i = 0; i < m_nSize; i++)
         m_pArray[i].~T();
      delete[] (char*)m_pArray;
   }

   // return number of elements in vector
   size_type size() { return m_nSize; }
   // return ???
   size_type max_size() { /*return m_n; to-do */ }
   // return capacity of vector
   size_type capacity() { return m_nCapacity; }

   // resize vector to new size (if grows and capacity is to small realloc vector-data to bigger one,
   // init new element with default constructor)
   void resize(size_type _new_size)
   {
      T* _pArray = m_pArray;

      if (_new_size > m_nCapacity)
      {
         size_type _new_capacity = (_new_size/__DEFAULT_VECTOR_CAPACITY + 1) * __DEFAULT_VECTOR_CAPACITY;
         _pArray = (T*)new char[_new_capacity * sizeof(T)];
         if (!_pArray) throw out_of_memory();
         m_nCapacity = _new_capacity;
      }

      internal_resize(_new_size, _pArray); // resize/copy/delete ...
   }

   // resize vector to new size (if grows and capacity is to small realloc vector-data to bigger one,
   // init new elements with given object by copy constructor)
   void resize(size_type _new_size, const T& _init)
   {
      T* _pArray = m_pArray;

      if (_new_size > m_nCapacity)
      {
         size_type _new_capacity = (_new_size/__DEFAULT_VECTOR_CAPACITY + 1) * __DEFAULT_VECTOR_CAPACITY;
         _pArray = (T*)new char[_new_capacity * sizeof(T)];
         if (!_pArray) throw out_of_memory();
         m_nCapacity = _new_capacity;
      }

      internal_resize(_new_size, _pArray, _init); // resize/copy/delete ...
   }

   // realloc vector
   void reserve(size_type _new_capacity)
   {
      if (m_nCapacity == _new_capacity)
         return;

      // alloc new memory
      T* _pNewArray = (T*)new char[_new_capacity * sizeof(T)];
      if (!_pNewArray) throw out_of_memory();

      m_nCapacity = _new_capacity;

      // check if vector should be shrunken
      size_type _nNewSize = (m_nSize > _new_capacity) ? _new_capacity : m_nSize;

      internal_resize(_nNewSize, _pNewArray); // resize/copy/delete ...
   }

   // chceck vectro if it is empty
   bool empty() const { return (m_nSize == 0); }

   // erase all elements in vector and shrunk it (??)
   void clear()
   {
      // call destructor for each object
      for (size_type i = 0; i < m_nSize; i++)
         m_pArray[i].~T();
      m_nSize = 0;

      // should we resize-down ????? to-do ... check STL documentation
      reserve(__DEFAULT_VECTOR_CAPACITY);
   }

   iterator begin() { return iterator(m_pArray); }
   iterator end() { return iterator(&m_pArray[m_nSize]); }
   reverse_iterator rbegin() { return reverse_iterator(&m_pArray[m_nSize - 1]); }
   reverse_iterator rend() { return reverse_iterator(&m_pArray[-1]); }

   reference operator =(const vector<T>& _vec)
   {
      m_nSize = 0;
      m_nCapacity = 0;
      internal_copy_from(_vec);
   }

   reference operator [](unsigned int _idx) const { return m_pArray[_idx]; }
   reference at(unsigned int _idx) const throw(out_of_range)
   {
      if (_idx >= m_nSize) throw out_of_range();
      return m_pArray[_idx];
   }

   // push given element on the end of vector, if out of capacity realloc
   void push_back(const T& _elem)
   {
      // check if enough capacity
      if (m_nSize == m_nCapacity)
         reserve(m_nCapacity + __DEFAULT_VECTOR_CAPACITY);

      new_placement(&m_pArray[m_nSize++], _elem); // construct by copy object
   }

   // push element on the end of vector, if out of capacity realloc
   void push_back()
   {
      // check if enough capacity
      if (m_nSize == m_nCapacity)
         reserve(m_nCapacity + __DEFAULT_VECTOR_CAPACITY);

      new_placement(&m_pArray[m_nSize++]); // construct object
   }

   // remove last element from vector
   void pop_back()
   {
      // no resize in pop_back
      //if (m_nSize == m_nCapacity - __DEFAULT_VECTOR_CAPACITY)
      //   reserve(m_nCapacity - __DEFAULT_VECTOR_CAPACITY)
      m_pArray[--m_nSize].~T();
   }

   iterator Insert(iterator _iter, const T& _elem);
   iterator erase(iterator _iter)
   {
      // erase at position _iter
      iterator _iter_next = _iter;
      ++_iter_next;
      internal_copy_down(_iter_next, _iter); // src, dst

      m_pArray[--m_nSize].~T();

      return _iter;
   }

   iterator erase(iterator _begin_iter, iterator _end_iter);

private:
   // copy down elements
   void internal_copy_down(iterator _src, iterator _dest)
   {
      while (_src.m_pCurrent != &m_pArray[m_nSize])
      {
         *_dest = *_src;
         ++_dest; ++_src;
      }
   }

   // copy only to empty vector this
   void internal_copy_from(const vector<T>& _vec)
   {
      // alloc memory
      m_pArray = (T*)new char[_vec.m_nCapacity * sizeof(T)];
      if (!m_pArray) throw out_of_memory();
      m_nCapacity = _vec.m_nCapacity;

      // copy elements
      for (size_type i = 0; i < _vec.m_nSize; i++)
         new_placement(&m_pArray[i], _vec.m_pArray[i]);
      m_nSize = _vec.m_nSize;   
   }

   void internal_resize_BEGIN(size_type _new_size, T* _new_array)
   {
      if (!_new_array)
         _new_array = m_pArray;

      if (_new_array == m_pArray && _new_size == m_nSize)
         return;

      // copying objects
      if (_new_array != m_pArray) // only perform when arrays are different
      {
         // are we going to resize down / resize up / none ?
         size_type _copy_size = (m_nSize >= _new_size) ? _new_size : m_nSize; // min

         for (size_type i = 0; i < _copy_size; i++)
            new_placement(&_new_array[i], m_pArray[i]);
      }

      // deleting old and/or adding new ones
      if (_new_array != m_pArray)
      {
         // delete all objects (call destructor) in current array
         for (size_type i = 0; i < m_nSize; i++)
            m_pArray[i].~T();
      }
   }

   void internal_resize_END(size_type &_new_size, T* &_new_array)
   {
      // change current size and current array
      m_nSize = _new_size;
      if (_new_array != m_pArray)
      {
         delete[] (char*)m_pArray;
         m_pArray = _new_array;
      }
   }

   void internal_resize(size_type _new_size, T* _new_array)
   {
      internal_resize_BEGIN(_new_size, _new_array);

      if (_new_array == m_pArray && m_nSize > _new_size)
      {
         // delete objects (call destructor) in current array above new size
         for (size_type i = _new_size; i < m_nSize; i++)
            m_pArray[i].~T();
      }
      else if (m_nSize < _new_size)
      {
         // add objects (call constructor) in current above current size
         for (size_type i = m_nSize; i < _new_size; i++)
            new_placement(&_new_array[i]); // default constructor
      }
  
      internal_resize_END(_new_size, _new_array);
   }

   void internal_resize(size_type _new_size, T* _new_array, const T& _init)
   {
      internal_resize_BEGIN(_new_size, _new_array);

      if (_new_array == m_pArray && m_nSize > _new_size)
      {
         // delete objects (call destructor) in current array above new size
         for (size_type i = _new_size; i < m_nSize; i++)
            m_pArray[i].~T();
      }
      else if (m_nSize < _new_size)
      {
         // add objects (call constructor) in current above current size
         for (size_type i = m_nSize; i < _new_size; i++)
            new_placement(&_new_array[i], _init); // copy constructor
      }
  
      internal_resize_END(_new_size, _new_array);
   }

public:

   class iterator
   {
      friend class vector<T>;

      iterator(T* _pointer) : m_pCurrent(_pointer) {}
   public:
      iterator() : m_pCurrent(NULL) {}
      ~iterator() {}

      T& operator*() const { return *m_pCurrent; }
      int operator==(const iterator& _iter) const { return (m_pCurrent == _iter.m_pCurrent); }
      int operator!=(const iterator& _iter) const { return (m_pCurrent != _iter.m_pCurrent); }
      iterator& operator++() { ++m_pCurrent; return *this; }
      iterator operator++(int) { return ++m_pCurrent; }
      iterator& operator--() { --m_pCurrent; return *this; }
      iterator operator--(int) { return --m_pCurrent; }

      // to-do ...
   protected:
      T* m_pCurrent;
   }; // iterator

   class reverse_iterator : public iterator
   {
      reverse_iterator(T* _pointer) : iterator(_pointer) {}

   public:
      reverse_iterator& operator++() { --m_pCurrent; return *this; }
      reverse_iterator operator++(int) { return --m_pCurrent; }
      reverse_iterator& operator--() { ++m_pCurrent; return *this; }
      reverse_iterator operator--(int) { return ++m_pCurrent; }
   protected:
      T* m_pCurrent;
   }; // reverse_iterator

// vector members
private:
   T* m_pArray;
   size_type m_nSize; // number of elements in vector
   size_type m_nCapacity; // capacity of array 
};

}; // std

#endif // LINUX, MORPHOS

#endif // __TD_STL_VECTOR_H
