
#ifndef PROJECTX_INCLUDES_PROJECTX_HPP_
#define PROJECTX_INCLUDES_PROJECTX_HPP_

#if defined(__unix__)
#include <sys/types.h>
#include <unistd.h>
#endif

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>

#include <algorithm>
#include <any>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <utility>
#include <variant>
#include <vector>

namespace FileSystem = std::filesystem;

#include <boost/compute.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

namespace Options = boost::program_options;

#include <boost/algorithm/algorithm.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/math/distributions.hpp>
#include <boost/math/special_functions.hpp>
#include <boost/math/tr1.hpp>

#include <gmp.h>

#endif // PROJECTX_INCLUDES_PROJECTX_HPP_
