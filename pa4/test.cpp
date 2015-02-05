#include "user.h"
#include <string>

int main()
{
    User a(0,"Jess",1995,90007);
    User b(1,"Oz",1996,90007);
    User c(2,"Oz",1996,90007);
    User d(3,"Oz",1996,90007);

    a.add_friend(b.getID());
    a.add_friend(c.getID());
    a.add_friend(d.getID());

    vector<int>* friends = a.getFriendsID();

    for(unsigned int i = 0; i < friends->size(); i++)
    {
        cout << friends->at(i) << endl;
    }

}
