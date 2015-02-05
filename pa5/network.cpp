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

    ifile.close();
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

string Network::find_name(int id)
{
    if(users.size() ==0)
    {
        cerr << "Empty userlist" << endl;
        return "Invalid ID";
    }

    return users.at(id).getName();
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

//This function use the breath-first search function to find the shorteast
// path from a user to another user.
vector<int> Network::shortest_path(int from, int to)
{
    return breathfirst_search(from, to);
}


//The function is designed to find the shortest path from user
// with id from to the user with id to. Also, if the input "from"  
// a user's id and the input "to" is -2, the function will return
// the list of ids of all users in one group, which contain the user
// with id "from".
vector<int> Network::breathfirst_search(int from, int to)
{
    //Declare a boolean array to record whether a user is visited
    //Declare a queue to implement the BFS algorithm
    //Declare a predecessor array to backtrace.
    bool* footprint = new bool[users.size()];
    int* queue = new int[users.size()];
    int* prede = new int[users.size()];    

    //Initialize a variable to record whether the path is found;
    bool isFounded = false;
    //Initialize a vector to store the result.
    vector<int> result_list;

    //Initialize the footprint array and the queue
    for(unsigned int i = 0; i < users.size(); i++)
    {
        footprint[i] = false;
        queue[i] = -1;
    }

    //Mark the start person as visited
    //Store the start id as the first of queue;
    //The predecessor of the first person is -1.
    footprint[from] = true;
    queue[0] = from;
    prede[0] = -1;

    //Initialize the head and tail to implement the BFS algorithm.
    int head = 0;
    int tail = 1;

    //The loop always run.
    while(true)
    {
        
        //If the head item of the queue is equals to the target
        // assign true to the flag "isFounded", and break the loop.
        if(queue[head] == to)
        {
            isFounded = true;
            break;
        }
        //If the target is never founded, and the searching reach the 
        // end, which means every person that is connected has been searched.
        // break the loop and do not mark the flag.
        else if(head >= tail)
        {
            break;
        }


        //Get the list of IDs of a user's friend.
        vector<int>* listFri = (users.at(queue[head])).getFriendsID();

        //Loop through the friend list.
        for(unsigned int i = 0; i < listFri->size(); i++)
        {

            //Get each id from the list.
            int thisID = listFri->at(i);

            //Check whether this id(person) was visited.
            // if not, add this id to the queue, mark its predecessor,
            // mark the footprint, and add one to tail.
            if(!footprint[thisID])
            {
                queue[tail] = thisID;
                prede[tail] = head;
                footprint[thisID] = true;
                tail++;
            }
        }
        
        //Add 1 to the head
        head++;
    }

    //If the path is founded.
    if(isFounded)
    {
        //Initialize a vector that would store the reverse list of the path.
        vector<int> reverseList;
        int i = head;

        //Backtrace the queue, the reverse path was added to the vector.
        while(i != -1)
        {
            reverseList.push_back(queue[i]);
            i = prede[i];
        }

        //Get the length of the reverse list.
        unsigned len = reverseList.size();

        //Start at the last item, add them to the result list
        // the order would be appropriate now.
        for(int j = len - 1; j >= 0; j--)
        {
            result_list.push_back(reverseList.at(j));
        }        
    }
    //If the parameter "to" is (-2), which will never find the target person,
    // the function would return a vector containing every connected user,
    // which is used to find disjointed group and suggest friends.
    // The reason why is -2 is that the program initialize every queue item as
    // -1.
    else if (to == -2)
    {
        for(int i = 0; i < tail; i++)
        {
            result_list.push_back(queue[i]);
        }
    }

    //Free the memory.
    delete [] footprint;
    delete [] queue;
    delete [] prede;    
    
    //Return the result list.
    return result_list;

}    

//The function is designed to find groups within a network.
// It utilize repeated BFS algorithm to find all the groups.
vector<vector<int> > Network::groups()
{
    //Initialize the result list.
    //Declare and initialize the footprint, to mark and check
    // whether a person is categorized into a group.
    vector<vector<int> > result_list;
    bool* footprint = new bool[users.size()];
    for(unsigned int i = 0; i < users.size(); i++)
    {
        footprint[i] = false;
    }

    //Loop throught the users vector.
    for(unsigned int i = 0; i < users.size(); i++)
    {
        //If a id(person) is not visited(not categorized)
        if(!footprint[i])
        {
            //Get the every ids in the group containing this person
            // using shortest_path defined before.
            vector<int> tmp = breathfirst_search(i,-2);

            //Mark every id in the group as visited(categorized)
            for(unsigned int i = 0; i < tmp.size(); i++)
            {
                footprint[tmp.at(i)] = true;
            }

            //Add the id list to the result list.
            result_list.push_back(tmp);
        }
    }

    //Return the result list.
    return result_list;
}

//This function is used to find the suggested friends of specific user
// with input of the user's id.
vector<int> Network::suggest_friends(int who, int& score)
{
    //Initialize the score as -1
    score = -1;

    //Initialize the result list.
    vector<int> suggest_list;

    //Get the every id of this user's group.
    vector<int> group = shortest_path(who, -2);
    for(unsigned int i = 0; i < group.size(); i++)
    {
        //Get each id of the group.
        int user_id = group.at(i);

        //If the id dose not refer to the input user.
        if(!(user_id == who))
        {
            //Use the BFS to find the shortest path from the input user
            // to another user in the group.
            vector<int> path = breathfirst_search(who, user_id);

            //If they are not direct friends, and the distance must be 2,
            // and the size should be 3.
            if(path.size() == 3)
            {
                //Find the common friend of the two user.
                vector<int> com_friends = common_friends(who, user_id);

                //Initialize newScore to be the size of the list of common
                // friends.
                int newScore = com_friends.size();                

                //If the new score is larger than the previous score
                // set the score to be the newScore, clear the vector, which
                // contains suggests users with lower score, and push back
                // the new user
                if(newScore > score)
                {
                    score = newScore;
                    suggest_list.clear();
                    suggest_list.push_back(user_id);
                }
                //If the newScore is equals to the previous score
                //  add the score to the list.
                else if(newScore == score)
                {
                    suggest_list.push_back(user_id);
                }
            }
        }
    }

    //Return the suggest list.
    return suggest_list;
}

//This function return the list of common friends of two users.
vector<int> Network::common_friends(int first, int second)
{
    //Get two lists of friends' id
    vector<int>* list_fir = users.at(first).getFriendsID();
    vector<int>* list_sec = users.at(second).getFriendsID();

    //Initialize the common friends vector
    vector<int> com_friends;

    //Compare the two list, and push back the identical ones to the vector.
    for(unsigned int i = 0; i < list_fir->size(); i++)
    {
        for(unsigned int j = 0; j < list_sec->size(); j++)
        {
            if(list_fir->at(i) == list_sec->at(j))
            {
                com_friends.push_back(list_fir->at(i));
            }
        }
    }

    //Return the vector.
    return com_friends;
}

