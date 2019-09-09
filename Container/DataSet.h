#ifndef DATA_SET_H
#define DATA_SET_H

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "Bimap.h"
#include "..\util\config.h"

/* Declarations */

// The structure that holds a column of data as well as the other relevent configuration information for the column
class Column {
    private: 
        std::string label;
        bool masked;
        std::shared_ptr<Bimap<long double, std::string>> translation_map_ptr; // Need to implement Bimap
        std::vector<long double> data;

    public:
        // Constructors
        Column();                                                 // Basic constructor
        Column(const Column &c);                                  // Copy constructor
        Column(std::vector<long double> data);                    // Data constructor
        Column(std::vector<long double> data, std::string label); // Data and label constructur

        // Access functions
        long double& at(unsigned int index) { return data.at(index); }       // Returns a the raw element at position 'index' as a reference.
        long double at(unsigned int index) const { return data.at(index); }  // Returns a the raw element at position 'index' for const. No reference.
        std::string as_string(unsigned int index) const;                     // Returns, if possible, the string translation of the value at 'index'. This is determined by the Bimap pointer.

        // Getters and Setters
        bool is_masked() const { return masked; }
        void set_masked(bool b) { masked = b; }

        const std::vector<long double>& get_data() const { return data; }
        void set_data(const std::vector<long double>& data) { this->data = data; }

        std::string get_label() const { return label; }
        void set_label(std::string label) { this->label = label; }

        Bimap<long double, std::string> get_map() { return *translation_map_ptr.get(); }               // Returns the literal Bimap object
        std::shared_ptr<Bimap<long double, std::string>> get_map_ptr() { return translation_map_ptr; } // Returns the shared_ptr of the Bimap

        void set_map(Bimap<long double, std::string> bm) { translation_map_ptr = std::make_shared<Bimap<long double, std::string>>(bm); } // Makes a new shared_ptr out of the pass-in object
        void set_map(std::shared_ptr<Bimap<long double, std::string>> bm_ptr) { translation_map_ptr = bm_ptr; }                           // Uses an existing shared_ptr object
};


class DataSet {
private:
    std::vector<std::unique_ptr<Column>> data;                             // A vector of unique_ptrs of columns. This 
    std::shared_ptr< Bimap<long double, std::string>> translation_map_ptr; // A shared_ptr to the Bimap used to store the translation between a string and its hashed value

    bool add_term(std::string term); // Attempts to add a value to the Bimap with its auto-generated hash value. Returns true if no previous value exists, false if one does.

public:
    // Constructors
    DataSet();                  // Standard constructur 
    DataSet(const DataSet &ds); // Copy constructur
    DataSet(const std::vector<std::vector<long double>> &data);                                  // External data constructor: loads the vector of vectors in and auto-generates labels for the columns
    DataSet(const std::vector<std::vector<long double>> &data, unsigned int axis);                        // External data constructor: loads the vector of vectors in and auto-generates labels for the columns. Axis = 0 means that the vectors are rows, Axis = 1 means that the vectors are columns
    DataSet(const std::vector<std::vector<long double>> &data, std::vector<std::string> labels); // External data constructor: loads the vector of vectors in and uses the labels
    DataSet(const std::vector<std::vector<long double>> &data, std::vector<std::string> labels, unsigned int axis); // External data constructor: loads the vector of vectors in and uses the labels. Axis = 0 means that the vectors are rows, Axis = 1 means that the vectors are columns

    // Access Functions
    std::vector<long double>& at(unsigned int index) const;            // Returns the column at position 'index'
    long double& at(unsigned int index_x, unsigned int index_y) const; // Returns the value at position ('index_x', 'index_y')

    std::vector<long double> get_row(unsigned int index);
    void set_row(unsigned int index, const std::vector<long double>& row);

    std::vector<long double> get_col(unsigned int index);
    Column get_raw_col(unsigned int index);
    void set_col(unsigned int index, const std::vector<long double> &col);
    void set_col(unsigned int index, const Column &col);

    // Getters and Setters
    std::vector<std::vector<long double>> get_data();           // Returns a vector of long doubles directly reflecting the raw data stored in the DataSet
    std::vector<std::vector<std::string>> get_data_as_string(); // Returns a vector of strings instead of lond doubles. All possible values as translated, the rest are just cast to strings.
    void set_data(const std::vector<std::vector<long double>> &data);   // Sets the data of the DataSet from a vector of long double vectors
    void set_data(const std::vector<Column> &data);                     // Sets the data of the DataSet from a vector of Columns. Copies over the Columns' configuration as well (masked, label, etc...)
    
};
#endif

/* Definitions */

// Default constructor
Column::Column() {
    label = DEFAULT_LABEL; // Can be adjusted in config.h
    masked = false;
    data = std::vector<long double> { }; // Empty, but initialized, vector
    translation_map_ptr = std::shared_ptr<Bimap<long double, std::string>>(nullptr); // Initialize the smart pointer onto null. Will be adjusted later
}

// Copy constructor
Column::Column(const Column& c) {
    label = c.get_label();
    masked = c.is_masked();
    data = c.get_data();

    if (c.translation_map_ptr.get() != nullptr) { // Check if the other pointer is set to null
        translation_map_ptr = c.translation_map_ptr; // Copy the shared_ptr over
    } else {
        translation_map_ptr = std::shared_ptr<Bimap<long double, std::string>>(nullptr); // Initialize the shared_ptr to be null. Will be set later
    }
}

Column::Column(std::vector<long double> data) {
    label = DEFAULT_LABEL;
    masked = false;

    translation_map_ptr = std::shared_ptr<Bimap<long double, std::string>>(nullptr);
    this->data = data; // Set the current data to a copy of the passed-in data
}      

Column::Column(std::vector<long double> data, std::string label) {
    this->label = label;
    this->data = data;
    masked = false;
    translation_map_ptr = std::shared_ptr<Bimap<long double, std::string>>(nullptr);
}

// Returns the de-hashed version of the value at 'index', if possible. If it isn't, a string of the value is returned instead.
std::string Column::as_string(unsigned int index) const {
    if (translation_map_ptr.get() == nullptr) { // Make sure that the translation map exists
        if (VERBOSE_ERRORS) std::cout << "[Error] -> as_string() -> No translation map!" << std::endl;
        throw -1;
    }

    if (index >= data.size()) { // Make sure the index is within-bounds
        if (VERBOSE_ERRORS) std::cout << "[Error] -> as_string() -> Index is out of bounds!" << std::endl;
        throw -2;
    }

    if (translation_map_ptr.get()->has_key( data.at(index) )) { // Check if the key exists
        return translation_map_ptr.get()->get_value( data.at(index) ); // Return the value associated with the key
    } else {
        return (std::to_string( data.at(index) )); // Returns a string containing the number stored at position 'index' within the vector
    }
}


