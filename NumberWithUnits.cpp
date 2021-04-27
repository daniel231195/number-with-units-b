#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <map>
#include<math.h>
#include "NumberWithUnits.hpp"
using namespace std;
namespace ariel{

    static map<string,map<string,double> >board_units;
    const double eps=0.000001;
    NumberWithUnits::NumberWithUnits(double sum,const string& unit){
        if(board_units.count(unit)!=0){
            this->number=sum;
            this->type=unit;
        }
        else{
           throw std::invalid_argument("Unit does not exist 1");
        }
    }

    void NumberWithUnits::read_units(ifstream& units_file){
        double num1=0;
        std::string unit_1;
        std::string eq;
        double num2=0;
        std::string unit_2;

        while (units_file >> num1 >> unit_1 >> eq >> num2 >> unit_2)
        {
            board_units[unit_1][unit_2] = num2;
            board_units[unit_2][unit_1] = 1.0/num2;
            for (auto &add_u2:board_units[unit_1])
            { 

                    double sum=board_units[add_u2.first][unit_1]*num2;
                    board_units[add_u2.first][unit_2] = sum;
                    board_units[unit_2][add_u2.first] = 1.0/sum;

            }
            for (auto &add_u1:board_units[unit_2])
            { 
                    double sum=num2/board_units[add_u1.first][unit_2];
                    board_units[add_u1.first][unit_1] = 1.0/sum;
                    board_units[unit_1][add_u1.first] = sum;
            }  
        }
        //print board of unit 
        for(auto &i : board_units)
        {
            cout << "-------------------------------" << endl ; 
            cout << endl ;
            cout << "unit----->>>" << i.first << ": " ; 
            cout<< endl;
            for (auto &k: i.second)
            {
                cout <<"type to : " <<k.first << ", is : " << k.second << "|| " ;
            }
            cout<< endl;
        }        
    }
     double  changing(const std::string &unit_from,const std::string &unit_to, double num_change){
         string str_to;
         string str_from;
         for (size_t i = 0; i < unit_from.length(); i++)
        {
            if(unit_from.at(i)!='[' && unit_from.at(i)!=']' && unit_from.at(i)!=' ')
            {
                str_from=str_from+unit_from.at(i);
            }
        }
        for (size_t i = 0; i < unit_to.length(); i++)
        {
            if(unit_to.at(i)!='[' && unit_to.at(i)!=']' && unit_to.at(i)!=' ')
            {
                str_to=str_to+unit_to.at(i);
            }
        }
        if(str_to == str_from){
            return num_change;
        }
        if((board_units.count(str_from)!=0 && board_units.count(str_to)!=0))
        {
            if((board_units[str_from].count(str_to)>0)&&(board_units[str_to].count(str_from)>0)){
                double w=num_change*board_units[str_from][str_to];
                return w;
            }
            throw std::invalid_argument("Unit  from does not exist  2 ");               
            }
        throw std::invalid_argument("Unit  to does not exist  3 ");
    }


    ostream& operator<< (ostream& out, const NumberWithUnits& num){
        out <<  num.number << "[" << num.type << "]";
        return out;
    }
    istream& operator>> (istream& in, NumberWithUnits& num){
        char n=0;
        char t=0 ;
        string unit;
        in >> num.number >> n ;
        in >> t;
        while (t != ']'){
            unit+=t;
            in >> t;
        }
        if (board_units.count(unit)==0)
            {
                throw std::invalid_argument("Unit  to does not exist  4 ");
            }
        num.type = unit;
        return in;

    }

    NumberWithUnits NumberWithUnits::operator+ (const NumberWithUnits &x)const{ 
        double num=changing(x.type,this->type,x.number);
        return NumberWithUnits((this->number)+num, this->type);
    }
    NumberWithUnits NumberWithUnits::operator+ () const{
        return NumberWithUnits(+(this->number), this->type);
    }
    NumberWithUnits& NumberWithUnits::operator+= (const NumberWithUnits& x){
        double num=changing(x.type,this->type,x.number);
        this->number+=num;
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator- (const NumberWithUnits& x) const{
        double num=changing(x.type,this->type,x.number);
        return NumberWithUnits((this->number)-num, this->type);
    }
    NumberWithUnits NumberWithUnits::operator- () const{
        return NumberWithUnits(-(this->number), this->type);
    }
    NumberWithUnits& NumberWithUnits::operator-= (const NumberWithUnits& x){
        double num=changing(x.type,this->type,x.number);
        this->number-=num;
        return *this;
    }
    NumberWithUnits& NumberWithUnits::operator++ () {
        ++(this->number);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator++ (int) {
        return NumberWithUnits((this->number)++, this->type);
    }
    NumberWithUnits& NumberWithUnits::operator-- () {
        --(this->number);
        return *this;
    }
    NumberWithUnits NumberWithUnits::operator-- (int) {
        return NumberWithUnits((this->number)--, this->type);
    }
    NumberWithUnits operator* (const NumberWithUnits& num, double x) {
        return NumberWithUnits(num.number*x, num.type);
    }
    NumberWithUnits operator* (double x,const NumberWithUnits& num) {
        return NumberWithUnits(num.number*x, num.type);
    }
    NumberWithUnits& NumberWithUnits::operator*= (double x) {
        this->number*=x;
        return *this;
    }
    bool operator> (const NumberWithUnits& x, const NumberWithUnits& y){
        double num=x.number-changing(y.type,x.type,y.number);   
        return ((num>eps));
    }
    bool operator>= (const NumberWithUnits& x, const NumberWithUnits& y){
        double num=x.number-changing(y.type,x.type,y.number);
        return ((x>y)||(num==0));
    }
    bool operator< (const NumberWithUnits& x, const NumberWithUnits& y){
        double num=y.number-changing(x.type,y.type,x.number); 
        return ((eps<num));
    }
    bool operator<= (const NumberWithUnits& x, const NumberWithUnits& y){
        double num=y.number-changing(x.type,y.type,x.number);
        double p=changing(x.type,y.type,x.number);
        return ((num>eps)||(num==0)||((fabs(y.number-p)<eps)));
    }
    bool operator == (const NumberWithUnits& x, const NumberWithUnits& y){  
        double w=changing(y.type,x.type,y.number);
        return ((fabs(x.number-w)<eps));
    }
    bool operator!= (const NumberWithUnits& x, const NumberWithUnits& y){
        double num=abs(x.number)-abs(changing(y.type,x.type,y.number));
        return ((num!=0)||!((x>=y)&&(x<=y)));
    }
}
