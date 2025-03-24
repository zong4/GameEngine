#pragma once

#include "../src/Events/ApplicationEvent.hpp"
#include "../src/Events/KeyEvent.hpp"
#include "../src/Events/MouseEvent.hpp"
#include "../src/Events/WindowEvent.hpp"
#include "../src/Layer/LayerStack.hpp"
#include "../src/Logger/Logger.hpp"
#include "../src/Time/Timestep.hpp"
#include <algorithm>
#include <array>
#include <condition_variable>
#include <deque>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <future>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <memory>
#include <mutex>
#include <optional>
#include <ranges>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>
#include <tracy/Tracy.hpp>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace Engine {
#define ENGINE_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1) // todo
} // namespace Engine
