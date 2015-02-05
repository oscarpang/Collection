#include "user.h"
#include <iostream>
using namespace std;

//Constructor
User::User(int id, string name, int year, int zip, vector<int>& list)
{
    this->_id = id;
    this->_name = name;
    this->_year = year;
    this->_zip = zip;
    this->_friendsID = list;
}

//Destructor
User::~User()
{
}

//Setter of ID
void User::setID(int id)
{
    this->_id = id;
}

//Getter of ID
int User::getID()
{
    return this->_id;
}

//Setter of Year
void User::setYear(int year)
{
    this->_year = year;
}

//Getter of year
int User::getYear()
{
    return this->_year;
}

//Setter of name
void User::setName(string name)
{
    this->_name = name;
}

//Getter of name
string User::getName()
{
    return this->_name;
}

//Setter of zip
void User::setZip(int zip)
{
    this->_zip = zip;
}

//Getter of zip
int User::getZip()
{
    return this->_zip;
}



//Getter of the friends id list
vector<int>* User::getFriendsID()
{
    return &this->_friendsID;
}

//Add friend to the list
void User::add_friend(int id)
{
    //Go through the list, check whether the id is existed.
    for(unsigned int i = 0; i < this->_friendsID.size(); i++)
    {
        if(this->_friendsID.at(i) == id)
        {
            cerr << "Already hase this friend" << endl;
            return;
        }
    }

    //Add the id to the id_list
    this->_friendsID.push_back(id);
}


//Delete friend from the list
void User::delete_friend(int id)
{
    //Loop through the list, if the id is existed in the list
    // use erase() function in vector<int>.
    for(unsigned int i = 0; i < this->_friendsID.size(); i++)
    {
        if(this->_friendsID.at(i) == id)
        {
            this->_friendsID.erase(this->_friendsID.begin()+i);
            return;
        }
    }

    //If the id is not found, print out error message.
    cerr << "You do not have this friend" << endl;
    
}
