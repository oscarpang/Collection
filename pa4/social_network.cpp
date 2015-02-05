#include "network.h"
#include "user.h"
#include <iomanip>
#include <iostream>
#include <sstream>
using namespace std;

//Define helper methods to reduce the length of main.
void printMenu();
void add_User_To_Network(Network*, string, string, int, int);
void add_Friend_Connection(Network*, string, string, string, string);
void remove_Friend_Connection(Network*, string, string, string, string);
void print_Users(Network*);
void list_Friends(Network*, string, string);
void write_File(Network*, char*);

int main(int argc, char *argv[])
{
    //Initialize a Network object net
    Network net;

    //Read network from file, and get the return value to check whether if the 
    // file is exist.
    int isFail = net.read_friends(argv[1]);
    
    if(isFail == -1)
    {
        cerr << "Invalid filename to read: " << argv[1] << endl;
        return -1;
    }

    //Create a pointer to the network object.
    Network *netPt = &net;

    //While loop to prompt the user repeatedly.
    while(true)
    {
        //Print menu to the user.
        printMenu();

        //Get the choice of the user.
        int option;
        cin >> option;
        
        //If the input is not a integer, break
        // there is another terminate condition below.
        if(cin.fail())
        {
            break;
        } 

        //Based on user's input, execute different task.
        //Add a friends into the network
        if(option == 1)
        {
            //Read the input and assign to the variable
            string firstname, lastname;
            int year, zip;
            cin >> firstname >> lastname >> year >> zip;

            //If the input is invalid, skip over this loop.
            if(cin.fail())
            {
                cerr << "Invalid input" << endl;
                cin.clear();
                cin.ignore(10000,'\n');
                continue;
            }
            
            //Call the function to add friend.
            add_User_To_Network(netPt, firstname, lastname, year, zip);
        }
        //Add connection between two friends
        else if(option == 2)
        {
            //Read input and assign variable.
            string f1, l1, f2, l2;
            cin >> f1 >> l1 >> f2 >> l2;

            //Input checking
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(10000,'\n');
                continue;
            }

            //Call helper function
            add_Friend_Connection(netPt, f1, l1 , f2, l2);
        }
        //Remove friends connection between two friends.
        else if(option == 3)
        {

            //Read input and assign varaible
            string f1, l1, f2, l2;
            cin >> f1 >> l1 >> f2 >> l2;

            //Input checking
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(10000,'\n');
                continue;
            }

            //Call helper function.
            remove_Friend_Connection(netPt, f1, l1 , f2, l2);
        }
        //Print users
        else if(option == 4)
        {
            print_Users(netPt);
        }
        //List friends of a specific user.
        else if(option == 5)
        {
            //Read input, assign value, and check input.
            string firstname, lastname;
            cin >> firstname >> lastname;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(10000,'\n');
                continue;
            }
            //Call helper function.
            list_Friends(netPt, firstname, lastname);
        }
        //Write the network into a file
        else if(option == 6)
        {
            //Read the target filename, assign, and check input
            char buf[80];
            cin >> buf;
            if(cin.fail())
            {
                cin.clear();
                cin.ignore(10000,'\n');
                continue;
            }

            //Call helper function.
            write_File(netPt,buf);
        }
        //If the input is a number but not between 1 and 6, break the whileloop
        else
        {
            break;
        }
    }
    return 0;
}


//Print menu
void printMenu()
{
    cout << "Please enter your options" << endl;
    cout << "Option 1. Add a user" << endl;
    cout << "Option 2. Add friend connection" << endl;
    cout << "Option 3. Remove friend connection" << endl;
    cout << "Option 4. Print User" << endl;
    cout << "Option 5. List friends" << endl;
    cout << "Option 6. Write to file" << endl;
    cout << "Press any other key to quit" << endl;

    cout << endl;
}

