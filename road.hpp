#ifndef ROAD_HPP
#define ROAD_HPP

#include <string>
#include <cmath>
#include <iostream>

class Road
{
	private:
		std::string streetName = "";
		double distance = 0.0;
		static constexpr double EPSILON = 0.001;
	public:
		Road();
		Road (std::string streetName, double distance);
		std::string GetName () const;
		double GetDistance () const;

		bool operator== (const Road &otherRoad) const{
    		return (this->streetName == otherRoad.GetName())&&(std::fabs(this->distance - otherRoad.GetDistance()) <= this->EPSILON);
		}
		friend std::ostream &operator<< (std::ostream &out, const Road &roadToShow){
    		out << roadToShow.streetName << ": " << roadToShow.distance << "km";
    		return out;
		}
		void operator = (const Road &r){
			this->streetName = r.GetName();
			this->distance = r.GetDistance();
		}
};

#endif /*ROAD_HPP*/
