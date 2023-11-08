#include <iostream>
#include <vector>
#include <map>

using namespace std;

int id = -1;
map<string, pair<string, pair<string, int>>> acct; // mail- pass- user-id

class Users {
public:
    string username;
    string mailid;
    string pass;
    int userid;
    map<string,vector<vector<char>>>allLayouts;
    void putdata(string nm,string mail,string ps){
        username=nm;
        mailid=mail;
        pass=ps;
        userid=id;
    }

    void addLayout(vector<vector<char>>tmp,string type){
        allLayouts[type]=tmp;
    }

    void getallLayouts(){
        for (const auto& layoutEntry : allLayouts) {
        const string& layoutName = layoutEntry.first;
        const vector<vector<char>>& layout = layoutEntry.second;

        cout << "Layout Name: " << layoutName << endl;

        // Print the layout, row by row
        for (const vector<char>& row : layout) {
            for (char cell : row) {
                cout << cell << ' ';
            }
            cout << '\n';
        }

        cout << '\n'; // Add a blank line between layouts
        }
    }

   string getusername() const {
        return username;
    }

    string getmailid() const {
        return mailid;
    }

    string getpass() const {
        return pass;
    }
    int getuserid() const {
        return userid;
    }
};




class Furniture {
public:
    string name;
    int width; // vert
    int depth; // hori
    void getdata(){
        cout << "Enter furniture name: ";
        cin >> name;
        cout << "Enter furniture width: ";
        cin >> width;
        cout << "Enter furniture depth: ";
        cin >> depth;
        //cout<<"Dhh";
    }

    string getName() const {
        return name;
    }

    int getWidth() const {
        return width;
    }

    int getDepth() const {
        return depth;
    }
};

class Room {
public:
    string roomType;
    int length; // vert
    int width;  // hori
    vector<Furniture> furnitureList;
    vector<vector<char>> workspaceLayout;
    void getdata(){
        cout << "Enter Workspace type: ";
        cin >> roomType;
        cout << "Enter Workspace length: ";
        cin >> length;
        cout << "Enter Workspace width: ";
        cin >> width;
        vector<char>tmp;
        workspaceLayout.clear();
        for(int i=0;i<length;i++){
            for(int j=0;j<width;j++)
                tmp.push_back('.');
            workspaceLayout.push_back(tmp);
            tmp.clear();
        }
    }
    int getLength() const {
        return length;
    }
    string getRoomType() const {
        return roomType;
    }
    int getWidth() const {
        return width;
    }

    void addcoordinatesfurn(const Furniture& furniture, int x, int y, bool& done) {
        if (canPlaceFurniture(furniture, x, y, 1)) {
            for (int i = 0; i < length; i++) {
                for (int j = 0; j < width; j++) {
                    if (workspaceLayout[i][j] == furniture.getName()[0])
                        workspaceLayout[i][j] = '.';
                }
            }
            placeFurniture(furniture, x, y, 1);
        } else
            done = 1;
    }

  

    void removeFurniture(const Furniture& furniture){
        for(int i=0;i<length;i++){
            for(int j=0;j<width;j++){
                if(workspaceLayout[i][j]==furniture.getName()[0])
                    workspaceLayout[i][j]='.';
            }
        }
    }
   
    void addexistfurn(const Furniture& furniture,string nm){
        int i,j;
        int minx=INT_MAX,miny=INT_MAX,maxx=INT_MIN,maxy=INT_MIN;
        for(i=0;i<length;i++){
            for(j=0;j<width;j++){
                if(workspaceLayout[i][j] == nm[0]) {
                    minx=min(minx,i);
                    miny=min(miny,j);
                    maxx=max(maxx,i);
                    maxy=max(maxy,j);
                }
            }
        }
        if (minx == INT_MAX || maxx == INT_MIN || miny == INT_MAX || maxy == INT_MIN) {
            cout << "Existing furniture not found in the workspace." << endl;
            return;
        }
        bool placed = false;
        // Try to place the new furniture to the right of the existing furniture
        for (int i = minx; i <= maxx; i++) {
            for (int j = maxy + 1; j < width; j++) {
                if (canPlaceFurniture(furniture, i, j, 1)) {
                    placeFurniture(furniture, i, j, 1);
                    placed = true;
                    break;
                }
            }
            if (placed) {
                break;
            }
        }
        if(!placed) {
            // Try to place the new furniture to the bottom of the existing furniture
            for (int i = maxx+1; i <length; i++) {
                for (int j = minx; j<=miny; j++) {
                    if (canPlaceFurniture(furniture, i, j, 1)) {
                        placeFurniture(furniture, i, j, 1);
                        placed = true;
                        break;
                    }
                }
                if (placed) {
                    break;
                }
            }
        }

        if(!placed) {
            // Try to place the new furniture to the left of the existing furniture
            for (int i = minx; i <= maxx; i++) {
                for (int j = 0; j < miny; j++) {
                    if (canPlaceFurniture(furniture, i, j, 1)) {
                        placeFurniture(furniture, i, j, 1);
                        placed = true;
                        break;
                    }
                }
                if (placed) {
                    break;
                }
            }
        }
        if(!placed) {
            // Try to place the new furniture to the top of the existing furniture
            for (int i = 0; i < minx; i++) {
                for (int j = minx; j<=miny; j++) {
                    if (canPlaceFurniture(furniture, i, j, 1)) {
                        placeFurniture(furniture, i, j, 1);
                        placed = true;
                        break;
                    }
                }
                if (placed) {
                    break;
                }
            }
        }
    }


