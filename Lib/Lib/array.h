#ifndef ARRAY_H_
#define ARRAY_H_
#include "assert.h"
namespace util{

	namespace array
	{
		const int kCapacity = 3;
		template<typename T>
		class Array
		{
		public:
			Array(int _capacity = kCapacity){ allocate(_capacity);}
			virtual ~Array(){ release();}
			Array( const Array<T>& rhs ){ copyFrom(rhs,0,rhs.size()); }
			Array<T>& operator=(const Array<T>& rhs);

			// help function, copy from rhs, [lo, hi)
			void copyFrom( const T* rhs, int lo, int hi);
			void copyFrom( const Array<T>& rhs , int lo, int hi);
			
			void allocate( int c = kCapacity);
			void release();
			

			inline int size()const { return size_; }
			inline int capacity()const{ return capacity_ ;}
			
			T& get( int idx);
			const T& get( int idx)const; 
			
			T& operator[](int) ;
			const T& operator[](int)const;

			virtual int insert( int idx, const T& e);
			virtual int insert( const T& e){ return insert(size_, e); }

			virtual T remove( int idx);
			virtual int remove( int lo, int hi);

			virtual bool empty(){ return size_<=0 ;}

			void swap(int a, int b);
			
			void demo(); 
		
		protected:
			void expand();
			void shrink();


			T * elem_;
			int capacity_;
			int size_;
		};

		template<typename T>
		void util::array::Array<T>::demo()
		{
			//demo
			util::array::Array<int> a;
			for(int i=0;i<10;++i)
				a.insert(i);
			a.remove(0,10);
			std::cout<<a.size()<<"	"<<a.capacity()<<std::endl;
		}

		template<typename T>
		void util::array::Array<T>::swap( int a, int b )
		{
			assert(a>=0 && a< size_ && b >=0 && b < size_);

			T tmp = elem[a];
			elem_[a] = elem[b];
			elem_[b] = tmp;

		}

		template<typename T>
		T util::array::Array<T>::remove( int idx )
		{
			T e = elem_[idx]; 
			remove(idx, idx+1);
			return e;
		}

		template<typename T>
		int util::array::Array<T>::remove( int lo, int hi )
		{
			 assert(lo < hi && lo>=0 && hi <= size_);

			 for(; hi< size_; ++lo, ++hi)
				elem_[lo] = elem_[hi];
			 size_ = lo;
			 shrink();
			 return hi-lo;
		}


		template<typename T>
		int util::array::Array<T>::insert( int idx, const T& e)
		{
			assert(idx>=0 && idx<=size_);
			expand();
			for (int i = size_; i>idx; --i)
				elem_[i] = elem_[i-1];
			elem_[idx] = e;
			++size_;
			return idx;
		}

		template<typename T>
		void util::array::Array<T>::shrink()
		{
			if(capacity_ < kCapacity<<1) return ;
			if(size_<<2 > capacity_) return ; // size is 25%+ of capacity
			T* old_elem = elem_;
			int old_size = size_;
			allocate( capacity_>>1);
			for( int i=0; i< old_size; ++i)
				elem_[size_++] = old_elem[i];

			delete []old_elem;
			old_elem = NULL;
		}

		template<typename T>
		void util::array::Array<T>::expand()
		{
		   if(size_ < capacity_ ) return ;
		   if( capacity_ < kCapacity ) capacity_ = kCapacity ;
		   
		   T * old_elem = elem_;
		   int old_size = size_;
		   allocate( capacity_<<1 );
		   
		   for( int i=0 ; i< old_size ;++i)
			   elem_[size_++] = old_elem[i];
		   
		   delete []old_elem;
		   old_elem = NULL;
		}

		template<typename T>
		Array<T>& util::array::Array<T>::operator=( const Array<T>& rhs )
		{
			//std::cout<<"operator"<<std::endl;
			int sz=rhs.size();
			if (capacity() < sz)
			{
				release();
				allocate(sz<<1);
			}
			copyFrom(rhs,0,sz);
			return *this;
		}

		template<typename T>
		const T& util::array::Array<T>::operator[]( int ) const
		{
			assert(idx>= 0 && idx<=size_);
			return elem_[idx];
		}


		template<typename T>
		T& util::array::Array<T>::operator[]( int idx)
		{
			assert(idx>= 0 && idx<=size_);
			return elem_[idx];
		}

		template<typename T>
		const T& util::array::Array<T>::get( int idx ) const
		{
			assert(idx>= 0 && idx<=size_);
			return elem_[idx];
		}

		template<typename T>
		T& util::array::Array<T>::get( int idx )
		{
				assert(idx>= 0 && idx<=size_);
				return elem_[idx];
		}

		template<typename T>
		void util::array::Array<T>::copyFrom( const Array<T>& rhs , int lo, int hi )
		{
			 copyFrom(rhs.elem_, lo, hi);
		}

		template<typename T>
		void util::array::Array<T>::allocate( int c)
		{
		   elem_ = new T[ capacity_ = c]; 
		   size_ =0;
		}

		template<typename T>
		void util::array::Array<T>::release()
		{
			 if(elem_!=NULL)
			 {
				 delete []elem_;
				 elem_=NULL;
			 }
		}

		template<typename T>
		void util::array::Array<T>::copyFrom( const T* rhs, int lo, int hi )
		{

			allocate((hi-lo)<<1);

			while(lo < hi)
			{
				elem_[size_++] = rhs[lo++];
			}
		}

	}//namespace array



} //namespace util


#endif