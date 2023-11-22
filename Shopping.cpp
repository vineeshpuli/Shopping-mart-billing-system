#include <cstring>
#include <string>
#include<iostream>
#include<fstream>
#include<sqlite3.h>
#include<vector>

using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);
  
    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
  
    printf("\n");
    printf("\n");
printf("\n");
printf("\n");
    return 0;
}


int callback1(void* data, int argc, char** argv, char** azColName)
{
    int i;
    vector<string>* d=reinterpret_cast<vector<string>*> (data);
    //fprintf(stderr, "%s: ", (const char*)data);
    
    for (i = 0; i < argc; i++) {
	string s=*(argv+i);
        d->push_back(s);
    }
    //data->push_back(argv[i]);
    //printf("\n");
    return 0;
}




class shopping{
    private:
    int code;
    int price;
    int discount;
    string name;

    public:
    //shopping();
    void menu();
    void admin();
    void buyer();
    void add();
    void edit();
    void rem();
    void list();
    void receipt();

};



void shopping::menu(){
    m:
    int choice;
    string email;
    string password;

    cout <<"\t\t\t\t__________________________________\n";
    cout <<"\t\t\t\t                                  \n";
    cout <<"\t\t\t\t       Shopping main menu         \n";
    cout <<"\t\t\t\t                                  \n";
    cout <<"\t\t\t\t__________________________________\n";
    cout <<"\t\t\t\t                                  \n";
    cout <<"\t\t\t\t       1)Administrator            \n";
    cout <<"\t\t\t\t                                  \n";
    cout <<"\t\t\t\t       2)Buyer                    \n";
    cout <<"\t\t\t\t                                  \n";
    cout <<"\t\t\t\t       3)Exit                     \n";
    cout <<"\t\t\t\t                                  \n";
    cout <<"\t\t\t\t       Please select:";
    cin >> choice;

    switch(choice){
        case 1:
            cout <<"\t\t\tPlease login  \n";
            cout <<"\t\t\tEmail:\n";
            cin >> email;
            cout <<"\t\t\tPassword:\n";
            cin >> password;

            if(email=="john@email.com" && password=="hello123"){
                admin();
            }
            else{
                cout <<"Invalid email/Password";
            }
            break;
        case 2:
            buyer();
            break;
        case 3:
            exit(0);
            break;
        
        default:
            cout <<"Please select from above options";
            
    }
    goto m;
}


void shopping::admin(){
    m:
    int choice;
    cout <<"\t\t\t______Administer menu________";
    cout<<"\n\n\t\t\t_____1)Add item to list_____";
    cout<<"\n\n\t\t\t_____2)Modify the product___";
    cout<<"\n\n\t\t\t_____3)Delete the product___";
    cout<<"\n\n\t\t\t_____4)Back to main menu___";
    cout<<"\n\n\t\t\tPlease enter your choice:";
    cin >> choice;

    switch(choice){
        case 1:
            add();
            break;
        case 2:
            edit();
            break;
        case 3:
            rem();
            break;
        case 4:
            menu();
            break;
        default:
            cout<<"Please select from options";

    }
    goto m;

}


void shopping::buyer(){
    m:
    int choice;
    cout<<"\t\t\t___Buyer____\n";
    cout<<"\t\t\t___1)Buy items___\n";
    cout<<"\t\t\t___2)Go back____\n";
    cout <<"\t\t\t Enter the choice:";
    cin>>choice;

    switch(choice){
        case 1:
            receipt();
            break;
        case 2:
            menu();
            break;
        default:
            cout << "Invalid choice";
    }
    goto m;
}

void shopping::add(){
    m:

    cout<<"\n\t\t\t Add new product";
    cout<<"\n\t\t\t Enter product code:";
    cin >>code;
    cout<<"\n\t\t\t Enter product name:";
    cin >> name;
    cout<<"\n\t\t\t Enter product price:";
    cin >> price;
    cout<<"\n\t\t\t Enter product discount:";
    cin >> discount;

    sqlite3* DB;
    int exit = 0;
    char* messaggeError;
    exit = sqlite3_open("shopping.db", &DB);
  
    if (exit) {
        cerr << "Error open DB" << sqlite3_errmsg(DB) <<endl;
        return;
    }
    else
	{
  
    string sql="INSERT INTO LIST(CODE,NAME,PRICE,DISCOUNT) VALUES ("+to_string(code)+",'"+name+"',"+to_string(price)+","+to_string(discount)+");";
  
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert" << endl;
        sqlite3_free(messaggeError);
	//goto m;
    }
    else{
        cout << "Records created Successfully!" << endl;
	list();
	}
  
	}
	
	sqlite3_close(DB);
	return;
}

