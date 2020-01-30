template<typename T, typename Iterator>
auto Line(const T& value, Iterator first, Iterator last){
    for(auto i = first; i != last; i++){
        if(*i == value){
            return i;
        }
    }
    return last;
}

template<typename T, typename Iterator>
auto Iter(const T& value, Iterator first, Iterator last, std::random_access_iterator_tag){
    auto p =  std::lower_bound(first, last, value);
    if(*p == value){
        return p;
    }
    else{
        return last;
    }
}
template<typename T, typename Iterator>
auto Iter(const T& value, Iterator first, Iterator last, std::bidirectional_iterator_tag ){
    return Line(value, first, last);
}
template<typename T, typename Iterator>
auto Iter(const T& value, Iterator first, Iterator last,  std::forward_iterator_tag){
    return Line(value, first, last);
}
template<typename T, typename Iterator>
auto Iter(const T& value, Iterator first, Iterator last, std::input_iterator_tag){
    return Line(value, first, last);
}


template<typename T, typename Iterator>
Iterator Find(const T& value, Iterator first, Iterator last){
    typedef typename std::iterator_traits<Iterator>::iterator_category category;
    Iter(value, first, last, category());
}
