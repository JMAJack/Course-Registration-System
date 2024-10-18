#include <iostream>
#include <string>

using namespace std;

class Admin {
private:
    string adminId;
    string name;

public:
    Admin(string id, string adminName) {
        adminId = id;
        name = adminName;
    }

    string GetAdminId() {
        return adminId;
    }

    string GetName() {
        return name;
    }

    string ToString() {
        return "Admin{id='" + adminId + "', name='" + name + "'}";
    }
};
