#include<bits/stdc++.h>
using namespace std;

int id = -1;
map<string, pair<string, pair<string, int>>> acct; // mail- pass- user-id

bool isStrongPassword(string& password) {
    // Check the length of the password
    if (password.length() < 8) {
        cout << "Password must be at least 8 characters long.\n";
        return false;
    }

    // Check for at least one uppercase letter
    bool hasUppercase = false;
    // Check for at least one lowercase letter
    bool hasLowercase = false;
    // Check for at least one digit
    bool hasDigit = false;
    // Check for at least one special character
    bool hasSpecialChar = false;

    for (char ch : password) {
        if (isupper(ch)) {
            hasUppercase = true;
        } else if (islower(ch)) {
            hasLowercase = true;
        } else if (isdigit(ch)) {
            hasDigit = true;
        } else if (ispunct(ch)) {
            hasSpecialChar = true;
        }
    }

    // Check if all criteria are met
    if (hasUppercase && hasLowercase && hasDigit && hasSpecialChar) {
        cout << "Strong password!\n";
        return true;
    } else {
        cout << "Password must contain at least one uppercase letter, one lowercase letter, one digit, and one special character.\n";
        return false;
    }
}


// Function to center the text within a given width
void printCentered(const string& text, int width) {
    int len = text.length();
    int padding = (width - len) / 2;
    cout << setw(padding + len) << text << endl;
}

bool isValidEmail(const std::string& email) {
    // Regular expression for a simple email validation
    std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");

    // Test the email against the regular expression
    return std::regex_match(email, emailRegex);
}

