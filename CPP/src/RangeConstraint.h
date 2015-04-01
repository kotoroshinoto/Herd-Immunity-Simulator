//
// Created by mgooch on 4/1/15.
//

#ifndef HERDIMMUNITYSIMULATOR_RANGECONSTRAINT_H
#define HERDIMMUNITYSIMULATOR_RANGECONSTRAINT_H

#include <string>
#include <tclap/Constraint.h>
#include <iostream>

#include <sstream>
#include <limits>
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
        std::stringstream ss_short;
        std::stringstream ss_long;
        std::numeric_limits<T> limits;
        if(h_or_l){
            //true means high end being defined
            high=val;
            boundary_state=UNBOUND_LOW;
            high_inclusive=true;
            ss_short<<'['<<limits.min()<<" - "<<high<<']';
            ss_long<<"value in range: "<<'['<<limits.min()<<" - "<<high<<']';
            _desc =ss_long.str();
            _shortID=ss_short.str();
        } else {
            //false means low end being defined
            low=val;
            boundary_state=UNBOUND_HIGH;
            low_inclusive=true;
            ss_short<<'['<<low<<" - "<<limits.max()<<']';
            ss_long<<"value in range: "<<'['<<low<<" - "<<limits.max()<<']';
            _desc =ss_long.str();
            _shortID=ss_short.str();
        }
    }
    RangeConstraint(T val, bool h_or_l, bool val_i){
        std::stringstream ss_short;
        std::stringstream ss_long;
        std::numeric_limits<T> limits;
        //one side unbounded
        if(h_or_l){
            //true means high end being defined
            high=val;
            boundary_state=UNBOUND_LOW;
            high_inclusive=val_i;
            ss_short<<'['<<limits.min()<<" - "<<high<<high_inclusive ? ']' : ')';
            ss_long<<"value in range: "<< '['<<limits.min()<<" - "<<high<<high_inclusive ? ']' : ')';
            _desc =ss_long.str();
            _shortID=ss_short.str();
        } else {
            //false means low end being defined
            low=val;
            boundary_state=UNBOUND_HIGH;
            low_inclusive=val_i;
            ss_short<<low_inclusive ? '[' : '('<<low<<" - "<<limits.max()<<']';
            ss_long<<"value in range: "<<low_inclusive ? '[' : '('<<low<<" - "<<limits.max()<<']';
            _desc =ss_long.str();
            _shortID=ss_short.str();
        }
    }
    RangeConstraint(T l, T h) : low(l), high(h), low_inclusive(true),high_inclusive(true),boundary_state(FINITE){
        if(l > h){
            throw std::invalid_argument("low must be smaller in value than high");
        }

        std::stringstream ss_short;
        std::stringstream ss_long;

        ss_short<<'['<<low<<" - "<<high<<']';
        ss_long<<"value in range: "<<'['<<low<<" - "<<high<<']';
        _desc =ss_long.str();
        _shortID=ss_short.str();
    }
    RangeConstraint(T l, T h, bool l_i, bool h_i): low(l), high(h), low_inclusive(l_i),high_inclusive(h_i),boundary_state(FINITE){
        if(l > h){
            throw std::invalid_argument("low must be smaller in value than high");
        }
        if(l == h && !(low_inclusive && high_inclusive)){
            throw std::invalid_argument("range low==high requires both low and high to be inclusive");
        }

        std::stringstream ss_short;
        std::stringstream ss_long;

        ss_short<<low_inclusive ? '[' : '('<<low<<" - "<<high<<high_inclusive ? ']' : ')';
        ss_long<<"value in range: "<<low_inclusive ? '[' : '('<<low<<" - "<<high<<high_inclusive ? ']' : ')';
        _desc =ss_long.str();
        _shortID=ss_short.str();

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
//                std::cout<<"UNBOUND_HIGH check"<<std::endl;
                //low end has boundary
                if(value < low){
                    return false;
                }
                if(!low_inclusive && value == low){
                    return false;
                }
                return true;
            case UNBOUND_LOW:
//                std::cout<<"UNBOUND_LOW check"<<std::endl;
                //high end has boundary
                if(value > high){
                    return false;
                }
                if(!high_inclusive && value == high){
                    return false;
                }
                return true;
            case FINITE:
//                std::cout<<"FINITE check"<<std::endl;
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
