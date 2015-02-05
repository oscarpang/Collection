#include "network.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//Empty constructor and destructor
Network::Network()
{
    
}

Network::~Network()
{

}

//Add user function
void Network::add_user(int id, string name, int year, 
                       int zip, vector<int>& list)
{
    //Create a user based on the parameter info.
    User tmp(id,name,year,zip,list);
    //Add the user into the vector.
    this->users.push_back(tmp);
}

//Write firend into file
int Network::write_friends(char * fileName)
{
    //Initialize a ostringstream
    ostringstream oss;

    //Put the count of user into oss
    oss << users.size() << endl;

    //Loop through the list.
    for(unsigned int i = 0; i < users.size(); i++)
    {
        //Assign the info with format.
        User tmp = users.at(i);
        oss << tmp.getID() << endl;
        oss << '\t' << tmp.getName() << endl;
        oss << '\t' << tmp.getYear() << endl;
        oss << '\t' << tmp.getZip() << endl;

        vector<int>* list = tmp.getFriendsID();
        oss << '\t';
        for(unsigned int j = 0; j < list->size(); j++)
        {
            oss << list->at(j);
            if(j < list->size() -1)
            {
                oss << " ";
            }
        }
        oss << endl;
    }

    //Create a ofstream object
    ofstream ofile(fileName);
    //Write the info into the file.
    ofile << oss.str();
    ofile.close();

    return 0;
}

int Network::read_friends(char * fileName)
{
    //Create a ifstream object.
    ifstream ifile(fileName);

    //If the filename could not find, return -1.
    if(ifile.fail())
    {
        return -1;
    }

    //Declare string buffer to store the every line.
    string text;
    getline(ifile,text);
    istringstream iss(text);

    //Assign value to variable from the input file.
    int count;
    iss >> count;

    //Clear the iss object.
    iss.clear();

    //Loop through every set of info
    for(int i = 0; i < count; i++)
    {
        //Declare some variable.
        int id;
        string name;
        int year;
        int zip;
        vector<int> friendsID;
    
        //Loop through every line of an individual.
        for(int j = 0; j < 5; j++)
        {
            //Get line, and prepare to do assignment.
            getline(ifile,text);
            iss.str(text);
            

            if(j==0)
            {
                //Assign to id
                iss >> id;
            }
            else if(j==1)
            {

                //Get the firstname and lastname
                // combine them and assign to name.
                string firstName;
                string lastName;

                iss >> firstName;
                iss >> lastName;

                name = firstName + " "+ lastName;
            }
            else if(j==2)
            {
                //Assign to year.
                iss >> year;
            }
            else if(j==3)
            {
                //Assign to zip
                iss >> zip;
            }
            else if(j==4)
            {
                //Loop through every integer in that line.
                // and add everyone into the vector
                int tmp;
                iss >> tmp;
                if(iss.fail())
                {
                    cout << "EEEEE" << endl;
                    iss.clear();
                    continue;
                }

                friendsID.push_back(tmp);
                while(true)
                {
                    iss >> tmp;
                    //When an integer could not be found, break the whileloop.
                    if(iss.fail())
                    {
                        break;
                    }
                    friendsID.push_back(tmp);
                }
            }

            //Clear the istringstream object everytime.
            iss.clear();
        }

        //Call the add_user function to create and add the user
        //  to the user list.
        add_user(id,name,year,zip,friendsID);
    }

    //If the reading is appropriate, return 0
    return 0;
}

//Add connection between two users
int Network::add_connection(int first, int sec)
{
    //Get the index of the two users in the users list
    // based on the ids

    int indexFir = -1;
    int indexSec = -1;

    for(unsigned int i = 0; i < users.size(); i++)
    {
        if(users.at(i).getID() == first)
        {
            indexFir = i;
        }

        if(users.at(i).getID() == sec)
        {
            indexSec = i;
        }
        
    }


    //If both of the users are found, call the add_friend function
    // of each user to add friend.
    if(indexFir != -1 && indexSec != -1)
    {
        users.at(indexFir).add_friend(sec);
        users.at(indexSec).add_friend(first);
        return 0;
    }
    //Else, do nothing to the data and return -1
    else
    {
        return -1;
    }
    
}


int Network::remove_connection(int first, int sec)
{
    //Get the index of the two users in the users list
    // based on the ids
    int indexFir = -1;
    int indexSec = -1;

    for(unsigned int i = 0; i < users.size(); i++)
    {
        if(users.at(i).getID() == first)
        {
            indexFir = i;
        }

        if(users.at(i).getID() == sec)
        {
            indexSec = i;
        }
        
    }

    //If both of the users are found, call the add_friend function
    // of each user to add friend.
    if(indexFir != -1 && indexSec != -1)
    {
        users.at(indexFir).delete_friend(sec);
        users.at(indexSec).delete_friend(first);
        return 0;
    }
    //Else, do nothing to the data and return -1
    else
    {
        return -1;
    }
}

//Get id according to the name.
int Network::get_id(string name)
{
    if(users.size()==0)
    {
        cerr << "Empty userlist" << endl;
        return -1;
    }

    //Loop through the users list, return the id
    for(unsigned int i = 0; i < users.size(); i++)
    {
        if(users.at(i).getName() == name)
        {
            return users.at(i).getID();
        }
    }

    //If the name is not found, print error message and return -1;
    cerr << "Invalid name " << name << endl; 
    return -1;
}

//Get the the id of the last user.
int Network::getLastID()
{
    
    if(users.size()==0)
    {
        cerr << "Empty userlist" << endl;
        return -1;
    }
    //Get the last user
    User tmp = users.back();
    //Get the id and return.
    int i = tmp.getID();
    return i;
}

//Getter of the private user list.
vector<User> Network::getUserList()
{
    return this->users;
}    
