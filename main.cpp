#include <string>
using std::string;
#include <sstream>
using std::istringstream;
using std::ostringstream;
#include <vector>
using std::vector;
#include <map>
using std::map;
#include <iostream>
#include <utility>
using std::pair;
using std::getline;
using std::endl;
using std::cin;
using std::cout;
#include <set>
using std::set;
#include <iomanip>
using std::fixed;
using std::setprecision;


// from clock project in the lectures
void split(string const &s, vector<string> &elems, char sep) {
    istringstream iss(s);
    string item;
    while (getline(iss, item, sep)) elems.push_back(item);
}
// from clock project in the lectures adapted to separate quantity
//and item by first space
void split_two(string const &s, vector<string> &elems, char sep) {
    istringstream iss(s);
    string item;
    if (getline(iss, item, sep)) elems.push_back(item);
    getline(iss, item);
    elems.push_back(item);
}

//struct to load items and to help with item info output
struct Items {
    //Items variable declarations
    string item_name;
    long quantity = 0;
    long price = 0;
//Items member function declarations
    Items() = default;
    Items(string in, long q, long p) : item_name(in), quantity(q), price(p){};
    Items(string j);
};

//Item struct constructor loads item name, quantity, and price
Items::Items(string j)
{
    std::vector<string> information;
    split(j, information, ',');
    item_name = information[0];
    quantity = stol(information[1]);

    price = static_cast<long>(100 * stof(information[2].substr(1)));
    //use rounding protection for price by multiplying by 100
}

//struct to load store name, location, and vector of item info
struct Store
{
    //Store struct variable declarations
    string name;
    string location;
    vector<Items> item_list;

//Store struct member function declarations
    Store() = default;
    Store(string n, string l, vector<Items> list) : name(n), location(l), item_list(list){};
};




