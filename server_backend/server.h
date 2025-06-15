#ifndef _server_h_
#define _server_h_
#include "server.h"
#include <windows.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
#include <pthread.h>
#include <semaphore.h>

std::string getCurrentTimestamp() ;

std::string token(const std::string&str,UINT32&start_index);

void* user_thread(void*input);

class user
{
	public:
		friend class server ;
		std::vector<std::string>files;
		std::string email ;
		std::string password;
		UINT32 wanted_space ;
		UINT32 used_space ;
		user*left ;
		user*right ;
	public:

	user(const std::string&,const std::string&,UINT32);
	user(void) ;

};
class server{
	UINT32 users_count;
	user*root ;
	user* remove_user_tour(const std::string &email,user*ptr = NULL) ;
	BOOL save_tour( std::ofstream &file,user*ptr);
	user* load_tour( std::vector<std::string>vec,user*ptr,UINT32 beg ,UINT32 end);
	user*to_user(const std::string&);

public:

	server(void) ; 
	~server(void) ;
	user* insert(const std::string&,const std::string&,UINT32);
	user*  insert(const std::string&);
	BOOL remove_server(user*ptr) ;
	BOOL remove_user(const std::string& email);
	user* login(const std::string&,const std::string&) ; 
	BOOL save( const std::string&path) ;
	BOOL load( const std::string&path) ;
	void display(user*ptr=NULL);
    void preorder(void) ;
	user*  login(const std::string&) ; 
	user*get_user(const std::string&);
	

};

#endif
