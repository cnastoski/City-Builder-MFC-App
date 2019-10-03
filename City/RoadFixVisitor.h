/**
 * \file RoadFixVisitor.h
 *
 * \author Chris Nastoski
 *
 * A class that visits road tiles and sets them to the correct image
 */



#pragma once


#include "TileVisitor.h"
#include "TileRoad.h"






/**
 * A class that visits road tiles and sets them to the correct image
 */
class CRoadFixVisitor :
	public CTileVisitor
{

public:


	/**
	* A class that visits road tiles and sets them as road tiles
	*/
	class CIsRoadVisitor :
		public CTileVisitor
	{
	public:
		
		/** visits all of the road tiles and sets them as roads
		* \param road The tile we want to set as a road
		* \returns the road */
		void CIsRoadVisitor::VisitRoad(CTileRoad* road)
		{
			mIsRoad = true;
		}

		/** checks to see if the tile is a road
		* \returns true if tile is a road */
		bool IsRoad() { return mIsRoad; }

	private:
		
		bool  mIsRoad = false; ///< sets the tile as a road tile
	};



	/** Visit a CTileRoad object
	* \param road Road we are visiting */
	void CRoadFixVisitor::VisitRoad(CTileRoad* road)
	{

		///intantiate all of the visitors to the adjacent tiles
		CRoadFixVisitor::CIsRoadVisitor visitor;
		CRoadFixVisitor::CIsRoadVisitor visitor2;
		CRoadFixVisitor::CIsRoadVisitor visitor3;
		CRoadFixVisitor::CIsRoadVisitor visitor4;

		///get all of the adjacent tiles
		auto roadul = road->GetAdjacent(-1, -1);
		auto roadur = road->GetAdjacent(1, -1);
		auto roadll = road->GetAdjacent(-1, 1);
		auto roadlr = road->GetAdjacent(1, 1);

		if (roadul != nullptr)
		{
			roadul->Accept(&visitor);
			if (visitor.IsRoad()) {
				ul = true;
			}
		}

		if (roadur != nullptr)
		{
			roadur->Accept(&visitor2);
			if (visitor2.IsRoad()) {
				ur = true;
			}
		}

		if (roadll != nullptr)
		{
			roadll->Accept(&visitor3);
			if (visitor3.IsRoad()) {
				ll = true;
			}
		}

		if (roadlr != nullptr)
		{
			roadlr->Accept(&visitor4);
			if (visitor4.IsRoad()) {
				lr = true;
			}
		}

		road->SetAdjacencies(ul, ur, ll, lr);

		ul = false;
		ur = false;
		lr = false;
		ll = false;
	}


private:
	bool ul = false; ///<  upper left tile
	bool ur = false; ///< upper right tile
	bool lr = false; ///< lower right tile
	bool ll = false; ///< lower left tile

};

