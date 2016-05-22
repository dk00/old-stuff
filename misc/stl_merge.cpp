template<typename BidirectionalIterator>
void inplace_merge(BidirectionalIterator first,BidirectionalIterator middle,
                                               BidirectionalIterator last)
{
    typedef typename iteratortraits<BidirectionalIterator>::
    valuetype ValueType;
    typedef typename iteratortraits<BidirectionalIterator>::
    differencetype DistanceType;
    glibcxxfunctionrequires(MutableBidirectionalIteratorConcept
                                        <BidirectionalIterator>)
    glibcxxfunctionrequires(LessThanComparableConcept<ValueType>)
    glibcxxrequiressorted(first,middle);
    glibcxxrequiressorted(middle,last);
    if(first==middle || middle==last)
        return;
    DistanceType len1=std::distance(first, middle);
    DistanceType len2=std::distance(middle, last);
    Temporarybuffer<BidirectionalIterator,ValueType> buf(first,last);
    if(buf.begin()==0)
        std::merge_without_buffer(first,middle,last,len1,len2);
    else
        std::merge_adaptive(first,middle,last,len1,len2,
                 buf.begin(),DistanceType(buf.size()));
}
template<typename BidirectionalIterator,typename Distance,
                                        typename Pointer>
void merge_adaptive(BidirectionalIterator first,BidirectionalIterator middle,
                    BidirectionalIterator last,Distance len1,Distance len2,
                                            Pointer buffer,Distance buffersize)
{
    if (len1<=len2 && len1<=buffersize)
    {
       Pointer bufferend=std::copy(first,middle,buffer);
       std::merge(buffer,bufferend,middle,last,first);
    }
    else if (len2 <= buffersize)
    {
       Pointer bufferend=std::copy(middle,last,buffer);
       std::mergebackward(first,middle,buffer,bufferend,last);
    }
    else
    {
        BidirectionalIterator firstcut=first;
        BidirectionalIterator secondcut=middle;
        Distance len11=0;
        Distance len22=0;
        if(len1>len2)
        {
            len11=len1/2;
            std::advance(firstcut, len11);
            secondcut=std::lowerbound(middle, last,*firstcut);
            len22=std::distance(middle, secondcut);
        }
        else
        {
            len22=len2/2;
            std::advance(secondcut,len22);
            firstcut=std::upperbound(first, middle,*secondcut);
            len11=std::distance(first,firstcut);
        }
        BidirectionalIterator newmiddle=
        std::rotateadaptive(firstcut,middle,secondcut,
                   len1-len11,len22,buffer,buffersize);
        std::merge_adaptive(first,firstcut,newmiddle,len11,
                                len22, buffer, buffersize);
        std::merge_adaptive(newmiddle,secondcut,last,
            len1-len11,len2-len22,buffer,buffersize);
    }
}
