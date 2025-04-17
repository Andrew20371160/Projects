#ifndef _multiset_h_
#define _multiset_h_
#include "bst.h" 
#include <vector>
#include <math.h>

enum mode {
	SET=0,MULTISET=1
};
template<typename DataType>
bool remove_duplicates_function (DataType&d1,uint32_t&c1,DataType*v1,uint32_t*v2,const uint32_t){
	c1 = 1 ; 
}
template<typename DataType>
bool standardize_element (DataType&d1,uint32_t&c1,DataType*v1,uint32_t*v2,const uint32_t){
	d1=d1-v1[0];
	d1 =d1/v1[1] ; 
}

template<typename DataType>
class multiset{
	private:
		bst<DataType>tree;
		bool mode ;
		bool intersection_tour(const node<DataType>*src_tree_ptr,const bst<DataType>*other_tree,
							   const node<DataType>**match_vector,uint32_t& match_counter)const;
		bool union_tour(const node<DataType>*src_tree_ptr,const bst<DataType>*other_tree,
							   const node<DataType>**match_vector,uint32_t& match_counter)const;
		bool unique_elements_tour(const node<DataType>*src_tree_ptr,const bst<DataType>*other_tree,
					   const node<DataType>**match_vector,uint32_t& match_counter)const;

		bool difference_tour(const node<DataType>*src_tree_ptr,const bst<DataType>*other_tree,
			   const node<DataType>**match_vector,uint32_t& match_counter)const;

		bool merge(const node<DataType>**dest,const node<DataType>**,const node<DataType>** ,
				   const uint32_t &v1_c,const uint32_t &v2_c)const;	
		multiset<DataType> form_tree(const node<DataType>**vec,uint32_t size)const;
		bool contain_tour(const node<DataType>*src_tree_ptr,const bst<DataType>*other_tree,
					      uint32_t& match_counter)const;		
		bool equality_tour(const node<DataType>*src_tree_ptr,const bst<DataType>*other_tree,
					      uint32_t& match_counter)const;
		bool avg_tour(const node<DataType>*src_tree_ptr,DataType& avg)const;
		
		bool powered_avg_tour(const node<DataType>*src_tree_ptr,DataType& avg,double power)const;

		bool variance_tour(const node<DataType>*src_tree_ptr,DataType& avg1,DataType&avg2)const;

		bool median_tour (const node<DataType>*src_tree_ptr,const node<DataType>*& median_ptr)const ;

		bool pmf_tour(const node<DataType>*src_tree_ptr,std::vector<double>&pmf_vec,uint32_t &counter)const;
		bool cmf_tour(const node<DataType>*src_tree_ptr,std::vector<double>&pmf_vec,uint32_t &counter)const;
		bool addition_tour(node<DataType>*src_tree_ptr,const bst<DataType>*intersect_tree)const;
		bool apply_function_tour(node<DataType>*src_tree_ptr,bool(*f_ptr)(DataType&,uint32_t&,
														  	  		  DataType*,uint32_t*,const uint32_t),
																	  DataType*v1,uint32_t*v2,uint32_t size);

	public:
		multiset(void);		
		multiset(const multiset&) ;
		multiset&operator =(const multiset&) ; 
		multiset(const int&);
		~multiset(void) ;
		bool set_mode(const int&);
		bool insert(const DataType& ,const uint32_t c=1) ;
		bool remove(const DataType& ) ;
		bool clear(void);
		bool search(const DataType&)const ;
		bool adjust_count(const DataType&,const uint32_t&);
		uint32_t count(const DataType&)const ;	
		multiset intersect(const multiset&) const;
		multiset unite(const multiset&) const;
		multiset operator-(const multiset&) const;	
		multiset operator+(const multiset&) const;	
		bool operator>=(const multiset&) const;
		bool operator<=(const multiset&) const;
		bool operator==(const multiset&) const;
		DataType average(void)const ;	
		DataType average(const double&)const;	
		DataType variance(void)const ;
		void display(void)const;
		DataType median(void)const ;
		std::vector<double> pmf(void)const ;
		std::vector<double> cmf(void)const ;
		DataType standard_deviation(void)const;
		DataType range(void) const ; 
		bool remove_duplicates(void);    
		bool replace(const DataType&old_data,const DataType&new_data) ;
		multiset normalize(void) ;

};

#endif 
