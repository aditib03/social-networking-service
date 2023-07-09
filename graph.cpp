#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <unordered_set>

using namespace std;

struct User {
    string name;
    string institute;
    int duration;
    string hobby;

    User(const string& n, const string& inst, int dur, const string& h) : name(n), institute(inst), duration(dur), hobby(h) {}
};

class SocialNetwork {
private:
    unordered_map<string, User*> users;
    unordered_map<string, vector<string>> connections;

public:
    void addUser(const string& username, const string& name, const string& institute, int duration, const string& hobby) {
        if (users.find(username) != users.end()) {
            cout << "Username already exists. Please choose a different username." << endl;
            return;
        }

        User* newUser = new User(name, institute, duration, hobby);
        users[username] = newUser;
        connections[username] = vector<string>();

        cout << "User added successfully." << endl;
    }

    void addConnection(const string& username1, const string& username2) {
        if (users.find(username1) == users.end() || users.find(username2) == users.end()) {
            cout << "One or both usernames do not exist. Please check and try again." << endl;
            return;
        }

        connections[username1].push_back(username2);
        connections[username2].push_back(username1);

        cout << "Connection added successfully." << endl;
    }

    void printUserDetails(const string& username) {
        if (users.find(username) == users.end()) {
            cout << "Username does not exist. Please check and try again." << endl;
            return;
        }

        User* user = users[username];
        cout << "Name: " << user->name << endl;
        cout << "Institute: " << user->institute << endl;
        cout << "Duration: " << user->duration << " years" << endl;
        cout << "Hobby: " << user->hobby << endl;
    }

    void printConnections(const string& username) {
        if (users.find(username) == users.end()) {
            cout << "Username does not exist. Please check and try again." << endl;
            return;
        }

        vector<string>& userConnections = connections[username];

        cout << "Connections for user " << username << ":" << endl;
        for (const string& connection : userConnections) {
            cout << connection << endl;
        }
    }

    void findMates(const string& username) {
        if (users.find(username) == users.end()) {
            cout << "Username does not exist. Please check and try again." << endl;
            return;
        }

        User* user = users[username];
        string userInstitute = user->institute;

        cout << "Current and past mates for user " << username << ":" << endl;
        for (const auto& pair : users) {
            User* otherUser = pair.second;
            if (otherUser->institute == userInstitute && pair.first != username) {
                cout << pair.first << endl;
            }
        }
    }

   

   bool areConnected(const string& username1, const string& username2) {
    if (users.find(username1) == users.end() || users.find(username2) == users.end()) {
        cout << "One or both usernames do not exist. Please check and try again." << endl;
        return false;
    }

    unordered_set<string> visited;
    queue<pair<string, int>> q;

    q.push({username1, 0});
    visited.insert(username1);

    while (!q.empty()) {
        string current = q.front().first;
        int distance = q.front().second;
        q.pop();

        if (current == username2) {
            cout << "Person " << username1 << " is connected to person " << username2 << " with a degree of separation: " << distance << endl;
            return true;
        }

        for (const string& connection : connections[current]) {
            if (visited.find(connection) == visited.end()) {
                q.push({connection, distance + 1});
                visited.insert(connection);
            }
        }
    }

    cout << "Person " << username1 << " is not connected to person " << username2 << " in the network." << endl;
    return false;
}


    void findPaths(const string& username1, const string& username2) {
        if (users.find(username1) == users.end() || users.find(username2) == users.end()) {
            cout << "One or both usernames do not exist. Please check and try again." << endl;
            return;
        }

        unordered_set<string> visited;
        vector<string> path;

        findPathsUtil(username1, username2, visited, path);
    }


    void findPathsUtil(const string& current, const string& destination, unordered_set<string>& visited, vector<string>& path) {
        visited.insert(current);
        path.push_back(current);

        if (current == destination) {
            cout << "Path found: ";
            for (const string& username : path) {
                cout << username << " ";
            }
            cout << endl;
        } else {
            for (const string& connection : connections[current]) {
                if (visited.find(connection) == visited.end()) {
                    findPathsUtil(connection, destination, visited, path);
                }
            }
        }

        visited.erase(current);
        path.pop_back();
    }

       void showContactList(const string& username) {
        if (users.find(username) == users.end()) {
            cout << "Username does not exist. Please check and try again." << endl;
            return;
        }

        vector<string>& userConnections = connections[username];

        cout << "Contact list for user " << username << ":" << endl;
        for (const string& connection : userConnections) {
            cout << connection << endl;
        }
    }

    void showCompleteNetwork(const string& username) {
        if (users.find(username) == users.end()) {
            cout << "Username does not exist. Please check and try again." << endl;
            return;
        }

        cout << "Complete network for user " << username << ":" << endl;

        unordered_set<string> visited;
        showCompleteNetworkUtil(username, visited);
    }


    void showCompleteNetworkUtil(const string& current, unordered_set<string>& visited) {
        visited.insert(current);

        cout << current << endl;

        for (const string& connection : connections[current]) {
            if (visited.find(connection) == visited.end()) {
                showCompleteNetworkUtil(connection, visited);
            }
        }
    }

