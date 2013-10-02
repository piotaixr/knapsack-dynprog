/* 
 * File:   InstanceException.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 31 mai 2013, 11:57
 */

template<typename P, typename W>
InstanceException<P, W>::InstanceException(const Instance<P, W>& instance) : instance(instance) {
    message = generateMessage(instance);
}

template<typename P, typename W>
InstanceException<P, W>::InstanceException(const Instance<P, W>& instance, const std::string& message) : instance(instance), message(message) {
}

template<typename P, typename W>
InstanceException<P, W>::InstanceException(const InstanceException<P, W>& orig) : instance(orig.getInstance()) {
}

template<typename P, typename W>
InstanceException<P, W>::~InstanceException() throw () {
}

template<typename P, typename W>
std::string InstanceException<P, W>::generateMessage(const Instance<P, W>& instance) {
    return "An error occurs during the resolution of the instance " + instance.getName();
}

template<typename P, typename W>
const char* InstanceException<P, W>::what() const throw () {
    return message.c_str();
}