//Add user function.
void add_User_To_Network(Network* net, string firstName, 
                                       string lastName, 
                                       int year, 
                                       int zip)
{
    //Combine the firstname and lastname.
    //Get appropriate ID for this user.
    string name = firstName + " " + lastName;
    int id = net->getLastID() + 1;

    //Create a empty friendlist for this user,
    // and make reference to it.
    vector<int> friendList;
    vector<int> &ref = friendList;

    //Call the function add_user in network class.
    net->add_user(id, name, year,zip, ref);
}

//Add friend's connection function
void add_Friend_Connection(Network* net, string firstNameOne, 
                                         string lastNameOne, 
                                         string firstNameTwo, 
                                         string lastNameTwo)
{
    //Combine names.
    string name_first = firstNameOne + " " + lastNameOne;
    string name_sec = firstNameTwo + " " + lastNameTwo;

    //Get ids according to their name.
    int id_first = net->get_id(name_first);
    int id_sec = net->get_id(name_sec);

    //call the function add_connection in network class.
    net->add_connection(id_first,id_sec);
}

//Remove connection function
void remove_Friend_Connection(Network* net, string firstNameOne, 
                                            string lastNameOne, 
                                            string firstNameTwo, 
                                            string lastNameTwo)
{
    //Combine names
    string name_first = firstNameOne + " " + lastNameOne;
    string name_sec = firstNameTwo + " " + lastNameTwo;

    //Get ids according to their names
    int id_first = net->get_id(name_first);
    int id_sec = net->get_id(name_sec);

    //Call the function remove_connection of network class.
    net->remove_connection(id_first,id_sec);

}

//Print users in the network
void print_Users(Network* net)
{
    //Initialize ostringstream object.
    ostringstream oss;

    //Set the format of the table.
    oss << "ID" << setw(20) << "Name" << setw(20);
    oss << "Year" << setw(10) << "ZIP" << endl;
    oss << "=========================================================="<< endl;

    //Get the user list of the network.
    vector<User> user_list = net->getUserList();

    //Loop through the user_list.
    for(unsigned int i = 0; i < user_list.size(); i++)
    {
        //Create a temporary User object which has all infomation
        // of each user in the user_list.
        User tmp = user_list.at(i);

        //Assigned the info with format into ostringstream object.
        oss << tmp.getID() << left << setw(17)<< "."; 
        oss << left <<setw(20) << tmp.getName();
        oss << left << setw(10) << tmp.getYear() << tmp.getZip() << endl;
    }

    //Print out the table.
    cout << oss.str() << endl;
}


void list_Friends(Network* net, string firstname, string lastname)
{
    //Combine a name
    string name = firstname + " " + lastname;

    //Initialize a ostringstream object
    ostringstream oss;

    //Set the format of the table
    oss << "ID" << setw(20) << "Name" << setw(20);
    oss << "Year" << setw(10) << "ZIP" << endl;
    oss << "=========================================================="<< endl;
    
    //Get the user_list of the network
    vector<User> user_list = net->getUserList();
    //Get the id according to the name
    // if not found, -1 would be returned.
    int id = net->get_id(name);

    if(id < 0)
    {
        return;
    }
    

    //We could not assumed that the id of user are consequent.
    // even though the program define the add user function in consequent
    // behavior. The inconsequence will happen when the user in the file
    // are not consequent. So the program need to find the index of the
    // user in the user_list.
    int index;

    for(unsigned int i = 0; i < user_list.size(); i++)
    {
        User tmp = user_list.at(i);
        if(tmp.getID() == id)
        {
            index = i;
        }
    }

    //Get the int vector of the specific user.
    vector<int>* friendsID_list = user_list.at(index).getFriendsID();

    //Loop through the list
    for(unsigned int i = 0; i < friendsID_list->size(); i++)
    {
        //Get the each user's info, and put them in ostringstrem with format.
        User tmp = user_list.at(friendsID_list->at(i));
        oss << tmp.getID() << left << setw(17) << "."; 
        oss << left << setw(20) << tmp.getName(); 
        oss << left << setw(10) << tmp.getYear() << tmp.getZip() << endl;
    }

    //Print the table.
    cout << oss.str() << endl;
}

//Write to file function.
void write_File(Network* net, char* filename)
{   
    //Call the function in network class.
    net->write_friends(filename);
}



