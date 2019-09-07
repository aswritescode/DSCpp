#ifndef DATA_SET_H
#define DATA_SET_H

#include <string>
#include <vector>
// #include "util/config.h"

/* Declerations */

// The structure that holds a column of data as well as the other relevent configuration information for the column
class Column {
    private: 
        std::string label;
        bool masked;
        //shared_ptr<Bimap<long double, std::string> translation_map> translation_map; // Need to implement Bimap
        std::vector<long double> data;

    public:
        Column();                                                 // Basic constructor
        Column(const Column& c);                                  // Copy constructor
        Column(std::vector<long double> data);                    // Data constructor
        Column(std::vector<long double> data, std::string label); // Data and label constructur

        long double& at(int index) const;        // Returns a reference to the raw element at position 'index'
        std::string  as_string(int index) const; // Returns, if possible, the string translation of the value at 'index'. This is determined by the Bimap pointer.

        bool is_masked(int index) const; 
        void set_masked(bool b) const;

        std::vector<long double>& get_data() const;
        void set_data(const std::vector<long double>& data);
};


class DataSet {
private:
    std::vector<Column> data;
    //Bimap<long double, std::string> translation_map;

    bool add_term(std::string term); // Attempts to add a value to the Bimap with its auto-generated hash value. Returns true if no previous value exists, false if one does.


public:
    DataSet();                  // Standard constructur 
    DataSet(const DataSet &ds); // Copy constructur
    DataSet(const std::vector<std::vector<long double>> &data);                                  // External data constructor: loads the vector of vectors in and auto-generates labels for the columns
    DataSet(const std::vector<std::vector<long double>> &data, std::vector<std::string> labels); // External data constructor: loads the vector of vectors in and uses the labels


};
#endif

/* Definitions */