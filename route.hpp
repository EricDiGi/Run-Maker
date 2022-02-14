#ifndef ROUTE_HPP
#define ROUTE_HPP

#include <vector>
#include <iostream>
#include <algorithm>
#include "road.hpp"

class Route
{
	private:
		double distance = 0.0;
		std::vector<Road> legs;
	public:
		void AddLeg(Road r);
		double GetDistance () const;
		int SIZE();
		bool Includes (Road roadToSearchFor) const;
		Road FIRST();
		Road LAST();
		bool operator == (const Route& otherRoute) const{
			if((this->legs.size() != otherRoute.legs.size())||(std::fabs(this->distance-otherRoute.distance) > 0.001)){
				return false;
			}
			else{
				return equal(this->legs.begin(),this->legs.end(),otherRoute.legs.begin());
			}
			return false;
		}
		friend std::ostream & operator << (std::ostream & out, const Route & routeToShow){
			out << routeToShow.distance << "km route\n";
			for(Road limp: routeToShow.legs){
				out << limp << "\n";
			}
			return out;
		}
};

#endif /*ROUTE_HPP*/
