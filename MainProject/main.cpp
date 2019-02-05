#include <stdio.h>
#include <conio.h>
#include <bits/stdc++.h>
#include <fstream>
#include <string.h>
#include <iostream>
#include <sstream>
#define TABLE_SIZE 300
#define PRIME 139

using namespace std;

char foodItem[10], foodType[10], foodPrice[10];
string foodId;
int key;
int curr_size;
int *hashTable;
string value[TABLE_SIZE][100];

class Items
{

public:
    void AddItems();
    void DeleteItems();
    void SearchItem();
    void DisplayItem();
    void InsertIndex(int Index, int key, string TypeOfFood);
    void LinearProbing(int key, string foodId, int Index, string TypeOfFood);
    void SecondHash(int key, string foodId, int Index, string TypeOfFood);
    void FoodItemInsert(string foodId, string TypeOfFood);
    void SaveHashTable();
    void ReadHashTable();
    void check(string foodId, int start, int ends, string food);
};

bool isFull()
{
    return (curr_size == TABLE_SIZE);
}

int hash1(int key)
{
    return (key % TABLE_SIZE);
}

int hash2(int key)
{
    return (PRIME - (key % PRIME));
}

void Items::LinearProbing(int key, string foodId, int Index, string TypeOfFood)
{
    int i;
    Items k;
    int start = Index;
    for(i = Index; i < TABLE_SIZE;)
    {
        if(hashTable[i] == -1)
        {
            value[i][0] = foodId;
            k.InsertIndex(i, key, TypeOfFood);
            break;
        }
        i++;
        if(i == TABLE_SIZE)
        {
            int j;
            for(j = 0; j<start; j++)
            {
                value[j][0] = foodId;
                k.InsertIndex(j, key, TypeOfFood);
                break;
            }
        }
    }
    cout<<"\n Linear probing is done to insert!!\n";
};

void Items::SecondHash(int key,string foodId, int Index, string TypeOfFood)
{
    Items k;
    int index2 = hash2(key);
        int i = 1;
        while (1)
        {
            int newIndex = (Index + i * index2) % TABLE_SIZE;

            if (hashTable[newIndex] == -1)
            {
                value[newIndex][0] = foodId;
                k.InsertIndex(newIndex, key, TypeOfFood);
                break;
            }
            i++;
        }
    cout<<"\n Second Hash is done to insert!!\n";
};

void Items::FoodItemInsert(string foodId, string TypeOdFood)
{
    Items k;
    if(isFull())
    {
        cout<<"\n Table is full!!";
        return;
    }
    int key = 0;
        for(int x = 0; foodId[x] != '\0'; x++)
        {
            key += int(foodId[x]);
        }

    key = key/299;
    int Index = hash1(key);

    if (hashTable[Index] != -1)
    {
        int collisionchoice;
        cout<<"\n.....Collision occurred.....";
        cout<<"\n --> 1. LinearProbing";
        cout<<"\n --> 2. Second Hash";
        cout<<"\n............................\n";
        cout<<"\n Enter your method you want to insert: ";
        cin>>collisionchoice;
        switch(collisionchoice)
        {
            case 1 : k.LinearProbing(key, foodId, Index, TypeOdFood);
                     break;
            case 2 : k.SecondHash(key, foodId, Index, TypeOdFood);
                     break;
        }
    }
    else
    {
        value[Index][0] = foodId;
        k.InsertIndex(Index, key, TypeOdFood);
    }
    curr_size++;
};

void Items::check(string foodId, int start, int ends, string food)
{
    string x = foodId;
    int b = atoi(x.c_str());
    Items k;
    int flag = 1;
    for(int i = 0; i <TABLE_SIZE; i++)
    {
        if(b == hashTable[i])
        {
            flag = 0;
        }
    }

    if(flag == 1)
    {
        if(b >= start && b < ends)
            {
                k.FoodItemInsert(foodId, food);
            }
            else
            {
                cout<<"\n Invalid FoodID and is not between "<<start<<" and "<<ends<<" \n";
            }
    }
    else
    {
        cout<<"\n Food ID already exists\n";
    }
};

void Items::AddItems()
{
    Items k;
    int FoodItemChoice;
    cout<<"\n .....Type of food items.....";
    cout<<"\n 1. South Indian Food";
    cout<<"\n 2. North Indian Food";
    cout<<"\n 3. Chinese Food";
    cout<<"\n 4. Italian Food";
    cout<<"\n ............................\n";
    cout<<"\n Enter the type of food item: ";
    cin>>FoodItemChoice;

    if(FoodItemChoice == 1)
    {
        cout<<"\n Enter the Food id between (0 to 99): ";
        cin>>foodId;
        k.check(foodId, 0, 100, "South_Indian_Food");
    }
    else if(FoodItemChoice == 2)
    {
        cout<<"\n Enter the Food id between (100 to 199): ";
        cin>>foodId;
        k.check(foodId, 100, 200, "North_Indian_Food");
    }
    else if(FoodItemChoice == 3)
    {
        cout<<"\n Enter the Food id between (200 to 299): ";
        cin>>foodId;
        k.check(foodId, 200, 300, "Chinese_Food");
    }
    else if(FoodItemChoice == 4)
    {
        cout<<"\n Enter the Food id between (300 to 399): ";
        cin>>foodId;
        k.check(foodId, 300, 400, "Italian_Food");
    }
};

