#include "server.h" 
    using namespace std;
    pthread_t *thread_pool = NULL ; 
    pthread_t listener_thread_id ;
    sem_t requests_number,pipe_lock ,logged_users_lock,tree_lock;  




    #define max_threads 1000

    enum front_end {
        SIGNUP_USER = 0,  // 0 for signup
        LOGIN_USER = 1 ,   // 1 for login
        
        UPLOAD_FILE = 2,
        DOWNLOAD_FILE,
        EDIT_FILE,
        REMOVE_FILE,

        REMOVE_USER,
        LOGOUT_USER    ,
        LIST_FILES      
    };
    static HANDLE g_pipe = INVALID_HANDLE_VALUE;
    
    struct user_session_t {
        user* user_ptr;
        UINT32 session_number;
        INT32 request_number;
        string temp_str;
    };

    UINT32 session_count =1 ;       

    server s;
    vector<user_session_t>logged_users ; 




void* user_thread(void*) {
    INT32 idx ;

    while(1){
        idx = 0 ;
        //if there's request
        sem_wait(&requests_number);
        //acquire logged users lock so that one thread at a time can read a service
        DWORD bytesWritten;
        
        sem_wait(&logged_users_lock);
            user_session_t user_req;
            for (; idx < logged_users.size(); ++idx) {
                if (logged_users[idx].request_number>0) {
                    user_req = logged_users[idx];
                    //now user is blocked from servicies till his/her service is done 
                    logged_users[idx].request_number = -1;
                    break;
                }
            }
        sem_post(&logged_users_lock);

        int svc = user_req.request_number;
        string response;
        string path = user_req.user_ptr->email + "\\" + user_req.temp_str;

        switch (svc) {
            case UPLOAD_FILE: {
                sem_wait(&pipe_lock) ;
                    // 1. Send approval
                    WriteFile(g_pipe, "1", 1, &bytesWritten, NULL);                
                    FlushFileBuffers(g_pipe);
                    ofstream file(path, ios::binary);
                    // 2. Receive file data
                    char buffer[4096];
                    DWORD bytesRead;
                    
                    while (ReadFile(g_pipe, buffer, sizeof(buffer), &bytesRead, NULL)) {
                        if (bytesRead == 0) break;
                        file.write(buffer, bytesRead);
                    }
                    file.close();   
                    WriteFile(g_pipe, "1", 1, &bytesWritten, NULL);                
                    FlushFileBuffers(g_pipe);
                sem_post(&pipe_lock);
                user_req.user_ptr->files.push_back(user_req.temp_str);
                break;
            }

            case DOWNLOAD_FILE: {
                sem_wait(&pipe_lock);
                    ifstream file(path, ios::binary | ios::ate);
                    if (!file.is_open()) {
                        WriteFile(g_pipe, "0", 1, &bytesWritten, NULL);
                        FlushFileBuffers(g_pipe);
                        break;
                    }
                    // 1. Send approval
                    WriteFile(g_pipe, "1", 1, &bytesWritten, NULL);
                    FlushFileBuffers(g_pipe);
                    // 2. Send file data
                    streamsize size = file.tellg();
                    file.seekg(0, ios::beg);
                    vector<char> fileData(size);
                    file.read(fileData.data(), size);
                    WriteFile(g_pipe, fileData.data(), size, &bytesWritten, NULL);
                    FlushFileBuffers(g_pipe);
                sem_post(&pipe_lock) ;
                break;
            }
            case LIST_FILES: {
                string fileList = "0"; 
                if(user_req.user_ptr->files.size()){                    
                    fileList = "1";  // Error code
                    for(UINT32 i = 0 ; i <user_req.user_ptr->files.size();i++){
                        fileList =fileList+" "+user_req.user_ptr->files[i];
                    }
                    cout<<fileList;
                }
                sem_wait(&pipe_lock);
                    WriteFile(g_pipe, fileList.c_str(), fileList.size(), &bytesWritten, NULL);                
                    FlushFileBuffers(g_pipe);
                sem_post(&pipe_lock) ;
                break;
            }

            case REMOVE_FILE: {
                if (DeleteFile(path.c_str())) {
                    int i=0 ;
                    for(; i <user_req.user_ptr->files.size();i++){
                        if(user_req.user_ptr->files[i]==user_req.temp_str){
                            break;
                        }
                    }
                    user_req.user_ptr->files.erase(user_req.user_ptr->files.begin()+i);
                    sem_wait(&pipe_lock);
                        WriteFile(g_pipe, "1", 1, &bytesWritten, NULL);
                        FlushFileBuffers(g_pipe);
                    sem_post(&pipe_lock);
                } 
                else {
                    sem_wait(&pipe_lock);
                        WriteFile(g_pipe, "0", 1, &bytesWritten, NULL);                    
                        FlushFileBuffers(g_pipe);                    
                    sem_post(&pipe_lock);

                }
                break;
            }

            case REMOVE_USER: {
                sem_wait(&logged_users_lock);
                logged_users.erase(logged_users.begin() + idx);
                sem_post(&logged_users_lock);

                sem_wait(&tree_lock);
                bool success = s.remove_user(user_req.user_ptr->email);
                sem_post(&tree_lock);

                sem_wait(&pipe_lock);
                    WriteFile(g_pipe, success ? "1" : "0", 1, &bytesWritten, NULL);                    
                    FlushFileBuffers(g_pipe);
                sem_post(&pipe_lock);
                break;
            }

            case LOGOUT_USER: {    
                sem_wait(&logged_users_lock);    
                    logged_users.erase(logged_users.begin() + idx);
                sem_post(&logged_users_lock); 

                sem_wait(&pipe_lock);
                    WriteFile(g_pipe, "1", 1, &bytesWritten, NULL);                    
                    FlushFileBuffers(g_pipe);
                sem_post(&pipe_lock);
                break;
            }

            default: {
                sem_wait(&pipe_lock);
                WriteFile(g_pipe, "0", 1, &bytesWritten, NULL);
                FlushFileBuffers(g_pipe);
                sem_post(&pipe_lock);
                break;
            }
        }
        //now user can request
        sem_wait(&logged_users_lock);
            logged_users[idx].request_number=0;
        sem_post(&logged_users_lock);
    }
    return NULL; 
}
    
