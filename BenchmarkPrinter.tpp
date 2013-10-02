/* 
 * File:   BenchmarkPrinter.tpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 26 juillet 2013, 14:47
 */

#include <boost/filesystem.hpp>
#include <boost/algorithm/string/trim.hpp>

template<typename P, typename W>
BenchmarkPrinter<P, W>::BenchmarkPrinter(std::string filenamePattern) : filenamePattern(filenamePattern) {
}

template<typename P, typename W>
std::set<std::string> BenchmarkPrinter<P, W>::getCounterNames() {
    std::set<std::string> names;

    for (times_type::iterator it = times.begin(); it != times.end(); it++) {
        for (vector_counter_map_type::iterator itVector = it->second.begin(); itVector != it->second.end(); itVector++) {
            for (counter_map_type::iterator itCounter = itVector->begin(); itCounter != itVector->end(); itCounter++) {
                names.insert(itCounter->first);
            }
        }
    }

    names.insert("Total");

    return names;
}

template<typename P, typename W>
BenchmarkPrinter<P, W>::~BenchmarkPrinter() {
    using namespace std;
    using namespace boost;
    using namespace boost::filesystem;

    vector<string> sizes;
    transform(times.begin(), times.end(), back_inserter(sizes), bind(StringConverter<uint64_t>(), bind(RetrieveKey<times_type::value_type>(), _1)));

    set<string> counterNames = getCounterNames();

    path p(filenamePattern);
    string extension = p.extension().generic_string();
    string relativePath = p.relative_path().generic_string();

    string filenameBegin = trim_right_copy_if(relativePath, is_any_of(extension));

    for (times_type::iterator itTaille = times.begin(); itTaille != times.end(); itTaille++) {
        uint64_t taille = itTaille->first;
        vector_counter_map_type& vect = itTaille->second;

        stringstream ss;
        ss << filenameBegin << "_" << taille << extension;
        cout << "Ecriture dans " << ss.str() << endl;
        ofstream out(ss.str().c_str(), ofstream::out);

        out << boost::algorithm::join(counterNames, "\t") << endl;
        for (vector_counter_map_type::iterator vectIterator = vect.begin(); vectIterator != vect.end(); vectIterator++) {
            counter_map_type& map = *vectIterator;
            for (set<string>::iterator itCounterName = counterNames.begin(); itCounterName != counterNames.end(); itCounterName++) {
                uint64_t value = 0;
                counter_map_type::iterator valueptr = map.find(*itCounterName);
                if (valueptr != map.end())
                    value = valueptr->second;

                out << value << "\t";
            }

            out << endl;
        }
        out << flush;
        out.close();
    }
}

template<typename P, typename W>
void BenchmarkPrinter<P, W>::notify(const std::string& eventName, Event<P, W>& eventData) {
    using namespace std;

    if (eventName == BaseEvent::OPTIMAL_SOLUTION_FOUND) {
        boost::regex regex("KP(_[[:upper:]]+)+_([[:digit:]]+)_R([[:digit:]]+)_[[:digit:]]+");
        boost::cmatch what;

        if (boost::regex_match(eventData.getInstance()->getName().c_str(), what, regex)) {
            unsigned size = atoi(what[2].first);

            counter_map_type map = eventData.getTimes();

            Counter& counter = eventData.getCounter();
            map[counter.getName()] = counter.getTime();

            times[size].push_back(map);
        }
    }

}