void Items::InsertIndex(int Index, int key, string TypeOfFood)
{
    Items k;
    string s = value[Index][0];
    stringstream geek(s);
    geek >> hashTable[Index];
    cout<<"\n Enter the Food type: ";
    cout<<"\n   >>>> 1. Vegetarian";
    cout<<"\n   >>>> 2. Non-Vegetarian";
    cout<<"\n enter your choice: ";
    int foodTypeChoice;
    cin>>foodTypeChoice;
    switch(foodTypeChoice)
    {
        case 1 : value[Index][2] = "Vegetarian";
                 break;
        case 2 : value[Index][2] = "Non-Vegetarian";
                 break;
    }
    cout<<"\n Enter the Food name: ";
    cin>>foodItem;
    cout<<"\n Enter the Food price: ";
    cin>>foodPrice;
    value[Index][1] = foodItem;
    value[Index][3] = foodPrice;
    cout<<"\n Food Item inserted.\n";
    k.SaveHashTable();
    return;
};

void Items::DeleteItems()
{
    Items k;
    cout<<"\n Enter the Food ID you want to Delete: ";
    cin>>foodId;
    int flag = 0;
    for(int i=0; i < TABLE_SIZE; i++)
    {
        if(value[i][0] == foodId)
        {
            flag = 1;
            hashTable[i] = -1;
            value[i][0] = "";
            value[i][1] = "";
            value[i][2] = "";
            value[i][3] = "";
            value[i][4] = "";
            k.SaveHashTable();
            cout<<"\n Food item deleted!!!\n";
        }
    }
    if(flag == 0)
    {
        cout<<"\n Food ID not found!!!\n";
    }

};

void Items::SearchItem()
{
    Items k;
    int optionId, referenceID, i;
    int modifyChoice;
    int flag = 0;
    int id;
    string ys;
    cout<<"\n Enter the Food ID you want the details: ";
    cin>>optionId;
    for(i = 0; i < TABLE_SIZE; i++)
    {
        string s = value[i][0];
        stringstream geek(s);
        geek >> referenceID;
        if(referenceID == optionId)
        {
            flag = 1;
            id = i;
            break;
        }
    }
    if(flag == 0)
    {
        cout<<"\n Food ID not found!!\n";
    }
    else
    {
            cout<<"\n   >>>>>> FoodID    : "<<value[id][0];
            cout<<"\n   >>>>>> Food Name : "<<value[id][1];
            cout<<"\n   >>>>>> Food Type : "<<value[id][2];
            cout<<"\n   >>>>>> Food Price: "<<value[id][3];
            cout<<"\n   Food ID found!!!\n";
            cout<<"\n   Want to modify any item (y/n): ";
            cin>>ys;
            if(ys == "y")
            {
                do
                {
                    cout<<"\n   -------Modify Items-----";
                    cout<<"\n   1. Food Name";
                    cout<<"\n   2. Food Type";
                    cout<<"\n   3. Food price";
                    cout<<"\n   4. Exit";
                    cout<<"\n   ------------------------\n";
                    cout<<"\n   Enter your choice to modify: ";
                    cin>>modifyChoice;
                    switch(modifyChoice)
                    {
                        case 1 : cout<<"\n  Enter the name: ";
                                 cin>>foodItem;
                                 value[id][1] = foodItem;
                                 cout<<"\n  Food name modified!!!\n";
                                 break;
                        case 2 : cout<<"\n  Enter the Food type: ";
                                 cout<<"\n      >>>> 1. Vegetarian";
                                 cout<<"\n      >>>> 2. Non-Vegetarian";
                                 cout<<"\n  Enter your choice: ";
                                 int foodTypeChoice;
                                 cin>>foodTypeChoice;
                                 switch(foodTypeChoice)
                                 {
                                    case 1 : value[id][2] = "Vegetarian";
                                             break;
                                    case 2 : value[id][2] = "Non-Vegetarian";
                                             break;
                                 }
                                 cout<<"\n  Food type modified!!!\n";
                                 break;
                        case 3 : cout<<"\n  Enter Food Price: " ;
                                 cin>>foodPrice;
                                 value[id][3] = foodPrice;
                                 cout<<"\n  Food price modified!!!\n";
                                 break;
                        case 4 : modifyChoice = 5;
                    }

                    k.SaveHashTable();

                }while(modifyChoice < 4);

            }
            else
            {
                cout<<"\n Thanks for Displaying all details!!!\n";
            }
    }
};