void* listener_thread(void*) {
    string listen_buffer;
    UINT32 i = 0;
    const string pipeName = "\\\\.\\pipe\\my_program_pipe";
    while (1) {
        /*
        _pipe = win32file.CreateFile(
            r'\\.\pipe\my_program_pipe',
            win32file.GENERIC_READ | win32file.GENERIC_WRITE,
            0, None,
            win32file.OPEN_EXISTING,
            win32file.FILE_FLAG_OVERLAPPED,
            None
        )
        */
        HANDLE pipe = CreateNamedPipe(pipeName.c_str(),PIPE_ACCESS_DUPLEX,PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
            1,4096, 4096,0, NULL
        );

        if (pipe == INVALID_HANDLE_VALUE) {
            cerr << "CreateNamedPipe failed: " << GetLastError() << endl;
            return NULL ; 
        }

        cout << "Waiting for client..." << endl;
        BOOL connected = ConnectNamedPipe(pipe, NULL)
                         || GetLastError() == ERROR_PIPE_CONNECTED;

        if (!connected) {
            cerr << "ConnectNamedPipe failed: " << GetLastError() << endl;
            CloseHandle(pipe);
            continue;
        }

        cout << "Client connected!" << endl;            
        g_pipe = pipe; 
        while (true) {
            i = 0;
            char buffer[1024];
            DWORD bytesRead;
            sem_wait(&pipe_lock);
            if (ReadFile(pipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL)) {
                sem_post(&pipe_lock);

                buffer[bytesRead] = '\0';
                listen_buffer = string(buffer);
                cout << "Received:" << listen_buffer << endl;
                int f_service = listen_buffer[0] - '0';

                string response;
                switch (f_service) {
                    case SIGNUP_USER: {
                        
                        sem_wait(&tree_lock);
                        user* p = s.insert(listen_buffer.substr(1));
                        sem_post(&tree_lock);

                        if (p) {
                            user_session_t u;
                            u.user_ptr = p;
                            u.session_number = session_count;
                            u.request_number = 0;
                            
                            sem_wait(&logged_users_lock);
                            logged_users.push_back(u);
                            sem_post(&logged_users_lock) ;

                            response = "1" + to_string(session_count);
                            session_count++;
                        } 
                        else {
                            response = "0";
                        }
                    }break;
                    
                    case LOGIN_USER: {
                        sem_wait(&tree_lock);
                        user* p = s.login(listen_buffer.substr(1));
                        sem_post(&tree_lock);

                        if (p) {
                            //already logged users can't login again
                            sem_wait(&logged_users_lock);
                            BOOL already_logged = 0;
                            for (UINT32 i = 0; i < logged_users.size(); i++) {
                                if (logged_users[i].user_ptr == p) {
                                    already_logged = 1;
                                    break;
                                }
                            }
                            sem_post(&logged_users_lock);

                            if (!already_logged) {
                                response = "1" + to_string(session_count);
                                user_session_t u;
                                u.user_ptr = p;
                                u.session_number = session_count;
                                u.request_number = 0;
                                
                                sem_wait(&logged_users_lock);
                                logged_users.push_back(u);
                                sem_post(&logged_users_lock);

                                session_count++;
                            } 

                            else {
                                response = "0";
                            }
                        } 
                        else {
                            response = "0";
                        }
                    }break;

                    default: {
                        response = "0";
                        
                        i = 1;
                        string session_str = token(listen_buffer, i);
                        UINT32 session_number = atoi(session_str.c_str());
                        
                        sem_wait(&logged_users_lock);
                            for (int j = 0; j < logged_users.size(); j++) {
                                //for the user with according session number assign the service
                                if (logged_users[j].session_number == session_number) {
                                    if (logged_users[j].request_number == 0) {
                                        logged_users[j].request_number = f_service;
                                        logged_users[j].temp_str = listen_buffer.substr(2);
                                        response = "1";
                                        break;
                                    }
                                }
                            }
                        sem_post(&logged_users_lock);

                        if(response=="1"){
                           //valid service
                           sem_post(&requests_number);
                        }
                    }
                }
                sem_wait(&pipe_lock);
                    WriteFile(pipe, response.c_str(), response.length(), NULL, NULL);
                    FlushFileBuffers(pipe);
                sem_post(&pipe_lock); 
                    cout << "Sent:" << response << endl;                
                sem_wait(&tree_lock);
                    s.save("server.txt");
                sem_post(&tree_lock) ;
            }
            else{
                sem_post(&pipe_lock);
            } 
        }
    }
}


    user::user(const string& _email,const string& _password,UINT32 _wanted_space){
        email= _email;
        password=_password;
        wanted_space=_wanted_space;
        used_space = 0;
        left=NULL;
        right=NULL;
    }

    user::user(void) {
        email="";
        password="";
        wanted_space=0;
        used_space = 0;
        left=NULL;
        right=NULL;
    }

    user*server::get_user(const string& email_code){
        if(root){
            user*ptr = root ;
            while(1){
                if(ptr->email==email_code){
                    return ptr;
                }
                else if(email_code<ptr->email){
                    if(ptr->left){
                        ptr = ptr->left;
                    }
                    else{
                        return NULL;
                    }
                }
                else{
                    if(ptr->right){
                        ptr = ptr->right;
                    }
                    else{
                        return NULL;
                    }
                }
            }
        }
        return NULL;
    }
    server::server(void)  {
        root =NULL;
        users_count=0;
    }
    server::~server(void) {
        remove_server(root) ;
        users_count= 0;
    }
    user* server::insert(const std::string&email_code,const std::string& password,UINT32 wanted_space){
        if(root){
            user*ptr = root ;
            while(1){
                
                if(ptr->email==email_code){
                    return NULL;
                }
                else if(email_code<ptr->email){
                    if(ptr->left){
                        ptr = ptr->left;
                    }
                    else{
                        ptr->left = new user(email_code,password,wanted_space);
                        users_count++ ;
                        CreateDirectoryA(email_code.c_str(),NULL);
                        cout<<"\ninserted "<<ptr->left->email<<" "<<ptr->left->password;
                        return ptr->left ;
                    }
                }
                else{
                    if(ptr->right){
                        ptr = ptr->right;
                    }
                    else{
                        ptr->right = new user(email_code,password,wanted_space);
                        users_count++ ;                     
                        CreateDirectoryA(email_code.c_str(),NULL);                        
                        cout<<"\ninserted "<<ptr->right->email<<" "<<ptr->right->password;

                        return ptr->right ;
                    }
                }
            }
        }
        else{
            root =new user(email_code,password,wanted_space);                       
            CreateDirectoryA(email_code.c_str(),NULL);
            users_count++;
            cout<<"\ninserted "<<root->email<<" "<<root->password;

        }
        return root;
    }
    user* server::remove_user_tour(const std::string&email,user*ptr) {
        if(root){
            if(email<ptr->email){
                if(ptr->left){
                    ptr->left=remove_user_tour(email,ptr->left);
                }
                return ptr ;
            }
            if(email>ptr->email){
                if(ptr->right){
                    ptr->right=remove_user_tour(email,ptr->right);
                }
                return ptr ;
            }
            else{
                if(ptr->left==NULL&&ptr->right==NULL){
                    delete ptr;
                    ptr =NULL;
                    users_count-- ;
                    return NULL;
                }
                else if(ptr->right==NULL){
                    user*temp = ptr->left;
                    delete ptr;
                    ptr = NULL;
                    users_count-- ;
                    return temp;
                }
                else if(ptr->left==NULL){
                    user*temp = ptr->right;
                    delete ptr;
                    ptr = NULL;
                    users_count-- ;
                    return temp;
                }
                else{
                    user*max_at_left = ptr->left ;
                    while(max_at_left->right){
                        max_at_left=max_at_left->right;
                    }
                    ptr->email =max_at_left->email;
                    ptr->password = max_at_left->password;

                    ptr->wanted_space = max_at_left->wanted_space;
                    ptr->used_space = max_at_left->used_space;
                    ptr->files = max_at_left->files ; 
                    ptr->left=remove_user_tour(ptr->email,ptr->left) ;

                    return ptr ;
                }
            }
        }
    }
    BOOL server::remove_server(user*ptr ) {
        if(ptr==NULL){
            ptr =root;
        }
        if(ptr){
            if(ptr->left){
                remove_server(ptr->left);
            }
            if(ptr->right){
                remove_server(ptr->right) ;
            }
            BOOL is_root =0 ;
            if(ptr==root){
                is_root=1;
            }
            delete ptr ;
            ptr = NULL;
            if(is_root){
                root=NULL;
            }
            users_count-- ;
            return 1 ;
        }
        return 0 ;
    }

    user* server::login(const string& email,const string& password) {
        user*ptr = get_user(email);
        if(ptr){
            if(password==ptr->password){
                return ptr  ;
            }
        }
        return NULL ;
    }

    BOOL server::remove_user(const string& email) {
        if(root){
            if(get_user(email)){
                root = remove_user_tour(email,root)  ;
                RemoveDirectoryA(email.c_str());
                return 1 ;
            }
        }
        return 0  ;
    }

    BOOL server::save_tour(ofstream &file,user*ptr) {
        if(ptr){
            if(ptr->left){
                save_tour(file,ptr->left);
            }
            file<<ptr->email<<" "<<ptr->password<<" "<<
                  ptr->wanted_space<<" "<<ptr->used_space<<" ";
                  for(UINT32 i = 0 ; i <ptr->files.size();i++){
                      file<<ptr->files[i];
                      if(i<ptr->files.size()-1){
                          file<<" ";
                      }
                  }
                  file<<'\n';
            if(ptr->right){
                save_tour(file,ptr->right);
            }
        }
    }

    BOOL server::save(const  string& path) {
        if(root){
            ofstream file;
            file.open(path, ios::out);
            if(file.is_open()){
                file<<users_count<<'\n';
                save_tour(file,root);
                file.close() ;
            }
            return 1;
        }
        return 0;
    }
    string token(const string& str, UINT32& start_index) {
        while(start_index<str.size()&&str[start_index]==' '){
            start_index++;
        }
        string ret_str = "";
        if (start_index >= str.size()) return ret_str;
        UINT32 temp_start = start_index;
        // Correct condition order to prevent out-of-bounds access
        while (start_index < str.size() && str[start_index] != ' ') {
            start_index++;
        }
        ret_str = str.substr(temp_start, start_index - temp_start);
        return ret_str;
    }
    user*server::to_user(const string&str){
        string temp_str = "";
        user * new_user = new user();
        UINT32 i=0;
        //extract email
        new_user->email = token(str,i) ;
        //extract password
        new_user->password = token(str,i) ;
        temp_str=  token(str,i) ;
        new_user->wanted_space = atoi(temp_str.c_str()) ;
        temp_str=  token(str,i) ;
        new_user->used_space = atoi(temp_str.c_str()) ;            
        cout<<new_user->email<<"\n";
        UINT32 counter = 0 ; 
        while(i<str.size()){
            new_user->files.push_back(token(str,i)) ; 
            cout<<new_user->files[counter];
            counter++;
            i++;
        }
        return new_user;
    }
    user*server:: load_tour( std::vector<string>vec,user*ptr,UINT32 beg ,UINT32 end){
        if(beg<=end){
            UINT32 mid = (beg+end)/2;
            ptr = to_user(vec[mid]);
            //so that overflow doesn't happen
            if(mid!=0){
                ptr->left = load_tour(vec,ptr->left,beg,mid-1);
            }
            ptr->right = load_tour(vec,ptr->right,mid+1,end);
            return ptr ;
        }
        return NULL;
    }
    BOOL server::load( const string&path) {
        ifstream file;
        file.open(path, ios::in);
        if(file.is_open()){
            remove_server(root)  ;
            string str= "";
            //get users count
            std::getline(file,str,'\n');
            UINT32 i =0 ;
            const string&users_count_str =token(str,i) ;
            users_count= atoi(users_count_str.c_str());
            if(users_count>0){
                //vector to load server into
                vector<string> vec(users_count);
                UINT32 i= 0  ;
                while(i<users_count){
                    getline(file,vec[i],'\n');
                    i++;
                }
                file.close()  ;
                for(int i =0 ; i <vec.size() ;i++){
                    cout<<vec[i]<<",";
                }
                //create the balanced tree
                root = load_tour(vec,root,0,users_count-1);
            }
            else{
                file.close() ;
            }
            return 1 ;
        }
        return 0;
    }

    void server::display(user*ptr){
        if(ptr==NULL){
            ptr=root ;
        }
        if(ptr){
            if(ptr->left){
                display(ptr->left) ;
            }
            cout<<ptr->email<<","<<ptr->password<<","<<ptr->wanted_space<<","<<ptr->used_space<<"\n";
            if(ptr->right){
                display(ptr->right) ;
            }
        }
    }

    void server::preorder(void){
        if(root){
            queue<user*> q;
            q.push(root);
            while(!q.empty()){
                user*temp = q.front() ;
                cout<<temp->email<<"\n";
                if(temp->left){
                    q.push(temp->left);
                }
                if(temp->right){
                    q.push(temp->right) ;
                }
                q.pop();
            }
        }
    }

