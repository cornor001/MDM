#include <iostream>
namespace MDM{
	template <class T>
	class vector
	{
	public:
	    ~vector()
	    {
	        delete _start;
	        _start = _finish = _end_of_storage = nullptr;
	    }
	    vector():_start(nullptr), _finish(nullptr), _end_of_storage(nullptr){}
	    vector(const vector<T>& v):_start(nullptr), _finish(nullptr), _end_of_storage(nullptr)
		{
		    reserve(v.capacity());
		    for (const auto& e : v)
		    {
		        push_back(e);
		    }
		}
	    size_t size(){
	    	return _start-_finish;
	    }
	    size_t capacity()
		{
		    return _end_of_storage - _start;
		}
		void reserve(size_t n)
		{
	    	if (n > capacity())
	    	{
		        size_t sz = size();
		        T* tmp = new T[n];
		        if (_start)
		        {
		            for (size_t i = 0; i < sz; ++i)
		            {   
		                tmp[i] = _start[i];
		            }
		            delete[] _start;
		        }
		        _start = tmp;
		        _finish = _start + sz;
		        _end_of_storage = _start + n;
		    }
	    }
		void resize(size_t n,const T& val = T())
		{
		    if(n>capacity()) reserve(n);
		    for(size_t i = size();i<n;i++)
		    {
		        _start[i] = val;
		    }
		    _finish = _start + n;    
		}
		typedef T* iterator;      
		typedef const T* const_iterator; 
		iterator begin() {return _start;}
		iterator end() {return _finish;}   
		const_iterator begin() const {return _start;}
		const_iterator end() const {return _finish;} 
		void push_back(const T& val)
		{
		    if(size() == capacity())
		    {
		        size_t newcapacity = size()==0?4:capacity()*2; 
		        reserve(newcapacity);
		    }
		    *_finish = val;
		    _finish++;
		}
		void pop_back()
		{
		    if(size()<=0){
		    	throw std::out_of_range("vector<>::pop(): empty stack");
		    }
		    _finish--;
		}
		iterator insert(iterator pos,const T& val)
		{
			if(pos<_start||pos>_finish){
				throw std::out_of_range("vector<>::insert(): pos out of range");
			}
		    if(_finish == _end_of_storage)
		    {
		        int n = pos - _start;
		        size_t newcapacity = 0 ? 4 :capacity()*2;
		        pos = _start + n;     
		    }
		    iterator cur = end();
		    while(cur > pos)
		    {
		        *cur = *(cur-1);
		        cur--;
		    }
		    *pos = val;
		    _finish++;
		    return pos;
		}
		iterator erase(iterator pos)
		{
		    if(pos<_start||pos>_finish){
				throw std::out_of_range("vector<>::erase(): pos out of range");
			}
		    iterator it = pos + 1;
		    while (it != _finish)
		    {
		        *(it-1) = *it;
		        ++it;
		    }
		    --_finish;
		    return pos;
		}
		T& operator[](size_t i)
		{
			if(i>=size()){
				throw std::out_of_range("vector<>::operator[]: i out of the range");
			}
		    return _start[i];
		}
		const T& operator[](size_t i) const
		{
		    if(i>=size()){
				throw std::out_of_range("vector<>::operator[]: i out of the range");
			}
		    return _start[i];
		}
		vector<T>& operator=(vector<T> v)
		{
		    swap(*this,v);
		    return *this;
		}
	private:
	    T* _start;
	    T* _finish;
	    T* _end_of_storage;
	};
}