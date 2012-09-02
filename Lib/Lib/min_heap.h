#ifndef MIN_HEAP_H_
#define MIN_HEAP_H_

#include "array.h"
#include <map>
namespace util{

	namespace heap
	{

		template<typename T, typename V>
		class HeapElem
		{
		public:
			HeapElem(){;}
			HeapElem(T _key, V _value):key_(_key),value_(_value){;}


			~HeapElem(){;}
			inline T key()const{return key_;}
			inline V value()const {return value_;}
			inline void set_key(T _key){key_ = _key;}
			inline void set_value(V _value){value_ = _value;}
		private:
			T key_;
			V value_;
		};






		template<typename T, typename V>
		class MinHeap: public array::Array< HeapElem<T,V> >{	 

		public:
			MinHeap(): Array< HeapElem<T,V> >()
			{ 
				Array< HeapElem<T,V> >::insert(HeapElem<T,V>()); 
				key_position.clear();
			}
			~MinHeap();
			virtual int insert(const HeapElem<T,V>& e);
			virtual void decreaseKey( T _key, V _value);
			virtual const HeapElem<T,V> get_min()const {return elem_[1]; }
			virtual HeapElem<T,V> extract();
			virtual bool empty();

			void demo();

		private:
			std::map<T, int> key_position;
		};

		template<typename T, typename V>
		void util::heap::MinHeap<T, V>::demo()
		{
			MinHeap<int,int> min_heap;
			//std::cout<<min_heap.capacity()<<"	"<<min_heap.size()<<std::endl;
			for(int i=1;i<10;++i)
				min_heap.insert(HeapElem<int,int>(i,i));
			min_heap.decreaseKey(9,1);
			int i=0;
			while(!min_heap.empty())
			{
				std::cout<<++i<<std::endl;
				HeapElem<int, int >	ex = min_heap.extract();
				std::cout<<ex.key()<<"	"<<ex.value()<<std::endl;
			}
			return ;
		}

		template<typename T, typename V>
		util::heap::MinHeap<T, V>::~MinHeap()
		{
			 key_position.clear();
		}

		template<typename T, typename V>
		bool util::heap::MinHeap<T, V>::empty()
		{
			  return size_<=1;
		}

		template<typename T, typename V>
		HeapElem<T,V> util::heap::MinHeap<T, V>::extract()
		{
		   HeapElem<T,V> e = get_min();
		 //  std::cout<< size_<<std::endl;
		   HeapElem<T,V> r = remove( size_-1 );
		   int i, son;
		   for (i=1;(son=i<<1) < size_; i=son )
		   {
			   if (son+1 < size_ && elem_[son+1].value() <elem_[son].value())
				   son++;
			   if (son < size_ && elem_[son].value() < r.value())
			   {
				   elem_[i]=elem_[son];
				   key_position[elem_[i].key()]=i;
			   }
			   else
				   break;
		   }
		   elem_[i]= r;
		   key_position[elem_[i].key()]=i;
		   return e;
		}

		template<typename T, typename V>
		void util::heap::MinHeap<T, V>::decreaseKey( T _key, V _value )
		{
			HeapElem<T,V> e(_key,_value);
			int i, parent;
			for(i = key_position[_key], parent = i>>1; i>0 && parent>0; i=parent,parent =i>>1)
			{
				if(e.value() < elem_[parent].value())
				{
					elem_[i] = elem_[parent];
					key_position[elem_[i].key()] = i;
				}
				else break;
			}

			elem_[i] = e;
			key_position[elem_[i].key()] = i;
		}

		template<typename T, typename V>
		int util::heap::MinHeap<T, V>::insert( const HeapElem<T,V>& e )
		{
			Array< HeapElem<T,V> >::insert(e);
			int i,parent;
			for( i = size_-1, parent = i>>1; i>0 && parent>0; i=parent ,parent =i>>1)
			{
				//std::cout <<"i: "<<i<<"	"<<"parent: "<<parent<<std::endl;
				if(e.value() < elem_[parent].value())
				{
					elem_[i] = elem_[parent];
					key_position[elem_[i].key()] = i;
				}
				else break;
			}

			elem_[i] = e;
			key_position[elem_[i].key()] = i;
			return i;
		}


	

	}//namespace heap

}//namespace util 

#endif