    void addFurniture(const Furniture& furniture) {
        // Try to find an available corner

        if (workspaceLayout[0][0] == '.' && canPlaceFurniture(furniture, 0, 0, 1)) {
            placeFurniture(furniture, 0, 0, 1);
            return;
        } else if (workspaceLayout[0][width - 1] == '.' && canPlaceFurniture(furniture, 0, width - 1, 0)) {
            placeFurniture(furniture, 0, width - 1, 0);
            return;
        } else if (workspaceLayout[length - 1][0] == '.' && canPlaceFurniture(furniture, length - 1, 0, 0)) {
            placeFurniture(furniture, length - 1, 0, 0);
            return;
        }

        // If all corners are filled, place in the middle
        bool placedInMiddle = false;

        for (int i = 1; i < length - 1; i++) {
            for (int j = 1; j < width - 1; j++) {
                if (workspaceLayout[i][j] == '.' && canPlaceFurniture(furniture, i, j, 1)) {
                    placeFurniture(furniture, i, j, 1);
                    placedInMiddle = true;
                    break;
                }
            }
            if (placedInMiddle) {
                break;
            }
        }
        if(placedInMiddle==false)
            cout << "You cannot place your furniture at the location you gave\n";

    }



    bool canPlaceFurniture(const Furniture& furniture, int x, int y, bool st) {

        if (st == 1) {
            for (int i = x; i < x + furniture.getWidth(); i++) {
                for (int j = y; j < y + furniture.getDepth(); j++) {
                    if (i < 0 || i >= length || j < 0 || j >= width || workspaceLayout[i][j] != '.') {
                        return false;
                    }
                }
            }
            return true;
        } else {
            int w = furniture.getWidth(); //ver
            int d = furniture.getDepth();
            int sc, sr;
            if (x == 0) {
                sc = y - d + 1;
                sr = 0;
                for (int i = sr; i < w; i++) {
                    for (int j = sc; j <= y; j++) {
                        if (i < 0 || i >= length || j < 0 || j >= width || workspaceLayout[i][j] != '.') {
                            return false;
                        }
                    }
                }
                return true;
            } else {
                sr = x - w + 1;
                sc = 0;
                for (int i = sr; i <= x; i++) {
                    for (int j = sc; j < d; j++) {
                        if (i < 0 || i >= length || j < 0 || j >= width || workspaceLayout[i][j] != '.') {
                            return false;
                        }
                    }
                }
                return true;
            }
        }
    }

     

    void placeFurniture(const Furniture& furniture, int x, int y, bool st) {
        if (st == 1) {
            for (int i = x; i < x + furniture.getWidth(); i++) {
                for (int j = y; j < y + furniture.getDepth(); j++) {
                    workspaceLayout[i][j] = furniture.getName()[0];
                }
            }
            furnitureList.push_back(furniture);
        } else {
            int w = furniture.getWidth(); //ver
            int d = furniture.getDepth();
            int sc, sr;
            if (x == 0) {
                sc = y - d + 1;
                sr = 0;
                for (int i = sr; i < w; i++) {
                    for (int j = sc; j <= y; j++) {
                        workspaceLayout[i][j] = furniture.getName()[0];
                    }
                }
                furnitureList.push_back(furniture);
            } else {
                sr = x - w + 1;
                sc = 0;
                for (int i = sr; i <= x; i++) {
                    for (int j = sc; j < d; j++) {
                        workspaceLayout[i][j] = furniture.getName()[0];
                    }
                }
                furnitureList.push_back(furniture);
            }
        }
    }

 
    double calculateSpaceUtilization() const {
        double totalFurnitureArea = 0;
        for (const Furniture& furniture : furnitureList) {
            totalFurnitureArea += furniture.getWidth() * furniture.getDepth();
        }
        return totalFurnitureArea / (length * width);
    }