void shopping::edit(){
	int pkey;
    cout<<"\n\t\t\t___Modify the record\n";
    cout<<"\t\t\tProduct code:";
    cin>>pkey;

    cout<<"\n\t\t\t Update new product";
    cout<<"\n\t\t\t Enter new product code:";
    cin >>code;
    cout<<"\n\t\t\t Enter new product name:";
    cin >> name;
    cout<<"\n\t\t\t Enter new product price:";
    cin >> price;
    cout<<"\n\t\t\t Enter new product discount:";
    cin >> discount;

   sqlite3* DB;
    int exit = 0;
    char* messaggeError;
    exit = sqlite3_open("shopping.db", &DB);
  
    if (exit) {
        cerr << "Error open DB" << sqlite3_errmsg(DB) <<endl;
        return;
    }
    else
	{
  
    string sql="UPDATE LIST SET CODE="+to_string(code)+", NAME='"+name+"', PRICE="+to_string(price)+", DISCOUNT="+to_string(discount)+" WHERE CODE="+to_string(pkey)+";";
  
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Insert" << endl;
        sqlite3_free(messaggeError);
	//goto m;
    }
    else{
        cout << "Records created Successfully!" << endl;
	list();
	}
  
	}
	
	sqlite3_close(DB);
	return;
    


}


void shopping::rem(){
    //fstream data,data1;
    int pkey;
    //int token=0;
    cout<<"\n\n\t\t Delete Product\n";
    cout<<"\nProduct Code:";
    cin>>pkey;

    sqlite3* DB;
    int exit = 0;
    char* messaggeError;
    exit = sqlite3_open("shopping.db", &DB);
  
    if (exit) {
        cerr << "Error open DB" << sqlite3_errmsg(DB) <<endl;
        return;
    }
    else
	{
  
    string sql="DELETE FROM LIST WHERE CODE="+to_string(pkey)+";";
  
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
    if (exit != SQLITE_OK) {
        cerr << "Error Delete" << endl;
        sqlite3_free(messaggeError);
	//goto m;
    }
    else{
        cout << "Records deleted Successfully!" << endl;
	list();
	}
  
	}
	
	sqlite3_close(DB);
	return;
    
}

void shopping::list(){
    sqlite3* DB;
    int exit = 0;
    char* messaggeError;
    exit = sqlite3_open("shopping.db", &DB);
  
    if (exit) {
        cerr << "Error open DB" << sqlite3_errmsg(DB) <<endl;
        return;
    }
    else
	{
  
    string sql="SELECT * FROM LIST;";
  
    exit = sqlite3_exec(DB, sql.c_str(),callback,NULL,&messaggeError);
    
  
	}
	
	sqlite3_close(DB);
	return;
}



void shopping::receipt(){
    
    
    int arrc[100];
    int arrq[100];
    char choice;
    int c=0;
    float amount=0;
    int dis=0;
    int total=0;

    cout <<"\n\n\t\t\t Receipt ";
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("shopping.db", &DB);
  
    if (exit) {
        std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
        return;
    }
    else
	{
        cout << "Opened Database Successfully!" << endl;
        list();
        cout<<"\n______________________________\n";
        cout<<"\n                              \n";
        cout<<"\n     Please place the order   \n";
        cout<<"\n                              \n";
        cout<<"\n______________________________\n";
        do{
	    m:
            cout<<"\n\n Enter Product code:";
            cin>>arrc[c];
            cout <<"\n\nEnter the quantity:";
            cin>>arrq[c];
            for(int i=0;i<c;i++){
                if(arrc[c]==arrc[i]){
                    cout<<"\n\nDuplicate Product Code,Try again!";
		    
                    goto m;
                }
            }
            c++;
            cout<<"\n\n Do you want to buy another product?Y/N\n";
            cin>>choice;


        }
        while(choice=='Y'|| choice=='y');

        cout<<"\n\n\t\t\t_______________Receipt___________\n";
        

        for(int i=0;i<c;i++){

            string sql="SELECT * FROM LIST WHERE CODE="+to_string(arrc[i])+";";
  	    vector<string> temp;
	    char* messaggeError;
            exit = sqlite3_exec(DB, sql.c_str(),callback1,&temp,&messaggeError);
	    code=stoi(temp[0]);
	    name=temp[1];
	    price=stoi(temp[2]);
	    discount=stoi(temp[3]);
	    amount=price*arrq[i]*(float)(100-discount)/100;
	    total=total+amount;
	    cout<<"Code of product:"<<code<<endl;
	    cout<<"Name of product:"<<name<<endl;
	    cout<<"Quantity of product:"<<arrq[i]<<endl;
	    cout <<"Amount of prooduct:"<<amount<<endl;
	    cout <<"\n\n"<<endl;
            }
           

            
        }
        sqlite3_close(DB);
    
    cout<<"\n\n____________________________________";
    cout<<"\n Total amount: "<<total<<endl;
return;
}

int main(){
    sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("shopping.db", &DB);
  
    if (exit) {
        std::cerr << "Error open DB" << sqlite3_errmsg(DB) << std::endl;
        return -1;
    }
    else
	{
        cout << "Opened Database Successfully!" << endl;
    string sql = "CREATE TABLE IF NOT EXISTS LIST(CODE INT PRIMARY KEY NOT NULL,NAME TEXT NOT NULL,PRICE INT NOT NULL,DISCOUNT INT NOT NULL);";
    //int exit = 0;
    //exit = sqlite3_open("shopping.db", &DB);
    char* messaggeError;
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
  
    if (exit != SQLITE_OK) {
        cerr << "Error Create Table" << endl;
        sqlite3_free(messaggeError);
    }
    else{
        cout << "Table is accessible" << endl;
	}
    }

    sqlite3_close(DB);

	
    shopping s;
    s.menu();
   
   

   return 0;

}



