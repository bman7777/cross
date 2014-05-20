/****************************************************************/
/// \class Cross::AllocTracker
/// \ingroup Service
/// \date May 15, 2014
/// \brief Track info about the allocations that are coming and
///         going from the allocation service.  These should be
///         considered private to the rest of the system and just
///         used internal by allocation service(s).
/****************************************************************/

#ifndef ALLOCTRACKER_H_
#define ALLOCTRACKER_H_

#include <boost/unordered_map.hpp>

namespace Cross
{

template <class T>
class AllocTracker
{
public:
    AllocTracker() {}
    ~AllocTracker() {}

    void StartTrack(void* ptr, T* info);
    T* EndTrack(void* ptr);

private:
    typedef boost::unordered_map<void*, T*> TrackList;
    TrackList mAllocs;
};

/// \brief start tracking a ptr and some info related
///         to that ptr.  This will be tracked for the
///         lifetime of the ptr.
/// \param ptr - pointer to some allocation
/// \param info - some info tracked with ptr
template <class T>
void AllocTracker<T>::StartTrack(void* ptr, T* info)
{
    mAllocs[ptr] = info;
}

/// \brief stop tracking a ptr and retrieve some info
///         related to that ptr.
/// \param ptr - pointer to some allocation
/// return info - some info tracked with ptr from starttrack()
template <class T>
T* AllocTracker<T>::EndTrack(void* ptr)
{
    T* retInfo = NULL;
    typename TrackList::iterator iter = mAllocs.find(ptr);
    if(iter != mAllocs.end())
    {
        retInfo = iter->second;
        mAllocs.erase(iter);
    }

    return retInfo;
}

}


#endif /* ALLOCTRACKER_H_ */
