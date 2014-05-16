/****************************************************************/
/// \class cross::AllocTracker.h
/// \ingroup /home/brian/Documents/projects/cross/src/cross/Service/AllocTracker.h
/// \date May 15, 2014
/// \brief TODO
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

template <class T>
void AllocTracker<T>::StartTrack(void* ptr, T* info)
{
    mAllocs[ptr] = info;
}

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
