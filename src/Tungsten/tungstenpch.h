//
// Created by Andrew Graser on 11/9/2024.
//


#pragma once

//std
#include <string>
#include <iostream>
#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <unordered_map>
#include <queue>
#include <future>
#include <ostream>
#include <fstream>
#include <set>
#include <utility>

#include <cstdio>

#include "Core/Logger.h"


#define ASSETS_DIR std::string("../../assets/")

//Engine Types
#define TUNGSTEN_BIND_EVENT_FUNC(x) std::bind(&x, this, std::placeholders::_1)
