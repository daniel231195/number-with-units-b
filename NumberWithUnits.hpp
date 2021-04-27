
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

namespace ariel {
    class NumberWithUnits{

        private:
            double number;
            std::string type;

        public:
            NumberWithUnits(double sum,const string& unit);
            ~NumberWithUnits(){};
            static void read_units(ifstream& units_file);
            //friend bool compare(const NumberWithUnits& x, const NumberWithUnits& y);
            friend double changing(const string unit_from,const string unit_to, double num_change);

            // in & out
            friend ostream& operator<< (ostream& out, const NumberWithUnits& num);
            friend istream& operator>> (istream& in, NumberWithUnits& num);
            //artm +
            NumberWithUnits operator+ (const NumberWithUnits& x)const;
            NumberWithUnits operator+ () const;
            NumberWithUnits& operator+= (const NumberWithUnits& x);
            //artm -
            NumberWithUnits operator- (const NumberWithUnits& x)const;
            NumberWithUnits operator- ()const;
            NumberWithUnits& operator-= (const NumberWithUnits& x);

            // ++ & --
            NumberWithUnits& operator++ ();
            NumberWithUnits operator++ (int);
            NumberWithUnits& operator--();
            NumberWithUnits operator-- (int);

            // *
            friend NumberWithUnits operator* (const NumberWithUnits& num, double x);
            friend NumberWithUnits operator* (double x,const NumberWithUnits& num);
            NumberWithUnits& operator*= (double x);

            // bool
            friend bool operator> (const NumberWithUnits& x, const NumberWithUnits& y);
            friend bool operator>= (const NumberWithUnits& x, const NumberWithUnits& y);
            friend bool operator< (const NumberWithUnits& x, const NumberWithUnits& y);
            friend bool operator<= (const NumberWithUnits& x, const NumberWithUnits& y);
            friend bool operator== (const NumberWithUnits& x, const NumberWithUnits& y);
            friend bool operator!= (const NumberWithUnits& x, const NumberWithUnits& y);
        };
}