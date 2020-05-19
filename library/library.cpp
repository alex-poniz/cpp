#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#define EXECEPTION_ELEMENT_ISNOT_FOUND "Element is not found"
using namespace std;

class Book
{
private:
    string m_name;
    unsigned int m_id;
public:
    Book(const unsigned int id, const string &name) : m_id(id), m_name(name) {};
    string getName() { return m_name; };
    unsigned getId() { return m_id; };
    bool operator ==(const Book &other) {
        return m_name == other.m_name && m_id == other.m_id;

    }
};

class Library
{
public:
    vector<Book> m_library;

    Library()
    {
        //m_library.Init();
    };
    void addBook(const Book &book) {
        m_library.push_back(book);
    };

    void deleteBook(Book &book) {
        auto it = std::find(m_library.begin(), m_library.end(), book);

        if (it != m_library.end())
            m_library.erase(it);
    };

    Book& findByName(const string &name)
    {
        auto it = std::find_if(m_library.begin(), m_library.end(),
                            [&] (auto &ele) { return ele.getName() == name; } );
        if (it == m_library.end())
            throw string(EXECEPTION_ELEMENT_ISNOT_FOUND);

        return *it;
    };

    Book& findById(const unsigned int &id)
    {
        auto it = std::find_if(m_library.begin(), m_library.end(),
                            [&] (auto &ele) { return ele.getId() == id; } );
        if (it == m_library.end())
            throw string(EXECEPTION_ELEMENT_ISNOT_FOUND);

        return *it;
    };

    unsigned size() { return m_library.size(); };

};

int main(int argc, char** argv)
{
    Book b1(1, "b1");
    Book b2(2, "b2");

    Library lib;

    lib.addBook(b1);
    lib.addBook(b2);
    std::cout << "size: " << lib.size() << std::endl;

    std::cout << lib.findByName("b1").getName() << std::endl;
    std::cout << lib.findById(1).getId() << std::endl;

    lib.deleteBook(b1);

    std::cout << "size: " << lib.size() << std::endl;
    try {
        std::cout << lib.findById(1).getId() << std::endl;
    }
    catch (string e)
    {
        if (e == EXECEPTION_ELEMENT_ISNOT_FOUND)
        {
            cout << "Cannot find element with id 1" << endl;
        }
    }
    std::cout << lib.findById(2).getId() << std::endl;

    cout << "Size : " << lib.m_library.size();
    cout << "\nCapacity : " << lib.m_library.capacity();
    cout << "\nMax_Size : " << lib.m_library.max_size();
    return 0;
}




#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <stdio.h>

#include "api.h"

namespace solution {
  using namespace api;
  using namespace std;

  class Solution : public SolutionInterface {
    public:
      Solution(APICaller* api) {
        this->api = api;
        // You can initiate and calculate things here
      }

      /**
       * High-SNR packed format
       */
      double highSnrDecode(int snr) {
        // Write your code here
        double ret = 0;
        int16_t snr_16 = (int16_t)snr;
        snr_16 = 0xFFFF;
        //float myFloat = 100;
       //int16_t mantissa = reinterpret_cast<int16_t&>(snr) & (((int16_t)1 << 11) - 1);
        int16_t exponent = snr_16 >> 12;

        int mantissa =  snr_16 & 0b0000011111111111;
        int sign     = (snr_16 & 0b0000100000000000) >> 10;
       //printf("m: %X\n ", mantissa);
        std::cout << "Input: "  << std::bitset<16>(snr_16)
            << " Mantissa: "    << std::bitset<16>(mantissa)
            << " Exponent: "    << std::bitset<16>(exponent)
            << " Sign: "        << std::bitset<16>(sign) << std::endl;
       //int exponent = (snr )

        if (exponent)
        {
            if (sign)

        }
        else
        {
          ret = mantissa;
        }
        return ret;
      }

    private:
      APICaller* api;
  };
}
