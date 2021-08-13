#include "ItemPallet.hpp"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

// function to return the hash value based on the first digit
unsigned int hashfct1(unsigned int sku) {
  int answer = 0;
  answer = (sku / 100000) % 10;
  return (answer);
}

// function to return the hash value based on the second digit
unsigned int hashfct2(unsigned int sku) {
  int answer = 0;
  answer = (sku / 10000) % 10;
  return (answer);
}

// function to return the hash value based on the third digit
unsigned int hashfct3(unsigned int sku) {
  int answer = 0;
  answer = (sku / 1000) % 10;
  return (answer);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct4(unsigned int sku) {
  int answer = 0;
  answer = (sku / 100) % 10;
  return (answer);
}

// function to return the hash value based on the fifth digit
unsigned int hashfct5(unsigned int sku) {
  int answer = 0;
  answer = (sku / 10) % 10;
  return (answer);
}

// function to return the hash value based on the fourth digit
unsigned int hashfct6(unsigned int sku) {
  int answer = 0;
  answer = (sku / 1) % 10;
  return (answer);
}

// Constructor for struct Item
Item::Item(string itemName, unsigned int sku)
    : itemName_(itemName), sku_(sku){};

// Load information from a text file with the given filename
// THIS FUNCTION IS COMPLETE
void ItemPallet::readTextfile(string filename) {
  ifstream myfile(filename);

  if (myfile.is_open()) {
    cout << "Successfully opened file " << filename << endl;
    string itemName;
    unsigned int sku;
    while (myfile >> itemName >> sku) {
      if (itemName.size() > 0)
        addItem(itemName, sku);
    }
    myfile.close();
  } else
    throw std::invalid_argument("Could not open file " + filename);
}

void ItemPallet::addItem(string itemName, unsigned int sku) {
  // function that adds the specified SKU to the pallet (i.e., to all hash
  // tables) declare and initialize add_item
  Item adding_item(itemName, sku);
  // use .insert to add new element item and make_pair to construct an object
  // pair
  hT1.insert(std::make_pair(sku, adding_item));
  hT2.insert(std::make_pair(sku, adding_item));
  hT3.insert(std::make_pair(sku, adding_item));
  hT4.insert(std::make_pair(sku, adding_item));
  hT5.insert(std::make_pair(sku, adding_item));
  hT6.insert(std::make_pair(sku, adding_item));
}

bool ItemPallet::removeItem(unsigned int sku) {

  bool answer = true;

  hT1.erase(hT1.find(sku));
  hT2.erase(hT2.find(sku));
  hT3.erase(hT3.find(sku));
  hT4.erase(hT4.find(sku));
  hT5.erase(hT5.find(sku));
  hT6.erase(hT6.find(sku));
  // return bool
  return answer;
}

unsigned int ItemPallet::bestHashing() {
  unsigned int min = hT1.bucket_size(0);
  unsigned int max = hT1.bucket_size(0);
  for (auto i = 1; i < 10; ++i) {
    unsigned int bucket = hT1.bucket_size(i);
    if (bucket < min) {
      min = bucket;
    } else if (bucket > max) {
      max = bucket;
    }
  }
  unsigned int best1 = max - min;

  min = hT2.bucket_size(0);
  max = hT2.bucket_size(0);
  for (auto i = 1; i < 10; ++i) {

    unsigned int bucket = hT2.bucket_size(i);
    if (bucket < min) {
      min = bucket;
    } else if (bucket > max) {
      max = bucket;
    }
  }
  unsigned int best2 = max - min;

  min = hT3.bucket_size(0);
  max = hT3.bucket_size(0);
  for (auto i = 1; i < 10; ++i) {

    unsigned int bucket = hT3.bucket_size(i);
    if (bucket < min) {
      min = bucket;
    } else if (bucket > max) {
      max = bucket;
    }
  }
  unsigned int best3 = max - min;

  min = hT4.bucket_size(0);
  max = hT4.bucket_size(0);
  for (auto i = 1; i < 10; ++i) {

    unsigned int bucket = hT4.bucket_size(i);
    if (bucket < min) {
      min = bucket;
    } else if (bucket > max) {
      max = bucket;
    }
  }
  unsigned int best4 = max - min;

  min = hT5.bucket_size(0);
  max = hT5.bucket_size(0);
  for (auto i = 1; i < 10; ++i) {

    unsigned int bucket = hT5.bucket_size(i);
    if (bucket < min) {
      min = bucket;
    } else if (bucket > max) {
      max = bucket;
    }
  }
  unsigned int best5 = max - min;

  min = hT6.bucket_size(0);
  max = hT6.bucket_size(0);
  for (auto i = 1; i < 10; ++i) {

    unsigned int bucket = hT6.bucket_size(i);
    if (bucket < min) {
      min = bucket;
    } else if (bucket > max) {
      max = bucket;
    }
  }
  unsigned int best6 = max - min;

  unsigned int array[6] = {best1, best2, best3, best4, best5, best6};
  unsigned int smallest = array[0];
  for (int i = 0; i <= 5; i++) {
    if (array[i] <= smallest && i != 5) {
      smallest = array[i];

    } else if (array[i] <= smallest && i == 5) {
      smallest = array[i];
      cout << smallest << endl;
    }
  }
  std::cout << "smallest val;ue" << smallest << std::endl;
  for (int i = 1; i <= 6; i++) {
    if (smallest == best1) {
      return 1;
    } else if (best2 == smallest) {
      return 2;
    } else if (smallest == best3) {
      return 3;
    } else if (smallest == best4) {
      return 4;
    } else if (smallest == best5) {
      return 5;
    } else if (smallest == best6) {
      return 6;
    }
  }
  return 0;
}

// ALREADY COMPLETED
size_t ItemPallet::size() {
  if ((hT1.size() != hT2.size()) || (hT1.size() != hT3.size()) ||
      (hT1.size() != hT4.size()) || (hT1.size() != hT5.size()) ||
      (hT1.size() != hT6.size()))
    throw std::length_error("Hash table sizes are not the same");

  return hT1.size();
}
