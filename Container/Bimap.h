// This class needs to be re-written. While it is currently stable, it is somewhat memory-inefficient and lacks many-to-one value-to-key support.


#ifndef BIMAP_H
#define BIMAP_H

#include <unordered_map>
#include <map>
//#include <unordered_set>

template <typename KeyType, typename ValueType>

class Bimap {

	//typedef std::unordered_set<KeyType> keys; // For many-to-one support
	typedef std::unordered_map<KeyType, ValueType> KeyMap;
	typedef std::unordered_map<ValueType, KeyType> ValueMap;
	
	public:
		/**** Constructors ****/
		Bimap() { }
		Bimap(const Bimap &bp) {left_map = bp.left_map; right_map = bp.right_map; }
		
		/**** Memeber Functions ****/
		
		const KeyMap& left()    const { return left_map;  }  // Returns a const reference to the key map
		const ValueMap& right() const { return right_map; }  // Returns a const reference to the value map
		
		// Returns true if the key exists in left_map
		bool has_key (const KeyType &key) const {
			auto ptr = left_map.find(key);
			return ptr != left_map.end();
		}

		bool has_value (const ValueType &value) const {
			auto ptr = right_map.find(value);
			return ptr != right_map.end();
		}
		
		// Returns the key for a given value
		KeyType get_key(const ValueType &value) const {
			return right_map.at(value);
		}
		
		// Returns the value for a given key
		ValueType get_value(const KeyType &key) const {
			return left_map.at(key);
		}
		
		// Symetrically adds the values to each map
		void set(const KeyType &key, const ValueType &value) {
			left_map.insert (std::pair<KeyType,   ValueType>(key, value));
			right_map.insert(std::pair<ValueType, KeyType>  (value, key));
			
		}
		
		// Removes the key value pair for a given key from both maps
		bool remove_key( const KeyType &key) {
			bool has = has_key(key);
			
			if (has) {
				ValueType value = get_value(key);
				
				left_map.erase(key);
				right_map.erase(value);
			}
			
			return has;
		}
		
		// Removes the key value pair for a given key from both maps
		bool remove_value(const ValueType &value) {
			bool has = has_value(value);
			
			if (has) {
				KeyType key = get_key(value);
				
				left_map.erase(key);
				right_map.erase(value);
			}
			
			return has;
		}
		
		unsigned long size() { return left_map.size(); }
		
	private:
		/**** Member Variabls ****/
		KeyMap left_map; 	// Key map	
		ValueMap right_map; // Value map

};

#endif 