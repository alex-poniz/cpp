#include <iostream>
#include <string>
#include <vector>
#include <cstdlib> // rand()
#include <ctime>
#include <map>
#include <list>
#include <algorithm>

using namespace std;

typedef list<string> HobbyContainer;
typedef unsigned int id_t;
typedef list<id_t> UserIdContainer;

class SocialNetwork;
class User;

enum Hobby {

};

enum Gender {
    Male,
    Female
};

class User
{
    friend class SocialNetwork;
protected:
    Gender _gender;
    unsigned _age;
    unsigned _height;
    string _name;
    id_t _id;
    //friend void SocialNetwork::addUser(const User&);
    HobbyContainer _hobbies;
    UserIdContainer _friends;

public:
    User()
    {
        cout << __PRETTY_FUNCTION__<< endl;
    };

    User(const string& name, unsigned age = 0, unsigned height = 0, HobbyContainer hobbies = {})
        : _name(name), _age(age), _height(height), _hobbies(hobbies)
    {
        cout << __PRETTY_FUNCTION__<< endl;
        //_id = DateTime.Now()
    };

    id_t  getId() { return _id; }

    string getName() { return _name; }

    unsigned getAge() { return _age; }

    UserIdContainer getFriends() { return _friends; }

    HobbyContainer getHobbies() { return _hobbies; }

    void addHobby(string& hobby) { _hobbies.push_back(hobby); }

    void deleteHobby(string& hobby) { _hobbies.remove(hobby); }

    void printInfo()
    {
        cout << "Name: " << _name << " Age: " << _age << " ID: " << _id << endl;
    }

};

class SocialNetwork {
protected:
    map<id_t, User> _usersMap;

    id_t generateUniqId()
    {
        id_t ret = 0;

        srand(static_cast<unsigned int>(time(0)));

        for (int i = 0; i < 100; i++)
        {
             ret = rand();
             if (! _usersMap.count(ret))
                 return ret;
        }

        return 0;
    }

public:
    void addUser(User& user)
    {
        id_t id = this->generateUniqId();
        user._id = id;

        cout << __PRETTY_FUNCTION__ << "Generated ID: " << id << endl;

        _usersMap.insert(pair<id_t, User>(id, user));
    }

    User& getUserById(const id_t &id)
    {
        return _usersMap.at(id);
    }

    UserIdContainer searchUserByAge(const unsigned &age)
    {
        UserIdContainer matches;
        auto it = _usersMap.begin();
        auto it_end = _usersMap.end();

        while (it != it_end)
        {
            it = find_if(it, _usersMap.end(), [age](auto &element){ return element.second.getAge() == age; } );
            if (it != it_end) {
                matches.push_back((*it).second.getId());
                it++;
            }
        }

        return matches;
    }

    UserIdContainer searchUserByHobbies(const HobbyContainer &hobbies)
    {
        UserIdContainer matches;
        auto it = _usersMap.begin();
        auto it_end = _usersMap.end();

        while (it != it_end)
        {
            it = find_if(it, _usersMap.end(), [hobbies](auto &element)
            {
                auto other_hobbies = element.second.getHobbies();
                bool ret = !other_hobbies.empty();

                for (auto my_hobby : hobbies)
                {

                    if (find(other_hobbies.begin(), other_hobbies.end(), my_hobby) == other_hobbies.end())
                    {
                        ret = false;
                        break;
                    }
                }

                return ret;
            });
            if (it != it_end) {
                matches.push_back((*it).second.getId());
                it++;
            }
        }

        return matches;

    }

    UserIdContainer getFriendsOfUser(const id_t &id)
    {
        return this->getUserById(id).getFriends();
    }

    UserIdContainer searchUserByName(const string &name)
    {
        UserIdContainer matches;
        auto it = _usersMap.begin();
        auto it_end = _usersMap.end();

        while (it != it_end)
        {
            it = find_if(it, _usersMap.end(), [name](auto &element){ return element.second.getName() == name; } );
            if (it != it_end) {
                matches.push_back((*it).second.getId());
                it++;
            }
        }

        return matches;
    }

};

#define HOBBY_JOGGING   "Jogging"
#define HOBBY_FOOTBALL  "Football"
#define HOBBY_TENNIS    "Tennis"
#define HOBBY_CYCLING   "Cycling"
#define HOBBY_SKIING    "Skiing"
#define HOBBY_GAMING    "Gaming"

void printPeopleWhoLikes(SocialNetwork &sn, const HobbyContainer &hobbies)
{
    cout << "People, who likes ";

    for (auto h : hobbies)
    {
        cout << h << ", ";
    }
    cout << ": ";

    auto hobby_matches = sn.searchUserByHobbies(hobbies);
    for (auto userId : hobby_matches)
    {
        cout << sn.getUserById(userId).getName() << ", ";
    }
    cout << endl;
}

int main()
{
    //User user_0;
    User user_3("Alexander", 44, 185, {HOBBY_CYCLING, HOBBY_FOOTBALL, HOBBY_SKIING});
    User user_1("Oleg", 13, 163, {HOBBY_GAMING, HOBBY_CYCLING, HOBBY_SKIING});
    User user_2("Igor", 8, 138,  {HOBBY_GAMING, HOBBY_CYCLING, HOBBY_SKIING});

    SocialNetwork sn;

    sn.addUser(user_1);
    sn.addUser(user_2);
    sn.addUser(user_3);

    cout << "user_1.getId() : " << user_1.getId() << endl;
    user_2.printInfo();
    user_3.printInfo();

    string paramName = "U_33";

    auto matches = sn.searchUserByName(paramName);

    cout << "Elemets found  for name \"" << paramName << "\" : ";

    for ( auto userId : matches)
    {
        cout << sn.getUserById(userId).getName() << " ";
    }
    cout << endl;

    printPeopleWhoLikes(sn, {HOBBY_CYCLING});
    printPeopleWhoLikes(sn, {HOBBY_SKIING});
    printPeopleWhoLikes(sn, {HOBBY_FOOTBALL});
    printPeopleWhoLikes(sn, {HOBBY_JOGGING});
    printPeopleWhoLikes(sn, {HOBBY_SKIING, HOBBY_CYCLING});

    printPeopleWhoLikes(sn, {});

}
