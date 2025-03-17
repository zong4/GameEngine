#pragma once

#include <string>
#include <memory>
#include <functional>
#include <algorithm>
#include <vector>
#include <sstream>
#include <deque>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <array>
#include <utility>
#include <optional>
#include <type_traits>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <thread>
#include <future>
#include <mutex>
#include <stdexcept>
#include <condition_variable>

#include "Core/Logger/Logger.hpp"

#define BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)