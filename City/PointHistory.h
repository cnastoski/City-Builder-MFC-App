/**
* \file PointHistory.cpp
*
* \author Charles Owen
*
* Class that maintains a collection of Point objects in order.
*/

#pragma once
#include <memory>
#include <random>


/**
 * Class that maintains a collection of Point objects in order.
 */
class CPointHistory
{
public:
    CPointHistory();
    virtual ~CPointHistory();

    void Add(Gdiplus::Point p);

protected:
    /**
    * Nested class that stores up to five points in a bin.
    */
    class PointBin
    {
    public:
        PointBin(int max);
        virtual ~PointBin();

        /// Get the current count of items in this bin
        /// \return Count (zero to MaxPoints)
        int GetCnt() { return mCnt; }

        /// Get the maximum points we allow in this bin
        /// \return Maximum integer value
        int GetMax() { return mMax; }

        bool Add(Gdiplus::Point point);

        /// Get a stored point
        /// \param i Index to the point (0 to mCnt-1)
        /// \return Stored point value
        Gdiplus::Point Get(int i) { return mPoints[i]; }

        /// Get the next bin in the list
        /// \return Pointer to next bin or null if none
        std::shared_ptr<PointBin> GetNext() { return mNext; }

        /// Set the next bin in the list
        /// \param next Next pointer to set
        void SetNext(std::shared_ptr<PointBin> next) { mNext = next; }


    private:
        PointBin() = delete;

        /// Array to store the points
        Gdiplus::Point *mPoints;

        /// Maximum number of elements we can store in the array
        int mMax;

        /// Number of elements currently stored in array
        int mCnt = 0;

        /// Next bin
        std::shared_ptr<PointBin> mNext;
    };


    /// Pointer to the head of the linked list of bins
    std::shared_ptr<PointBin> mHead;

private:
    int MakeSize();


    /// Random number generator
    std::mt19937 mGen;

    /// Pointer to the tail of the linked list of bins (last node)
    std::shared_ptr<PointBin> mTail;


public:



	/** Iterator that iterates over mouse movements */
	class Iter
	{
	public:

		/** Constructor
		* \param  collection the collection we are iterating over
		* \param  node the current point bin we are in
		* \param  pos the position in the bin*/
		Iter(CPointHistory* collection, std::shared_ptr<PointBin> node,int pos) : mCollection(collection), mNode(node), mPos(pos)  {}

		/** Test for end of the iterator
		* \param other the other iterator we are comparing
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter& other) const
		{
			if (mNode != other.mNode) {
				return mNode != other.mNode;
			}
			return mPos != other.mPos;
		}

		/** Get value at current position
		 * \returns Value at mPos in the collection */
		Gdiplus::Point operator *() const { return  mNode->Get(mPos); }

		/** Increment the iterator
		 * \returns Reference to this iterator */
		const Iter& operator++()
		{
			if (mNode != nullptr) {
				if (mPos == (mNode->GetCnt()-1))
				{
					mNode = mNode->GetNext();
					mPos = 0;

				}
				else
					mPos++;
			}
			else
				mPos = 0;

			return *this;
		}

	private:
		CPointHistory* mCollection; ///< The collection of the mouse history
		
		std::shared_ptr<PointBin> mNode;  ///< a bin in the collection 

		int mPos = 0;///< Position in the bin
	};


	/** Get an iterator for the beginning of the collection
	* \returns Iter object at last location in the array */
	Iter begin() { return Iter(this, mHead, 0); }

	/** Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, nullptr, 0); }

};

