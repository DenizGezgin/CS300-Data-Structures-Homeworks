#include <vector>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "AABB.h"
#include "BVHTree.h"


using namespace std;

std::ostream& operator<<(std::ostream& out, std::vector<std::string> v) {
    sort(v.begin(), v.end());
    string output;
    for (int i = 0; i < v.size(); i++) {
        output += v[i] + ", ";
    }
    if (output.size() > 0) {
        output = output.substr(0, output.size() - 2);
    }
    out << output;
    return out;
}

int main() {
    // agent_file contains the component information of the agent
    // actions_file contains the action that we will do
    string agent_file = "agent.txt", actions_file = "actions.txt";
    ifstream agent_in(agent_file);
    if (agent_in.fail()) {
        cout << "The agent.txt file was not found. Exiting." << endl;
        return 1;
    }
    ifstream actions_in(actions_file);
    if (actions_in.fail()) {
        cout << "The actions.txt file was not found. Exiting." << endl;
        return 1;
    }
    // The tree representing our agent
    BVHTree tree;
    string name;
    int minX, minY, maxX, maxY;
    // Read the names and locations of all the components of our agent
    while (agent_in >> name >> minX >> minY >> maxX >> maxY) {
        AABB location(minX, minY, maxX, maxY);
        tree.addBVHMember(location, name);
    }

    char action;
    // Iterate over the actions in the actions file
    while (actions_in >> action) {
        // Action to check what components from our agent collide with this object 
        if (action == 'c') {
            actions_in >> minX >> minY >> maxX >> maxY;
            AABB location(minX, minY, maxX, maxY);
            vector<string> collisions = tree.getCollidingObjects(location);
            cout << "Projectile (" << minX << ", " << minY << "), (" << maxX << ", " << maxY << ")" << endl;
            cout << "Collides with: ";
            cout << collisions << endl;
        }
        // Action to move one of our agent's components  
        else if (action == 'm') {
            actions_in >> name >> minX >> minY >> maxX >> maxY;
            AABB location(minX, minY, maxX, maxY);
            tree.moveBVHMember(name, location);
            cout << "Moved the " << name << " to the location ";
            cout << "(" << minX << ", " << minY << "), (" << maxX << ", " << maxY << ")" << endl;
        }
        // Print the state of the tree
        else if (action == 'p') {
            cout << "Current tree:" << endl;
            cout << tree << endl;
        }
    }


    cout << "------------------------------------" << endl;
    cout << tree << endl;
    cout << "------------------------------------" << endl;
    tree.moveBVHMember("right-ear", AABB(5, 0, 6, 3));
    cout << tree << endl;
    tree.moveBVHMember("right-ear", AABB(5, 1, 6, 4));
    cout << tree << endl;
    cout << "------------------------------------" << endl;
    tree.removeBVHMember("right-ear");
    cout << tree << endl;
    tree.removeBVHMember("left-ear");
    cout << tree << endl;
    tree.removeBVHMember("head-extension");
    cout << tree << endl;
    tree.removeBVHMember("right-leg2");
    cout << tree << endl;
    tree.removeBVHMember("right-leg");
    cout << tree << endl;
    cout << "------------------------------------" << endl;
    tree.removeBVHMember("torso");
    cout << tree << endl;
    tree.removeBVHMember("left-leg");
    cout << tree << endl;
  
    /*left-leg 0 0 1 3
right-leg 2 0 3 3
torso 0 3 3 7
head 1 7 3 8
left-ear 3 8 4 10
right-ear 0 8 1 10
right-leg2 3 0 4 3
head-extension 0 7 1 8*/


    return 0;
}