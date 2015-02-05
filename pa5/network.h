#ifndef NETWORK_H
#define NETWORK_H
#include "user.h"

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

        string find_name(int);

        //Get a copy of the user_list of the network.
        vector<User> getUserList();

        //The function return the shortest path from a user to another.
        vector<int> shortest_path(int, int);

        //The function returns the groups in the network.
        vector<vector<int> > groups();

        //The function returns the set of suggested friends.
        vector<int> suggest_friends(int, int&);
    
        //The function returns the set of common friends of two users.
        vector<int> common_friends(int, int);
    private:

        //A private user list
        vector<User> users;

        //This function implement implement BFS search. It is used by public 
        // member function 
        vector<int> breathfirst_search(int, int);
};


#endif