    void generateWorkspaceLayout() const {
        for (const vector<char>& row : workspaceLayout) {
            for (char cell : row) {
                cout << cell << ' ';
            }
            cout << '\n';
        }
    }
    vector<vector<char>> getLayout(){
        return workspaceLayout;
    }
};

int main() {
    Users users[100]; // Array of Users
    Room workspace[100]; // Array of Rooms
    Furniture furniture[100]; // Array of Furnitures
   

    int exit = 0, exit2 = 0;
    int t, opt, opt2;
    string user, mail, p1, p2;
    start:
    cout << "Welcome to Room Sketchers!!!\nWhat do you want to do??\n\t1.Register\n\t2.Log in";
    cin >> t;

    if (t == 1) {
        cout << "Enter your Name ";
        cin >> user;
        cout << "Enter your mail id ";
        cin >> mail;
        while (1) {
            cout << "Enter your password ";
            cin >> p1;
            cout << "Confirm Password ";
            cin >> p2;
            if (p1 == p2)
                break;
            else
                cout << "Passwords don't match";
        }
        id++;
        acct[mail] = {p1, {user, id}};
        cout << "Successfully created your account. Please now log in to use our application!!!";
        users[id].putdata(user,mail,p1);
    } 
    else {
        while (1) {
            cout << "Enter your mail id ";
            cin >> mail;
            cout << "Enter your password ";
            cin >> p1;
            if (acct[mail].first == p1) {
                cout << "Successfully logged in!!";
                break;
            } else
                cout << "Email id and password don't match";
        }
    }

    while (true) {
        cout << "What do you want to do ??\n\t1.View all Workspaces \n\t2.Create a new Workspace \n\t3.Update a Workspace \n\t4.Log out  ";
        cin >> opt;
        exit = 0;
        switch (opt) {
            case 1:{
                users[id].getallLayouts();
                break;
            }
            case 2: {
                workspace[id].getdata();
                while (1) {
                    cout << "What do you want to do ??\n\t1.Add Furnitures\n\t2.Remove Furnitures\n\t3.Save and Exit  ";
                    cin >> opt2;
                    exit2 = 0;
                    switch (opt2) {
                        case 1: {
                            int t;
                            string nm;
                            furniture[id].getdata();
                            cout<<"Do you want to place it near an existing furniture ( 0-no 1- yes)";
                            cin>>t;
                            if(t==1){
                                cout<<"Enter the furniture to which you need to place this";
                                cin>>nm;
                                workspace[id].addexistfurn(furniture[id],nm);
                            }
                            else
                                workspace[id].addFurniture(furniture[id]);
                            workspace[id].generateWorkspaceLayout();
                            double spaceUtilization = workspace[id].calculateSpaceUtilization();
                            cout << "Space Utilization: " << (spaceUtilization * 100) << "%" << endl;
                            int ch;
                            while (1) {
                                cout << "Are you fine with the furniture placement?? (0 - No 1 - Yes)";
                                cin >> ch;
                                int x, y;
                                if (ch == 0) {
                                    int x, y;
                                    cout << "Enter the x-coordinate where you want to place : ";
                                    cin >> x;
                                    cout << "Enter the y-coordinate where you want to place : ";
                                    cin >> y;
                                    bool done = 0;
                                    workspace[id].addcoordinatesfurn(furniture[id], x, y, done);
                                    if (done == 1)
                                        cout << "You cannot place your furniture at the location you gave\n";
                                    workspace[id].generateWorkspaceLayout();
                                    double spaceUtilization = workspace[id].calculateSpaceUtilization();
                                    cout << "Space Utilization: " << (spaceUtilization * 100) << "%" << endl;
                                } 
                                else
                                    break;
                            }
                            break;
                        }
    
                        case 2:{
                            string fname;
                            cout<<"Enter the furniture name which you want to remove ";
                            cin>>fname;
                            workspace[id].removeFurniture(furniture[id]);
                            workspace[id].generateWorkspaceLayout();
                            double spaceUtilization = workspace[id].calculateSpaceUtilization();
                            cout << "Space Utilization: " << (spaceUtilization * 100) << "%" << endl;
                            break;
                        }
                        
                        case 3: {
                            users[id].addLayout(workspace[id].getLayout(),workspace[id].getRoomType());
                            exit2 = 1;
                            cout<<"Successfully saved Workspace";
                            break;
                        }
                    }
                    if (exit2 == 1)
                        break;
                }
                break;
            }
            case 4: {
                cout << "Thanks for Choosing Room Sketchers... \n\tLogged Out Successfully!!!";
                exit = 1;
                break;
            }
        }
        if (exit == 1)
            break;
    }
    return 0;
}
