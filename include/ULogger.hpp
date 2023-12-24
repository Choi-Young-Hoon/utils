#pragma once

#include "logger/ULogger.hpp"
#include "logger/ULoggerIOWriter.hpp"

#define LOG_WRITE_INFO(ioWriter, log) (ioWriter->write(utils::LOG_LEVEL::INFO, log, __FILE__, __LINE__))

#define LOG_WRITE_ERROR(ioWriter, log) (ioWriter->write(utils::LOG_LEVEL::ERROR, log, __FILE__, __LINE__))