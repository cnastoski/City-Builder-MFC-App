/**
 * \file BuildingCounter.h
 *
 * \author Chris Nastoski
 *
 * A class that counts the number of buildings in the city.
 */


#pragma once


#include "TileVisitor.h"


/**
 * A class that counts the number of buildings in the city.
 */
class CBuildingCounter :
	public CTileVisitor
{
public:
	/** Get the number of buildings
	* \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }

	/** Visit a CTileBuilding object
	* \param building Building we are visiting */
	void CBuildingCounter::VisitBuilding(CTileBuilding* building)
	{
		mNumBuildings++;
	}

private:
	/// Buildings counter
	int mNumBuildings = 0;

};

