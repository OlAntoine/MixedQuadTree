/*
 <Mix-mesher: region type. This program generates a mixed-elements 2D mesh>

 Copyright (C) <2013,2018>  <Claudio Lobos> All rights reserved.

 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/lgpl.txt>
 */
/**
* @file Quadrant.h
* @author Claudio Lobos, Fabrice Jaillet
* @version 0.1
* @brief
**/

#ifndef Quadrant_h
#define Quadrant_h 1

#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <limits>

#include "Visitors/Visitor.h"

#include "MeshPoint.h"
#include "Point3D.h"
#include "QuadEdge.h"

using Clobscode::MeshPoint;
using Clobscode::QuadEdge;
using Clobscode::Point3D;
//using SurfMesh::SurfTriangle;
using std::vector;
using std::list;
using std::set;
using std::pair;

namespace Clobscode
{
	
	class Quadrant{
        friend class IntersectionsVisitor;
        friend class OneIrregularVisitor;
        friend class PointMovedVisitor;
        friend class SplitVisitor;
        friend class EdgeVisitor;
        friend class TransitionPatternVisitor;
        friend class SurfaceTemplatesVisitor;
        friend class RemoveSubElementsVisitor;

	public:
		
		Quadrant(vector<unsigned int> &epts, 
			   const unsigned short &ref_level);
		
		virtual ~Quadrant();

        bool accept(Visitor *v);
		
		virtual void addProjectionInfluence(const Point3D &dir);
		
		virtual const Point3D &getProjectionInfluence();
		
		virtual void noMoreProjectionInfluences();
				
		//access methods
		virtual vector<unsigned int> &getPoints();
		
		virtual bool isInside();
		
		virtual bool intersectsSurface();
		
		virtual unsigned short &getRefinementLevel();
		
		virtual bool wasShrink();
		
		virtual bool wasConsideredInProjection();
		
		virtual void resetProjectionInfluence();

        virtual list<unsigned int> &getIntersectedEdges();
		
		virtual vector<vector<unsigned int> > &getSubElements();
		
		virtual void computeMaxDistance(vector<MeshPoint> &mp);
		
        virtual double getMaxDistance();
		
		//flag for inside Quadrants that due to "inside node" moved
		//to the input domain, it must be treated as a surface
		//element by the surfacePatterns
		virtual void setSurface();
		
		virtual bool isSurface();
		
        virtual void setIntersectedEdges(list<unsigned int> &iedges);

    protected:
        
		//protected:
		vector<unsigned int> pointindex;
		vector<vector<unsigned int> > sub_elements, possibles, continuity;
        list<unsigned int> intersected_edges;
		//the level at which this Quadrant is found in the
		//the tree structure (octree). Used for optimization
		unsigned short ref_level;
		
		Point3D projection_influence;
		unsigned short n_influences;
		bool influence_commit;
		bool surface;
		
		double max_dis;
	};
	
	
	inline vector<unsigned int> &Quadrant::getPoints(){
		return pointindex;
	}
	
	inline bool Quadrant::isInside(){
        return intersected_edges.empty();
	}
	
	inline bool Quadrant::intersectsSurface(){
        return !intersected_edges.empty();
	}
	
    inline list<unsigned int> &Quadrant::getIntersectedEdges(){
        return intersected_edges;
	}
	
	inline unsigned short &Quadrant::getRefinementLevel() {
		return ref_level;
	}
	
	inline vector<vector<unsigned int> > &Quadrant::getSubElements() {
		return sub_elements;
	}
	
	inline void Quadrant::addProjectionInfluence(const Point3D &dir) {
		projection_influence += dir;
		n_influences++;
	}
	
	inline bool Quadrant::wasShrink() {
		return n_influences!=0;
	}
	
	inline const Point3D &Quadrant::getProjectionInfluence(){
		return projection_influence;
	}
	
	inline void Quadrant::noMoreProjectionInfluences(){
		if (n_influences==0) {
			return;
		}
		influence_commit = true;
		projection_influence = projection_influence / n_influences;
	}
	
	inline void Quadrant::resetProjectionInfluence() {
		projection_influence = projection_influence * 0;
		n_influences = 0;
	}
	
	inline bool Quadrant::wasConsideredInProjection(){
		return influence_commit;
	}
	
	inline void Quadrant::computeMaxDistance(vector<MeshPoint> &mp){
		Point3D p0 = mp[pointindex[0]].getPoint();
        Point3D p1 = mp[pointindex[2]].getPoint();
		max_dis = 0.3 * (p0 - p1).Norm();
	}
	
	inline double Quadrant::getMaxDistance(){
		return max_dis;
	}
	
	inline void Quadrant::setSurface(){
		surface = true;
	}
	
	inline bool Quadrant::isSurface(){
        return surface || !intersected_edges.empty();
	}
	
    inline void Quadrant::setIntersectedEdges(list<unsigned int> &iedges){
        intersected_edges = iedges;
	}
	
	std::ostream& operator<<(ostream& o,Quadrant &e);
}
#endif