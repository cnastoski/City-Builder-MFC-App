/**
 * \file PointHistory.cpp
 *
 * \author Charles Owen
 */


#include "pch.h"
#include "PointHistory.h"

/// Minimum bin size
const int MIN_BIN = 2;

/// Maximum bin size
const int MAX_BIN = 10;

using namespace std;
using namespace Gdiplus;

/**
 * Constructor
 */
CPointHistory::CPointHistory()
{
    // Lists are initially empty
    mHead = nullptr;
    mTail = nullptr;

    // Random number seed generator
    std::random_device rd;

    // And seed it
    mGen.seed(rd());
}


/**
 * Destructor
 */
CPointHistory::~CPointHistory()
{
}



/**
 * Add a pointer to the collection of points.
 * \param p Point to add
 */
void CPointHistory::Add(Gdiplus::Point p) 
{
    // On first add we create the first node
    if (mHead == nullptr)
    {
        mHead = make_shared<PointBin>(MakeSize());
        mTail = mHead;
    }

    // Is the last node (tail) full?
    if (mTail->GetCnt() >= mTail->GetMax()) 
    {
        // If so, add a new tail node
        auto newTail = make_shared<PointBin>(MakeSize());
        mTail->SetNext(newTail);
        mTail = newTail;
    }

    // Assertion: Tail not is not empty
    // Add point to the tail node
    mTail->Add(p);
}

/**
 * Create a random bin size
 * \return Random size from MIN_BIN to MAX_BIN
 */
int CPointHistory::MakeSize()
{
    std::uniform_int_distribution<> dis(MIN_BIN, MAX_BIN);
    return dis(mGen);
}

/// Constructor

/**
 * Constructor for nested PointBin class
 * \param max Maximum posible loading for this bin
 */
CPointHistory::PointBin::PointBin(int max)
{
    mMax = max;
    mPoints = new Point[mMax];
}

/// Destructor
CPointHistory::PointBin::~PointBin() 
{
    delete mPoints;
}


/**
* Add a point to this bin.
* \param point Point to add to the bin
* \return true if successful, false if bin is full
*/
bool CPointHistory::PointBin::Add(Gdiplus::Point point)
{
    if (mCnt >= mMax) {
        return false;
    }

    mPoints[mCnt++] = point;

    return true;
}
