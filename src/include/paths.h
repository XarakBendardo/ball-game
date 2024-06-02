#include <string>
#include <boost/dll/runtime_symbol_info.hpp>

#ifndef PATHS_H
#define PATHS_H

namespace paths
{
    static inline std::string getWorkingDir()
    {
        return boost::dll::program_location().parent_path().string();
    }

    const std::string WORKING_DIR = getWorkingDir();
    const std::string RESOURCES_DIR = WORKING_DIR + "/../resources";
    const std::string FONTS_DIR = RESOURCES_DIR + "/fonts";
    const std::string SOUNDS_DIR = RESOURCES_DIR + "/sounds";
} // namespace paths

#endif