     int calculateMaxDegreeOfSeparation() {
        int maxDegree = 0;

        for (const auto& userPair : users) {
            const string& username = userPair.first;
            unordered_set<string> visited;
            queue<pair<string, int>> q;

            q.push({username, 0});
            visited.insert(username);

            while (!q.empty()) {
                string current = q.front().first;
                int distance = q.front().second;
                q.pop();

                if (distance > maxDegree) {
                    maxDegree = distance;
                }

                for (const string& connection : connections[current]) {
                    if (visited.find(connection) == visited.end()) {
                        q.push({connection, distance + 1});
                        visited.insert(connection);
                    }
                }
            }
        }

        return maxDegree;
    }

    void listPotentialGroups() {
        unordered_map<string, vector<string>> potentialGroups;

        
        for (const auto& userPair : users) {
            const string& username = userPair.first;
            User* user = userPair.second;

            const string& hobby = user->hobby;

        
            potentialGroups[hobby].push_back(username);
        }

       
        for (const auto& groupPair : potentialGroups) {
            const string& hobby = groupPair.first;
            const vector<string>& usernames = groupPair.second;

            cout << "Group with hobby " << hobby << ":" << endl;
            for (const string& username : usernames) {
                cout << "- " << username << endl;
            }
            cout << endl;
        }
    }

    void listLatestConnections(const string& username) {
        if (users.find(username) == users.end()) {
            cout << "Username does not exist. Please check and try again." << endl;
            return;
        }

        vector<string>& contactList = connections[username];

        cout << "Latest connections for users in the contact list of " << username << ":" << endl;
        for (const string& contact : contactList) {
            cout << "Latest connection for user " << contact << ": ";
            vector<string>& userConnections = connections[contact];
            if (!userConnections.empty()) {
                cout << userConnections.back() << endl;
            } else {
                cout << "No connections found." << endl;
            }
        }
    }

    void showMutuals(const string& username1, const string& username2) {
    if (users.find(username1) == users.end() || users.find(username2) == users.end()) {
        cout << "One or both usernames do not exist. Please check and try again." << endl;
        return;
    }

    vector<string>& connections1 = connections[username1];
    vector<string>& connections2 = connections[username2];

    cout << "Mutual connections between " << username1 << " and " << username2 << ":" << endl;
    for (const string& connection : connections1) {
        if (find(connections2.begin(), connections2.end(), connection) != connections2.end()) {
            cout << connection << endl;
        }
    }
}

bool detectCycle() {
    unordered_set<string> visited;

    for (const auto& userPair : users) {
        const string& username = userPair.first;
        if (visited.find(username) == visited.end()) {
            if (hasCycleDFS(username, "", visited)) {
                cout << "A cycle is present in the user connections." << endl;
                return true;
            }
        }
    }

    cout << "No cycle found in the user connections." << endl;
    return false;
}

bool hasCycleDFS(const string& username, const string& parent, unordered_set<string>& visited) {
    visited.insert(username);

    for (const string& connection : connections[username]) {
        if (visited.find(connection) == visited.end()) {
            if (hasCycleDFS(connection, username, visited)) {
                return true;
            }
        } else if (connection != parent) {
            
            return true;
        }
    }

    return false;
}



      void deleteUser(const string& username) {
        if (users.find(username) == users.end()) {
            cout << "Username does not exist. Please check and try again." << endl;
            return;
        }

        
        for (auto& userPair : connections) {
            vector<string>& userConnections = userPair.second;
            userConnections.erase(remove(userConnections.begin(), userConnections.end(), username), userConnections.end());
        }

        
        delete users[username];
        users.erase(username);
        connections.erase(username);

        cout << "User " << username << " has been successfully deleted." << endl;
    }
};

int main() {
    SocialNetwork socialNetwork;

    socialNetwork.addUser("riya123", "Riya", "University of ABC", 4, "Reading");
    socialNetwork.addUser("ashok456", "Ashok", "XYZ College", 2, "Photography");
    socialNetwork.addUser("alex789", "Alex", "University of ABC", 3, "Singing");
    socialNetwork.addUser("rahul985", "Rahul", "University B", 3, "Singing");
    socialNetwork.addUser("neel221", "Neel", "University A", 5, "Reading");


    socialNetwork.addConnection("riya123", "ashok456");
    socialNetwork.addConnection("riya123", "alex789");
    socialNetwork.addConnection("ashok456", "neel221");
    socialNetwork.addConnection("ashok456", "rahul985");
    socialNetwork.addConnection("neel221", "alex789");

    socialNetwork.printUserDetails("ashok456");
    socialNetwork.printConnections("ashok456");

    socialNetwork.findMates("riya123");

    socialNetwork.areConnected("riya123", "rahul985");
    socialNetwork.findPaths("riya123", "rahul985");

    socialNetwork.showContactList("riya123");
    socialNetwork.showCompleteNetwork("riya123");

    int maxDegree = socialNetwork.calculateMaxDegreeOfSeparation();
    cout<<maxDegree<<endl;


    socialNetwork.listPotentialGroups();

    socialNetwork.listLatestConnections("riya123");

    socialNetwork.showMutuals("riya123","neel221");

    socialNetwork.detectCycle();


    return 0;
}
