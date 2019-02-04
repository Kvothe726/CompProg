// finds longest strictly increasing subsequence when duplicate elements are allowed

vector<int> LIS(const vector<int> &elements) {
    // declare the set with a custom comparison function
    // that compares values instead of indices
    auto compare = [&](int x, int y) {
        return elements[x] < elements[y];
    };
    set< int, decltype(compare) > S(compare);

    // process the elements; for each length
    // maintain the index of the best end so far
    vector<int> previous( elements.size(), -1 );
    for (int i=0; i<int( elements.size() ); ++i) {
        auto it = S.insert(i).first;
        if (it != S.begin())
            previous[i] = *prev(it);
        if (*it == i && next(it) != S.end())
            S.erase(next(it));
    }

    // reconstruct the indices that form
    // one possible optimal answer
    vector<int> answer;
    answer.push_back( *S.rbegin() );
    while ( previous[answer.back()] != -1 )
        answer.push_back( previous[answer.back()] );
    reverse( answer.begin(), answer.end() );
    return answer;
}
