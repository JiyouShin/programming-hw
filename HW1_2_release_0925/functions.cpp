#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <list>
#include "json/json.h"
#include <algorithm>
#include <memory>

using namespace std;

void ParseJSON(const string filename, Json::Value & json_object){
    ifstream file(filename, ifstream::binary);
    
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    Json::CharReaderBuilder readerBuilder;
    string errs;
    bool ok = Json::parseFromStream(readerBuilder, file, &json_object, &errs);
    if (!ok) {
        cerr << "Json Parsing Error" << endl;
    }

    file.close();
}

unique_ptr<string> CheckTarget(const Json::Value & json_object, string & target_key){
    if (json_object.isMember(target_key) && json_object[target_key].isString()) {
        unique_ptr<string> json_value(new string(json_object[target_key].asString()));
        return json_value;
    } else {
        return nullptr;
    }
}


void CompleteList(const Json::Value & json_object,  std::list<std::string> & empty_list){
    vector<string> keys = json_object.getMemberNames();
    sort(keys.rbegin(), keys.rend());

    for (const auto& key: keys) {
        if (json_object[key].isString()) {
            empty_list.push_back(json_object[key].asString());
        } 
    }

    if (empty_list.size() == 0) {
        empty_list.push_back("NO_STRING");
    }
}

void SumTwoMembers(std::string &key1, std::string &key2, const std::string & out_filename, Json::Value & json_object){
    ofstream output_file(out_filename);
    Json::StyledWriter writer;
    
    if (!json_object.isMember(key1) || !json_object.isMember(key2)) {
        cerr << "key1 or key2 is not a member of json object" << endl;
        return;
    }

    auto json_key1 = json_object[key1];
    auto json_key2 = json_object[key2];

    if (!json_key1.isArray() || !json_key2.isArray()) {
        cerr << "key1 or key2 is not an array" << endl;
        return;
    }

    if ((json_key1.size() == json_key2.size()) && !json_key1.empty() && !json_key2.empty()) {
        Json::Value arr(Json::arrayValue);
        for (int i=0; i < json_key1.size(); i++) {
            if (!json_key1[i].isInt() || !json_key2[i].isInt()) {
                cerr << "There is an element which is not int" << endl;
                return;
            }
            int sum = json_key1[i].asInt() + json_key2[i].asInt();
            arr.append(sum);
        }
        json_object["SumOf" + key1 + "And" + key2]  = arr;
        output_file << writer.write(json_object);
    } else {
        output_file << writer.write(json_object);
    }
    output_file.close();
}