void printCompanyInfo() {
    cout << string(80, '=') << endl;
    printCentered("Welcome to Room Sketchers!", 80);
    cout << string(80, '=') << endl;

    // Add more formatted company information and features
    printCentered("Company Name: Room Sketchers", 80);
    printCentered("Mission: To provide innovative room designing solutions", 80);
   
    cout << string(80, '-') << endl;
    printCentered("Features:", 80);
    printCentered(" - Create and view different workspaces", 80);
    printCentered(" - Add and remove furniture in your workspace", 80);
    printCentered(" - Save and manage your room layouts", 80);
    cout << string(80, '-') << endl;

    cout << string(80, '=') << endl;
}


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
   
   
    void deletelayout(string nm){
        allLayouts.erase(nm);
        cout<<"Deleted successfully \n";
        cout<<"Updated layouts \n";
        getallLayouts();
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
        cout << "Enter Workspace name: ";
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

 /*   void addcoordinatesfurn(const Furniture& furniture, int x, int y, bool& done) {
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
*/
 

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
            j=maxy+1;
                if (canPlaceFurniture(furniture, i, j, 1)) {
                    placeFurniture(furniture, i, j, 1);
                    placed = true;
                    break;
                }
        }
       
        if(!placed) {
           
            // Try to place the new furniture to the bottom of the existing furniture
                i=maxx+1;
                for (int j = minx; j<=miny; j++) {
                    if (canPlaceFurniture(furniture, i, j, 1)) {
                        placeFurniture(furniture, i, j, 1);
                        placed = true;
                        break;
                    }
                }
        }

        if(!placed) {
               
            // Try to place the new furniture to the left of the existing furniture
            for (int i = minx; i <= maxx; i++) {
                j=0;      
                    if (canPlaceFurniture(furniture, i, j, 1)) {
                        placeFurniture(furniture, i, j, 1);
                        placed = true;
                        break;
                    }
            }
        }
 
        if(!placed) {
            // Try to place the new furniture to the top of the existing furniture
                i=0;
                for (int j = minx; j<=miny; j++) {
                    if (canPlaceFurniture(furniture, i, j, 1)) {
                        placeFurniture(furniture, i, j, 1);
                        placed = true;
                        break;
                    }
                }
        }

    }


    void alternateexistfurn(const Furniture& furniture,string nm){
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
        while(!placed)  {  
        // Try to place the new furniture to the right of the existing furniture
        for (int i = minx; i <= maxx; i++) {
            j=maxy+1;
                if (canPlaceFurniture(furniture, i, j, 1)) {
                    placeFurniture(furniture, i, j, 1);
                    placed = true;
                    break;
                }
        }
       
        if(!placed) {
           
            // Try to place the new furniture to the bottom of the existing furniture
                i=maxx+1;
                for (int j = minx; j<=miny; j++) {
                    if (canPlaceFurniture(furniture, i, j, 1)) {
                        placeFurniture(furniture, i, j, 1);
                        placed = true;
                        break;
                    }
                }
        }

        if(!placed) {
            // Try to place the new furniture to the left of the existing furniture
            for (int i = minx; i <= maxx; i++) {
                j=0;      
                    if (canPlaceFurniture(furniture, i, j, 1)) {
                        placeFurniture(furniture, i, j, 1);
                        placed = true;
                        break;
                    }
            }
        }
 
        if(!placed) {
            // Try to place the new furniture to the top of the existing furniture
                i=0;
                for (int j = minx; j<=miny; j++) {
                    if (canPlaceFurniture(furniture, i, j, 1)) {
                        placeFurniture(furniture, i, j, 1);
                        placed = true;
                        break;
                    }
                }
        }
        }

    }

    void addFurniture(const Furniture& furniture) {

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

    void alternatepos(const Furniture& furniture){
        int i,j;
        for(i=0;i<length;i++){
            for(j=0;j<width;j++){
                if(workspaceLayout[i][j]==furniture.getName()[0]){
                    workspaceLayout[i][j]='*';
                    break;
                }
            }
        }
        for(i=0;i<length;i++){
            for(j=0;j<width;j++){
                if(workspaceLayout[i][j]==furniture.getName()[0]){
                    workspaceLayout[i][j]='.';
                }
            }
        }
        for(i=0;i<length;i++){
            for(j=0;j<width;j++){
                if(workspaceLayout[i][j]=='.' && canPlaceFurniture(furniture,i,j,1)){
                    placeFurniture(furniture, i, j, 1);
                    return;
                }
                else if(workspaceLayout[i][j]=='.' && canPlaceFurniture(furniture,i,j,0)){
                    placeFurniture(furniture, i, j, 1);
                    return;
                }
            }
        }
      /*  bool plc=0;
        for(i=0;i<length;i++){
            for(j=0;j<width;j++){
                if((workspaceLayout[i][j]=='.' || workspaceLayout[i][j]==furniture.getName()[0])  && canPlaceFurniture(furniture,i,j,1)) {
                    alternateplacefurniture(furniture,i,j,1);
                    plc=1;
                    break;
                }
                else if(workspaceLayout[i][j]=='.' && canPlaceFurniture(furniture,i,j,0)) {
                    alternateplacefurniture(furniture,i,j,0);
                    plc=1;
                    break;
                }
            }
            if(plc==1)
                break;
        }
        */
    }    


    void finalize(const Furniture& furniture){
        int i,j;
        for(i=0;i<length;i++){
            for(j=0;j<width;j++){
                if(workspaceLayout[i][j]=='*')
                    workspaceLayout[i][j]='.';
            }
        }
        furnitureList.push_back(furniture);
    }

    void alternateplacefurniture(const Furniture& furniture,int x,int y,bool st){
     
        int i,j;
         if (st == 1) {
             for(i=0;i<length;i++){
                 for(j=0;j<width;j++){
                     if(workspaceLayout[i][j]==furniture.getName()[0])
                        workspaceLayout[i][j]='*';
                 }
             }
            for (int i = x; i < x + furniture.getWidth(); i++) {
                for (int j = y; j < y + furniture.getDepth(); j++) {
                    workspaceLayout[i][j] = furniture.getName()[0];
                }
            }
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
            } else {
                sr = x - w + 1;
                sc = 0;
                for (int i = sr; i <= x; i++) {
                    for (int j = sc; j < d; j++) {
                        workspaceLayout[i][j] = furniture.getName()[0];
                    }
                }
            }
        }
   
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

    void existalternate(Furniture& furniture){
         int i,j;
         bool loop=0;
        for(i=0;i<length;i++){
            for(j=0;j<width;j++){
                if(workspaceLayout[i][j]==furniture.getName()[0]){
                    //cout<<"hii";
                    loop=1;
                    workspaceLayout[i][j]='*';
                    break;
                }
            }
            if(loop==1)
                break;
        }
        for(i=0;i<length;i++){
            for(j=0;j<width;j++){
                if(workspaceLayout[i][j]==furniture.getName()[0]){
                    workspaceLayout[i][j]='.';
                }
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

    void generateWorkspaceLayout()  {
        int i, j;
        cout<<"Layout Name : "<<getRoomType()<<endl;
        cout<<endl;
        cout << string(80, '=') << endl;
        cout<<endl;
        for (i = 0; i < length; i++) {
            // Calculate padding for centering each row
            int padding = (80 - (width * 2)) / 2;
       
            // Print leading padding
            cout << setw(padding) << "";
       
            for (j = 0; j < width; j++) {
                if (workspaceLayout[i][j] == '*')
                    cout << ". ";
                else
                    cout << workspaceLayout[i][j] << " ";
            }
       
            // Print trailing padding and move to the next line
            cout << setw(padding) << "" << endl;
        }
        cout<<endl;
        cout << string(80, '=') << endl;
         cout<<endl;
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
 
        printCompanyInfo();

    printCentered("What would you like to do?", 80);
    printCentered("1. Register", 80);
    printCentered("2. Log in", 80);
     cout<<endl;
   cout << string(80, '=') << endl;
    cout<<endl;
    cin >> t;
   
   
    if (t == 1) {
        cout << "Enter your Name : ";
        cin >> user;
        mailid:
        cout << "Enter your mail id : ";
        cin >> mail;
        if(isValidEmail(mail)==0) {
            cout<<"Invalid Mail format!!!\nTry again\n";
            goto mailid;
        }
        while (1) {
            pass:
            cout << "Enter your password : ";
            cin >> p1;
            /*if(isStrongPassword(p1)==0) {
                cout<<"Your password is not so strong!!!\nTry again\n";
                goto pass;
            }*/
            cout << "Confirm Password : ";
            cin >> p2;
            if (p1 == p2)
                break;
            else
                cout << "Passwords don't match!!!\nPlease Try again \n";
        }
        id++;
        acct[mail] = {p1, {user, id}};
        cout << "Successfully created your account. Please now log in to use our application!!!\n";
        goto start;
        users[id].putdata(user,mail,p1);
    }
    else {
        while (1) {
            cout << "Enter your mail id : ";
            cin >> mail;
            cout << "Enter your password : ";
            cin >> p1;
            if (acct[mail].first == p1) {
                cout << "Successfully logged in!!\n";
                break;
            } else
                cout << "Email id and password don't match!!!\nPlease Try again \n";
        }
    }

    while (true) {
         cout<<endl;
         cout << string(80, '=') << endl;
          cout<<endl;
        printCentered("What do you want to do?", 80);
        printCentered("1. View all Workspaces", 80);
        printCentered("2. Create a new Workspace", 80);
        printCentered("3. Update a Workspace", 80);
        printCentered("4. Remove Workspace", 80);
        printCentered("5. Get Feedback",80);
        printCentered("5. Log out", 80);
         cout<<endl;
        cout << string(80, '=') << endl;
         cout<<endl;
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
                     cout<<endl;
                    cout << string(80, '=') << endl;
                     cout<<endl;
                    printCentered("What do you want to do?", 80);
                    printCentered("1. Add furnitures", 80);
                    printCentered("2. Remove Furnitures", 80);
                    printCentered("3. Save and Exit", 80);
                     cout<<endl;
                    cout << string(80, '=') << endl;
                     cout<<endl;
                    cin >> opt2;
                    exit2 = 0;
                    switch (opt2) {
                        case 1: {
                            int t;
                            string nm;
                            furniture[id].getdata();
                            cout<<"Do you want to place it near an existing furniture ( 0-no 1- yes) : ";
                            cin>>t;
                            if(t==1){
                                cout<<"Enter the furniture to which you need to place this : ";
                                cin>>nm;
                                workspace[id].addexistfurn(furniture[id],nm);
                            }
                            else
                                workspace[id].addFurniture(furniture[id]);
                            workspace[id].generateWorkspaceLayout();
                            double spaceUtilization = workspace[id].calculateSpaceUtilization();
                            cout << "Space Utilization: " << (spaceUtilization * 100) << "%" << endl;
                            int ch;
                         
                            cout << "Are you fine with the furniture placement?? (0 - No 1 - Yes) : ";
                            cin >> ch;
                            int x, y;
                            if(ch==0 && t==1){
                                while(ch==0 ){
                                    workspace[id].existalternate(furniture[id]);
                                //    cout<<"hii";
                                    workspace[id].alternateexistfurn(furniture[id],nm);
                                    workspace[id].generateWorkspaceLayout();
                                    cout << "Are you fine with the furniture placement?? (0 - No 1 - Yes) : ";
                                    cin >> ch;
                                }
                            }
                            else {
                                while (ch == 0) {
                                  /*  int x, y;
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
                                    cout << "Space Utilization: " << (spaceUtilization * 100) << "%" << endl;*/
                                   
                                    workspace[id].alternatepos(furniture[id]);
                                    workspace[id].generateWorkspaceLayout();
                                //    workspace[id].generate();
                                    cout << "Are you fine with the furniture placement?? (0 - No 1 - Yes) : ";
                                    cin >> ch;
                                }
                            }
                            workspace[id].finalize(furniture[id]);
                            break;
                        }
   
                        case 2:{
                            string fname;
                            cout<<"Enter the furniture name which you want to remove :  ";
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
                            cout << "Successfully saved Workspace.\n";
                            break;
                        }
                        default: {
                            cout << "Invalid choice. Please try again.\n";
                            break;
                        }
                    }
                    if (exit2 == 1)
                        break;
                }
                break;
            }
            case 4:{
                users[id].getallLayouts();
                string lay;
                cout << "Enter the layout you want to delete : ";
                cin >> lay;
                users[id].deletelayout(lay);
                break;
            }
            case 5:{
                string st,msg;
                users[id].getallLayouts();
                printCentered("Enter the workspace which you want to send to get Feedback",80);
                cout<<endl;
                cin>>st;
                PrintCentered("What message you want to additionally specify to get better feedback",80);
                cout<<endl;
                cin>>msg;
                givedesignerinfo();
                printCentered("Whi designer you want to share your layout ( Enter their Did) ",80);
                cin>>id;
                putfeedback(Did,st,msg);
                break;
            }
            case 6: {
                printCentered("Thanks for choosing Room Sketchers.", 80);
                printCentered("Logged Out Successfully!", 80);
                exit = 1;
                break;
            }
            default: {
                printCentered("Invalid choice. Please try again.", 80);
                break;
            }
        }
        if (exit == 1)
            break;
    }
    goto start;
    return 0;
}
