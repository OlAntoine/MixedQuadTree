/*
 <Mix-mesher: region type. This program generates a mixed-elements mesh>
 
 Copyright (C) <2013,2017>  <Claudio Lobos>
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/gpl.txt>
 */

#include "QuadEdge.h"

namespace Clobscode
{
	
	QuadEdge::QuadEdge(){
		info.assign(3,0);
	}
	
	QuadEdge::QuadEdge(const unsigned int &point1, const unsigned int &point2){
		info.assign(3,0);
		if (point1<point2) {
			info[0]=point1;
			info[1]=point2;
		}
		else {
			info[1]=point1;
			info[0]=point2;
		}
	}
	
	QuadEdge::~QuadEdge(){
		
	}
	
	void QuadEdge::assign(const unsigned int &point1, const unsigned int &point2){
		if (point1<point2) {
			info[0]=point1;
			info[1]=point2;
		}
		else {
			info[1]=point1;
			info[0]=point2;
		}
	}
	
	bool QuadEdge::split(set<QuadEdge> &allQuadEdges, unsigned int maxp){
		
		pair<set<QuadEdge>::iterator , bool> result;
		//create possible new QuadEdge
		QuadEdge ne1(info[0],maxp);
		
		cout << "trying to insert " << ne1 << "\n";
		
		result = allQuadEdges.insert(ne1);
		
		
		if (!result.second) {
			cout << "cannot split this QuadEdge " << *this << "\n";
			return false;
		}
		else {
			
			QuadEdge ne2(info[1],maxp);
			allQuadEdges.insert(ne2);
			cout << "QuadEdge " << *this << " was split\n";
		}
		return true;

	}
	
	ostream& operator<<(ostream& o, const QuadEdge &e){
		o << e[0] << " ";
		o << e[1] << " ";
		o << e[2];
		return o;
	}
	
	bool operator==(const QuadEdge &e1, const QuadEdge &e2) {
		//this possible as QuadEdges are sorted by min index
		if (e1[0]==e2[0] && e1[1]==e2[1])
			return true;
		return false;
	}
	
	bool operator!=(const QuadEdge &e1, const QuadEdge &e2) {
		return !(e1==e2);
	}

	bool operator<(const QuadEdge &e1, const QuadEdge &e2) {
		if (e1[0]!=e2[0]){
			return e1[0]<e2[0];
		}
		return e1[1] < e2[1];
	}
	
	void QuadEdge::operator=(const QuadEdge &e){
		info[0]=e[0];
		info[1]=e[1];
		info[2]=e[2];
	}
	
}