void Items::DisplayItem()
{
    Items k;
    string ys;
    int FoodItemChoice, i;
    cout<<"\n .....Type of food items.....";
    cout<<"\n 1. South Indian Food";
    cout<<"\n 2. North Indian Food";
    cout<<"\n 3. Chinese Food";
    cout<<"\n 4. Italian Food";
    cout<<"\n ............................\n";
    cout<<"\n Enter the type of food item you want to display: ";
    cin>>FoodItemChoice;


    cout<<"\n ----------HashTable----------";
    cout<<"\n |     Address   |    Food ID    |";
    cout<<"\n -----------------------------";
    if(FoodItemChoice == 1)
    {
        for(i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i] >= 0 && hashTable[i] <99)
                cout <<"\n |\t"<<i<<"\t|\t"<<hashTable[i]<<"\t|";
        }
    }

    if(FoodItemChoice == 2)
    {
        for(i = 0; i <= TABLE_SIZE; i++)
        {
            if (hashTable[i] >= 100 && hashTable[i] < 199)
                cout <<"\n |\t"<<i<<"\t|\t"<<hashTable[i]<<"\t|";
        }
    }

    if(FoodItemChoice == 3)
    {
        for(i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i] >= 200 && hashTable[i] < 299)
                cout <<"\n |\t"<<i<<"\t|\t"<<hashTable[i]<<"\t|";
        }
    }

    if(FoodItemChoice == 4)
    {
        for(i = 0; i < TABLE_SIZE; i++)
        {
            if (hashTable[i] >= 300 && hashTable[i] < 399)
                cout <<"\n |\t"<<i<<"\t|\t"<<hashTable[i]<<"\t|";
        }
    }
    cout<<"\n -----------------------------";
    cout<<"\n Do you want to display any food details(y/n): ";
    string yesno;
    cin>>yesno;
    if(yesno == "y")
    {
        k.SearchItem();
    }
    else
    {
        cout<<"\n Thanks for Displaying Hash Table!!!\n";
    }
};


void Items::SaveHashTable()
{
    fstream f1,f2;
    int m;
    f1.open("HashTable.txt", ios::out);
    f2.open("Records.txt", ios::out);
    for(int i = 0; i < TABLE_SIZE; i++)
    {
        m = hashTable[i];
        if(hashTable[i] != -1)
        {
            f1<<i<<" "<<m<<endl;
            f2<<i<<" "<<hashTable[i]<<" "<<value[i][0]<<" "<<value[i][1]<<" "<<value[i][2]<<" "<<value[i][3]<<endl;
        }
    }
    f1.close();
    f2.close();
};

void Items::ReadHashTable()
{
    ifstream f1,f2;
    f1.open("HashTable.txt", ios::in);
    f2.open("Records.txt", ios::in);
    int j, m;
    int f,g;
    while(f1 >>j>> m)
    {
        hashTable[j] = m;
    }
    f1.close();
    while(f2 >>f >> g>> foodId>>  foodItem>> foodType>> foodPrice)
    {
        value[f][0] = foodId;
        value[f][1] = foodItem;
        value[f][2] = foodType;
        value[f][3] = foodPrice;
    }
    f2.close();
};

int main()
{
    cout<<"\n >>>>>>     ADDING RESTAURENT MENU     <<<<<<";
    cout<<"\n >>>>>> METHOD BASED ON DOUBLE HASHING <<<<<< \n";
    Items i;
    int choice;

    hashTable = new int[TABLE_SIZE];
    curr_size = 0;
    for (int i=0; i<TABLE_SIZE; i++)
    {
        hashTable[i] = -1;
    }

    i.ReadHashTable();

    while(1)
    {
        cout<<"\n :::::::::: MENU ::::::::::";
        cout<<"\n 1. Add Items";
        cout<<"\n 2. Delete Items ";
        cout<<"\n 3. Search and Modify Items";
        cout<<"\n 4. Display Items";
        cout<<"\n 5. Exit";
        cout<<"\n :::::::::::::::::::::::::::";
        cout<<"\n\n Enter your choice: ";
        cin>>choice;

        switch(choice)
        {
            case 1 :    i.AddItems();
                        break;
            case 2 :    i.DeleteItems();
                        break;
            case 3 :    i.SearchItem();
                        break;
            case 4 :    i.DisplayItem();
                        break;
            case 5 :    exit(0);
                        break;
            default:    printf("\n Please enter valid input.\n ");
        }
    }
}