user* server::insert(const std::string&str){
    UINT32 i=0;
    //extract email
    string email = token(str,i) ;
    //extract password
    string password = token(str,i) ;
    string temp_str=  "";
    temp_str=  token(str,i) ;
    UINT32 wanted_space = atoi(temp_str.c_str()) ;
    user* is_inserted =insert(email,password,wanted_space);
    return is_inserted ;
}

user* server::login(const std::string&str){
    UINT32 i=0;
    //extract email
    string email = token(str,i) ;   
    //extract password
    string password = token(str,i) ;
    user* is_login =login(email,password);
    return is_login ;
}


int main() {
    /*
    
    sem_t requests_number,pipe_lock ,logged_users_lock,tree_lock;  

    */
    //initially no servicies
    sem_init(&requests_number,0,0);
    sem_init(&logged_users_lock,0,1);
    sem_init(&pipe_lock,0,1);
    sem_init(&tree_lock,0,1);
    thread_pool = new pthread_t[max_threads] ;
    for(int i = 0 ; i<max_threads ;i++){
        pthread_create(thread_pool+i,NULL,user_thread,NULL);
    }
    s.load("server.txt");
    pthread_create(&listener_thread_id,NULL,listener_thread,NULL); 
    pthread_join(listener_thread_id,NULL);
    delete[]thread_pool;
    thread_pool= NULL ; 
    s.save("server.txt");

    return 0;
}