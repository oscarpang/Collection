#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include <iostream>
using namespace std;

class User {
    public:
        //Constructor and destuctor
        User(int, string, int, int,vector<int>&);
        ~User();

        //Add friend and delete friend
        void add_friend(int id);
        void delete_friend(int id);

        //Setter and getter of variables
        void setID(int id);
        int getID();
        void setYear(int year);
        int getYear();
        void setName(string name);
        string getName();
        int getZip();
        void setZip(int zip);
//        bool isEmpty();
        //The friendsID only hava getter.
        vector<int>* getFriendsID();


    private:
        int _id;
        string _name;
        int _year;
        int _zip;
        vector<int> _friendsID;
//        bool emptyList;

};


#endif
