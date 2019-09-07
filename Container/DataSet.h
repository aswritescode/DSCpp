#ifndef DATA_SET_H
#define DATA_SET_H

#include <string>
#include <vector>
#include <memory>

#include "Bimap.h"
#include "util/config.h"

/* Declarations */

// The structure that holds a column of data as well as the other relevent configuration information for the column
class Column {
    private: 
        std::string label;
        bool masked;
        std::shared_ptr<Bimap<long double, std::string>> translation_map; // Need to implement Bimap
        std::vector<long double> data;

    public:
        // Constructors
        Column();                                                 // Basic constructor
        Column(const Column &c);                                  // Copy constructor
        Column(std::vector<long double> data);                    // Data constructor
        Column(std::vector<long double> data, std::string label); // Data and label constructur

        // Access functions
        long double& at(int index) const;        // Returns a reference to the raw element at position 'index'
        std::string  as_string(int index) const; // Returns, if possible, the string translation of the value at 'index'. This is determined by the Bimap pointer.

        // Getters and Setters
        bool is_masked() const { return masked; }
        void set_masked(bool b) { masked = b; }

        const std::vector<long double>& get_data() const { return data; }
        void set_data(const std::vector<long double>& data) { this->data = data; }

        std::string get_label() const { return label; }
        void set_label(std::string label) { this->label = label; }

        long double& at(int index) { return data.at(index); }
};


class DataSet {
private:
    std::vector<Column> data;
    std::shared_ptr< Bimap<long double, std::string>> translation_map;

    bool add_term(std::string term); // Attempts to add a value to the Bimap with its auto-generated hash value. Returns true if no previous value exists, false if one does.


public:
    // Constructors
    DataSet();                  // Standard constructur 
    DataSet(const DataSet &ds); // Copy constructur
    DataSet(const std::vector<std::vector<long double>> &data);                                  // External data constructor: loads the vector of vectors in and auto-generates labels for the columns
    DataSet(const std::vector<std::vector<long double>> &data, int axis);                        // External data constructor: loads the vector of vectors in and auto-generates labels for the columns. Axis = 0 means that the vectors are rows, Axis = 1 means that the vectors are columns
    DataSet(const std::vector<std::vector<long double>> &data, std::vector<std::string> labels); // External data constructor: loads the vector of vectors in and uses the labels
    DataSet(const std::vector<std::vector<long double>> &data, std::vector<std::string> labels, int axis); // External data constructor: loads the vector of vectors in and uses the labels. Axis = 0 means that the vectors are rows, Axis = 1 means that the vectors are columns

    // Access Functions


    // Getters and Setters

};
#endif

/* Definitions */

Column::Column() {
    label = DEFAULT_LABEL;
    masked = false;
    data = std::vector<long double> { };
    translation_map = std::shared_ptr<Bimap<long double, std::string>>(nullptr);
}

Column::Column(const Column& c) {
    label = c.get_label();
    masked = c.is_masked();
    data = c.get_data();

    if (c.translation_map.get() != nullptr) {
        translation_map = c.translation_map;
    } else {
        translation_map = std::shared_ptr<Bimap<long double, std::string>>(nullptr);
    }
}

Column::Column(std::vector<long double> data) {
    label = DEFAULT_LABEL;
    masked = false;

    translation_map = std::shared_ptr<Bimap<long double, std::string>>(nullptr);
    this->data = data;
}      

Column::Column(std::vector<long double> data, std::string label) {
    this->label = label;
    this->data = data;
    masked = false;
    translation_map = std::shared_ptr<Bimap<long double, std::string>>(nullptr);
}


