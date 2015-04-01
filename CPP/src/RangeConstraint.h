//
// Created by mgooch on 4/1/15.
//

#ifndef HERDIMMUNITYSIMULATOR_RANGECONSTRAINT_H
#define HERDIMMUNITYSIMULATOR_RANGECONSTRAINT_H

#include <string>
#include <tclap/Constraint.h>
#include <iostream>
template<class T>
class RangeConstraint : public TCLAP::Constraint<T> {
private:
    enum RangeBounds {FINITE,UNBOUND_HIGH,UNBOUND_LOW};
    T low;
    T high;
    bool low_inclusive;
    bool high_inclusive;
    enum RangeBounds boundary_state;
    std::string _shortID;
    std::string _desc;
public:
    RangeConstraint(T val, bool h_or_l){
        //one side unbounded
        if(h_or_l){
            //true means high end being defined
            high=val;
            boundary_state=UNBOUND_LOW;
            high_inclusive=true;
        } else {
            //false means low end being defined
            low=val;
            boundary_state=UNBOUND_HIGH;
            low_inclusive=true;
        }
    }
    RangeConstraint(T val, bool h_or_l, bool val_i){
        //one side unbounded
        if(h_or_l){
            //true means high end being defined
            high=val;
            boundary_state=UNBOUND_LOW;
            high_inclusive=val_i;
        } else {
            //false means low end being defined
            low=val;
            boundary_state=UNBOUND_HIGH;
            low_inclusive=val_i;
        }
    }
    RangeConstraint(T l, T h) : low(l), high(h), low_inclusive(true),high_inclusive(true),boundary_state(FINITE){
        if(l > h){
            throw std::invalid_argument("low must be smaller in value than high");
        }
    }
    RangeConstraint(T l, T h, bool l_i, bool h_i): low(l), high(h), low_inclusive(l_i),high_inclusive(h_i),boundary_state(FINITE){
        if(l > h){
            throw std::invalid_argument("low must be smaller in value than high");
        }
        if(l == h && !(low_inclusive && high_inclusive)){
            throw std::invalid_argument("range low==high requires both low and high to be inclusive");
        }
    }
    ~RangeConstraint(){}
    virtual std::string description() const{
        return _desc;
    }
    virtual std::string shortID() const{
        return _shortID;
    }
    virtual bool check(const T &value) const{
        switch(boundary_state){
            //infinite range with one bounded side
            case UNBOUND_HIGH:
                std::cout<<"UNBOUND_HIGH check"<<std::endl;
                //low end has boundary
                if(value < low){
                    return false;
                }
                if(!low_inclusive && value == low){
                    return false;
                }
                return true;
            case UNBOUND_LOW:
                std::cout<<"UNBOUND_LOW check"<<std::endl;
                //high end has boundary
                if(value > high){
                    return false;
                }
                if(!high_inclusive && value == high){
                    return false;
                }
                return true;
            case FINITE:
                std::cout<<"FINITE check"<<std::endl;
                //finite range
                if (low == high) {
                    return value == low;
                } else {
                    if (value < low || value > high) {
                        return false;
                    }
                    if (value == low && !low_inclusive) {
                        return false;
                    }
                    if (value == high && !high_inclusive) {
                        return false;
                    }
                }
                return true;
        }
    }
};


#endif //HERDIMMUNITYSIMULATOR_RANGECONSTRAINT_H
