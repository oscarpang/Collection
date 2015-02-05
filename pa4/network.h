#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"
#include <string>

class Network {
    public:
        //Constructor and destructor
        Network();
        ~Network();
        
        //Read friend and write friend from and to file.
        int read_friends(char *);
        int write_friends(char *);

        //Add user to the network.
        void add_user(int,string,int,int,vector<int>&);
        
        //Add and remove connection based on ids.
        int add_connection(int, int);
        int remove_connection(int, int);

        //Get id based on user's name.
        int get_id(string name);

        //The the last one's id
        int getLastID();
        string find_name(int)

        //Get a copy of the user_list of the network.
        vector<User> getUserList();
    private:

        //A private user list
        vector<User> users;
};


#endif