int main()
{
    string line;
    vector<string> tmp_split_string;
    getline(cin, line);
    //get store count
    split(line, tmp_split_string, ' ');
    int store_count = stoi(tmp_split_string[0]);
    // get the number of stores from the first line
    Items item;
    vector<Items> item_vec;
    Store store;
    vector<Store> store_vec;
    string store_name;
    string store_location;
    for(int i=0;i<store_count;i++)
    {
        //loop until out of stores
        getline(cin, line);
        if (line.empty())
        {
            //restart for each new store
            continue;
        }
        else
        {
            //block of store info
            store_name = line;
            getline(cin,line);
            store_location = line;
            while(true)
            {
                getline(cin, line);
                // load the item
                if(line.empty()){
                    store = Store(store_name, store_location, item_vec);
                    store_vec.push_back(store);
                    item_vec.clear();
                    // clear information about last store before breaking
                    break;
                }
                else{
                    //item line
                    item = Items(line);
                    item_vec.push_back(item);
                }
            }
        }
    }

    getline(cin, line);
    tmp_split_string.clear();
    split(line, tmp_split_string, ' ');
    int shopping_count = stoi(tmp_split_string[0]);
    vector<pair<int, string>> shopping_list;


    for(int i=0;i<shopping_count;i++){
        // get amount of item
        getline(cin, line);
        tmp_split_string.clear();
        split_two(line, tmp_split_string, ' ');
        //account for spaces between S and Phone

        shopping_list.push_back({stoi(tmp_split_string[0]), tmp_split_string[1]});
//append to shopping list
    }

    getline(cin, line);
    //account for the last line of empty input
    set<string> distinct_item_names;
    map<string, int> map_name_qty;
    cout<<"Store Related Information (ordered by in-file order):"<<endl;
    cout<<"There are "<<store_count<<" store(s)."<<endl;
//output amount of stores

    for(int i=0;i<store_count;i++){
        for (auto item_iterable: store_vec[i].item_list){
            distinct_item_names.insert(item_iterable.item_name);
            //use set to make a list of unique items
        }
        cout<< store_vec[i].name <<" has "<<store_vec[i].item_list.size()<<" distinct items."<<endl;
    }
    cout<<endl;
    cout<<"Item Related Information (ordered alphabetically):"<<endl;
    cout<<"There are "<<distinct_item_names.size()<<" distinct item(s) available for purchase."<<endl;
    //output unique items

    for(auto item_name_iterable: distinct_item_names){
        for (auto store_iterable: store_vec){
            for (auto item_iterable2: store_iterable.item_list){
                if (item_iterable2.item_name == item_name_iterable){
                    //if current item iteration is equal to surface level item name iteration
                    if (map_name_qty.find(item_name_iterable) != map_name_qty.end()){
                        //if item name is in the map of names
                        map_name_qty[item_name_iterable] += item_iterable2.quantity;
                        //add to count of that item
                    }
                    else{
                        map_name_qty[item_name_iterable] = item_iterable2.quantity;
                    }
                    break;
                }
            }
        }
        cout<<"There are "<< map_name_qty[item_name_iterable] <<" "<<item_name_iterable<<"(s)."<<endl;
        //generate output
    }
    cout<<endl<<"Shopping:"<<endl;
    string shopping_item_name;
    int shopping_item_count;
    map <int, pair<Store, int>> map_price_store_qty;
    vector <pair<int, Store>> how_many_item_from_which_store;
    int items_still_needed;
    int total_price = 0;
    int total = 0;
    // total sum of total_price
    for(int i=0;i<shopping_count;i++)
    {
        //loop for the number of shops

        shopping_item_count = shopping_list[i].first;
        items_still_needed = shopping_item_count;
        shopping_item_name = shopping_list[i].second;
        //assign variables to values in shopping list
        cout<<"Trying to order "<<shopping_item_count<<" "<<shopping_item_name<<"(s)."<<endl;
        // search through the store lists to see how many stores that sell this item are in shopping_item_name;
        for (auto store_iter: store_vec)
        {
            for (auto item_iter: store_iter.item_list)
            {
                if (item_iter.item_name == shopping_item_name)
                {
                    //if current item iteration is the desired item name
                    map_price_store_qty.insert({item_iter.price, {store_iter, item_iter.quantity}});
                    //append pairs of key price and value-pair of store iteration and item iteration to map
                    //to keep track of counts
                }
            }
        }
        cout<< map_price_store_qty.size() <<" store(s) sell "<< shopping_item_name <<"."<<endl;

        for(auto price_store_qty : map_price_store_qty)
        {
            if (items_still_needed>0 && items_still_needed >= price_store_qty.second.second){
                //if the shopping list still needs more of that item
                //and if the store still has that item
                total_price += price_store_qty.first * price_store_qty.second.second;
                //update total price based on price of that item at that shop and its quantity
                items_still_needed -= price_store_qty.second.second;
                //update count of item taken
                how_many_item_from_which_store.push_back({price_store_qty.second.second, price_store_qty.second.first });
            }
            else if(items_still_needed > 0 && items_still_needed < price_store_qty.second.second){
                total_price += price_store_qty.first * items_still_needed;
                //update total price
                how_many_item_from_which_store.push_back({items_still_needed, price_store_qty.second.first });
                items_still_needed = 0;
                //reset before break
                break;
            }
        }

        cout<<"Total price: $"<<fixed<<setprecision(2)<<float(total_price)/100<<endl;
        //undo rounding protection
        total += total_price;
        //update total price of all item total prices
        for(auto how_many_which: how_many_item_from_which_store){
            cout<<"Order "<<how_many_which.first<<" from "<<how_many_which.second.name<<" in "<<how_many_which.second.location<<endl;
        }

        map_price_store_qty.clear();
        how_many_item_from_which_store.clear();
        total_price = 0;
        //reset variables at the end of each loop
        cout<<endl;
    }
    cout<<"Be sure to bring $"<<fixed<<setprecision(2)<<float(total)/100<<" when you leave for the stores."<<endl;
    //use set precision and vision by zero to re acquire the correct price values
}
