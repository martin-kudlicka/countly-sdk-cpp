#ifndef COUNTLY_HPP_
#define COUNTLY_HPP_

#include <string>

#define COUNTLY_SDK_VERSION "0.1.0"

class Countly {
public:
	Countly();

	static Countly& getInstance();

	// Do not implicitly generate the copy constructor, this is a singleton.
	Countly(const Countly&) = delete;

	// Do not implicitly generate the copy assignment operator, this is a singleton.
	void operator=(const Countly&) = delete;

	std::string detectOSName();

	std::string detectOSVersion();

	void setPath(std::string path);
};

#endif
