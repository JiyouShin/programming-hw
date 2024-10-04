#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>

#include "functions.hpp"

using namespace std;

void ParseCSV(const string & filename, map<int, string> & header_cols, map<string, vector<string> > & data_map){
    ifstream file(filename);
    string line;
    bool is_header = true;

    while (getline(file, line)) {
        stringstream ss(line);
        string cell;
        char ch;
        vector<string> row;
        bool is_quote = false;

        while(ss.get(ch)) {
            if (ch == '"') {
                is_quote = !is_quote;
            }

            if (ch == ',' && !is_quote) {
                 if (!cell.empty()) {
                    row.push_back(cell);
                    cell.clear();
                }
            } else {
                cell += ch;
            }
        }
        if (!cell.empty()) {
            row.push_back(cell);
        }

        if (is_header) {
            for (int i = 0; i < row.size(); i++) {
                header_cols[i] = row[i];
                data_map[row[i]] = vector<string>(); 
            }
            is_header = false; 
        } else {
            if (header_cols.size() == row.size()) {
                for (int i = 0; i < row.size(); i++) {
                    data_map[header_cols[i]].push_back(row[i]);
                }
            }
            
        }
    }
    file.close();

    // for (const auto& pair : header_cols) {
    //     std::cout << pair.first << " : " << pair.second << std::endl;
    // }

    // for (const auto& pair : data_map) {
    //     std::cout << pair.first << " : ";
    //     for (const auto& value : pair.second) {
    //         std::cout << value << " ";
    //     }
    //     std::cout << std::endl;
    // }

}

// Sum all elements in the column  
int SumColumn(const string &column_name, map<string, vector<string> > &data_map){
    if (data_map.find(column_name) == data_map.end()) {
        return -1;
    }

    int sum = 0;
    for (const string &value_str : data_map[column_name]) {
        int value = stoi(value_str);
        sum += value;
    }
    return sum;
}


double FilterMostFrequentAvg(const string &key_col, string &value_col, map<string, vector<string> > &data_map){
    map<string, int> key_cnt_map;

    if (data_map.find(key_col) == data_map.end() || data_map.find(value_col) == data_map.end()) {
        return -1;
    }

    vector<string> &key_col_value = data_map[key_col];
    for (int i=0;i<key_col_value.size();i++) {
        if (key_cnt_map.find(key_col_value[i]) != key_cnt_map.end()) {
            key_cnt_map[key_col_value[i]]++;
        } else {
                key_cnt_map[key_col_value[i]] = 0;
        }
    }

    string most_frequent_key;
    int max_cnt = 0;
    for (const auto& pair : key_cnt_map) {
        if (pair.second > max_cnt) {
            max_cnt = pair.second;
            most_frequent_key = pair.first;
        }
    }

    int sum = 0;
    int cnt = 0;

    for (int i=0;i<key_col_value.size();i++) {
        if (key_col_value[i] == most_frequent_key) {
            sum += stoi(data_map[value_col][i]);
            cnt++;
        }
    }

    if (cnt == 0) {
        return -1;
    } else {
        return sum / cnt;
    }
}


void SumTwoColumns(std::string &value_col1, std::string &value_col2, const std::string & out_filename, std::map<int, std::string> & header_cols, map<std::string, vector<std::string> > & data_map){
    if (data_map.find(value_col1) == data_map.end() || data_map.find(value_col2) == data_map.end()) {
        return;
    }

    if (data_map[value_col1].size() != data_map[value_col2].size()){
        return;
    }

    string new_header_cols = "SumOf" + value_col1 + "And" + value_col2;
    data_map[new_header_cols] = vector<string>();
    for (int i=0;i<data_map[value_col1].size();i++) {
        int sum = stoi(data_map[value_col1][i]) + stoi(data_map[value_col2][i]);
        data_map[new_header_cols].push_back(to_string(sum));
    }

    std::ofstream output_file(out_filename);

    if (!output_file.is_open()) {
        return;
    }

    for (const auto &pair : header_cols) {
        output_file << pair.second << ",";
    }
    output_file << new_header_cols << "\n"; 

    for (int i = 0; i < data_map[value_col1].size(); i++) {
        for (const auto &pair : header_cols) {
            const string &col_name = pair.second;
            output_file << data_map[col_name][i] << ",";
        }
        output_file << data_map[new_header_cols][i] << "\n";
    }
    output_file.close();
}